#include "PASSWORD.h"

//�ڴ�������ʱ,��������е����ݵ��ڴ���
PASSWORD::PASSWORD()
{
	PASSWORD::ErgodicFileAnyInfo();
}

PASSWORD::~PASSWORD()
{
	PASSWORD::DeleteUserDataInfoList();
}

//�൱��ˢ���ڴ��е�����
void PASSWORD::InitData()
{
	PASSWORD::ErgodicFileAnyInfo();
}

BOOL PASSWORD::SaveData(const char *Account, const char *Password, const char *Info)
{
	PASSWORD::Assert((void*)Account);
	PASSWORD::Assert((void*)Password);


	FILE *File = PASSWORD::OpenFile_Write();

	//����˺Ų�����
	if (IsExistence(Account, File) == FALSE)
	{
		Pass_word PW;
		PW.AccoundLenght = strlen(Account);
		PW.DataHeadLenght = sizeof(Pass_word);
		PW.PasswordLenght = strlen(Password);
		if (Info)
		{
			PW.UserInfoLenght = strlen(Info);
		}
		else
		{
			PW.UserInfoLenght = 0;
		}
		fwrite(&PW, PW.DataHeadLenght, 1, File);

		PASSWORD::Encryption(Account);
		PASSWORD::WriteEncryptionInfo(File);
		PASSWORD::Encryption(Password);
		PASSWORD::WriteEncryptionInfo(File);
		PASSWORD::NULL_Encryption(Info);
		PASSWORD::WriteEncryptionInfo(File);

		PASSWORD::OpenFile_End(File);
		return TRUE;
	}
	else//�˺Ŵ���
	{
		printf("�˺�:%s �Ѿ�����,����ʧ��,���Ҫ������Ϣ��������,������������!\n", Account);
	}
	PASSWORD::OpenFile_End(File);
	return FALSE;
}

BOOL PASSWORD::SaveData(UserInfo UserData)
{
	return PASSWORD::SaveData(UserData.Account, UserData.Password, UserData.UserInfo);
}

BOOL PASSWORD::DeleteData(const char *Account, int DEFINE)
{
	PASSWORD::Assert((void*)Account);

	switch (DEFINE)
	{
	case DELETEACCOUNT:
	{
		return PASSWORD::DeleteAccount(Account);
	}; break;
	case DELETEPASSWORD:
	{
		return PASSWORD::DeleteAccountPassword(Account);
	}; break;
	case DELETEINFO:
	{
		return PASSWORD::DeleteAccountInfo(Account);
	}; break;
	}
	return FALSE;
}

void PASSWORD::GetDataPassword(const char *Account, char *PasswordBuf)
{
	PASSWORD::Assert((void*)Account);

	FILE *File = PASSWORD::OpenFile_Read();

	//����˺Ŵ���
	if (IsExistence(Account, File))
	{
		Pass_word PW;
		char EncryptionInfo[256] = { 0 };
		int AccountLen = 0;
		int PasswordLen = 0;
		long Offset = 0;
		char Buf[256] = { 0 };

		while (true)
		{
			ZeroMemory(&PW, sizeof(Pass_word));
			ZeroMemory(EncryptionInfo, sizeof(EncryptionInfo));
			ZeroMemory(&AccountLen, sizeof(int));
			ZeroMemory(&PasswordLen, sizeof(int));
			ZeroMemory(&Offset, sizeof(long));
			ZeroMemory(Buf, sizeof(Buf));

			fread_s(&PW, sizeof(Pass_word), sizeof(Pass_word), 1, File);
			//����ͷ �˺� ����
			if (PW.DataHeadLenght == 0 || PW.AccoundLenght == 0)
			{
				PASSWORD::OpenFile_End(File);
				return;
			}

			//�˺ų���ƥ��
			fread_s(&AccountLen, sizeof(int), sizeof(int), 1, File);
			if (AccountLen != PW.AccoundLenght)
			{
				printf("��������\n");
				PASSWORD::OpenFile_End(File);
				return;
			}
			//���볤��ƥ��
			fseek(File, PW.AccoundLenght, SEEK_CUR);
			fread_s(&PasswordLen, sizeof(int), sizeof(int), 1, File);
			if (PasswordLen != PW.PasswordLenght)
			{
				printf("������������\n");
				PASSWORD::OpenFile_End(File);
				return;
			}

			//�˵��˺���Ϣͷ��ǰ��
			Offset = sizeof(int) + PW.AccoundLenght + sizeof(int);
			fseek(File, -Offset, SEEK_CUR);
			fread_s(EncryptionInfo, sizeof(EncryptionInfo), PW.AccoundLenght + sizeof(int), 1, File);

			//��������
			PASSWORD::Decode(EncryptionInfo, Buf);

			//�˺�ƥ��
			if (PASSWORD::StringCompare(Account, Buf) == TRUE)
			{
				int PasswordLen = 0;
				fread_s(&PasswordLen, sizeof(int), sizeof(int), 1, File);
				if (PasswordLen != PW.PasswordLenght)
				{
					printf("��������\n");
					PASSWORD::OpenFile_End(File);
					return;
				}
				ZeroMemory(EncryptionInfo, sizeof(EncryptionInfo));
				Offset = sizeof(int);
				fseek(File, -Offset, SEEK_CUR);
				fread_s(EncryptionInfo, sizeof(EncryptionInfo), PasswordLen + sizeof(int), 1, File);
				PASSWORD::Decode(EncryptionInfo, PasswordBuf);

				PASSWORD::OpenFile_End(File);
				return;
			}

			//��������˺Ŷ�ȡ��һ���˺�
			int TempVar = sizeof(int) * 2;
			fseek(File, (long)(PW.PasswordLenght + TempVar + PW.UserInfoLenght), SEEK_CUR);
		}
	}
	else
	{
		printf("�˺Ų����ڣ�");
	}

	PASSWORD::OpenFile_End(File);
}

