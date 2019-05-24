#include "stdafx.h"
#include "ANYTOOL.h"
#include "ANYTOOLDlg.h"
#include "afxdialogex.h"
#include "resource.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};
CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX){}
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


CANYTOOLDlg::CANYTOOLDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ANYTOOL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CANYTOOLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_IPEdit);

	DDX_Control(pDX, IDC_MFCBUTTON1, m_Exit);
	DDX_Control(pDX, IDC_EDIT3, m_PortEdit);
	DDX_Control(pDX, IDC_EDIT4, m_ThreadEdit);
	DDX_Control(pDX, IDC_EDIT2, m_VideoPath);
	DDX_Control(pDX, IDC_EDIT6, m_ImageType);
	DDX_Control(pDX, IDC_EDIT7, m_FrameNumber);
	DDX_Control(pDX, IDC_PROGRESS1, m_MusicProgress);
	DDX_Control(pDX, IDC_SLIDER1, m_EditMusicProgress);
	DDX_Control(pDX, IDC_SLIDER2, m_EditMusicVolume);
	DDX_Control(pDX, IDC_MFCBUTTON8, m_PauseMusic);
}

BEGIN_MESSAGE_MAP(CANYTOOLDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_BUTTON1, &CANYTOOLDlg::OnBnClicked_StartLOIC)
	ON_BN_CLICKED(IDC_BUTTON2, &CANYTOOLDlg::OnBnClicked_StartGoldWave)


	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_MFCBUTTON1, &CANYTOOLDlg::OnBnClicked_Exit)
	ON_BN_CLICKED(IDC_MFCBUTTON2, &CANYTOOLDlg::OnBnClicked_Begined)
	ON_BN_CLICKED(IDC_MFCBUTTON3, &CANYTOOLDlg::OnBnClicked_Ended)

	ON_BN_CLICKED(IDC_BUTTON3, &CANYTOOLDlg::OnBnClicked_StartLOICPLUS)
	ON_BN_CLICKED(IDC_BUTTON4, &CANYTOOLDlg::OnBnClicked_PasswordManager)
	ON_BN_CLICKED(IDC_MFCBUTTON4, &CANYTOOLDlg::OnBnClicked_GetComputerIP)
	ON_BN_CLICKED(IDC_MFCBUTTON5, &CANYTOOLDlg::OnBnClicked_GetComputerName)
	ON_BN_CLICKED(IDC_MFCBUTTON6, &CANYTOOLDlg::OnBnClicked_OpenVideoFile)
	ON_BN_CLICKED(IDC_BUTTON5, &CANYTOOLDlg::OnBnClicked_Sound__R)
	ON_BN_CLICKED(IDC_MFCBUTTON7, &CANYTOOLDlg::OnBnClicked_PlayMusic)
	ON_BN_CLICKED(IDC_MFCBUTTON8, &CANYTOOLDlg::OnBnClicked_PauseMusic)

	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &CANYTOOLDlg::OnNMCustomdrawSlider_EditMusicVolume)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CANYTOOLDlg::OnNMCustomdrawSlider_EditMusicProgress)

END_MESSAGE_MAP()


// CANYTOOLDlg 消息处理程序

