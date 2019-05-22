#pragma once
#include "TOOL.h"
#include <string>
#include <iostream>
#include "DDOS.h"
//嵌入OpenGL
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
	WORD idCount;            // 目录数
};
#pragma pack(1)
struct TResDirHeader
{
	BYTE bWidth;             // 图像宽度，以象素为单位。一个字节
	BYTE bHeight;            // 图像高度，以象素为单位。一个字节
	BYTE bColorCount;        // 图像中的颜色数（如果是>=8bpp的位图则为0）
	BYTE bReserved;          // 保留字必须是0
	WORD wPlanes;            // 标设备说明位面数，其值将总是被设为1
	WORD wBitCount;          // 每象素所占位数
	DWORD lBYTEsInRes;       // 每份资源所占字节数
	DWORD lImageOffset;      // 图像数据（iconimage）起点偏移位置
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
	//初始编辑框的内容
	void INIT_CEditControl(CEdit *CEditControl, CString Text);
	//初始编辑框的内容
	void Set_CEditControl(CEdit *CEditControl, CString Text);
	// CString 转 const char*
	const char *CString_To_ConstChar(CString String);
	// CString 转 string
	std::string CString_To_String(CString String);
	void Char_To_Wchar_T(wchar_t *Buf, int BufSize, const char *String);
	// 获取当前exe运行目录
	char *GetCur_ExeRunPath(char *Buffer, int BufferLen);
	// 启动低轨道粒子炮
	int StartLOIC();
	// 启动音频剪辑
	int StartGoldWave();
	// 启动低轨道粒子炮加强版
	int StartLOICPLUS();
	// 开始TCP协议的ddos攻击
	int Begined_TCP_DDOSAttack(CString IP, CString Port, CString Thread);
	// 结束TCP协议的ddos攻击
	int Ended_TCP_DDOSAttack();
	// 打开密码管理器
	int PasswordManager();
	// 获取当前计算机IP
	void Get_ComputerIP();
	// 获取当前计算机名字
	void Get_ComputerName();
	//打开电脑录音程序
	void SoundRecording();
private:
	// 更改exe文件图标
	bool ChangeExeIcon(LPWSTR IconFile, LPWSTR ExeFile);
	// 查找某个路径下的后缀名为exe的文件并更改图标
	// 实例 //	FindFile("Exe\\","*.exe", L"Bitmap.ico");
	bool Find_EXE_ChangeFileIcon(const char *Path, const char *Type, const wchar_t *IconName);
	WORD MakeLangID();
	// 更改exe文件图标
	void ChangeIcon(const char* szFileName, const char* szIconFile);
public:
	//SETTIME_BEGIN_DDOS
	void SOCKETDDOS(CString IP, UINT Port);

	//===================================================
	//创建一个打开文件对话框
	CString CreateCFileDialog();
	//mov,mp4,m4a,3gp,3g2,mj2
	//剪辑视频为帧数
	void EditVideoBecomeFrame(CString VideoPathName, CString ImageType, CString FrameNumber);
	//播放帧动画
	void PlayFrameAnimation(CDC *pCDC);
	//PlayMusic
	void PlayerMusic();
	//PauseMusic
	void PauseMusic();
	//初始化音乐进度信息数据
	void InitMusicProgressInfoData(CProgressCtrl *MusicProgress, CSliderCtrl *EditMusicProgress, CSliderCtrl *EditMusicVolume, CMFCButton *PauseMusic);
	//是否在播放音乐
	int IsPlayMusic();
	//获取音乐信息数据来自AT引擎
	void GetMusicInfoDataFromATBAudioEngine();
	//设置音乐进度
	void SetMusicProgress();
	//设置音乐音量
	void SetMusicVolume();
};