char *PASSWORD::GetDataPassword(const char *Account)
{
	PASSWORD::Assert((void*)Account);

	FILE *File = PASSWORD::OpenFile_Read();

	//����˺Ŵ���
	if (IsExistence(Account, File))
	{
		Pass_word PW;
		char EncryptionInfo[256] = { 0 };
		int AccountLen = 0;
		int PasswordLen = 0;
		long Offset = 0;
		char Buf[256] = { 0 };

		while (true)
		{
			ZeroMemory(&PW, sizeof(Pass_word));
			ZeroMemory(EncryptionInfo, sizeof(EncryptionInfo));
			ZeroMemory(&AccountLen, sizeof(int));
			ZeroMemory(&PasswordLen, sizeof(int));
			ZeroMemory(&Offset, sizeof(long));
			ZeroMemory(Buf, sizeof(Buf));

			fread_s(&PW, sizeof(Pass_word), sizeof(Pass_word), 1, File);
			//����ͷ �˺� ����
			if (PW.DataHeadLenght == 0 || PW.AccoundLenght == 0)
			{
				PASSWORD::OpenFile_End(File);
				return NULL;
			}

			//�˺ų���ƥ��
			fread_s(&AccountLen, sizeof(int), sizeof(int), 1, File);
			if (AccountLen != PW.AccoundLenght)
			{
				printf("��������\n");
				PASSWORD::OpenFile_End(File);
				return NULL;
			}
			//���볤��ƥ��
			fseek(File, PW.AccoundLenght, SEEK_CUR);
			fread_s(&PasswordLen, sizeof(int), sizeof(int), 1, File);
			if (PasswordLen != PW.PasswordLenght)
			{
				printf("������������\n");
				PASSWORD::OpenFile_End(File);
				return NULL;
			}

			//�˵��˺���Ϣͷ��ǰ��
			Offset = sizeof(int) + PW.AccoundLenght + sizeof(int);
			fseek(File, -Offset, SEEK_CUR);
			fread_s(EncryptionInfo, sizeof(EncryptionInfo), PW.AccoundLenght + sizeof(int), 1, File);

			//��������
			PASSWORD::Decode(EncryptionInfo, Buf);

			//�˺�ƥ��
			if (PASSWORD::StringCompare(Account, Buf) == TRUE)
			{
				int PasswordLen = 0;
				fread_s(&PasswordLen, sizeof(int), sizeof(int), 1, File);
				if (PasswordLen != PW.PasswordLenght)
				{
					printf("��������\n");
					PASSWORD::OpenFile_End(File);
					return NULL;
				}
				ZeroMemory(EncryptionInfo, sizeof(EncryptionInfo));
				Offset = sizeof(int);
				fseek(File, -Offset, SEEK_CUR);
				fread_s(EncryptionInfo, sizeof(EncryptionInfo), PasswordLen + sizeof(int), 1, File);
				static char PasswordBuf[256] = { 0 };
				PASSWORD::Decode(EncryptionInfo, PasswordBuf);

				PASSWORD::OpenFile_End(File);
				return PasswordBuf;
			}

			//��������˺Ŷ�ȡ��һ���˺�
			int TempVar = sizeof(int) * 2;
			fseek(File, (long)(PW.PasswordLenght + TempVar + PW.UserInfoLenght), SEEK_CUR);
		}
	}
	else
	{
		printf("�˺Ų����ڣ�\n");
	}

	PASSWORD::OpenFile_End(File);
	return NULL;
}

BOOL PASSWORD::SetDataPassword(const char *Account, const char *Password)
{
	PASSWORD::Assert((void*)Account);
	PASSWORD::Assert((void*)Password);

	FILE *File = PASSWORD::OpenFile_Read();

	//����˺Ŵ���
	if (IsExistence(Account, File))
	{
		for (int i = 0; i < m_UserNum; i++)
		{
			if (PASSWORD::StringCompare(m_DATAINFO[i].Account, Account))
			{
				ZeroMemory(m_DATAINFO[i].Password, sizeof(m_DATAINFO[i].Password));
				int TempLen = 0;
				while (Password[TempLen]) { TempLen++; }
				memcpy_s(m_DATAINFO[i].Password, sizeof(m_DATAINFO[i].Password), Password, TempLen);
				break;
			}
		}
	}
	else
	{
		printf("�˺Ų����ڣ�");
		PASSWORD::OpenFile_End(File);
		return FALSE;
	}

	PASSWORD::OpenFile_End(File);

	//д�뻺���е�����
	PASSWORD::InsertData();
	return TRUE;
}

BOOL PASSWORD::SetDataInfo(const char *Account, const char *Info)
{
	PASSWORD::Assert((void*)Account);
	PASSWORD::Assert((void*)Info);

	FILE *File = PASSWORD::OpenFile_Read();

	//����˺Ŵ���
	if (IsExistence(Account, File))
	{
		for (int i = 0; i < m_UserNum; i++)
		{
			if (PASSWORD::StringCompare(m_DATAINFO[i].Account, Account))
			{
				ZeroMemory(m_DATAINFO[i].UserInfo, sizeof(m_DATAINFO[i].UserInfo));
				int TempLen = 0;
				while (Info[TempLen]) { TempLen++; }
				memcpy_s(m_DATAINFO[i].UserInfo, sizeof(m_DATAINFO[i].UserInfo), Info, TempLen);
				break;
			}
		}
	}
	else
	{
		printf("�˺Ų����ڣ�\n");
		PASSWORD::OpenFile_End(File);
		return FALSE;
	}

	PASSWORD::OpenFile_End(File);

	//д�뻺���е�����
	PASSWORD::InsertData();
	return TRUE;
}

