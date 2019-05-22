#pragma once
#include "OpenGL_AY_Engine.h"

class EXPORTDLL Sprite
{
	LPPIXCOLOR **m_BitMapRGBData = NULL;
	BITMAPFILEHEADER *m_bf = NULL;
	BITMAPINFOHEADER *m_bi = NULL;
	ATATPOS2D *m_Position = NULL;
	ATATSCALE2D *m_Scale = NULL;

	int m_SpriteState = 0;
public:
	Sprite();
	Sprite(const char *FileName);
	void *Create(const char *FileName);

	void SetSpriteScale(float X, float Y);
	//::::::::::::::::::::::::��������:::::::::::::::::::::::::::::::: ������ƵĿ�ʼλ�ó����ӿ�,��ô�ǻ��Ʋ�������
	void SetSpritePosition(float X, float Y);
	//float GetSpriteWidthAndHeight();

	LPPIXCOLOR *GetBitMapRGBData();

	void DrawSprite();
	//::::::::::::::::::::::::�������:::::::::::::::::::::::::::::::: void SetSpriteScale(float X, float Y); ��������Ч��
	void DrawSprite(float Width,float Height);
	//void DeleteSprite();
	~Sprite();
private:
	void InitSpriteInfoData();
	void DeleteSpriteInfoData();
};