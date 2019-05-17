#pragma once
#include <iostream>
#include <Windows.h>
#include <assert.h>
#include <stdio.h>


#define DELETEACCOUNT       0//ɾ�������˺�
#define DELETEPASSWORD     1//ɾ������
#define DELETEINFO                 2//ɾ����Ϣ

typedef struct PASS_WORD
{
	unsigned int DataHeadLenght = 0;//һ�����ݵ���Ϣͷ��
	unsigned long AccoundLenght = 0;//�˺ų���
	unsigned long PasswordLenght = 0;//���볤��
	long long UserInfoLenght = 0;//��Ϣ����
	//�ĸ��ֽڵĻ���
}Pass_word, *LPPassword;

typedef struct USERINFO
{
	char Account[256] = { 0 };
	char Password[256] = { 0 };
	char UserInfo[1024] = { 0 };
}UserInfo, *LPUserInfo;

class PASSWORD
{
	char m_FileName[256] = "Text";

	char m_EncryptionInfo[1024] = { };//����������Ϣ
	UserInfo *m_DATAINFO = NULL;//�û���Ϣ��
	int m_UserNum = 0;//�˺�����
public:
	//�ڴ�������ʱ,��������е����ݵ��ڴ���
	PASSWORD();
	~PASSWORD();

	//�൱��ˢ���ڴ��е�����
	void InitData();
	//�� �ɹ�����TRUE
	BOOL SaveData(const char *Account, const char *Password, const char *Info = NULL);
	BOOL SaveData(UserInfo UserData);

	//ɾ �ɹ�����TRUE
	BOOL DeleteData(const char *Account, int DEFINE);

	//���
	void GetDataPassword(const char *Account, char *PasswordBuf);
	char *GetDataPassword(const char *Account);
	BOOL SetDataPassword(const char *Account, const char *Password);

	BOOL SetDataInfo(const char *Account, const char *Info);
	void GetDataInfo(const char *Account, char *DataInfoBuf);
	char *GetDataInfo(const char *Account);

	BOOL SetDataAccount(const char *Account, const char *Accounts);



	//ɾ���û���Ϣ�б�
	void DeleteUserDataInfoList();

	//����ļ�����
	void ClearFileContent();
	int GetUserNum() { return m_UserNum; };
	UserInfo *GetDATAINFO() { return m_DATAINFO; };
private:
	//׷�ӵķ�ʽ��
	FILE *OpenFile_Write();
	//�Ա������ļ��Ķ�����ģʽ��
	FILE *OpenFile_Read();

	//���ļ�����
	void OpenFile_End(FILE *File);
	void Clear(const char *FileName);
	void Assert(void *Pointer);
	void DeleteMemory();

	//�˺��Ƿ����
	BOOL IsExistence(const char *Account, FILE *File);
	//�ַ����Ƚ� ��ͬ����TRUE
	BOOL StringCompare(const char *Str_1, const char *Str_2);
	//����Ϣ����
	//��ϢΪ��,���Ǵ�����Ϣͷ���ĸ��ֽ�
	BOOL NULL_Encryption(const char *Info);
	//�����ļ�������Ϣ
	void ErgodicFileAnyInfo();
	//ɾ��ĳ���˺ŵ�������Ϣ
	BOOL DeleteAccount(const char *Account);
	//ɾ��ĳ�˺ŵ�����
	BOOL DeleteAccountPassword(const char *Account);
	//ɾ��ĳ�˺ŵ���Ϣ
	BOOL DeleteAccountInfo(const char *Account);

	//д�뻺���е�����
	void InsertData(FILE *File);
	void InsertData();
	//��������
	void Encryption(const char *AnyInfo);
	//��������
	void Decode(char *EncryptionInfo, char *Buf);
	//д���������
	void WriteEncryptionInfo(FILE *File);
};


class PASSENGINE
{
	PASSWORD *m_PW = new PASSWORD();


	char m_Password[256] = { 0 };
	bool m_ImportPasswordOk = false;
	int m_Code = 0;
	bool m_PassOk = false;
	char m_EncryptionInfo[1024] = { };//����������Ϣ
	const char *FileName = "PASSWORD";
public:
	PASSENGINE();
	~PASSENGINE();
	void Run();
private:
	bool EnterPassword();
	void Get_Password();
	void Set_Password(FILE *File);
protected:
	void _Password();
	char _Pass_word[256] = "themyqq321";
	void _Print();
	void _SwitchCode(int Code);

	void _SaveAccount();
	void _DeleteAccount();
	void _ChangeAccount();
	void _ChangePassword();
	void _ChangeUserInfo();
};
