/*===================================================*\
|                                                     |
|  EASY-SIZE Macros                                   |
|                                                     |
|  Copyright (c) 2001 - Marc Richarme                 |
|      devix@devix.cjb.net                            |
|      http://devix.cjb.net                           |
|                                                     |
|  License:                                           |
|                                                     |
|  You may use this code in any commersial or non-    |
|  commersial application, and you may redistribute   |
|  this file (and even modify it if you wish) as      |
|  long as you keep this notice untouched in any      |
|  version you redistribute.                          |
|                                                     |
|  Usage:                                             |
|                                                     |
|  - Insert 'DECLARE_EASYSIZE' somewhere in your      |
|    class declaration                                |
|  - Insert an easysize map in the beginning of your  |
|    class implementation (see documentation) and     |
|    outside of any function.                         |
|  - Insert 'INIT_EASYSIZE;' in your                  |
|    OnInitDialog handler.                            |
|  - Insert 'UPDATE_EASYSIZE' in your OnSize handler  |
|  - Optional: Insert 'EASYSIZE_MINSIZE(mx,my);' in   |
|    your OnSizing handler if you want to specify     |
|    a minimum size for your dialog                   |
|                                                     |
|        Check http://devix.cjb.net for the           |
|              docs and new versions                  |
|                                                     |
\*===================================================*/


