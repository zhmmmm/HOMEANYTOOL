#include "stdafx.h"
#include "Bitbmp.h"
#include "Matrix3.h"

void GameBitmap::InitBmp(HWND hWnd, int w, int h)
{
	mh_w = w;
	mh_h = h;
	hdc = ::GetDC(hWnd); //�õ����ⲿһ���ľ���豸��
	mdc = CreateCompatibleDC(hdc);//��λͼ�豸
	bdc = CreateCompatibleDC(hdc); //����ͼ�豸
								   //����Ϊ�߼�ģʽ
	SetGraphicsMode(hdc, GM_ADVANCED);
	SetGraphicsMode(mdc, GM_ADVANCED);
	SetGraphicsMode(bdc, GM_ADVANCED);



	bmp = CreateCompatibleBitmap(hdc, mh_w, mh_h);
	SelectObject(mdc, bmp);//��λͼ���豸
}
void GameBitmap::LoadBmp(const char *BmpName, int w, int h)//����ֻ�б���ͼ
{
	m_w = w;
	m_h = h;
	backbmp = (HBITMAP)LoadImageA(NULL, BmpName, IMAGE_BITMAP, mh_w, mh_h, LR_LOADFROMFILE);//AΪchar*
}
void GameBitmap::LoadBmp(const char *BmpName, int w, int h, const char *Heroname, int wH, int hH)//�����б�����Ӣ��
{
	m_w = wH;
	m_h = hH;
	backbmp = (HBITMAP)LoadImageA(NULL, BmpName, IMAGE_BITMAP, mh_w, mh_h, LR_LOADFROMFILE);//AΪchar*
	Herobmp = (HBITMAP)LoadImageA(NULL, Heroname, IMAGE_BITMAP, wH, hH, LR_LOADFROMFILE);
}
void GameBitmap::LoadHero_Bmp(const char *Heroname, int w, int h)//����ֻ��Ӣ�ۺ����Ŀ��
{
	m_w = w;
	m_h = h;
	Herobmp = (HBITMAP)LoadImageA(NULL, Heroname, IMAGE_BITMAP, w, h, LR_LOADFROMFILE);//��ֻ��ʾԭ���Ŀ��
}
void GameBitmap::LoadArms_Bmp(const char *Armsname, int w, int h)//��������λͼ������ԭ���Ŀ��
{
	mw = w;
	mh = h;
	Armsbmp = (HBITMAP)LoadImageA(NULL, Armsname, IMAGE_BITMAP, w, h, LR_LOADFROMFILE);//��ֻ��ʾԭ���Ŀ��
}
void GameBitmap::Render_Hero_Arms_back_Bmp(int Mainx, int Mainy, int Mousex, int Mousey)//��ʾӢ���������뱳����������Ҫ����Ӣ�ۺ�����������,��Ҫ͸��
{
	//˭��˭�ڵ�
	SelectObject(bdc, backbmp);//����
	BitBlt(mdc, 0, 0, mh_w, mh_h, bdc, 0, 0, SRCCOPY);

	SelectObject(bdc, Herobmp);//Ӣ�۵�mdc
	TransparentBlt(mdc, Mainx, Mainy, m_w, m_h, bdc, 0, 0, m_w, m_h, 0xFFFFFF);

	SelectObject(bdc, Armsbmp);//������mdc
	TransparentBlt(mdc, Mousex, Mousey, mw, mh, bdc, 0, 0, mw, mh, 0xFF00FF);

	//float mAngle = 100.0f;
	//Matrix3 m;
	//m.Rotate_d(mAngle).Translate(Mousex, Mousey);
	//m.Identity();
	//SetWorldTransform(mdc, &m);

	BitBlt(hdc, 0, 0, mh_w, mh_h, mdc, 0, 0, SRCCOPY);
}
void GameBitmap::RenderBmp()//�б���ͼƬ��Ӣ��
{
	SelectObject(bdc, backbmp);
	BitBlt(mdc, 0, 0, mh_w, mh_h, bdc, 0, 0, SRCCOPY);

	SelectObject(bdc, Herobmp);
	TransparentBlt(mdc, 0, 0, m_w, m_h, bdc, 0, 0, m_w, m_h, 0xFF00FF);

	BitBlt(hdc, 0, 0, mh_w, mh_h, mdc, 0, 0, SRCCOPY);
}
void GameBitmap::RenderbackBmp()//��ʾֻ�б���ͼƬ
{
	SelectObject(bdc, backbmp);
	BitBlt(mdc, 0, 0, mh_w, mh_h, bdc, 0, 0, SRCCOPY);
	BitBlt(hdc, 0, 0, mh_w, mh_h, mdc, 0, 0, SRCCOPY);
}
void GameBitmap::RenderBmp(int Mainx, int Mainy)//����Ӣ���ƶ�
{
	SelectObject(bdc, backbmp);
	BitBlt(mdc, 0, 0, mh_w, mh_h, bdc, 0, 0, SRCCOPY);

	SelectObject(bdc, Herobmp);
	TransparentBlt(mdc, Mainx, Mainy, m_w, m_h, bdc, 0, 0, m_w, m_h, 0xFF00FF);

	BitBlt(hdc, 0, 0, mh_w, mh_h, mdc, 0, 0, SRCCOPY);
}
void GameBitmap::Delete(HWND hWnd)
{
	ReleaseDC(hWnd, hdc);

	DeleteObject(mdc);
	DeleteObject(bdc);
	DeleteObject(backbmp);
	DeleteObject(Herobmp);
	DeleteObject(Armsbmp);
	DeleteObject(bmp);
}

