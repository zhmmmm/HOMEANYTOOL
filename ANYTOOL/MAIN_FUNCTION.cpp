#include "stdafx.h"
#include "MAIN_FUNCTION.h"

void FUNCTION::INIT_CEditControl(CEdit *CEditControl, CString Text)
{
	CEditControl->SetWindowTextW(Text);
}
void FUNCTION::Set_CEditControl(CEdit *CEditControl, CString Text)
{
	CEditControl->SetWindowTextW(Text);

}

const char * FUNCTION::CString_To_ConstChar(CString String)
{
	if (String)
	{
		//���ַ���
		//USES_CONVERSION;
		//std::string str(W2A(String));

		//CStringA temp;
		//temp = Port;
		//char *p = temp.GetBuffer();

		m_String.clear();
		m_String = CT2A(String);

		return m_String.c_str();
	}
	return nullptr;
}

string FUNCTION::CString_To_String(CString String)
{
	USES_CONVERSION;
	std::string ToString(W2A(String));
	return ToString;
}

void FUNCTION::Char_To_Wchar_T(wchar_t *Buf, int BufSize, const char *String)
{
	if (Buf && String)
	{
		if (strlen(String) > BufSize) { return; }
		int i = 0;
		while (String[i])
		{
			Buf[i] = String[i];
			i++;
		}
	}
}

char *FUNCTION::GetCur_ExeRunPath(char *Buffer, int BufferLen)
{
	wchar_t Buf[256] = { 0 };
	GetModuleFileName(NULL, Buf, sizeof(Buf));
	char BufTemp[256] = { 0 };
	for (int i = 0; i < 256; i++)
	{
		if (Buf[i])
		{
			BufTemp[i] = (char)Buf[i];
		}
		else
		{
			break;
		}

	}
	std::cout << "exe ����Ŀ¼ " << BufTemp << std::endl;
	int BufLen = strlen(BufTemp);
	const char *AnyTool = "ANYTOOL";
	char Path[256] = { 0 };
	for (int i = 0; i < BufLen; i++)
	{
		bool Jump = true;
		if (BufTemp[i] == 'A')
		{
			for (int j = 0; j < 7; j++)
			{
				//�����һ������������ȥ������ֵ
				if (BufTemp[i + j] != AnyTool[j])
				{
					Jump = true;
					break;
				}
				else
				{
					Jump = false;
				}
			}
		}
		if (Jump)
		{
			Path[i] = BufTemp[i];
		}
		else
		{
			for (int j = 0; j < 7; j++)
			{
				Path[i + j] = AnyTool[j];
			}
			break;
		}
	}
	for (int i = 0; i < BufferLen; i++)
	{
		Buffer[i] = Path[i];
	}
	return NULL;
}

int FUNCTION::StartLOIC()
{
	char Path[256] = { 0 };
	MAIN::GetCur_ExeRunPath(Path, sizeof(Path));
	const char *LOIC = "\\ANYTOOL\\Tool\\LOIC.exe";//����λ��,���ɸ���
	std::cout << "�ַ���δ����ǰ " << Path << std::endl;
	strcat_s(Path, LOIC);
	std::cout << "�ַ������Ӻ� " << Path << std::endl;
	char PATH[256] = "START ";
	strcat_s(PATH, Path);
	std::cout << PATH << std::endl;
	//ֻҪexe�Ƿ���ANYTOOL�ļ���,����λ�ò�������,����׼ȷ������Ҫ�Ĺ���
	if (system(PATH) == 0)
	{
		std::cout << "�͹�������������ɹ���" << std::endl;
		return 0;
	}
	return -1;
}

int FUNCTION::StartGoldWave()
{
	char Path[256] = { 0 };
	MAIN::GetCur_ExeRunPath(Path, sizeof(Path));
	const char *GoldWave = "\\ANYTOOL\\Tool\\AudioEdit\\GoldWave\\GoldWave.exe";//����λ��,���ɸ���
	std::cout << "�ַ���δ����ǰ " << Path << std::endl;
	strcat_s(Path, GoldWave);
	std::cout << "�ַ������Ӻ� " << Path << std::endl;
	char PATH[256] = "START ";
	strcat_s(PATH, Path);
	std::cout << PATH << std::endl;
	//ֻҪexe�Ƿ���ANYTOOL�ļ���,����λ�ò�������,����׼ȷ������Ҫ�Ĺ���
	if (system(PATH) == 0)
	{
		std::cout << "��Ƶ�������������ɹ���" << std::endl;
		return 0;
	}
	return -1;
}