void PASSWORD::GetDataInfo(const char *Account, char *DataInfoBuf)
{
	PASSWORD::Assert((void*)Account);

	FILE *File = PASSWORD::OpenFile_Read();

	//����˺Ŵ���
	if (IsExistence(Account, File))
	{
		Pass_word PW;
		char EncryptionInfo[256] = { 0 };
		int AccountLen = 0;
		int PasswordLen = 0;
		long Offset = 0;
		char Buf[256] = { 0 };

		while (true)
		{
			ZeroMemory(&PW, sizeof(Pass_word));
			ZeroMemory(EncryptionInfo, sizeof(EncryptionInfo));
			ZeroMemory(&AccountLen, sizeof(int));
			ZeroMemory(&PasswordLen, sizeof(int));
			ZeroMemory(&Offset, sizeof(long));
			ZeroMemory(Buf, sizeof(Buf));

			fread_s(&PW, sizeof(Pass_word), sizeof(Pass_word), 1, File);
			//����ͷ �˺� ����
			if (PW.DataHeadLenght == 0 || PW.AccoundLenght == 0)
			{
				PASSWORD::OpenFile_End(File);
				return;
			}

			//�˺ų���ƥ��
			fread_s(&AccountLen, sizeof(int), sizeof(int), 1, File);
			if (AccountLen != PW.AccoundLenght)
			{
				printf("��������\n");
				PASSWORD::OpenFile_End(File);
				return;
			}
			//���볤��ƥ��
			fseek(File, PW.AccoundLenght, SEEK_CUR);
			fread_s(&PasswordLen, sizeof(int), sizeof(int), 1, File);
			if (PasswordLen != PW.PasswordLenght)
			{
				printf("������������\n");
				PASSWORD::OpenFile_End(File);
				return;
			}

			//�˵��˺���Ϣͷ��ǰ��
			Offset = sizeof(int) + PW.AccoundLenght + sizeof(int);
			fseek(File, -Offset, SEEK_CUR);
			fread_s(EncryptionInfo, sizeof(EncryptionInfo), PW.AccoundLenght + sizeof(int), 1, File);

			//��������
			PASSWORD::Decode(EncryptionInfo, Buf);

			//�˺�ƥ��
			if (PASSWORD::StringCompare(Account, Buf) == TRUE)
			{
				int PasswordLen = 0;
				fread_s(&PasswordLen, sizeof(int), sizeof(int), 1, File);
				if (PasswordLen != PW.PasswordLenght)
				{
					printf("��������\n");
					PASSWORD::OpenFile_End(File);
					return;
				}
				ZeroMemory(EncryptionInfo, sizeof(EncryptionInfo));
				fseek(File, PW.PasswordLenght, SEEK_CUR);
				int DataInfoLen = 0;
				fread_s(&DataInfoLen, sizeof(DataInfoLen), sizeof(int), 1, File);
				if (DataInfoLen != PW.UserInfoLenght)
				{
					printf("��������\n");
					PASSWORD::OpenFile_End(File);
					return;
				}
				Offset = sizeof(int);
				fseek(File, -Offset, SEEK_CUR);
				fread_s(&EncryptionInfo, sizeof(EncryptionInfo), (size_t)(PW.UserInfoLenght + (long long)sizeof(int)), 1, File);
				PASSWORD::Decode(EncryptionInfo, DataInfoBuf);

				PASSWORD::OpenFile_End(File);
				return;
			}

			//��������˺Ŷ�ȡ��һ���˺�
			int TempVar = sizeof(int) * 2;
			fseek(File, (long)(PW.PasswordLenght + TempVar + PW.UserInfoLenght), SEEK_CUR);
		}
	}
	else
	{
		printf("�˺Ų����ڣ�");
	}

	PASSWORD::OpenFile_End(File);
}

char *PASSWORD::GetDataInfo(const char *Account)
{
	PASSWORD::Assert((void*)Account);

	FILE *File = PASSWORD::OpenFile_Read();

	//����˺Ŵ���
	if (IsExistence(Account, File))
	{
		Pass_word PW;
		char EncryptionInfo[256] = { 0 };
		int AccountLen = 0;
		int PasswordLen = 0;
		long Offset = 0;
		char Buf[256] = { 0 };

		while (true)
		{
			ZeroMemory(&PW, sizeof(Pass_word));
			ZeroMemory(EncryptionInfo, sizeof(EncryptionInfo));
			ZeroMemory(&AccountLen, sizeof(int));
			ZeroMemory(&PasswordLen, sizeof(int));
			ZeroMemory(&Offset, sizeof(long));
			ZeroMemory(Buf, sizeof(Buf));

			fread_s(&PW, sizeof(Pass_word), sizeof(Pass_word), 1, File);
			//����ͷ �˺� ����
			if (PW.DataHeadLenght == 0 || PW.AccoundLenght == 0)
			{
				PASSWORD::OpenFile_End(File);
				return NULL;
			}

			//�˺ų���ƥ��
			fread_s(&AccountLen, sizeof(int), sizeof(int), 1, File);
			if (AccountLen != PW.AccoundLenght)
			{
				printf("��������\n");
				PASSWORD::OpenFile_End(File);
				return NULL;
			}
			//���볤��ƥ��
			fseek(File, PW.AccoundLenght, SEEK_CUR);
			fread_s(&PasswordLen, sizeof(int), sizeof(int), 1, File);
			if (PasswordLen != PW.PasswordLenght)
			{
				printf("������������\n");
				PASSWORD::OpenFile_End(File);
				return NULL;
			}

			//�˵��˺���Ϣͷ��ǰ��
			Offset = sizeof(int) + PW.AccoundLenght + sizeof(int);
			fseek(File, -Offset, SEEK_CUR);
			fread_s(EncryptionInfo, sizeof(EncryptionInfo), PW.AccoundLenght + sizeof(int), 1, File);

			//��������
			PASSWORD::Decode(EncryptionInfo, Buf);

			//�˺�ƥ��
			if (PASSWORD::StringCompare(Account, Buf) == TRUE)
			{
				int PasswordLen = 0;
				fread_s(&PasswordLen, sizeof(int), sizeof(int), 1, File);
				if (PasswordLen != PW.PasswordLenght)
				{
					printf("��������\n");
					PASSWORD::OpenFile_End(File);
					return NULL;
				}
				ZeroMemory(EncryptionInfo, sizeof(EncryptionInfo));
				fseek(File, PW.PasswordLenght, SEEK_CUR);
				int DataInfoLen = 0;
				fread_s(&DataInfoLen, sizeof(DataInfoLen), sizeof(int), 1, File);
				if (DataInfoLen != PW.UserInfoLenght)
				{
					printf("��������\n");
					PASSWORD::OpenFile_End(File);
					return NULL;
				}
				Offset = sizeof(int);
				fseek(File, -Offset, SEEK_CUR);
				fread_s(&EncryptionInfo, sizeof(EncryptionInfo), (size_t)(PW.UserInfoLenght + (long long)sizeof(int)), 1, File);

				static char DataInfoBuf[256] = { 0 };
				PASSWORD::Decode(EncryptionInfo, DataInfoBuf);

				PASSWORD::OpenFile_End(File);
				return DataInfoBuf;
			}

			//��������˺Ŷ�ȡ��һ���˺�
			int TempVar = sizeof(int) * 2;
			fseek(File, (long)(PW.PasswordLenght + TempVar + PW.UserInfoLenght), SEEK_CUR);
		}
	}
	else
	{
		printf("�˺Ų����ڣ�");
	}

	PASSWORD::OpenFile_End(File);
	return NULL;
}