//��ʦ��λͼ����
//==============================================================
void GameBitmap::Init(HWND hWnd, HINSTANCE hInst)//��ʼ��
{
	mhWnd = hWnd;
	mHinst = hInst;

	mHDC = ::GetDC(hWnd);
	GetClientRect(hWnd, &mRect);
	mWidth = mRect.right - mRect.left;//�ͻ����Ŀ��
	mHeight = mRect.bottom - mRect.top;
	mMDC = CreateCompatibleDC(mHDC);//mdc�����ǵ�hdc�����
									//����Ϊ�߼�ģʽ
	SetGraphicsMode(mMDC, GM_ADVANCED);

	HBITMAP mBMP;//λͼ�ľ��
	mBMP = CreateCompatibleBitmap(mHDC, mWidth, mHeight);//�����ǿ�λͼ
	DeleteObject(SelectObject(mMDC, mBMP));
	DeleteObject(mBMP);
}
void GameBitmap::Begin()
{
	//��ǳ��ɫ������DC����ɫ����
	FillRect(mMDC, &mRect, (HBRUSH)GetStockObject(WHITE_BRUSH));
}
void GameBitmap::End()
{
	//mdc��hdc��
	BitBlt(mHDC, 0, 0, mWidth, mHeight, mMDC, 0, 0, SRCCOPY);
}
int GameBitmap::Load_Bmp(const char *BmpName)
{
	if (BmpName == NULL) { return -1; }
	HBITMAP bmp = (HBITMAP)LoadImageA(mHinst, BmpName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (bmp == NULL) { return -2; }

	HDC bdc = CreateCompatibleDC(mHDC);
	HBITMAP old = (HBITMAP)SelectObject(bdc, bmp);
	DeleteObject(old);
	DeleteObject(bmp);
	for (int i = 0; i < (int)mBmps.size(); i++)
	{
		if (mBmps[i] == NULL)
		{
			mBmps[i] = bdc;//д��������
			return i;
		}
	}
	mBmps.push_back(bdc);
	return (int)(mBmps.size() - 1);
}
int GameBitmap::Load_Bmp(const char *BmpName, int x, int y)
{
	if (BmpName == NULL) { return -1; }
	HBITMAP bmp = (HBITMAP)LoadImageA(mHinst, BmpName, IMAGE_BITMAP, x, y, LR_LOADFROMFILE);
	if (bmp == NULL) { return -2; }

	HDC bdc = CreateCompatibleDC(mHDC);
	HBITMAP old = (HBITMAP)SelectObject(bdc, bmp);
	DeleteObject(old);
	DeleteObject(bmp);
	for (int i = 0; i < (int)mBmps.size(); i++)
	{
		if (mBmps[i] == NULL)
		{
			mBmps[i] = bdc;//д��������
			return i;
		}
	}
	mBmps.push_back(bdc);
	return (int)(mBmps.size() - 1);
}
void GameBitmap::DrawBmp1(int bmpid, int sx, int sy, int w, int h, int srcx, int srcy)//��ͼ���1
{
	BitBlt(mMDC, sx, sy, w, h, mBmps[bmpid], srcx, srcy, SRCCOPY);//bdc��mdc
}
void GameBitmap::DrawBmp2(int bmpid, int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh, DWORD color)//��ͼ���2
{
	//λͼ��͸�����
	TransparentBlt(mMDC, dx, dy, dw, dh, mBmps[bmpid], sx, sy, sw, sh, color);//color��Ҫ͸������ɫ
}
void GameBitmap::ReleaseBmp(int bmpid)
{
	DeleteDC(mBmps[bmpid]);
	mBmps[bmpid] = NULL;
	DeleteDC(mHDC);
	DeleteDC(mMDC);
}
void GameBitmap::SetWorldTransform(XFORM &m)
{
	::SetWorldTransform(mMDC, &m);
}

void GameBitmap::DrawRectangle2(int cx, int cy, int w, int h, DWORD color1, DWORD color2)//�߿���ɫ�������ɫ
{
	HPEN hp = CreatePen(PS_SOLID, 1, color1);
	HPEN op = (HPEN)SelectObject(mMDC, hp);
	HBRUSH hb = CreateSolidBrush(color2);
	HBRUSH ob = (HBRUSH)SelectObject(mMDC, hb);
	Rectangle(mMDC, cx, cy, cx + w, cy + h);
	SelectObject(mMDC, op);
	SelectObject(mMDC, ob);
	DeleteObject(hp);
	DeleteObject(hb);
}
//��ʦ���ַ�������
//==============================================================
int GameBitmap::LoadFont(const char *FontName, int w, int h)//�������
{
	LOGFONTA font;

	font.lfHeight = h;
	font.lfWidth = w;
	font.lfEscapement = 0;
	font.lfOrientation = 0;
	font.lfWeight = FW_NORMAL;
	font.lfItalic = 0;
	font.lfUnderline = 0;
	font.lfStrikeOut = 0;
	font.lfCharSet = DEFAULT_CHARSET;
	font.lfOutPrecision = OUT_DEFAULT_PRECIS;
	font.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	font.lfQuality = DEFAULT_QUALITY;
	font.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	strcpy_s(font.lfFaceName, FontName);
	HFONT pf = CreateFontIndirectA(&font);

	for (int i = 0; i < (int)mFonts.size(); i++)
	{
		if (mFonts[i] == NULL)
		{
			mFonts[i] = pf;
			return i;
		}
	}
	mFonts.push_back(pf);
	return (int)(mFonts.size() - 1);
}
void GameBitmap::DrawString_1(int Fontid, int sx, int sy, const char *string, int color)//�ַ�����ʾ���1
{
	HFONT oldFont = NULL;
	if (Fontid<0 || Fontid >= (int)mFonts.size()) { return; }
	else {
		if (mFonts[Fontid] != NULL)
		{
			oldFont = (HFONT)SelectObject(mMDC, mFonts[Fontid]);
		}
	}
	SetBkMode(mMDC, TRANSPARENT);//�����ı��ı���Ϊ͸��
	//SetBkColor(mMDC,RGB(255,0,0));//�����ı�������ɫ
	SetTextColor(mMDC, color);
	TextOutA(mMDC, sx, sy, string, strlen(string));
	if (oldFont != NULL) { SelectObject(mMDC, oldFont); }
}