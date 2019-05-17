#pragma once
#include "stdafx.h"
#include <Windows.h>
#include <vector>
#pragma comment(lib,"Msimg32.lib")

#define GoBitmap GameBitmap::Interface()
class GameBitmap
{
public:
	static GameBitmap *Interface()
	{
		static GameBitmap BMP;
		return &BMP;
	}
	void InitBmp(HWND hWnd, int w = 816, int h = 638);
	void LoadBmp(const char *BmpName, int w, int h);//ֻ�б���
	void LoadBmp(const char *BmpName, int w, int h, const char *Heroname, int wH, int hH);//�б�����Ӣ��
	void LoadHero_Bmp(const char *BmpName, int w, int h);//����ֻ��Ӣ�ۺ����Ŀ��
	void LoadArms_Bmp(const char *Heroname, int w, int h);//��������λͼ������ԭ���Ŀ��
	void Render_Hero_Arms_back_Bmp(int Mainx = 350, int Mainy = 250, int Mousex = 350, int Mousey = 250);//��ʾӢ���������뱳����������Ҫ����Ӣ�ۺ�����������
	void RenderBmp();
	void RenderbackBmp();//ֻ�б���ͼ
	void RenderBmp(int Mainx, int Mainy);//����Ӣ���ƶ�
	void Delete(HWND hWnd);

	//��ʦ��λͼ����
	//==============================================================
	void Init(HWND hWnd, HINSTANCE hInst);//��ʼ��
	HDC GetDC() { return mHDC; }
	HDC GetMDC() { return mMDC; }
	void Begin();
	void End();//mdc�����ǵ�hdc
	int Load_Bmp(const char *BmpName);
	int Load_Bmp(const char *BmpName, int w, int y);//����һ�£���Ϊ����ͼƬ
	void DrawBmp1(int bmpid, int sx, int sy, int w, int h, int srcx, int srcy);//��ͼ���1
	void DrawBmp2(int bmpid, int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh, DWORD color = RGB(255, 255, 255));//��ͼ���2
	void ReleaseBmp(int bmpid);
	void SetWorldTransform(XFORM &m);
	//ͼ��
	void DrawRectangle2(int cx, int cy, int w, int h, DWORD color1, DWORD color2);//�߿���ɫ�������ɫ
	 //��ʦ���ַ�������
	 //==============================================================
	int LoadFont(const char *FontName, int w, int h);//�������
	void DrawString_1(int Fontid, int sx, int sy, const char *string, int color = 0XFF00FF);//�ַ�����ʾ���1
private:
	GameBitmap() {}
	GameBitmap(const GameBitmap &data) {}
	HDC hdc, bdc, mdc;
	HBITMAP bmp, backbmp, Herobmp, Armsbmp;//��λͼ������ͼ��Ӣ��,����λͼ
	int m_w, m_h;//λͼʵ�ʵĿ��
	int mw, mh;//������ʵ�ʿ��
	int mh_w, mh_h; //ʵ�ʴ��ڵĿ��

	//��ʦ��λͼ����
	//==============================================================
	HDC mHDC, mMDC;//����mdc��hdc
	RECT mRect;
	HWND mhWnd; //���ھ��
	HINSTANCE mHinst; //ʵ�����
	std::vector<HDC> mBmps;//λͼ�б�
	int mWidth; //�ͻ����Ŀ�
	int mHeight; //�ͻ����ĸ�
	//��ʦ���ַ�������
	//==============================================================
	std::vector<HFONT> mFonts;//�����
};