int FUNCTION::StartLOICPLUS()
{
	char Path[256] = { 0 };
	MAIN::GetCur_ExeRunPath(Path, sizeof(Path));
	const char *LOIC = "\\ANYTOOL\\Tool\\LOICPLUS\\LOIC.exe";//����λ��,���ɸ���
	std::cout << "�ַ���δ����ǰ " << Path << std::endl;
	strcat_s(Path, LOIC);
	std::cout << "�ַ������Ӻ� " << Path << std::endl;
	char PATH[256] = "START ";
	strcat_s(PATH, Path);
	std::cout << PATH << std::endl;
	//ֻҪexe�Ƿ���ANYTOOL�ļ���,����λ�ò�������,����׼ȷ������Ҫ�Ĺ���
	if (system(PATH) == 0)
	{
		std::cout << "�͹�������������ɹ���" << std::endl;
		return 0;
	}
	return -1;
}

int FUNCTION::Begined_TCP_DDOSAttack(CString IP, CString Port, CString Thread)
{
	std::cout << MAIN::CString_To_ConstChar(IP) << std::endl;
	std::cout << MAIN::CString_To_ConstChar(Port) << std::endl;
	std::cout << MAIN::CString_To_ConstChar(Thread) << std::endl;

	int port = 0;
	int thread = 0;
	port = atoi(MAIN::CString_To_ConstChar(Port));
	thread = atoi(MAIN::CString_To_ConstChar(Thread));

	if (!Init_CSharP_DLL_To_CPlusPlus_DLL(MAIN::CString_To_ConstChar(IP),
		port,
		thread))
	{
		std::cout << "�����ɹ�!" << std::endl;
		m_ISDDOS = 1;
		return 0;
	}
	return -1;
}

int FUNCTION::Ended_TCP_DDOSAttack()
{
	if (m_ISDDOS == 1)
	{
		Stop_CSharP_DLL_To_CPlusPlus_DLL_DDosAttack();
		return 0;
	}
	return -1;
}

int FUNCTION::PasswordManager()
{
	char Path[256] = { 0 };
	MAIN::GetCur_ExeRunPath(Path, sizeof(Path));
	const char *PasswordManager = "\\ANYTOOL\\Tool\\PasswordManager\\PasswordManager.exe";//����λ��,���ɸ���
	std::cout << "�ַ���δ����ǰ " << Path << std::endl;
	strcat_s(Path, PasswordManager);
	std::cout << "�ַ������Ӻ� " << Path << std::endl;
	char PATH[256] = "START ";
	strcat_s(PATH, Path);
	std::cout << PATH << std::endl;
	//ֻҪexe�Ƿ���ANYTOOL�ļ���,����λ�ò�������,����׼ȷ������Ҫ�Ĺ���
	if (system(PATH) == 0)
	{
		std::cout << "PasswordManager�����ɹ���" << std::endl;
		return 0;
	}
	return -1;
}

void FUNCTION::Get_ComputerIP()
{
	char buf[256] = "";
	hostent *ph = NULL;
	WSADATA w;
	WSAStartup(0x0101, &w);//��һ�б�����ʹ���κ�SOCKET����ǰд��


	gethostname(buf, 256);
	std::string hostName = buf;//�˴���ñ�������

	ph = gethostbyname(buf);
	//GetAddrInfoW();

	int i = 0;
	while (ph->h_addr_list[i] != NULL)
	{
		printf("COMPUTER NAME : %s\n", ph->h_name);
		printf("COMPUTER     IP �� %s\n", inet_ntoa(*((struct in_addr *)ph->h_addr_list[i])));
		i++;
	}
	const char *IP = inet_ntoa(*((struct in_addr *)ph->h_addr_list[i - 1]));//�˴���ñ���IP
	int MessageBoxAValue = MessageBoxA(NULL, IP, "MessageBoxA", MB_OK);
	printf("MessageBoxAValue = %d\n", MessageBoxAValue);

	WSACleanup();
}

