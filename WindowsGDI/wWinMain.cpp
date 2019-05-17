#include "Game.h"

//===========================================
Game *GameObj = NULL;
//===========================================
//�ص���������
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
int __stdcall wWinMain(HINSTANCE hInstance,//���ڵ�ʵ�����
	HINSTANCE hPrevInstance,//ǰһ��ʵ�����
	LPTSTR    lpCmdLine,//������
	int       nCmdShow)//��ʾ��ʽ
{
	GameObj = new Game();
	//ע�ᴰ����
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"GameWindow";
	wcex.hIconSm = NULL;
	RegisterClassEx(&wcex);

	//�ͻ�����С
	RECT wndrc = { 0, 0, 800, 600 };
	AdjustWindowRect(&wndrc, WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_SYSMENU, FALSE);

	int screen_w = GetSystemMetrics(SM_CXSCREEN);
	int screen_h = GetSystemMetrics(SM_CYSCREEN);
	int wnd_w = wndrc.right - wndrc.left;
	int wnd_h = wndrc.bottom - wndrc.top;

	//��������
	HWND hWnd = CreateWindow(
		L"GameWindow", //��������
		L"Game", //���ڵı���
		WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_SYSMENU,//���ڷ��
		(screen_w - wnd_w) / 2, //������ʾ�����������x
		(screen_h - wnd_h) / 2, //������ʾ�����������y  (screen_h - wnd_h) / 2 - 2
		wnd_w, //�������ڵĿ������ͻ���
		wnd_h, //�������ڵĸߣ������ͻ���
		NULL, //�����ھ������0��ʾ������������
		NULL, //�˵����
		hInstance, //
		NULL);
	if (!hWnd)//������ڲ�����NULL˵���������ڳɹ�
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);//��ʾ����
	UpdateWindow(hWnd);

	//���صĴ�������(1)HDC hdc = GetDC(hWnd);�ͷ�	ReleaseDC(hWnd, hdc);
	//========================================================
	HDC hdc = GetDC(hWnd);
	GameObj->InitGame(hdc, hWnd, hInstance);
	//===================================================

	//������Ϣѭ��
	MSG msg;
	// ����Ϣѭ��:
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//��Ϸ�߼�����Ⱦ,�ڴ�����ʾ֮��᲻���������߼�д����ſ���(1)
			//===================================================
			GameObj->RunGame(hdc, hWnd, hInstance);
			//===================================================
			//InvalidateRect(hWnd, NULL, FALSE);//ˢ��
		}
	}
	//�ͷ���Դ����
	//===============================================
	GameObj->GameOver();
	delete GameObj;
	//===============================================
	return (int)msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	MouseMessage stame;
	memset(&stame, 0, sizeof(stame));
	KeyMessage Stame;
	memset(&Stame, 0, sizeof(Stame));
	HDC hdc;
	PAINTSTRUCT ps;//���ƻ�����Ϣ
	switch (message)
	{
	case WM_PAINT://��һ�δ��ڴ�����ʱ��
	{
		hdc = BeginPaint(hWnd, &ps);
		// TODO: �ڴ���������ͼ����...(2)
		//===================================================

		//===================================================
		EndPaint(hWnd, &ps);
	}; break;
	case WM_CREATE://������Լ�����Դ��ͼƬ�������Ӵ��ڵ�(2)
	{
		//============================================================
		//============================================================
	}; break;
	case WM_KEYDOWN://�����������
	{
		Stame.Which = wParam;
		Stame.State = 1;
		GameObj->GameKeyMessage(Stame);
	}; break;
	case WM_KEYUP://����̧��
	{
		Stame.Which = wParam;
		Stame.State = 0;
		GameObj->GameKeyMessage(Stame);
	}; break;
	case WM_LBUTTONDOWN: //����������
	{
		//MessageBox(hWnd, L"����������", L"�����Ϣ", 0);
		stame.Which = 1;
		stame.State = 1;
		stame.x = LOWORD(lParam);
		stame.y = HIWORD(lParam);
		GameObj->GameMouseMessage(stame);

	}; break;
	case WM_LBUTTONUP://������̧��
	{
		//MessageBox(hWnd, L"������̧��", L"�����Ϣ", 0);
		stame.Which = 1;
		stame.State = 0;
		stame.x = LOWORD(lParam);
		stame.y = HIWORD(lParam);
		GameObj->GameMouseMessage(stame);
	}; break;
	case WM_LBUTTONDBLCLK://������˫��
	{}; break;
	case WM_RBUTTONDOWN://����Ҽ�����
	{}; break;
	case WM_RBUTTONUP://����Ҽ�̧��
	{}; break;
	case WM_MOUSEMOVE://����ƶ���Ϣ
	{
		//stame.x = LOWORD(lParam);
		//stame.y = HIWORD(lParam);
		//GameObj->GameMouseMessage(stame);
	}; break;
	case WM_MOUSEWHEEL://��������Ϣ
	{}; break;
	case WM_SIZE: {}; break;//���ڴ�С�ı���Ϣ
	case WM_DESTROY://������������ڴ桢�ͷ���Դ��
	{
		//============================================================

		//============================================================
		PostQuitMessage(0);
	}; break;
	default:return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