BOOL CANYTOOLDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	ANYTOOLWINDOWS::Init_DATA();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CANYTOOLDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CANYTOOLDlg::OnPaint()
{
	std::cout << "开始绘制" << std::endl;
	CPaintDC MAIN_CDC(this); // 用于绘制的设备上下文
	SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(MAIN_CDC.GetSafeHdc()), 0);

	CRect rect;
	GetClientRect(&rect);
	MAIN_CDC.FillSolidRect(rect, RGB(37,8,88));
	


	//CBitmap Bitmap;
	//Bitmap.LoadBitmapW(IDB_BITMAP1);
	//CBrush brush;
	//brush.CreatePatternBrush(&Bitmap);
	//MAIN_CDC.SelectObject(brush);
	//MAIN_CDC.Rectangle(0, 0, rect.Width(), rect.Height());

	//OpenGL To MFC EX
	//========================================================================
	CPaintDC dc(this);
	MAIN_M_IOGL->OpenGL_TO_MFC__Update_ATENGINE(SCENE);
	SwapBuffers(dc.GetSafeHdc());
}
void CANYTOOLDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	MAIN_M_IOGL->OpenGL_TO_MFC__End_ATENGINE(SCENE);
	if (wglGetCurrentContext() != NULL)
	{
		wglMakeCurrent(NULL, NULL);
	}
	if (NULL != MAIN_M_IOGL->GetGLContext())
	{
		wglDeleteContext(MAIN_M_IOGL->GetGLContext());
		MAIN_M_IOGL->SetGLContext(NULL);
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CANYTOOLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CANYTOOLDlg::ControlAdaptive(int X, int Y)
{
	HWND hwndChild = ::GetWindow(m_hWnd, GW_CHILD);
	while (hwndChild)
	{
		UINT ID = ::GetDlgCtrlID(hwndChild);
		if (ID == IDC_MFCBUTTON1)
		{
			//CRect rec;
			//GetDlgItem(ID)->GetWindowRect(&rec);
			//int W = rec.Width();
			//int H = rec.Height();


			//int Left = X - W;
			//int Top = Y - H;
			//int RIght = X - W + W;
			//int Buttom = Y - (Y - H);


			//GetDlgItem(ID)->MoveWindow(CRect(Left, Top, RIght, Buttom), TRUE);
		}



		hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
	}

}

void CANYTOOLDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType,cx,cy);
	if (nType != SIZE_MINIMIZED)
	{
		printf("窗口大小改变! nType = %d cx = %d cy = %d\n",nType,cx,cy);
		GetClientRect(&m_Rect);


		CANYTOOLDlg::ControlAdaptive(cx, cy);


		//OpenGL To MFC EX
		//========================================================================
		MAIN_M_IOGL->OpenGL_TO_MFC__Init_ATENGINE(SCENE, cx, cy);
		//选择在GL_BACK缓存绘制图形，因为在SetWindowPixelFormat函数中设定了使用双缓存（PFD_DOUBLEBUFFER）
		glDrawBuffer(GL_BACK);
		//发出WM_PAINT消息，引起重新绘制，参数FALSE表示不需要Windows刷新背景，因为利用了OpenGL的glClear函数来刷新背景
		Invalidate(FALSE);
	}
}

void CANYTOOLDlg::OnMouseMove(UINT nType, CPoint Pos)
{
	SCENE->OnMouseMoveEvent(Pos.x, Pos.y);
}