BOOL PASSWORD::SetDataAccount(const char *Account, const char *Accounts)
{
	PASSWORD::Assert((void*)Account);
	PASSWORD::Assert((void*)Accounts);

	FILE *File = PASSWORD::OpenFile_Read();

	//����˺Ŵ���
	if (IsExistence(Account, File))
	{
		for (int i = 0; i < m_UserNum; i++)
		{
			if (PASSWORD::StringCompare(m_DATAINFO[i].Account, Account))
			{
				ZeroMemory(m_DATAINFO[i].Account, sizeof(m_DATAINFO[i].Account));
				int TempLen = 0;
				while (Accounts[TempLen]) { TempLen++; }
				memcpy_s(m_DATAINFO[i].Account, sizeof(m_DATAINFO[i].Account), Accounts, TempLen);
				break;
			}
		}
	}
	else
	{
		printf("�˺Ų����ڣ�\n");
		PASSWORD::OpenFile_End(File);
		return FALSE;
	}

	PASSWORD::OpenFile_End(File);

	//д�뻺���е�����
	PASSWORD::InsertData();
	return TRUE;
}

//ɾ���û���Ϣ�б�
void PASSWORD::DeleteUserDataInfoList()
{
	if (m_DATAINFO)
	{
		delete[] m_DATAINFO;
		m_DATAINFO = NULL;
	}
}

//��������
void PASSWORD::Encryption(const char *AnyInfo)
{
	PASSWORD::Assert((void*)AnyInfo);

	//���ݵĳ�
	int TempLen = strlen(AnyInfo);

	//ǰ�ĸ��ֽ�Ϊ���ݵĳ�
	*((int*)m_EncryptionInfo) = TempLen;
	for (int i = 0; i < TempLen; i++)
	{
		m_EncryptionInfo[i + sizeof(int)] = AnyInfo[i] + 1;
	}
}
//��������
void PASSWORD::Decode(char *EncryptionInfo, char *Buf)
{
	PASSWORD::Assert((void*)EncryptionInfo);
	PASSWORD::Assert((void*)Buf);

	int TempLen = *((int*)EncryptionInfo);
	for (int i = 0; i < TempLen; i++)
	{
		Buf[i] = EncryptionInfo[i + sizeof(int)] - 1;
	}
}

//�˺��Ƿ����
BOOL PASSWORD::IsExistence(const char *Account, FILE *File)
{
	PASSWORD::Assert((void*)Account);
	PASSWORD::Assert((void*)File);


	if (File)
	{
		Pass_word P_W;
		char EncryptionInfo[256] = { 0 };
		int AccountLen = 0;
		int PasswordLen = 0;
		long Offset = 0;
		char Buf[256] = { 0 };

		while (true)
		{
			ZeroMemory(&P_W, sizeof(Pass_word));
			ZeroMemory(EncryptionInfo, sizeof(EncryptionInfo));
			ZeroMemory(&AccountLen, sizeof(int));
			ZeroMemory(&PasswordLen, sizeof(int));
			ZeroMemory(&Offset, sizeof(long));
			ZeroMemory(Buf, sizeof(Buf));

			fread_s(&P_W, sizeof(Pass_word), sizeof(Pass_word), 1, File);
			//����ͷ �˺�
			if (P_W.DataHeadLenght == 0 || P_W.AccoundLenght == 0)
			{
				return FALSE;
			}
			//�˺ų���ƥ��
			fread_s(&AccountLen, sizeof(int), sizeof(int), 1, File);
			if (AccountLen != P_W.AccoundLenght)
			{
				printf("�˺���������\n");
				return FALSE;
			}
			//���볤��ƥ��
			fseek(File, P_W.AccoundLenght, SEEK_CUR);
			fread_s(&PasswordLen, sizeof(int), sizeof(int), 1, File);
			if (PasswordLen != P_W.PasswordLenght)
			{
				printf("������������\n");
				return FALSE;
			}

			//�˵��˺���Ϣͷ��ǰ��
			Offset = sizeof(int) + P_W.AccoundLenght + sizeof(int);
			fseek(File, -Offset, SEEK_CUR);
			fread_s(EncryptionInfo, sizeof(EncryptionInfo), P_W.AccoundLenght + sizeof(int), 1, File);

			//�����˺�����
			PASSWORD::Decode(EncryptionInfo, Buf);
			//��������˺�
			if (PASSWORD::StringCompare(Account, Buf) == TRUE)
			{
				rewind(File);
				return TRUE;
			}
			//��������˺Ŷ�ȡ��һ���˺�
			int TempVar = sizeof(int) * 2;
			fseek(File, (long)(P_W.PasswordLenght + TempVar + P_W.UserInfoLenght), SEEK_CUR);
		}
	}
	return FALSE;
}


