#pragma once
#include <iostream>
#include <Windows.h>


struct KeyMessage//������Ϣ
{
	int Which;//��һ����
	int State;//���»���̧��
};
struct MouseMessage//�����Ϣ
{
	int Which;//�����һ����
	int State;//���»���̧��
	int x;//�������
	int y;
};
struct COOR
{
	int x;
	int y;
};

class Game
{

public:
	Game()
	{

	}
	void InitPiece()
	{

	}
	void InitGame(HDC hdc, HWND hWnd, HINSTANCE hInst)
	{

	}
	void RenderGame(HDC hdc, HWND hWnd, HINSTANCE hInst)
	{

	}
	void GameLogic_Updata(HDC hdc, HWND hWnd, HINSTANCE hInst)
	{
		
	}
	void RunGame(HDC hdc, HWND hWnd, HINSTANCE hInst)
	{
		static DWORD lasttime = 0;//��̬�ľֲ�����
		DWORD curtime = GetTickCount();
		if (curtime - lasttime >= 60)
		{

			lasttime = curtime;
		}

		//������ֱ�ӻ��Ƶ�hdc�ϵ�

	}
	void GameOver(){}
	void GameKeyMessage(KeyMessage Key)
	{

	}
	void GameMouseMessage(MouseMessage MouseMsge)
	{

	}

	~Game()
	{

	}
};