void FUNCTION::Get_ComputerName()
{
	char buf[256] = "";
	hostent *ph = NULL;
	WSADATA w;
	WSAStartup(0x0101, &w);//��һ�б�����ʹ���κ�SOCKET����ǰд��


	gethostname(buf, 256);
	std::string hostName = buf;//�˴���ñ�������

	int MessageBoxAValue = MessageBoxA(NULL, hostName.c_str(), "MessageBoxA", MB_OK);
	printf("MessageBoxAValue = %d\n", MessageBoxAValue);
}

void FUNCTION::SoundRecording()
{
	char Path[256] = { 0 };
	MAIN::GetCur_ExeRunPath(Path, sizeof(Path));
	const char *SoundRecording = "\\ANYTOOL\\Tool\\SoundRecording\\svr\\wadfngrv.exe";//����λ��,���ɸ���
	std::cout << "�ַ���δ����ǰ " << Path << std::endl;
	strcat_s(Path, SoundRecording);
	std::cout << "�ַ������Ӻ� " << Path << std::endl;
	char PATH[256] = "START ";
	strcat_s(PATH, Path);
	std::cout << PATH << std::endl;
	//ֻҪexe�Ƿ���ANYTOOL�ļ���,����λ�ò�������,����׼ȷ������Ҫ�Ĺ���
	if (system(PATH) == 0)
	{
		std::cout << "SoundRecording�����ɹ���" << std::endl;
	}
}


bool FUNCTION::ChangeExeIcon(LPWSTR IconFile, LPWSTR ExeFile)
{
	ICONDIRENTRY stIDE;//Icon��Ϣ
	ICONDIR stID;//IconĿ¼
	GRPICONDIR stGID;//GrpIconĿ¼
	HANDLE hFile;//�ļ����
	DWORD nSize = 0;
	DWORD nGSize = 0;
	DWORD dwReserved = 0;
	HANDLE hUpdate;//Ҫ�����ļ��ľ��
	PBYTE pIcon, pGrpIcon;
	BOOL ret;
	//�����ļ�,�õ�ICON���ļ����
	hFile = CreateFileW(IconFile, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	//��ʼ��
	ZeroMemory(&stID, sizeof(ICONDIR));
	//���ļ�,���ļ�����ж�ȡ��iconĿ¼��
	ret = ReadFile(hFile, &stID, sizeof(ICONDIR), &dwReserved, NULL);
	//��ʼ��
	ZeroMemory(&stIDE, sizeof(ICONDIRENTRY));
	//���ļ�,���ļ�����ж�ȡ��icon��Ϣ��
	ret = ReadFile(hFile, &stIDE, sizeof(ICONDIRENTRY), &dwReserved, NULL);

	nSize = stIDE.dwBytesInRes;
	pIcon = (PBYTE)malloc(nSize);
	//�����ļ�ָ��
	//stIDE.dwImageOffset ƫ����
	SetFilePointer(hFile, stIDE.dwImageOffset, NULL, FILE_BEGIN);
	//���ļ�
	ret = ReadFile(hFile, (LPVOID)pIcon, nSize, &dwReserved, NULL);
	if (!ret)
	{
		CloseHandle(hFile);
		return false;
	}
	//��ʼ��
	ZeroMemory(&stGID, sizeof(GRPICONDIR));
	stGID.idCount = stID.idCount;
	stGID.idReserved = 0;
	stGID.idType = 1;
	CopyMemory(&stGID.idEntries, &stIDE, 12);
	stGID.idEntries.nID = 0;
	nGSize = sizeof(GRPICONDIR);
	pGrpIcon = (PBYTE)malloc(nGSize);
	CopyMemory(pGrpIcon, &stGID, nGSize);

	//�õ�Ҫ�����ļ��ľ��
	hUpdate = BeginUpdateResourceW(ExeFile, FALSE);//false Ϊ��ɾ�����е���Դ
	//������Դ,Icon ��Ŀ¼��Ϣ
	ret = UpdateResourceW(hUpdate, RT_GROUP_ICON, MAKEINTRESOURCE(1), 0, (LPVOID)pGrpIcon, nGSize);
	//������Դ
	ret = UpdateResourceW(hUpdate, RT_ICON, MAKEINTRESOURCE(1), 0, (LPVOID)pIcon, nSize);
	//����������Դ
	EndUpdateResourceW(hUpdate, FALSE);
	if (!ret)
	{
		CloseHandle(hFile);
		return false;
	}


	CloseHandle(hFile);
	free(pGrpIcon);
	free(pIcon);
	pIcon = NULL;
	pGrpIcon = NULL;
	return true;
}

bool FUNCTION::Find_EXE_ChangeFileIcon(const char *Path, const char *Type, const wchar_t *IconName)
{
	LPWSTR File_IconName = (LPWSTR)IconName;
	WIN32_FIND_DATAA FindFileData;
	char PATH[MAX_PATH] = { 0 };
	strcat_s(PATH, Path);
	strcat_s(PATH, Type);
	HANDLE HFinder = FindFirstFileA(PATH, &FindFileData);
	if (HFinder == INVALID_HANDLE_VALUE)
	{
		std::cout << "δ�ɹ���" << std::endl;
	}
	while (true)
	{
		//�Ƿ���������Ҫ���ļ�
		if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			char EXEPath[MAX_PATH] = { 0 };
			//������һ���ַ������ӵ�
			char Buf[MAX_PATH] = { 0 };
			strcpy_s(Buf, Path);
			strcat_s(Buf, "%s");
			sprintf_s(EXEPath, Buf, FindFileData.cFileName);
			int Lenth = 0;
			while (EXEPath[Lenth]) { Lenth++; }
			wchar_t EXE[MAX_PATH] = { 0 };
			for (int i = 0; i < Lenth; i++)
			{
				EXE[i] = EXEPath[i];
			}
			bool ok = MAIN::ChangeExeIcon(File_IconName, (LPWSTR)EXE);
		}
		if (!(FindNextFileA(HFinder, &FindFileData)))
		{
			break;
		}
	}
	FindClose(HFinder);
	return true;
}//	FindFile("Exe\\","*.exe", L"Bitmap.ico");

