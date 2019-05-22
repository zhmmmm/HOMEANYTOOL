#pragma once
#include "MAIN_FUNCTION.h"

#define MAIN_M_FUNCTION             (&(m_Function))
#define ANYTOOLWINDOWS             CANYTOOLDlg
#define MAIN_M_IOGL                        (&(m_ImplantOpenGL))
#define SCENE                                       (&(m_Object))


// CANYTOOLDlg 对话框
class CANYTOOLDlg : public CDialogEx
{

	MAIN m_Function;
	IOGL m_ImplantOpenGL;
	Scene m_Object;

// 构造
public:
	CANYTOOLDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANYTOOL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	void Init_DATA();
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType,int cx,int cy);
	afx_msg void OnMouseMove(UINT nType, CPoint Pos);
	void ControlAdaptive(int X, int Y);

	DECLARE_MESSAGE_MAP()//消息映射宏

	virtual BOOL PreTranslateMessage(MSG *pMsg);
public:
	afx_msg void OnBnClicked_StartLOIC();
	afx_msg void OnBnClicked_StartGoldWave();
	afx_msg void OnBnClicked_StartLOICPLUS();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags,CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

private:
	CEdit m_IPEdit;
	CEdit m_PortEdit;
	CEdit m_ThreadEdit;
public:
	CMFCButton m_Exit;
	afx_msg void OnBnClicked_Exit();
	afx_msg void OnBnClicked_Begined();
	afx_msg void OnBnClicked_Ended();

	afx_msg void OnBnClicked_PasswordManager();
	afx_msg void OnBnClicked_GetComputerIP();
	afx_msg void OnBnClicked_GetComputerName();
	afx_msg void OnBnClicked_OpenVideoFile();
	afx_msg void OnBnClicked_Sound__R();
	afx_msg void OnBnClicked_PlayMusic();
	afx_msg void OnBnClicked_PauseMusic();

	CEdit m_VideoPath;
	CEdit m_ImageType;
	CEdit m_FrameNumber;
public:
	CProgressCtrl m_MusicProgress;
	CSliderCtrl m_EditMusicProgress;
	CSliderCtrl m_EditMusicVolume;
	CMFCButton m_PauseMusic;
	UINT m_nSBCode = 0;
	afx_msg void OnNMCustomdrawSlider_EditMusicProgress(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider_EditMusicVolume(NMHDR *pNMHDR, LRESULT *pResult);

public:
	CRect m_Rect;
};