//ɾ��ĳ���˺ŵ�������Ϣ
BOOL PASSWORD::DeleteAccount(const char *Account)
{
	PASSWORD::Assert((void*)Account);

	if (m_UserNum == 0)
	{
		printf("��ǰһ���˺Ŷ�û�У�\n");
		return FALSE;
	}

	PASSWORD::InitData();

	FILE *File = PASSWORD::OpenFile_Read();

	//����˺Ŵ���
	if (IsExistence(Account, File))
	{
		if (m_UserNum >= 2)
		{
			for (int i = 0; i < m_UserNum; i++)
			{
				if (PASSWORD::StringCompare(m_DATAINFO[i].Account, Account))
				{
					if (i == 0)//ɾ����һ��
					{
						for (int j = 0; j < m_UserNum - 1; j++)
						{
							memcpy_s(&(m_DATAINFO[j]), sizeof(USERINFO), &(m_DATAINFO[j + 1]), sizeof(USERINFO));
						}
						break;
					}
					else if (i == m_UserNum - 1)//ɾ�������һ��
					{
						memset(&(m_DATAINFO[i]), 0, sizeof(USERINFO));
						break;
					}
					else//ɾ���м���һ��
					{
						for (int j = i; j < m_UserNum - 1; j++)
						{
							memcpy_s(&(m_DATAINFO[j]), sizeof(USERINFO), &(m_DATAINFO[j + 1]), sizeof(USERINFO));
						}
						memset(&(m_DATAINFO[m_UserNum - 1]), 0, sizeof(USERINFO));
						break;
					}
				}
			}
		}
	}
	else
	{
		printf("�˺Ų����ڣ�\n");
		PASSWORD::OpenFile_End(File);
		return FALSE;
	}

	PASSWORD::OpenFile_End(File);

	PASSWORD::ClearFileContent();
	File = PASSWORD::OpenFile_Write();

	m_UserNum -= 1;
	if (m_UserNum == 0)//�պ�ɾ������ֻ��һ���˺�
	{
		PASSWORD::OpenFile_End(File);
		PASSWORD::DeleteUserDataInfoList();
		return TRUE;
	}

	for (int i = 0; i < m_UserNum; i++)
	{
		Pass_word PW;
		PW.AccoundLenght = strlen(m_DATAINFO[i].Account);
		PW.DataHeadLenght = sizeof(Pass_word);
		PW.PasswordLenght = strlen(m_DATAINFO[i].Password);
		PW.UserInfoLenght = strlen(m_DATAINFO[i].UserInfo);
		fwrite(&PW, PW.DataHeadLenght, 1, File);

		PASSWORD::Encryption(m_DATAINFO[i].Account);
		PASSWORD::WriteEncryptionInfo(File);
		PASSWORD::Encryption(m_DATAINFO[i].Password);
		PASSWORD::WriteEncryptionInfo(File);
		PASSWORD::NULL_Encryption(m_DATAINFO[i].UserInfo);
		PASSWORD::WriteEncryptionInfo(File);
	}

	PASSWORD::OpenFile_End(File);

	PASSWORD::DeleteUserDataInfoList();
	PASSWORD::InitData();
	return TRUE;
}
//ɾ��ĳ�˺ŵ�����
BOOL PASSWORD::DeleteAccountPassword(const char *Account)
{
	PASSWORD::Assert((void*)Account);

	if (m_UserNum == 0)
	{
		printf("��ǰһ���˺Ŷ�û�У�\n");
		return FALSE;
	}

	PASSWORD::InitData();

	FILE *File = PASSWORD::OpenFile_Read();

	//����˺Ŵ���
	if (IsExistence(Account, File))
	{
		for (int i = 0; i < m_UserNum; i++)
		{
			if (PASSWORD::StringCompare(m_DATAINFO[i].Account, Account))
			{
				memset(m_DATAINFO[i].Password, 0, sizeof(m_DATAINFO[i].Password));
				break;
			}
		}
	}
	else
	{
		printf("�˺Ų����ڣ�\n");
		PASSWORD::OpenFile_End(File);
		return FALSE;
	}

	PASSWORD::OpenFile_End(File);

	PASSWORD::ClearFileContent();
	File = PASSWORD::OpenFile_Write();

	for (int i = 0; i < m_UserNum; i++)
	{
		Pass_word PW;
		PW.AccoundLenght = strlen(m_DATAINFO[i].Account);
		PW.DataHeadLenght = sizeof(Pass_word);
		PW.PasswordLenght = strlen(m_DATAINFO[i].Password);
		PW.UserInfoLenght = strlen(m_DATAINFO[i].UserInfo);
		fwrite(&PW, PW.DataHeadLenght, 1, File);

		PASSWORD::Encryption(m_DATAINFO[i].Account);
		PASSWORD::WriteEncryptionInfo(File);
		PASSWORD::Encryption(m_DATAINFO[i].Password);
		PASSWORD::WriteEncryptionInfo(File);
		PASSWORD::NULL_Encryption(m_DATAINFO[i].UserInfo);
		PASSWORD::WriteEncryptionInfo(File);
	}

	PASSWORD::OpenFile_End(File);

	PASSWORD::DeleteUserDataInfoList();
	PASSWORD::InitData();
	return TRUE;
}
//ɾ��ĳ�˺ŵ���Ϣ
BOOL PASSWORD::DeleteAccountInfo(const char *Account)
{
	PASSWORD::Assert((void*)Account);

	if (m_UserNum == 0)
	{
		printf("��ǰһ���˺Ŷ�û�У�\n");
		return FALSE;
	}

	PASSWORD::InitData();

	FILE *File = PASSWORD::OpenFile_Read();

	//����˺Ŵ���
	if (IsExistence(Account, File))
	{
		for (int i = 0; i < m_UserNum; i++)
		{
			if (PASSWORD::StringCompare(m_DATAINFO[i].Account, Account))
			{
				memset(m_DATAINFO[i].UserInfo, 0, sizeof(m_DATAINFO[i].UserInfo));
				break;
			}
		}
	}
	else
	{
		printf("�˺Ų����ڣ�\n");
		PASSWORD::OpenFile_End(File);
		return FALSE;
	}

	PASSWORD::OpenFile_End(File);

	PASSWORD::ClearFileContent();
	File = PASSWORD::OpenFile_Write();

	for (int i = 0; i < m_UserNum; i++)
	{
		Pass_word PW;
		PW.AccoundLenght = strlen(m_DATAINFO[i].Account);
		PW.DataHeadLenght = sizeof(Pass_word);
		PW.PasswordLenght = strlen(m_DATAINFO[i].Password);
		PW.UserInfoLenght = strlen(m_DATAINFO[i].UserInfo);
		fwrite(&PW, PW.DataHeadLenght, 1, File);

		PASSWORD::Encryption(m_DATAINFO[i].Account);
		PASSWORD::WriteEncryptionInfo(File);
		PASSWORD::Encryption(m_DATAINFO[i].Password);
		PASSWORD::WriteEncryptionInfo(File);
		PASSWORD::NULL_Encryption(m_DATAINFO[i].UserInfo);
		PASSWORD::WriteEncryptionInfo(File);
	}

	PASSWORD::OpenFile_End(File);

	PASSWORD::DeleteUserDataInfoList();
	PASSWORD::InitData();
	return TRUE;
}