WORD FUNCTION::MakeLangID()
{
	return  (SUBLANG_ENGLISH_US << 10) | LANG_ENGLISH;
}

void FUNCTION::ChangeIcon(const char* szFileName, const char* szIconFile)
{

	int i, FileGrpSize;
	DWORD dwFileSize, dwBytesRead;
	void * filemem, *p;
	PIconResDirGrp FileGrp;
	HANDLE hFile, hUpdateRes;
	const char*   szResName = "AyIcon";
	WCHAR   szFileNameWCHAR[MAX_PATH] = { 0 };
	WCHAR   szIconFileWCHAR[MAX_PATH] = { 0 };
	WCHAR   szResNameWCHAR[MAX_PATH] = { 0 };

	MultiByteToWideChar(CP_ACP, 0, szFileName, -1,
		szFileNameWCHAR, sizeof(szFileNameWCHAR));

	MultiByteToWideChar(CP_ACP, 0, szIconFile, -1,
		szIconFileWCHAR, sizeof(szIconFileWCHAR));

	MultiByteToWideChar(CP_ACP, 0, szResName, -1,
		szResNameWCHAR, sizeof(szResNameWCHAR));

	// open the icon file    
	hFile = CreateFile(szIconFileWCHAR, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, 0);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(0, L"Failed open Icon File!", NULL, 0);
		return;
	}

	// get the file size     
	dwFileSize = GetFileSize(hFile, NULL);

	filemem = malloc(dwFileSize);

	// read file to memory       
	ReadFile(hFile, filemem, dwFileSize, &dwBytesRead, NULL);

	CloseHandle(hFile);


	// assume the TIconResDirGrp STRUCT     ��
	FileGrp = PIconResDirGrp(filemem);

	// get Icon_Header size    
	FileGrpSize = sizeof(TIconResDirGrp) + (FileGrp->idHeader.idCount - 1)
		* sizeof(TResDirHeader);

	// begin to change the resource    
	hUpdateRes = BeginUpdateResource(szFileNameWCHAR, false);

	// change all frames'resource     
	for (i = 0; i < FileGrp->idHeader.idCount; i++)
	{

		p = (void *)((DWORD)filemem + FileGrp->idEntries[i].lImageOffset);

		// change every frame         
		UpdateResource(hUpdateRes, RT_ICON,
			MAKEINTRESOURCE(FileGrp->idEntries[i].lImageOffset)
			, MAIN::MakeLangID(), p, FileGrp->idEntries[i].lBYTEsInRes);
	}

	// update header information  
	UpdateResource(hUpdateRes, RT_GROUP_ICON, szResNameWCHAR, MAIN::MakeLangID(),
		FileGrp, FileGrpSize);

	EndUpdateResource(hUpdateRes, false);
	free(filemem);
	filemem = NULL;
}




