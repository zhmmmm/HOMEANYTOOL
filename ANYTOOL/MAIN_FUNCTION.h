#pragma once
#include "TOOL.h"
#include <string>
#include <iostream>
#include "DDOS.h"
//Ƕ��OpenGL
#include "ImplantOpenGL.h"
#include "Scene.h"

#pragma comment(lib,"ATENGINE\\bin\\ATENGINE.lib")

using namespace std;

#define MAIN                                   FUNCTION
#define TYPE__ONE__                      (1)
#define SETTIME_BEGIN_DDOS 	SetTimer((TYPE__ONE__), (100), (NULL));
#define KILLTIME_END_DDOS       KillTimer((TYPE__ONE__));

#define MUSICS__GETPROGRESSINFODATA__                 (0)
#define SETTIME_MUSICS__GETPROGRESSINFODATA__BEGIN_MUSIC 	SetTimer((MUSICS__GETPROGRESSINFODATA__), (1), (NULL));
#define KILLTIME_MUSICS__GETPROGRESSINFODATA__END_MUSIC       KillTimer((MUSICS__GETPROGRESSINFODATA__));



#define ATENGINE__ATUPDATEDATA__DRAW                 (2)
#define ATENGINE__ATUPDATEDATA__DRAW_BEGIN     SetTimer((ATENGINE__ATUPDATEDATA__DRAW), (1), (NULL));
#define ATENGINE__ATUPDATEDATA__DRAW_END        KillTimer((ATENGINE__ATUPDATEDATA__DRAW));


//================================================


//================================================
struct ICONDIRENTRY//IconDirentry
{
	BYTE bWidth;
	BYTE bHeight;
	BYTE bColorCount;
	BYTE bReserved;
	WORD wPlanes;
	WORD wBitCount;
	DWORD dwBytesInRes;
	DWORD dwImageOffset;
};
struct ICONDIR//IconDir
{
	WORD idReserved;
	WORD idType;
	WORD idCount;
	//ICONDIRENTRY idEntries;
};
struct GRPICONDIRENTRY//GrpIconDirentry
{
	BYTE bWidth;
	BYTE bHeight;
	BYTE bColorCount;
	BYTE bReserved;
	WORD wPlanes;
	WORD wBitCount;
	DWORD dwBytesInRes;
	WORD nID;
};
struct GRPICONDIR//GrpIconDir
{
	WORD idReserved;
	WORD idType;
	WORD idCount;
	GRPICONDIRENTRY idEntries;
};
//=============================================
struct TIconHeader
{
	WORD idReserved;
	WORD idType;
	WORD idCount;            // Ŀ¼��
};
#pragma pack(1)
struct TResDirHeader
{
	BYTE bWidth;             // ͼ���ȣ�������Ϊ��λ��һ���ֽ�
	BYTE bHeight;            // ͼ��߶ȣ�������Ϊ��λ��һ���ֽ�
	BYTE bColorCount;        // ͼ���е���ɫ���������>=8bpp��λͼ��Ϊ0��
	BYTE bReserved;          // �����ֱ�����0
	WORD wPlanes;            // ���豸˵��λ��������ֵ�����Ǳ���Ϊ1
	WORD wBitCount;          // ÿ������ռλ��
	DWORD lBYTEsInRes;       // ÿ����Դ��ռ�ֽ���
	DWORD lImageOffset;      // ͼ�����ݣ�iconimage�����ƫ��λ��
};
#pragma pack()
typedef struct TIconResDirGrp
{
	TIconHeader    idHeader;
	TResDirHeader idEntries[1];

} *PIconResDirGrp;



class FUNCTION
{
	std::string m_String;

	int m_ISDDOS = 0;
	int m_ISPlayMusic = 0;
	CString m_CurPlayerMusic;
	CProgressCtrl *m_MusicProgress = NULL;
	CSliderCtrl *m_EditMusicProgress = NULL;
	CSliderCtrl *m_EditMusicVolume = NULL;
	CMFCButton *m_PauseMusic = NULL;
	int m_ISPauseMusic = 0;
public:
	//��ʼ�༭�������
	void INIT_CEditControl(CEdit *CEditControl, CString Text);
	//��ʼ�༭�������
	void Set_CEditControl(CEdit *CEditControl, CString Text);
	// CString ת const char*
	const char *CString_To_ConstChar(CString String);
	// CString ת string
	std::string CString_To_String(CString String);
	void Char_To_Wchar_T(wchar_t *Buf, int BufSize, const char *String);
	// ��ȡ��ǰexe����Ŀ¼
	char *GetCur_ExeRunPath(char *Buffer, int BufferLen);
	// �����͹��������
	int StartLOIC();
	// ������Ƶ����
	int StartGoldWave();
	// �����͹�������ڼ�ǿ��
	int StartLOICPLUS();
	// ��ʼTCPЭ���ddos����
	int Begined_TCP_DDOSAttack(CString IP, CString Port, CString Thread);
	// ����TCPЭ���ddos����
	int Ended_TCP_DDOSAttack();
	// �����������
	int PasswordManager();
	// ��ȡ��ǰ�����IP
	void Get_ComputerIP();
	// ��ȡ��ǰ���������
	void Get_ComputerName();
	//�򿪵���¼������
	void SoundRecording();
private:
	// ����exe�ļ�ͼ��
	bool ChangeExeIcon(LPWSTR IconFile, LPWSTR ExeFile);
	// ����ĳ��·���µĺ�׺��Ϊexe���ļ�������ͼ��
	// ʵ�� //	FindFile("Exe\\","*.exe", L"Bitmap.ico");
	bool Find_EXE_ChangeFileIcon(const char *Path, const char *Type, const wchar_t *IconName);
	WORD MakeLangID();
	// ����exe�ļ�ͼ��
	void ChangeIcon(const char* szFileName, const char* szIconFile);
public:
	//SETTIME_BEGIN_DDOS
	void SOCKETDDOS(CString IP, UINT Port);

	//===================================================
	//����һ�����ļ��Ի���
	CString CreateCFileDialog();
	//mov,mp4,m4a,3gp,3g2,mj2
	//������ƵΪ֡��
	void EditVideoBecomeFrame(CString VideoPathName, CString ImageType, CString FrameNumber);
	//����֡����
	void PlayFrameAnimation(CDC *pCDC);
	//PlayMusic
	void PlayerMusic();
	//PauseMusic
	void PauseMusic();
	//��ʼ�����ֽ�����Ϣ����
	void InitMusicProgressInfoData(CProgressCtrl *MusicProgress, CSliderCtrl *EditMusicProgress, CSliderCtrl *EditMusicVolume, CMFCButton *PauseMusic);
	//�Ƿ��ڲ�������
	int IsPlayMusic();
	//��ȡ������Ϣ��������AT����
	void GetMusicInfoDataFromATBAudioEngine();
	//�������ֽ���
	void SetMusicProgress();
	//������������
	void SetMusicVolume();
};