//�����ļ�������Ϣ
void PASSWORD::ErgodicFileAnyInfo()
{
	FILE *File = PASSWORD::OpenFile_Read();

	if (File)
	{
		Pass_word P_W;
		char EncryptionInfo[256] = { 0 };
		int AccountLen = 0;
		int PasswordLen = 0;
		long Offset = 0;
		char Account[256] = { 0 };
		char Password[256] = { 0 };
		char UserInfo[1024] = { 0 };

		int UserNum = 0;

		while (true)
		{
			ZeroMemory(&P_W, sizeof(Pass_word));
			ZeroMemory(&AccountLen, sizeof(int));
			ZeroMemory(&PasswordLen, sizeof(int));

			fread_s(&P_W, sizeof(Pass_word), sizeof(Pass_word), 1, File);
			//����ͷ �˺� ����
			if (P_W.DataHeadLenght == 0 || P_W.AccoundLenght == 0)
			{
				rewind(File);
				break;
			}
			//�˺ų���ƥ��
			fread_s(&AccountLen, sizeof(int), sizeof(int), 1, File);
			if (AccountLen != P_W.AccoundLenght)
			{
				printf("�˺���������\n");
				PASSWORD::OpenFile_End(File);
				return;
			}
			//���볤��ƥ��
			fseek(File, P_W.AccoundLenght, SEEK_CUR);
			fread_s(&PasswordLen, sizeof(int), sizeof(int), 1, File);
			if (PasswordLen != P_W.PasswordLenght)
			{
				printf("������������\n");
				PASSWORD::OpenFile_End(File);
				return;
			}
			//������һ���˺�
			fseek(File, P_W.PasswordLenght + (long)(P_W.UserInfoLenght + (long long)sizeof(int)), SEEK_CUR);
			UserNum++;
		}
		m_UserNum = UserNum;

		if (m_UserNum == 0)
		{
			printf("��ǰû���˺ţ�\n");
			return;
		}

		printf("��ǰ�˺��� %d\n", UserNum);

		PASSWORD::DeleteUserDataInfoList();
		m_DATAINFO = new USERINFO[UserNum];

		int i = 0;
		while (true)
		{
			ZeroMemory(&P_W, sizeof(Pass_word));
			ZeroMemory(EncryptionInfo, sizeof(EncryptionInfo));
			ZeroMemory(&AccountLen, sizeof(int));
			ZeroMemory(&PasswordLen, sizeof(int));
			ZeroMemory(&Offset, sizeof(long));
			ZeroMemory(Account, sizeof(Account));
			ZeroMemory(Password, sizeof(Password));
			ZeroMemory(UserInfo, sizeof(UserInfo));

			fread_s(&P_W, sizeof(Pass_word), sizeof(Pass_word), 1, File);
			//����ͷ �˺�
			if (P_W.DataHeadLenght == 0 || P_W.AccoundLenght == 0)
			{
				break;
			}
			//�˺ų���ƥ��
			fread_s(&AccountLen, sizeof(int), sizeof(int), 1, File);
			if (AccountLen != P_W.AccoundLenght)
			{
				printf("�˺���������\n");
				PASSWORD::OpenFile_End(File);
				return;
			}
			//���볤��ƥ��
			fseek(File, P_W.AccoundLenght, SEEK_CUR);
			fread_s(&PasswordLen, sizeof(int), sizeof(int), 1, File);
			if (PasswordLen != P_W.PasswordLenght)
			{
				printf("������������\n");
				PASSWORD::OpenFile_End(File);
				return;
			}

			//�˵��˺���Ϣͷ��ǰ���ȡ�˺���Ϣ��������Ϣ���û���Ϣ
			Offset = sizeof(int) + P_W.AccoundLenght + sizeof(int);
			fseek(File, -Offset, SEEK_CUR);

			fread_s(EncryptionInfo, sizeof(EncryptionInfo), P_W.AccoundLenght + (long long)sizeof(int), 1, File);
			//�����˺�����
			PASSWORD::Decode(EncryptionInfo, Account);

			fread_s(EncryptionInfo, sizeof(EncryptionInfo), P_W.PasswordLenght + (long long)sizeof(int), 1, File);
			//����������Ϣ
			PASSWORD::Decode(EncryptionInfo, Password);

			fread_s(EncryptionInfo, sizeof(EncryptionInfo), (size_t)(P_W.UserInfoLenght + (long long)sizeof(int)), 1, File);
			//�����û���Ϣ
			PASSWORD::Decode(EncryptionInfo, UserInfo);

			memcpy_s(m_DATAINFO[i].Account, sizeof(m_DATAINFO[i].Account), Account, sizeof(Account));
			memcpy_s(m_DATAINFO[i].Password, sizeof(m_DATAINFO[i].Password), Password, sizeof(Password));
			memcpy_s(m_DATAINFO[i].UserInfo, sizeof(m_DATAINFO[i].UserInfo), UserInfo, sizeof(UserInfo));
			i++;
		}

		system("cls");
		for (int j = 0; j < UserNum; j++)
		{
			//printf("Account : %s\nPassword : %s\nUserInfo : %s\n", m_DATAINFO[j].Account, m_DATAINFO[j].Password, m_DATAINFO[j].UserInfo);
			printf("Account : %s\n", m_DATAINFO[j].Account);
		}
	}

	PASSWORD::OpenFile_End(File);
}