//===================================================
CString FUNCTION::CreateCFileDialog()
{
	CFileDialog CFileDialog(TRUE, NULL, NULL, 0, (LPCTSTR)_TEXT("��Ƶ�ļ�(*.mp4)|*.mp4|�����ļ�(*.*)|*.*||"));

	if (CFileDialog.DoModal() == IDOK)
	{
		return CFileDialog.GetPathName();
	}
	return NULL;
}

void FUNCTION::EditVideoBecomeFrame(CString VideoPathName, CString ImageType, CString FrameNumber)
{
	std::cout << "Ҫ��������Ƶ " << MAIN::CString_To_ConstChar(VideoPathName) << std::endl;
	std::cout << "ͼƬ���� " << MAIN::CString_To_ConstChar(ImageType) << std::endl;
	std::cout << "ÿ��֡�� " << MAIN::CString_To_ConstChar(FrameNumber) << std::endl;

	std::string Video = MAIN::CString_To_String(VideoPathName);
	std::string Type = MAIN::CString_To_String(ImageType);
	std::string FrameNum = MAIN::CString_To_String(FrameNumber);

	char EXERunPath[1024] = { 0 };
	char StartRuning[256] = " -i ";
	char StartType[256] = " -r ";
	char Vcodec[256] = " -vcodec ";
	char FramePath[256] = " ";
	char EditVideoFramePath[256] = "\\ANYTOOL\\Tool\\VideoTranslates\\Image\\%04d.";
	char Ffmpeg[256] = "\\ANYTOOL\\Tool\\VideoTranslates\\ffmpeg-20160425-git-9ac154d-win32-static\\bin\\ffmpeg.exe ";
	strcat_s(EditVideoFramePath, Type.c_str());//֡�����·��
	MAIN::GetCur_ExeRunPath(EXERunPath,sizeof(EXERunPath));
	strcat_s(FramePath, EXERunPath);//֡�Ļ������Ŀ¼
	strcat_s(FramePath, EditVideoFramePath);//֡�Ļ������·��

	strcat_s(StartRuning, Video.c_str());//�����Ƶ·��
	strcat_s(StartType, FrameNum.c_str());//֡��
	strcat_s(StartType, Vcodec);//����
	strcat_s(StartType,Type.c_str());//ͼƬ����
	strcat_s(StartRuning, StartType);//��Ƶ·��������֡����֡����

	strcat_s(EXERunPath, Ffmpeg); //exe����·��
	strcat_s(EXERunPath, StartRuning);//���Ӽ���
	strcat_s(EXERunPath, FramePath); //���ӻ���Ŀ¼
	std::cout << "�������е����� " << EXERunPath << std::endl;

	//ֻҪexe�Ƿ���ANYTOOL�ļ���,����λ�ò�������,����׼ȷ������Ҫ�Ĺ���
	if (system(EXERunPath) == 0)
	{
		char PathFile[256] = "START ";
		const char *EditVideoFrameDir = "\\ANYTOOL\\Tool\\VideoTranslates\\Image";
		MAIN::GetCur_ExeRunPath(EXERunPath, sizeof(EXERunPath));
		strcat_s(PathFile, EXERunPath);
		strcat_s(PathFile, EditVideoFrameDir);
		std::cout << "��Ƶ��֡������ɣ�" << std::endl;
		if (system(PathFile) == 0)
		{
			std::cout << "��Ƶ��ִ֡����ϣ�" << std::endl;
		}
	}
}