//初始化代码放这
//===============================================
void CANYTOOLDlg::Init_DATA()
{
	m_Exit.SetFaceColor(RGB(43, 0, 85));
	m_Exit.m_bTransparent = FALSE;
	m_Exit.m_bDontUseWinXPTheme = TRUE;

	//CRect c;
	//m_Exit.GetWindowRect(&c);

	//m_Exit.MoveWindow(100,100,300,200);

	//控制台开启  或者属性->配置属性->生成事件->后期生成事件->命令行 中添加  editbin /subsystem:console $(OutDir)\$(TargetName).exe
	//AllocConsole();
	//FILE *Journal = NULL;
	//freopen_s(&Journal, "CONOUT$", "a+", stdout);

	MAIN_M_FUNCTION->INIT_CEditControl(&m_IPEdit, CString("IP"));
	MAIN_M_FUNCTION->INIT_CEditControl(&m_PortEdit, CString("Port"));
	MAIN_M_FUNCTION->INIT_CEditControl(&m_ThreadEdit, CString("Thread"));
	MAIN_M_FUNCTION->INIT_CEditControl(&m_VideoPath, CString("VideoPath"));
	MAIN_M_FUNCTION->INIT_CEditControl(&m_ImageType, CString("ImageType"));
	MAIN_M_FUNCTION->INIT_CEditControl(&m_FrameNumber, CString("FramePerSecond"));

	m_EditMusicProgress.SetRange(0, 100);
	m_EditMusicProgress.SetTicFreq(10);
	m_EditMusicVolume.SetRange(0, 100);
	m_EditMusicVolume.SetTicFreq(10);

	GetClientRect(&m_Rect);//Left 左上角的X top 为左上角的Y 后面的连个同理,是右下角的


	//OpenGL To MFC EX
	//========================================================================
	MAIN_M_IOGL->InitHDCTOMFC(this);
	MAIN_M_IOGL->OpenGL_TO_MFC__Init_ATENGINE(SCENE, m_Rect.Width(), m_Rect.Height());
	ATENGINE__ATUPDATEDATA__DRAW_BEGIN;



	//下边两个函数获取的是显示屏幕的大小，但不包括任务栏等区域
	//int cx = GetSystemMetrics(SM_CXFULLSCREEN);
	//int cy = GetSystemMetrics(SM_CYFULLSCREEN);
	////下边这两个函数获取的是真正屏幕的大小：屏幕分辨率
	//int nWidth = GetSystemMetrics(SM_CXSCREEN);  //屏幕宽度    
	//int nHeight = GetSystemMetrics(SM_CYSCREEN); //屏幕高度

}
//===============================================
void CANYTOOLDlg::OnBnClicked_StartLOIC()
{
	MAIN_M_FUNCTION->StartLOIC();
}
void CANYTOOLDlg::OnBnClicked_StartGoldWave()
{
	MAIN_M_FUNCTION->StartGoldWave();
}
void CANYTOOLDlg::OnBnClicked_StartLOICPLUS()
{
	MAIN_M_FUNCTION->StartLOICPLUS();
}
void CANYTOOLDlg::OnBnClicked_PasswordManager()
{
	MAIN_M_FUNCTION->PasswordManager();
}
void CANYTOOLDlg::OnBnClicked_GetComputerIP()
{
	MAIN_M_FUNCTION->Get_ComputerIP();
}
void CANYTOOLDlg::OnBnClicked_GetComputerName()
{
	MAIN_M_FUNCTION->Get_ComputerName();
}

void CANYTOOLDlg::OnBnClicked_OpenVideoFile()
{
	CString VideoPathName = MAIN_M_FUNCTION->CreateCFileDialog();
	if (!VideoPathName.IsEmpty())
	{
		MAIN_M_FUNCTION->Set_CEditControl(&m_VideoPath, VideoPathName);
		CString ImageType;
		CString FrameNumber;
		m_ImageType.GetWindowText(ImageType);
		m_FrameNumber.GetWindowText(FrameNumber);
		MAIN_M_FUNCTION->EditVideoBecomeFrame(VideoPathName, ImageType, FrameNumber);
	}
}

void CANYTOOLDlg::OnBnClicked_Sound__R()
{
	MAIN_M_FUNCTION->SoundRecording();
}

void CANYTOOLDlg::OnBnClicked_PlayMusic()
{
	MAIN_M_FUNCTION->PlayerMusic();
	if (MAIN_M_FUNCTION->IsPlayMusic() == 1)
	{
		MAIN_M_FUNCTION->InitMusicProgressInfoData(&m_MusicProgress, &m_EditMusicProgress, &m_EditMusicVolume, &m_PauseMusic);
		SETTIME_MUSICS__GETPROGRESSINFODATA__BEGIN_MUSIC;
	}
}

void CANYTOOLDlg::OnBnClicked_PauseMusic()
{
	MAIN_M_FUNCTION->PauseMusic();
}

//================================================
void CANYTOOLDlg::OnLButtonDown(UINT nFlags, CPoint point)
{


	std::cout << "鼠标左键按下！" << std::endl;
	std::cout << "坐标为 " << point.x << " " << point.y << std::endl;

	//设置一个定时器,1000毫秒调用
	SETTIME_BEGIN_DDOS

	

}

void CANYTOOLDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	std::cout << "鼠标右键键按下！" << std::endl;
	std::cout << "坐标为 " << point.x << " " << point.y << std::endl;

	//杀死一个定时器
	KILLTIME_END_DDOS
}

BOOL CANYTOOLDlg::PreTranslateMessage(MSG *pMsg)
{
	SCENE->OnOrdinaryKeyboardDownEvent(pMsg->wParam, 0, 0);
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CANYTOOLDlg::OnBnClicked_Begined()
{
	std::cout << "开始！" << std::endl;

	CString IP;
	CString Port;
	CString Thread;
	m_IPEdit.GetWindowText(IP);
	m_PortEdit.GetWindowText(Port);
	m_ThreadEdit.GetWindowText(Thread);

	MAIN_M_FUNCTION->Begined_TCP_DDOSAttack(IP,Port,Thread);
}

void CANYTOOLDlg::OnBnClicked_Ended()
{
	std::cout << "停止攻击！" << std::endl;
	MAIN_M_FUNCTION->Ended_TCP_DDOSAttack();
}

void CANYTOOLDlg::OnBnClicked_Exit()
{
	MAIN_M_FUNCTION->PauseMusic();
	ATENGINE__ATUPDATEDATA__DRAW_END;
	KILLTIME_MUSICS__GETPROGRESSINFODATA__END_MUSIC;
	ATA->UninstallAudioEngine();
	exit(0);
}

void CANYTOOLDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case MUSICS__GETPROGRESSINFODATA__:
	{
		if (MAIN_M_FUNCTION->IsPlayMusic() == 0)
		{
			KILLTIME_MUSICS__GETPROGRESSINFODATA__END_MUSIC;
		}
		else
		{
			MAIN_M_FUNCTION->GetMusicInfoDataFromATBAudioEngine();
		}
	}; break;
	case TYPE__ONE__:
	{
		std::cout << "一种恶意程序正在工作,请不要乱点击 ！" << std::endl;
		std::cout << "小白鼠,点击鼠标右键停止它的工作 ！" << std::endl;
		//小白鼠
		MAIN_M_FUNCTION->SOCKETDDOS(CString("180.97.33.107"),80);
	}; break;
	//OpenGL To MFC EX
	//========================================================================
	case ATENGINE__ATUPDATEDATA__DRAW:
	{
		CPaintDC dc(this);
		MAIN_M_IOGL->OpenGL_TO_MFC__Update_ATENGINE(SCENE);
		SwapBuffers(dc.GetSafeHdc());
	}; break;
	}
}

//===================================================================================
void CANYTOOLDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	m_nSBCode = nSBCode;
}
void CANYTOOLDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	std::cout << "OnVScroll nSBCode " << nSBCode << std::endl;
	std::cout << "OnVScroll nPos " << nPos << std::endl;

}
void CANYTOOLDlg::OnNMCustomdrawSlider_EditMusicProgress(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	UpdateData(TRUE);
	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	if (m_nSBCode == SB_THUMBTRACK)//滚动中
	{
		m_nSBCode = 0;
	}
	if (m_nSBCode == SB_ENDSCROLL)//结束滚动
	{
		MAIN_M_FUNCTION->SetMusicProgress();
		m_nSBCode = 0;
	}



	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	*pResult = 0;
	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	UpdateData(FALSE);

	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
}
void CANYTOOLDlg::OnNMCustomdrawSlider_EditMusicVolume(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	UpdateData(TRUE);
	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	if (m_nSBCode == SB_THUMBTRACK)//滚动中
	{
		m_nSBCode = 0;
	}
	if (m_nSBCode == SB_ENDSCROLL)//结束滚动
	{
		MAIN_M_FUNCTION->SetMusicVolume();
		m_nSBCode = 0;
	}


	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	UpdateData(FALSE);
	*pResult = 0;
	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
}