//����Ϣ����
//��ϢΪ��,���Ǵ�����Ϣͷ���ĸ��ֽ�
BOOL PASSWORD::NULL_Encryption(const char *Info)
{
	if (Info == NULL)
	{
		//ǰ�ĸ��ֽ�Ϊ���ݵĳ�
		*((int*)m_EncryptionInfo) = 0;
		return FALSE;
	}
	PASSWORD::Encryption(Info);
	return TRUE;
}

//д�뻺���е�����
void PASSWORD::InsertData(FILE *File)
{
	for (int i = 0; i < m_UserNum; i++)
	{
		Pass_word PW;
		PW.AccoundLenght = strlen(m_DATAINFO[i].Account);
		PW.DataHeadLenght = sizeof(Pass_word);
		PW.PasswordLenght = strlen(m_DATAINFO[i].Password);
		PW.UserInfoLenght = strlen(m_DATAINFO[i].UserInfo);
		fwrite(&PW, PW.DataHeadLenght, 1, File);

		PASSWORD::Encryption(m_DATAINFO[i].Account);
		PASSWORD::WriteEncryptionInfo(File);
		PASSWORD::Encryption(m_DATAINFO[i].Password);
		PASSWORD::WriteEncryptionInfo(File);
		PASSWORD::NULL_Encryption(m_DATAINFO[i].UserInfo);
		PASSWORD::WriteEncryptionInfo(File);
	}
}

void PASSWORD::InsertData()
{
	PASSWORD::ClearFileContent();

	FILE *File = PASSWORD::OpenFile_Write();

	PASSWORD::InsertData(File);

	PASSWORD::OpenFile_End(File);
}

//д���������
void PASSWORD::WriteEncryptionInfo(FILE *File)
{
	//�������ݼ���Ϣͷ
	size_t Fwrite = fwrite(m_EncryptionInfo, sizeof(int) + *((int*)m_EncryptionInfo), 1, File);

	PASSWORD::DeleteMemory();
}

//�ַ����Ƚ� ��ͬ����TRUE
BOOL PASSWORD::StringCompare(const char *Str_1, const char *Str_2)
{
	PASSWORD::Assert((void*)Str_1);
	PASSWORD::Assert((void*)Str_2);

	int Str_1_Len = strlen(Str_1);
	int Str_2_Len = strlen(Str_2);

	if (Str_1_Len < Str_2_Len)
	{
		Str_1_Len = Str_2_Len;
	}

	int i = 0;
	while (true)
	{
		if (Str_1_Len == i)
		{
			return TRUE;
		}
		if (Str_1[i] != Str_2[i])
		{
			return FALSE;
		}
		i++;
	}
	return TRUE;
}

//����ļ�����
void PASSWORD::ClearFileContent()
{
	PASSWORD::Clear(m_FileName);
}

//׷�ӵķ�ʽ��
FILE *PASSWORD::OpenFile_Write()
{
	FILE *File = NULL;
	fopen_s(&File, m_FileName, "ab+");
	if (File)
	{
		return File;
	}
	return NULL;
}
//�Զ�����ģʽ��
FILE *PASSWORD::OpenFile_Read()
{
	FILE *File = NULL;
	fopen_s(&File, m_FileName, "rb+");
	if (File)
	{
		return File;
	}
	return NULL;
}

//���ļ�����
void PASSWORD::OpenFile_End(FILE *File)
{
	if (File)
	{
		fclose(File);
		File = NULL;
	}
}

void PASSWORD::Clear(const char *FileName)
{
	PASSWORD::Assert((void*)FileName);

	FILE *File = NULL;
	fopen_s(&File, FileName, "w+");
	if (File)
	{
		PASSWORD::OpenFile_End(File);
	}
}

void PASSWORD::Assert(void *Pointer)
{
	assert(Pointer);
}

void PASSWORD::DeleteMemory()
{
	ZeroMemory(m_EncryptionInfo, sizeof(m_EncryptionInfo));
}







//=================================================

PASSENGINE::PASSENGINE()
{
	PASSENGINE::Get_Password();
}
PASSENGINE::~PASSENGINE()
{
	delete m_PW;
	m_PW = NULL;
}
bool PASSENGINE::EnterPassword()
{
	system("cls");
	std::cout << "����Password��";
	std::cin >> m_Password;

	if (strcmp(m_Password, _Pass_word) != 0)
	{
		m_ImportPasswordOk = false;
		return false;
	}
	m_ImportPasswordOk = true;
	return true;
}
void PASSENGINE::Get_Password()
{
	FILE *File = NULL;
	fopen_s(&File, FileName, "rb+");
	if (File)
	{
		int PasswordLen = 0;
		fread_s(&PasswordLen,sizeof(PasswordLen),sizeof(int),1,File);
		if (PasswordLen == 0)
		{
			system("cls");
			printf("δ������������,����������������ã�\n");

			PASSENGINE::Set_Password(File);
		}
		else
		{
			ZeroMemory(_Pass_word, sizeof(_Pass_word));
			ZeroMemory(m_EncryptionInfo, sizeof(m_EncryptionInfo));
			rewind(File);
			fread_s(m_EncryptionInfo, sizeof(m_EncryptionInfo), PasswordLen + sizeof(int), 1, File);

			int TempLen = *((int*)m_EncryptionInfo);
			for (int i = 0; i < TempLen; i++)
			{
				_Pass_word[i] = m_EncryptionInfo[i + sizeof(int)] - 1;
			}
		}
	}

	fclose(File);
	File = NULL;
}
void PASSENGINE::Set_Password(FILE *File)
{
	ZeroMemory(_Pass_word, sizeof(_Pass_word));
	ZeroMemory(m_EncryptionInfo, sizeof(m_EncryptionInfo));
	do
	{
		printf("���������õ����룺");
		std::cin >> _Pass_word;
		char Buf[256] = { 0 };
		printf("�ٴ�ȷ�ϵ����룺");
		std::cin >> Buf;
		if (strcmp(_Pass_word, Buf) == 0)
		{
			break;
		}
		printf("���벻һ��,���������룡");
		system("cls");
	} while (true);
	rewind(File);
	//���ݵĳ�
	int TempLen = strlen(_Pass_word);
	//ǰ�ĸ��ֽ�Ϊ���ݵĳ�
	*((int*)m_EncryptionInfo) = TempLen;
	for (int i = 0; i < TempLen; i++)
	{
		m_EncryptionInfo[i + sizeof(int)] = _Pass_word[i] + 1;
	}
	fwrite(m_EncryptionInfo, sizeof(int) + *((int*)m_EncryptionInfo), 1, File);
	printf("��������ɹ�,�벻Ҫ������Ŷ��\n");
	Sleep(500);
	system("cls");
}

