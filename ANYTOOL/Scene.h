#pragma once
#define MAINATENGINE "ATENGINE/MAIN/OpenGL_AY_Engine.h"
#include MAINATENGINE


///*

///��ͨ���̰����ص�
/// void OnOrdinaryKeyboardDownEvent(unsigned char Key, int X, int Y);
///std::cout << "��ͨ���£�" << Key << " X = " << X << " Y = " << Y << std::endl;
/// void OnOrdinaryKeyboardUpEvent(unsigned char Key, int X, int Y);
///std::cout << "��̧ͨ��" << Key << " X = " << X << " Y = " << Y << std::endl;
///���ܼ��̰����ص�
/// void OnSpecialKeyboardDownEvent(int Key, int X, int Y);
///std::cout << "���ܰ��£�" << Key << " X = " << X << " Y = " << Y << std::endl;
/// void OnSpecialKeyboardUpEvent(int Key, int X, int Y);
///std::cout << "����̧��" <<Key<<" X = "<<X<<" Y = "<<Y<< std::endl;
///���ص�
///��������ĵ���¼�
///:::::::::::::::::::::::::::::::::::::::::::::::::::������ǰ���ֺ���� 0,1,2,3,4   :::::::::::::::::::::����̧�� 0,1
/// void OnMouseClickEvent(int Button, int State, int Mouse_X, int Mouse_Y);
///std::cout << "Button =" << Button << " State = " << State << " X = " << X << " Y = " << Y << std::endl;
///��껬��
/// void OnMouseMoveEvent(int Mouse_X, int Mouse_Y);
///std::cout << "����ƶ� " << "X = " << Mouse_X << " Y = " << Mouse_Y << std::endl;
///�����ק
/// void OnMousePassiveEvent(int Mouse_X, int Mouse_Y);
///std::cout << "�����ק " << "X = " << Mouse_X << " Y = " << Mouse_Y << std::endl;


///float Angle = 0;
///float p = 0;
///Sprite *S = NULL;
///S = new Sprite();
///S->Create("1.bmp");

///S->SetSpriteScale(-2.0, 1);
///S->DrawSprite();
///===============================================================================
///ATENGINE->ATENGINE_MatrixMode();
///ATENGINE->Rotate(++Angle, 0, 0, 1);
///ATENGINE->CreateTriangle(ATATRGB::RED, ATATPOS2D(-100, 0),
	///ATATRGB::GREEN, ATATPOS2D(100, 0), ATATRGB::WHITE, ATATPOS2D(0, 100));
///ATENGINE->DrawEnd();

///*///



class Scene:public Object
{
	float Angle = 0;
	float p = 0;

	Sprite *S = NULL;
public:
	virtual void Start();
	virtual void Update();
	virtual void End();

	//��ͨ���̰����ص�
	virtual void OnOrdinaryKeyboardDownEvent(unsigned char Key, int X, int Y);

	virtual void OnMouseMoveEvent(int Mouse_X, int Mouse_Y);
};