void FUNCTION::PlayFrameAnimation(CDC *pCDC)
{
	static int TimeValue = 0;


	CDC mdc;
	mdc.CreateCompatibleDC(pCDC);
	char Image[256] = { 0 };
	sprintf_s(Image, "Tool\\VideoTranslates\\Image\\%04d.bmp", TimeValue + 1);
	HBITMAP bmp = (HBITMAP)LoadImageA(NULL, Image, IMAGE_BITMAP, 600, 500, LR_LOADFROMFILE);//AΪchar*
	if (bmp)
	{
		SelectObject(mdc, bmp);

		pCDC->BitBlt(4, 50, 550, 500, &mdc, 0, 0, SRCCOPY);

		DeleteObject(bmp);
		DeleteDC(mdc);
	}


	TimeValue++;
}

void FUNCTION::PlayerMusic()
{
	CFileDialog CFileDialog(TRUE, NULL, NULL, 0, (LPCTSTR)_TEXT("�����ļ�(*.mp3)|*.mp3|�����ļ�(*.*)|*.*||"));

	if (CFileDialog.DoModal() == IDOK)
	{
		ATA->DeleteAllMusicAndSounds();
		m_CurPlayerMusic = CFileDialog.GetPathName();
		ATA->PlayMusics(MAIN::CString_To_String(CFileDialog.GetPathName()));
		m_ISPlayMusic = 1;
	}
}
void FUNCTION::PauseMusic()
{
	if (m_ISPlayMusic == 1)
	{
		if (m_ISPauseMusic == 0)
		{
			m_PauseMusic->SetWindowTextW(CString("StartMusic"));
			ATA->PauseAllMusics();
			m_ISPlayMusic = 1;
			m_ISPauseMusic = 1;
			return;
		}
		if (m_ISPauseMusic == 1)
		{
			m_PauseMusic->SetWindowTextW(CString("PauseMusic"));
			ATA->PlayMusics(MAIN::CString_To_String(m_CurPlayerMusic), FALSE);
			m_ISPlayMusic = 1;
			m_ISPauseMusic = 0;
			return;
		}
	}
}

void FUNCTION::InitMusicProgressInfoData(CProgressCtrl *MusicProgress, CSliderCtrl *EditMusicProgress, CSliderCtrl *EditMusicVolume, CMFCButton *PauseMusic)
{
	m_MusicProgress = MusicProgress;
	m_EditMusicProgress = EditMusicProgress;
	m_EditMusicVolume = EditMusicVolume;
	m_PauseMusic = PauseMusic;
	MusicProgress->SetPos(0);
	EditMusicProgress->SetPos(0);
	if (EditMusicVolume->GetPos()) {}
	else
	{
		EditMusicVolume->SetPos(100);
	}
}

int FUNCTION::IsPlayMusic()
{
	return m_ISPlayMusic;
}

void FUNCTION::GetMusicInfoDataFromATBAudioEngine()
{
	if (m_ISPlayMusic == 1)
	{
		string MusicName = MAIN::CString_To_String(m_CurPlayerMusic);

		m_MusicProgress->SetPos((int)(100 / ATA->GetTimeMinute(MusicName)) * (ATA->GetCurTimeMinute(MusicName)));
	}
}

void FUNCTION::SetMusicProgress()
{
	if (m_ISPlayMusic == 1)
	{
		string MusicName = MAIN::CString_To_String(m_CurPlayerMusic);
		double Scale = (((double)ATA->GetTimeMinute(MusicName)) / (double)100);
		ATA->SetTimeMinute(MusicName,
			(double)(m_EditMusicProgress->GetPos()) * Scale);
	}
}

void FUNCTION::SetMusicVolume()
{
	if (m_ISPlayMusic == 1)
	{
		ATA->SetVolume(m_EditMusicVolume->GetPos());
	}
}







//===================================================
//SETTIME_BEGIN_DDOS
void FUNCTION::SOCKETDDOS(CString IP, UINT Port)
{
	CSocket socket;
	socket.Create();

	if (socket.Connect(IP, Port))
	{
		char buf[200] = { 0 };
		srand(GetTickCount());
		for (int i = 0; i < 200; i++)
		{
			buf[i] = rand() % 128;
		}
		socket.Send(buf, 200);
	}
	socket.Close();
	//DOS S;
	//S.Run();
}