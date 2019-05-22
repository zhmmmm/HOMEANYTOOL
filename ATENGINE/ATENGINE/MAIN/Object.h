#pragma once

#define EXPORTDLL        _declspec(dllexport)

class EXPORTDLL Object
{
public:
	int m_Windows_X = 100;
	int m_Windows_Y = 100;
	int m_WindowsWidth = 800;
	int m_WindowsHeight = 600;
	int m_CurWindowsWidth = 0;
	int m_CurWindowsHeight = 0;

	//����������λ��
	float m_LookAt_X = 0;
	float m_LookAt_Y = 0;
	float m_LookAt_Z = 0;

	//�������λ��
	float m_CameraPos_X = 0;
	float m_CameraPos_Y = 50;
	float m_CameraPos_Z = 200;

	float m_MoveSpeed_X = 10.0f;
	float m_MoveSpeed_Y = 10.0f;
	float m_MoveSpeed_Z = 10.0f;


	virtual void Start();
	virtual void Update();
	virtual void End();

	//��ͨ���̰����ص�
	virtual void OnOrdinaryKeyboardDownEvent(unsigned char Key, int X, int Y);
	virtual void OnOrdinaryKeyboardUpEvent(unsigned char Key, int X, int Y);
	//���ܼ��̰����ص�
	virtual void OnSpecialKeyboardDownEvent(int Key, int X, int Y);
	virtual void OnSpecialKeyboardUpEvent(int Key, int X, int Y);
	//���ص�
	//��������ĵ���¼�
	//:::::::::::::::::::::::::::::::::::::::::::::::::::������ǰ���ֺ���� 0,1,2,3,4   :::::::::::::::::::::����̧�� 0,1
	virtual void OnMouseClickEvent(int Button, int State, int Mouse_X, int Mouse_Y);
	//��껬��
	virtual void OnMouseMoveEvent(int Mouse_X, int Mouse_Y);
	//�����ק
	virtual void OnMousePassiveEvent(int Mouse_X, int Mouse_Y);
};