#ifndef __EASYSIZE_H_
#define __EASYSIZE_H_
#define ES_BORDER 0xffffffff
#define ES_KEEPSIZE 0xfffffffe
#define ES_HCENTER 0x00000001
#define ES_VCENTER 0x00000002
#define DECLARE_EASYSIZE \
void __ES__RepositionControls(BOOL bInit);\
void __ES__CalcBottomRight(CWnd *pThis, BOOL bBottom, int &bottomright, int &topleft, UINT id, UINT br, int es_br, CRect &rect, int clientbottomright);
#define INIT_EASYSIZE __ES__RepositionControls(TRUE); __ES__RepositionControls(FALSE)
#define UPDATE_EASYSIZE if(GetWindow(GW_CHILD)!=NULL) __ES__RepositionControls(FALSE)
#define EASYSIZE_MINSIZE(mx,my,s,r) if(r->right-r->left < mx) { if((s == WMSZ_BOTTOMLEFT)||(s == WMSZ_LEFT)||(s == WMSZ_TOPLEFT)) r->left = r->right-mx; else r->right = r->left+mx; } if(r->bottom-r->top < my) { if((s == WMSZ_TOP)||(s == WMSZ_TOPLEFT)||(s == WMSZ_TOPRIGHT)) r->top = r->bottom-my; else r->bottom = r->top+my; }
#define BEGIN_EASYSIZE_MAP(class) \
void class::__ES__CalcBottomRight(CWnd *pThis, BOOL bBottom, int &bottomright, int &topleft, UINT id, UINT br, int es_br, CRect &rect, int clientbottomright) {\
if(br==ES_BORDER) bottomright = clientbottomright-es_br;\
else if(br==ES_KEEPSIZE) bottomright = topleft+es_br;\
else { CRect rect2;\
pThis->GetDlgItem(br)->GetWindowRect(rect2); pThis->ScreenToClient(rect2);\
bottomright = (bBottom?rect2.top:rect2.left) - es_br;}}\
void class::__ES__RepositionControls(BOOL bInit) { CRect rect,rect2,client; GetClientRect(client);
#define END_EASYSIZE_MAP Invalidate(); UpdateWindow(); }
#define EASYSIZE(id,l,t,r,b,o) \
static int id##_es_l, id##_es_t, id##_es_r, id##_es_b;\
if(bInit) {\
GetDlgItem(id)->GetWindowRect(rect); ScreenToClient(rect);\
if(o & ES_HCENTER) id##_es_l = rect.Width()/2; else {\
if(l==ES_BORDER) id##_es_l = rect.left; else if(l==ES_KEEPSIZE) id##_es_l = rect.Width(); else {\
	GetDlgItem(l)->GetWindowRect(rect2); ScreenToClient(rect2);\
	id##_es_l = rect.left-rect2.right;}}\
if(o & ES_VCENTER) id##_es_t = rect.Height()/2; else {\
if(t==ES_BORDER) id##_es_t = rect.top; else if(t==ES_KEEPSIZE) id##_es_t = rect.Height(); else {\
	GetDlgItem(t)->GetWindowRect(rect2); ScreenToClient(rect2);\
	id##_es_t = rect.top-rect2.bottom;}}\
if(o & ES_HCENTER) id##_es_r = rect.Width(); else { if(r==ES_BORDER) id##_es_r = client.right-rect.right; else if(r==ES_KEEPSIZE) id##_es_r = rect.Width(); else {\
	GetDlgItem(r)->GetWindowRect(rect2); ScreenToClient(rect2);\
	id##_es_r = rect2.left-rect.right;}}\
if(o & ES_VCENTER) id##_es_b = rect.Height(); else  { if(b==ES_BORDER) id##_es_b = client.bottom-rect.bottom; else if(b==ES_KEEPSIZE) id##_es_b = rect.Height(); else {\
	GetDlgItem(b)->GetWindowRect(rect2); ScreenToClient(rect2);\
	id##_es_b = rect2.top-rect.bottom;}}\
} else {\
int left,top,right,bottom; BOOL bR = FALSE,bB = FALSE;\
if(o & ES_HCENTER) { int _a,_b;\
if(l==ES_BORDER) _a = client.left; else { GetDlgItem(l)->GetWindowRect(rect2); ScreenToClient(rect2); _a = rect2.right; }\
if(r==ES_BORDER) _b = client.right; else { GetDlgItem(r)->GetWindowRect(rect2); ScreenToClient(rect2); _b = rect2.left; }\
left = _a+((_b-_a)/2-id##_es_l); right = left + id##_es_r;} else {\
if(l==ES_BORDER) left = id##_es_l;\
else if(l==ES_KEEPSIZE) { __ES__CalcBottomRight(this,FALSE,right,left,id,r,id##_es_r,rect,client.right); left = right-id##_es_l;\
} else { GetDlgItem(l)->GetWindowRect(rect2); ScreenToClient(rect2); left = rect2.right + id##_es_l; }\
if(l != ES_KEEPSIZE) __ES__CalcBottomRight(this,FALSE,right,left,id,r,id##_es_r,rect,client.right);}\
if(o & ES_VCENTER) { int _a,_b;\
if(t==ES_BORDER) _a = client.top; else { GetDlgItem(t)->GetWindowRect(rect2); ScreenToClient(rect2); _a = rect2.bottom; }\
if(b==ES_BORDER) _b = client.bottom; else { GetDlgItem(b)->GetWindowRect(rect2); ScreenToClient(rect2); _b = rect2.top; }\
top = _a+((_b-_a)/2-id##_es_t); bottom = top + id##_es_b;} else {\
if(t==ES_BORDER) top = id##_es_t;\
else if(t==ES_KEEPSIZE) { __ES__CalcBottomRight(this,TRUE,bottom,top,id,b,id##_es_b,rect,client.bottom); top = bottom-id##_es_t;\
} else { GetDlgItem(t)->GetWindowRect(rect2); ScreenToClient(rect2); top = rect2.bottom + id##_es_t; }\
if(t != ES_KEEPSIZE) __ES__CalcBottomRight(this,TRUE,bottom,top,id,b,id##_es_b,rect,client.bottom);}\
GetDlgItem(id)->MoveWindow(left,top,right-left,bottom-top,FALSE);\
}
#endif //__EASYSIZE_H_

/*
假设创建的对话框的类名是CMyDlg，具体过程如下：

步骤一：在CMyDlg对话框界面单击右键进入对话框的属性设置界面，将Border设置为Resizing；将Maximize box和Minimize box均设置为True；

步骤二：把easysize.h拷贝到CMyDlg项目文件夹中，同时在CMyDlg的.h文件和.cpp文件中加入#include "easysize.h"；


步骤三：在CMyDlg类的h文件中，加入DECLARE_EASYSIZE，注意结尾处不要加“；


// CMyDlg 对话框
class CMyDlg : public CDialog
{
       DECLARE_EASYSIZE
// 构造
public:
CMyDlg (CWnd* pParent = NULL);// 标准构造函数

……
}

步骤四：在CMyDlg类的OnInitDialog()函数的结尾处加入INIT_EASYSIZE, 注意此处结尾处要加“；


// CMyDlg 消息处理程序
BOOL CMyDlg::OnInitDialog()
{ 
CDialogEx::OnInitDialog();
// TODO: 在此添加额外的初始化代码

       INIT_EASYSIZE;
return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

步骤五：选中对话框编辑界面，右键进入类向导，选中WM_SIZE消息，点击右边“添加处理程序”，增加WM_SIZE消息响应函数OnSize()，在函数中加入UPDATE_EASYSIZE，注意此处结尾处要加“，WM_SIZING处理程序同此方法。

//最大化
void CMyDlg::OnSize(UINT nType, int cx, int cy)
{
CDialogEx::OnSize(nType, cx, cy);

// TODO: 在此处添加消息处理程序代码
UPDATE_EASYSIZE;
}

//如果需要限制对话框有一个最小尺寸，在OnSizing消息的响应函数添加EASYSIZE_MINSIZE(600, 400, fwSide, pRect)，其中600、400为最小的长高尺寸

void CMyDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
CDialogEx::OnSizing(fwSide, pRect);

// TODO: 在此处添加消息处理程序代码
EASYSIZE_MINSIZE(600, 400, fwSide, pRect);
}

步骤六：在CMyDlg的cpp文件中添加EASYSIZE 的宏映射

BEGIN_EASYSIZE_MAP(CMyDlg)

//EASYSIZE(Control_ID,left,top,right,bottom,options)

EASYSIZE(IDC_COMBO_COMMON,ES_BORDER,ES_BORDER,ES_BORDER,ES_KEEPSIZE,0)
EASYSIZE(IDC_BUTTON_OPEN,IDC_COMBO_COMMON,ES_BORDER,ES_BORDER,ES_KEEPSIZE,0)
EASYSIZE(IDC_BUTTON_CLOSE,IDC_BUTTON_OPEN,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,0)
EASYSIZE(IDC_EDIT_RECEVE,ES_BORDER,ES_KEEPSIZE,ES_BORDER,IDC_BUTTON_CLR_RXBUF,ES_HCENTER)
EASYSIZE(IDC_EDIT_SEND,IDC_BUTTON_CLOSE,ES_BORDER,ES_BORDER,ES_BORDER,0)
EASYSIZE(IDC_BUTTON_SETMAXSEND,ES_BORDER,ES_KEEPSIZE,ES_BORDER,ES_BORDER,0)
EASYSIZE(IDC_BUTTON_SETMAXRECV,ES_KEEPSIZE,ES_KEEPSIZE,ES_BORDER,ES_BORDER,0)
EASYSIZE(IDC_BUTTON_ALLSEND,ES_KEEPSIZE,ES_KEEPSIZE,ES_BORDER,ES_BORDER,0)
EASYSIZE(IDC_BUTTON_ALLRECEVE,ES_BORDER,ES_BORDER,ES_BORDER,ES_KEEPSIZE,0)
EASYSIZE(IDC_BUTTON_SEND,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,0)
EASYSIZE(IDC_BUTTON_AUTO_PICK,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,ES_BORDER,0)
EASYSIZE(IDC_BUTTON_END_PICK,IDC_BUTTON_AUTO_PICK,ES_KEEPSIZE,ES_KEEPSIZE,ES_BORDER,0)
EASYSIZE(IDC_STATIC_SEND1,IDC_BUTTON_END_PICK,ES_KEEPSIZE,ES_KEEPSIZE,ES_BORDER,0)
EASYSIZE(IDC_STATIC_SEND_COUNT,IDC_STATIC_SEND1,ES_KEEPSIZE,ES_KEEPSIZE,ES_BORDER,0)
EASYSIZE(IDC_STATIC_COUNT,IDC_STATIC_SEND_COUNT,ES_KEEPSIZE,ES_KEEPSIZE,ES_BORDER,0)
EASYSIZE(IDC_STATIC_NUM,IDC_STATIC_COUNT,ES_KEEPSIZE,ES_KEEPSIZE,ES_BORDER,0)
END_EASYSIZE_MAP
注意：如果没有添加EASYSIZE 的宏映射就开始编译的话，会出现链接错误！



二、EASYSIZE使用方法
这里需要解释的是宏EASYSIZE()的用法，其原型如下：
EASYSIZE(control,left,top,right,bottom,options)
该宏表示对ID值为control的控件实施缩放效果，缩放后的上下左右位置由control,left,top,right,bottom来确定，大小由option确定。

其中：control为对话框中的控件ID值，left,top,right,bottom四个参数为控件位置的坐标，其值可以选择ES_BOARD,ES_KEEPSIZE, 控件ID值三者之一。Options可以为ES_HCENTER, ES_VCENTER的结合，options可置0。

ES_BOARD表示控件与对话框边界（以下简称边界）的距离；

ES_KEEPSIZE表示控件水平/垂直方向上尺寸保持不变；

控件ID值表示当前控件与指定控件之间的距离；

ES_HCENTER表示缩放后控件在指定位置内水平居中；

ES_VCENTER表示缩放后控件在指定位置内垂直居中；

例如：

EASYSIZE(IDOK,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,0)
表示缩放后，值为IDOK的控件，距离边界上下左右位置保持不变，水平和垂直方向尺寸拉伸；


EASYSIZE(IDOK,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,ES_HCENTER)
表示缩放后，值为IDOK的控件，距离边界上下位置保持不变，垂直方向尺寸拉伸，水平居中；

EASYSIZE(IDOK,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,ES_HCENTER| ES_HCENTER)
表示缩放后，值为IDOK的控件，在对话框内垂直居中，水平居中；

EASYSIZE(IDOK,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,ES_BORDER,0)
表示缩放后，值为IDOK的控件，距离边界左、下方位置保持不变，同时保持控件尺寸；

EASYSIZE(IDOK,ES_BORDER,ES_KEEPSIZE, ES_BORDER,ES_BORDER,0)
表示缩放后，值为IDOK的控件，距离边界左、右、下方位置保持不变，水平方向尺寸拉伸，垂直方向尺寸不变；

EASYSIZE(IDOK,ES_BORDER,ES_BORDER,IDCANCEL,ES_BORDER,0)
表示缩放后，值为IDOK的控件，距离边界上下左位置保持不变，距离ID值为IDCANCEL的右方位置距离保持不变，水平和垂直方向尺寸拉伸；（当使用指定控件作为定位参数时候，确保指定控件的EASYSIZE在该宏前面）

*/