void PASSENGINE::Run()
{
	PASSENGINE::EnterPassword();
	while (true)
	{
		if (m_ImportPasswordOk)
		{
			if (m_PassOk == false)//ֻ��ʾһ��
			{
				std::cout << "������ȷ" << std::endl;
				Sleep(500);
			}
			system("cls");
			PASSENGINE::_Password();
		}
		else
		{
			std::cout << "���벻��ȷ�����������룡" << std::endl;
			Sleep(300);
			system("cls");
			PASSENGINE::EnterPassword();
		}
	}
}
void PASSENGINE::_Password()
{
	m_PassOk = true;
	for (int i = 0; i < m_PW->GetUserNum(); i++)
	{
		printf("�˺�:%s ��ȡ��Ϣ��%d���!\n", m_PW->GetDATAINFO()[i].Account, i + 1);
	}
	PASSENGINE::_Print();
	std::cin >> m_Code;
	PASSENGINE::_SwitchCode(m_Code);
}
void PASSENGINE::_Print()
{

	std::cout << "�ս�֧������,Bank������Ϣ��5000�����ļ��������ֱ����ʾ" << std::endl;
	std::cout << "                                          " << std::endl;
	std::cout << "9527(����һ���˺�)/9528(ɾ��һ���˺�)" << std::endl;
	std::cout << "9529(����һ���˺ŵ��˺�)/9530(����һ���˺ŵ�����)/9531(����һ���˺ŵ���Ϣ)" << std::endl;
	std::cout << "88888888(��������ļ����������⣡��Ǹ��)666(ˢ������)" << std::endl;
	std::cout << "                                          " << std::endl;
	std::cout << "5176 / 0(�˳�)������������в�����";
}
void PASSENGINE::_SwitchCode(int Code)
{
	if (Code != 0 && Code != 5000 && Code != 5176 && Code != 88888888 && Code != 666
		&& Code != 9527 && Code != 9528 && Code != 9529 && Code != 9530 && Code != 9531)
	{
		if (Code <= m_PW->GetUserNum())
		{
			system("cls");
			printf("\n");
			printf("------------------------------------------------------------------------------------------\n");
			printf("�˺ţ�<%s>   ����Ϣ����!\n����Ϊ��<%s>\n�˺ŵ���ϢΪ��<%s>\n",
				m_PW->GetDATAINFO()[Code - 1].Account,
				m_PW->GetDATAINFO()[Code - 1].Password,
				m_PW->GetDATAINFO()[Code - 1].UserInfo);
			printf("------------------------------------------------------------------------------------------\n");
			printf("\n");
			system("pause");
			system("cls");
		}
		else
		{
			printf("\n");
			printf("------------------------------------------------------------------------------------------\n");
			printf("��û����� ----->>>Code <<<-----  ��\n");
			printf("------------------------------------------------------------------------------------------\n");
			printf("\n");
			system("pause");
			system("cls");
		}
	}
	switch (Code)
	{
	case 0: {exit(0); }; break;
	case 5000: 
	{		
		system("cls");
		printf("    926498    \n    ����ɹ���");
		Sleep(2000);
	}; break;
	case 5176: {exit(0); }; break;
	case 88888888: {/*m_PW->ClearFileContent(); */}; break;
	case 666: {m_PW->InitData(); }; break;
	case 9527: {PASSENGINE::_SaveAccount(); }; break;
	case 9528: {PASSENGINE::_DeleteAccount(); }; break;
	case 9529: {PASSENGINE::_ChangeAccount(); }; break;
	case 9530: {PASSENGINE::_ChangePassword(); }; break;
	case 9531: {PASSENGINE::_ChangeUserInfo(); }; break;
	}
}
void PASSENGINE::_SaveAccount()
{
	UserInfo UserData;
	printf("�������Account��");
	std::cin >> UserData.Account;
	printf("�������Password��");
	std::cin >> UserData.Password;
	printf("�������AccountInfo��");
	std::cin >> UserData.UserInfo;
	if (m_PW->SaveData(UserData))
	{
		printf("����ɹ���\n");
		Sleep(300);
	}
	m_Code = 666;
}
void PASSENGINE::_DeleteAccount()
{
	char Account[256] = { 0 };
	printf("�������Account��");
	std::cin >> Account;
	if(m_PW->DeleteData(Account, DELETEACCOUNT))
	{
		printf("ɾ���ɹ���\n");
		Sleep(300);
	}
}
void PASSENGINE::_ChangeAccount()
{
	char Account[256] = { 0 };
	char Buf[256] = { 0 };
	printf("�������Account��");
	std::cin >> Account;
	printf("�������Account���˺ŵ����֣�");
	std::cin >> Buf;
	if(m_PW->SetDataAccount(Account, Buf))
	{
		printf("���ĳɹ���\n");
		Sleep(300);
	}
}
void PASSENGINE::_ChangePassword()
{
	char Account[256] = { 0 };
	char Password[256] = { 0 };
	printf("�������Account��");
	std::cin >> Account;
	printf("�������Password��");
	std::cin >> Password;
	if(m_PW->SetDataPassword(Account, Password))
	{
		printf("���ĳɹ���\n");
		Sleep(300);
	}
}
void PASSENGINE::_ChangeUserInfo()
{
	char Account[256] = { 0 };
	char UserInfo[256] = { 0 };
	printf("�������Account��");
	std::cin >> Account;
	printf("�������UserInfo��");
	std::cin >> UserInfo;
	if(m_PW->SetDataInfo(Account, UserInfo))
	{
		printf("���ĳɹ���\n");
		Sleep(300);
	}
}