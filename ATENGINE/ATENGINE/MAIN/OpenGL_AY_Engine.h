#pragma once
#include <iostream>
#include <glew.h>//OpenGLͷ�ļ�
#include <glut.h>//��������OpenGL������غ���
#include "OpenGLDefine/OpenGL_Define.h"
#include <Windows.h>
#pragma comment(lib, "glew32.lib")

#include "HeaderFile/HeaderFile.h"

#define EXPORTDLL        _declspec(dllexport)

#define ATENGINE           ATEngine::Interface()

#define AT ATENGINE

#define ATVARIABLE       ATEngine_Variable::Interface()

#define CLS system("cls");

#define ATENGINE_MAINDRAW(MAINDRAW) \
               ATENGINE->ATENGINE_OnRuning(MAINDRAW);

#define ATENGINE_ONWINDOWSCHANGE(ONWINDOWSCHANGE) \
               ATENGINE->ATENGINE_OnWindowsChange(ONWINDOWSCHANGE);

#define ATENGINE_ONIDLE(ONIDLE) \
               ATENGINE->ATENGINE_OnIdle(ONIDLE);

#define ATENGINE_ONORDINARYKEYBOARDDOWN(ONORDINARYKEYBOARDDOWN) \
               ATENGINE->ATENGINE_OnOrdinaryKeyboardDownEvent(ONORDINARYKEYBOARDDOWN);

#define ATENGINE_ONSPECIAKEYBOARDDOWN(ONSPECIAKEYBOARDDOWN) \
               ATENGINE->ATENGINE_OnSpecialKeyboardDownEvent(ONSPECIAKEYBOARDDOWN);

#define ATENGINE_ONORDINARYKEYBOARDUP(ONORDINARYKEYBOARDUP) \
               ATENGINE->ATENGINE_OnOrdinaryKeyboardUpEvent(ONORDINARYKEYBOARDUP);

#define ATENGINE_ONSPECIAKEYBOARDUP(ONSPECIAKEYBOARDUP) \
               ATENGINE->ATENGINE_OnSpecialKeyboardUpEvent(ONSPECIAKEYBOARDUP);

#define ATENGINE_ONMOUSECILCKEVENT(ONMOUSECILCKEVENT) \
               ATENGINE->ATENGINE_OnMouseClickEvent(ONMOUSECILCKEVENT);

#define ATENGINE_ONMOUSEMOVEEVENT(ONMOUSEMOVEEVENT) \
               ATENGINE->ATENGINE_OnMouseMoveEvent(ONMOUSEMOVEEVENT);

#define ATENGINE_ONMOUSEPASSIVEEVENT(ONMOUSEPASSIVEEVENT) \
               ATENGINE->ATENGINE_OnMousePassiveEvent(ONMOUSEPASSIVEEVENT);

//��������
#define ATENGINE_ONTIMEREND(MILLISECOND,ONTIMEREND,TIMERID) \
               ATENGINE->ATENGINE_OnSetTimerEnd((MILLISECOND), (ONTIMEREND), (TIMERID));


class EXPORTDLL ATROOT
{
public:
	BITMAPFILEHEADER m_bf;
	BITMAPINFOHEADER m_bi;
	LPPIXCOLOR *m_BitMapRGBData = NULL;

	ATROOT();
	~ATROOT();
	/*
	LPPIXCOLOR *RGBData = NULL;
		ATENGINE->LoadBitMap("1.bmp", &RGBData);
		glBegin(GL_POINTS);
				for (int i = 0; i < ATENGINE->GetBitMapHeight(); i++)
					{
						for (int j = 0; j < ATENGINE->GetBitMapWidth(); j++)
							{
								glColor3f(RGBData[i][j].R / 255.0f, RGBData[i][j].G / 255.0f, RGBData[i][j].B / 255.0f);
								glVertex2f(j,i);
							}
					}
	glEnd();
	*/
	//::::::::::::::::::::::::��������::::::::::::::::::::::::::::::::��Ҫ�ֶ��ͷ�
	int LoadBitMap(const char *FileName, LPPIXCOLOR **BitMapData);
	/*
	LPPIXCOLOR *RGBData = NULL;
	ATENGINE->LoadBitMapRGBData("1.bmp", &RGBData);
	glRasterPos2f(0, 0);
	glPixelZoom(1, 1);
	glDrawPixels(
		ATENGINE->GetBitMapWidth(), ATENGINE->GetBitMapHeight(),
		GL_BGR_EXT, GL_UNSIGNED_BYTE,
		RGBData);
	*/
	//:::::::::::::::::::::::::��������:::::::::::::::::::::::::::::::��Ҫ�ֶ��ͷ�
	int LoadBitMapRGBData(const char *FileName, LPPIXCOLOR **BitMapRGBData);
	//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::����Ҫ�ֶ��ͷ�
	LPPIXCOLOR **LoadBitMapRGBData(const char *FileName);
	//�ͷŵ����ⲿ�ļ��ص�λͼ����
	void DeleteBitMap(LPPIXCOLOR **BitMapData);

	//ֱ�ӻ�����ɫ����
	//:::::::::::::::::::::::::::::::::::::GL_RGB:::::::::::::::: GL_UNSIGNED_BYTE
	void DrawRGB_DATA(float Begin_X, float Begin_Y, float Scale_X, float Scale_Y, float Width, float Height, unsigned int Format = GL_RGB, unsigned int DataType = GL_UNSIGNED_BYTE, void *RGB = NULL);
	void DrawRGB_DATA(ATATPOS2D Begin, ATATSCALE2D Scale, ATATCONTENTSIZE Size, unsigned int Format = GL_RGB, unsigned int DataType = GL_UNSIGNED_BYTE, void *RGB = NULL);


	LONG GetBitMapWidth();
	LONG GetBitMapHeight();
	LPPIXCOLOR **GetBitMapRGBData();
};


class EXPORTDLL ATEngine_Variable
{
	AT_RGBA m_ClearColor;

	unsigned int m_glClear;

	BOOL m_EnablePoint;

	double m_Fovy;
	double m_Aspect;
	double m_ZNear;
	double m_ZFar;

public:
	//ATEngine_Variable ����
	static ATEngine_Variable *Interface();

	void SetClearColor(float R = 0.0f, float G = 0.0f, float B = 0.0f, float Alpha = 1.0f);
	ATRGBA *GetClearColor();


	//GL_COLOR_BUFFER_BIT ��ʾҪ���������Ϣ
	//GL_DEPTH_BUFFER_BIT ��ʾҪ�����Ȼ�����Ϣ��ÿһ�ζ�ʹ��Զ�����zֵΪ�����ֵ��
	void SetglClear(unsigned int glClear = GL_COLOR_BUFFER_BIT);
	unsigned int *GetglClear();


	/*
		�ο�
		90.0,//���½���н�
		1.0,//��߱���
		0.3,//���������
		1000.0);//Զ�������
	*/
	//�������������
	void SetFAZZ(double Fovy = 90.0, double Aspect = 1.0, double ZNear = 0.3, double ZFar = 1000.0);
	double GetF();
	double GetA();
	double GetZ();
	double Get_Z();
private:
	ATEngine_Variable();
	~ATEngine_Variable();
};


//ATEngine_Variable �ĳ�ʼ������ʱ�ı���Ҫ�ı�һ��Ҫ�ڳ�ʼ��ǰ����

class EXPORTDLL ATEngine :public ATROOT
{

public:
	//ATEngine ����
	static ATEngine *Interface();

	//��ʼ������
	void Init(DWORD Init, int *Argc, char **Argv);

	//��ʼ��_OpenGL����ʾģʽ
	/*
		GLUT_SINGLE ������
		GLUT_RGBA ��ɫ������

		CALL:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		GLUT_SINGLE | GLUT_RGBA ������ + ��ɫ������
	*/
	void InitMode(unsigned int Define);
	//��ʼ��_OpenGL����ʾģʽ
	/*
		GLUT_SINGLE ������
		GLUT_RGBA ��ɫ������

		CALL:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		GLUT_SINGLE | GLUT_RGBA ������ + ��ɫ������
		GLUT_DOUBLE | GLUT_RGBA ˫���� + ��ɫ������
	*/
	void InitMode(unsigned int Define, int window_X, int window_Y, int Width, int Height);

	//��ʼ��_���ô��ڿͻ���������������Ͻǵ�λ��
	void InitWindowPos(int window_X = 0, int window_Y = 0);

	//��ʼ��_���ô��ڵ����ؿ��(Ҳ���ǿͻ����Ŀ��)
	void InitWindowSize(int Width = 800, int Height = 600);

	//��ʼ��_�������ڣ���д���ڱ�����������
	void InitCreateWindows(const char *WindowName = "ATENGINE");


	//������ѭ��
	void ATENGINEMAIN_Loop();

private:

	ATEngine();

	~ATEngine();

	//��ʼ��_���õ����������һ�λ��Ƶ���ɫ���ݵ���ɫ���൱�ڱ�����ɫ��
	void InitClearColor();

public:
	//�����ƺ���
	void ATENGINE_OnRuning(void(*MainDisplay)());
	//����
	static void ATENGINE_Runing_Draw_Begin();

	//�ѻ����е�����д��
	static void ATENGINE_Runing_Draw_End();

	//FPSˢ��
	//��Ҫ�ں���������ӡ����֮���,��Ӱ��FPS,ֻ����չʾˢ�µ��ٶ�
	//������//ATENGINE->ATENGINE_RefreshDraw();����
	static void ATENGINE_FPSDRAW(DWORD FPS);

	//����������
	static void ATENGINE_SWAPBUFFERS();

	//��glBegin();�ɶ�
	static void DrawEnd();

	//����̨
	static void Console();

	//��������
	/*
	GL_CULL_FACE //������ü�
	GL_DEPTH_TEST //������Ȳ���
	*/
	static void ATENGINE_Enable(unsigned int FUNCTION = GL_CULL_FACE);

	//�رչ���
	/*
	GL_DEPTH_TEST //�ر���Ȳ���
	*/
	static void ATENGINE_Disable(unsigned int FUNCTION = GL_DEPTH_TEST);

	//�����ͻ�״̬��֧��
	/*
	GL_VERTEX_ARRAY //��������֧��
	GL_COLOR_ARRAY //��ɫ����֧��
	*/
	static void ATENGINE_EnableCilentState(unsigned int FUNCTION = GL_VERTEX_ARRAY);

	//����һ��
	/*
	GL_BACK �ü�������
	*/
	static void ATENGINE_CULLFACE(unsigned int CULLFACE = GL_BACK);


	//�ص�����
	//���ڴ�С�ͼ���״̬�ı��ǻ����
	void ATENGINE_OnWindowsChange(void(*OnWindowsChange)(int Width, int Height));

	//��ͨ���̰����ص�
	void ATENGINE_OnOrdinaryKeyboardDownEvent(void(*OnOrdinaryKeyboardDownEvent)(unsigned char Key, int X, int Y));
	void ATENGINE_OnOrdinaryKeyboardUpEvent(void(*OnOrdinaryKeyboardUpEvent)(unsigned char Key, int X, int Y));
	//���ܼ��̰����ص�
	void ATENGINE_OnSpecialKeyboardDownEvent(void(*OnSpecialKeyboardDownEvent)(int Key, int X, int Y));
	void ATENGINE_OnSpecialKeyboardUpEvent(void(*OnSpecialKeyboardUpEvent)(int Key, int X, int Y));

	//���ص�
	//��������ĵ���¼�
	//:::::::::::::::::::::::::::::::::::::::::::::::::::������ǰ���ֺ���� 0,1,2,3,4   :::::::::::::::::::::����̧�� 0,1
	void ATENGINE_OnMouseClickEvent(void(*OnMouseClickEvent)(int Button, int State, int Mouse_X, int Mouse_Y));
	//��껬��
	void ATENGINE_OnMouseMoveEvent(void(*OnMouseMoveEvent)(int Mouse_X, int Mouse_Y));
	//�����ק
	void ATENGINE_OnMousePassiveEvent(void(*OnMousePassiveEvent)(int Mouse_X, int Mouse_Y));


	//���ö�ʱ��
	//ÿ���ٺ�������ĸ�ʱ��
	/*
		void OnTimerEnd(int Timer_ID)
		{
			switch (Timer_ID)
			{
				case 10086:
					{
							ATENGINE->ATENGINE_PostRedisplayOnTimerBegin();
							std::cout << "10086" << std::endl;
							ATENGINE_ONTIMEREND(100, OnTimerEnd, 10086);
							//glutTimerFunc(100, OnTimerEnd, 10086);
					}; break;
				case 1008611:
					{
							ATENGINE->ATENGINE_PostRedisplayOnTimerBegin();
							std::cout << "1008611" << std::endl;
							ATENGINE_ONTIMEREND(200, OnTimerEnd, 1008611);
					}; break;
			}
		}
	*/
	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::��������
	void ATENGINE_OnSetTimerEnd(unsigned int Millisecond, void(*OnTimerEnd)(int Timer_ID), int TimerID);
	//Ͷ�����»�����Ϣ
	void ATENGINE_PostRedisplayOnTimerBegin();

	//ˢ�»���
	void ATENGINE_RefreshDraw();

	//���ڿ���ʱ����
	void ATENGINE_OnIdle(void(*OnIdle)());
private:
	//Ĭ�ϵ������õ���ɫ�����������һ�ε���ɫ����
	static void ATENGINE_Runing_Draw_glClear();

public:
	//�����ӿ����
	//2D����ͶӰ
	void ATENGINE_WindowsChangeMatrixModeAndOrtho2D(unsigned int MatrixMode = GL_PROJECTION, double Width = 0, double Height = 0, MATRIXMODE SourcePoint = MATRIXMODE::CENTER);

	//3D͸��ͶӰ ��ʼ�ĵ�һ������������
	void ATENGINE_WindowsChangeMatrixModeAndOrtho3D(unsigned int MatrixMode = GL_PROJECTION, double Width = 0, double Height = 0, MATRIXMODE SourcePoint = MATRIXMODE::CENTER);

	/*
		�ο�
		90.0,//���½���н�
		1.0,//��߱���
		0.3,//���������
		1000.0);//Զ�������
	*/
	//�������������
	void SetCamer(double Fovy = 90.0, double Aspect = 1.0, double ZNear = 0.3, double ZFar = 1000.0);

	//::::::::::::::::��ת:ƽ��:::::::::::::::::::::::::::::::::::::::��Ҫ�ֶ����þ���ģʽ
	void ATENGINE_MatrixMode(unsigned int MatrixMode = GL_MODELVIEW);
	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::����λ��
	void ATENGINE_MatrixLoadIdentity();
public:
	//OpenGL��һЩ����ͼԪ����
	//GL_POINTS				��(һ������)
	//GL_LINES				�߶�(2������)
	//GL_LINE_LOOP			����߶�//����β����
	//GL_LINE_STRIP			�����߶�
	//GL_TRIANGLES			�����Σ�3�����㣩
	//GL_TRIANGLE_STRIP		����������
	//GL_TRIANGLE_FAN		�������ȣ�
	//GL_QUADS				͹�ı���
	//GL_QUAD_STRIP			����͹�ı���
	//GL_POLYGON			����Σ� >= 3�����㣩
	/*
	void ATENGINE_MatrixMode(unsigned int MatrixMode = GL_MODELVIEW);
	*/
	//::::::::::::::::��ת:ƽ��:::::::::::::::::::::::::::::::::::::::��Ҫ�ֶ����þ���ģʽ���Լ�����:::::::----->ATENGINE->DrawEnd();
	void EnableBase(unsigned int Base);

	void Color3F(float R, float G, float B);
	void Color3F(ATATRGB ATAT_RGB);
	void Color3F(ATATRGBA ATAT_RGBA);
	void Color3UChar(unsigned char R, unsigned char G, unsigned char B);
	void Color3(unsigned char R, unsigned char G, unsigned char B);

	void Color4F(float R, float G, float B, float A);
	void Color4F(ATATRGB ATAT_RGB);
	void Color4F(ATATRGBA ATAT_RGBA);
	void Color4UChar(unsigned char R, unsigned char G, unsigned char B, unsigned char A);
	void Color4(unsigned char R, unsigned char G, unsigned char B, unsigned char A);

	//��������
	void Enable_Points();

	//��
	void Draw_Points(float X, float Y);
	void Draw_Points(float R, float G, float B, float X, float Y);
	//��0��������
	void Draw_Points(float R, float G, float B, float A, int *Null, float X, float Y);

	void Draw_Points(float X, float Y, float Z);
	void Draw_Points(float R, float G, float B, float X, float Y, float Z);
	void Draw_Points(float R, float G, float B, float A, float X, float Y, float Z);

	void Draw_Points(ATATPOS2D PointPos);
	void Draw_Points(ATATRGB ATAT_RGB, ATATPOS2D PointPos);
	void Draw_Points(ATATRGBA ATAT_RGBA, ATATPOS2D PointPos);

	void Draw_Points(ATATPOS3D PointPos);
	void Draw_Points(ATATRGB ATAT_RGB, ATATPOS3D PointPos);
	void Draw_Points(ATATRGBA ATAT_RGBA, ATATPOS3D PointPos);
public:
	//����������
	void CreateTriangle(float BeginPoint_X, float BeginPoint_Y, float CenterPoint_X, float CenterPoint_Y, float EndPoint_X, float EndPoint_Y);
	void CreateTriangle(
		float R_B, float G_B, float B_B, float BeginPoint_X, float BeginPoint_Y,
		float R_C, float G_C, float B_C, float CenterPoint_X, float CenterPoint_Y,
		float R_E, float G_E, float B_E, float EndPoint_X, float EndPoint_Y);
	//��0��������
	void CreateTriangle(
		float R_B, float G_B, float B_B, float A_B, int *Null_B, float BeginPoint_X, float BeginPoint_Y,
		float R_C, float G_C, float B_C, float A_C, int *Null_C, float CenterPoint_X, float CenterPoint_Y,
		float R_E, float G_E, float B_E, float A_E, int *Null_E, float EndPoint_X, float EndPoint_Y);

	void CreateTriangle(
		float BeginPoint_X, float BeginPoint_Y, float BeginPoint_Z,
		float CenterPoint_X, float CenterPoint_Y, float CenterPoint_Z,
		float EndPoint_X, float EndPoint_Y, float EndPoint_Z);
	void CreateTriangle(
		float R_B, float G_B, float B_B, float BeginPoint_X, float BeginPoint_Y, float BeginPoint_Z,
		float R_C, float G_C, float B_C, float CenterPoint_X, float CenterPoint_Y, float CenterPoint_Z,
		float R_E, float G_E, float B_E, float EndPoint_X, float EndPoint_Y, float EndPoint_Z);
	void CreateTriangle(
		float R_B, float G_B, float B_B, float A_B, float BeginPoint_X, float BeginPoint_Y, float BeginPoint_Z,
		float R_C, float G_C, float B_C, float A_C, float CenterPoint_X, float CenterPoint_Y, float CenterPoint_Z,
		float R_E, float G_E, float B_E, float A_E, float EndPoint_X, float EndPoint_Y, float EndPoint_Z);



	void CreateTriangle(ATATPOS2D BeginPoint, ATATPOS2D CenterPoint, ATATPOS2D EndPoint);
	void CreateTriangle(
		ATATRGB ATAT_RGB_B, ATATPOS2D BeginPoint,
		ATATRGB ATAT_RGB_C, ATATPOS2D CenterPoint,
		ATATRGB ATAT_RGB_E, ATATPOS2D EndPoint);
	void CreateTriangle(
		ATATRGBA ATAT_RGBA_B, ATATPOS2D BeginPoint,
		ATATRGBA ATAT_RGBA_C, ATATPOS2D CenterPoint,
		ATATRGBA ATAT_RGBA_E, ATATPOS2D EndPoint);

	void CreateTriangle(ATATPOS3D BeginPoint, ATATPOS3D CenterPoint, ATATPOS3D EndPoint);
	void CreateTriangle(
		ATATRGB ATAT_RGB_B, ATATPOS3D BeginPoint,
		ATATRGB ATAT_RGB_C, ATATPOS3D CenterPoint,
		ATATRGB ATAT_RGB_E, ATATPOS3D EndPoint);
	void CreateTriangle(
		ATATRGBA ATAT_RGBA_B, ATATPOS3D BeginPoint,
		ATATRGBA ATAT_RGBA_C, ATATPOS3D CenterPoint,
		ATATRGBA ATAT_RGBA_E, ATATPOS3D EndPoint);

	//����͹�ı���
	void CreateQuadrangle(
		float BeginPoint_X, float BeginPoint_Y,
		float CenterPoint_X_0, float CenterPoint_Y_0,
		float CenterPoint_X_1, float CenterPoint_Y_1,
		float EndPoint_X, float EndPoint_Y);
	void CreateQuadrangle(
		float R_B, float G_B, float B_B, float BeginPoint_X, float BeginPoint_Y,
		float R_C_0, float G_C_0, float B_C_0, float CenterPoint_X_0, float CenterPoint_Y_0,
		float R_C_1, float G_C_1, float B_C_1, float CenterPoint_X_1, float CenterPoint_Y_1,
		float R_E, float G_E, float B_E, float EndPoint_X, float EndPoint_Y);
	//��0��������
	void CreateQuadrangle(
		float R_B, float G_B, float B_B, float A_B, int *Null_B, float BeginPoint_X, float BeginPoint_Y,
		float R_C_0, float G_C_0, float B_C_0, float A_C_0, int *Null_C_0, float CenterPoint_X_0, float CenterPoint_Y_0,
		float R_C_1, float G_C_1, float B_C_1, float A_C_1, int *Null_C_1, float CenterPoint_X_1, float CenterPoint_Y_1,
		float R_E, float G_E, float B_E, float A_E, int *Null_E, float EndPoint_X, float EndPoint_Y);

	void CreateQuadrangle(
		float BeginPoint_X, float BeginPoint_Y, float BeginPoint_Z,
		float CenterPoint_X_0, float CenterPoint_Y_0, float CenterPoint_Z_0,
		float CenterPoint_X_1, float CenterPoint_Y_1, float CenterPoint_Z_1,
		float EndPoint_X, float EndPoint_Y, float EndPoint_Z);
	void CreateQuadrangle(
		float R_B, float G_B, float B_B, float BeginPoint_X, float BeginPoint_Y, float BeginPoint_Z,
		float R_C_0, float G_C_0, float B_C_0, float CenterPoint_X_0, float CenterPoint_Y_0, float CenterPoint_Z_0,
		float R_C_1, float G_C_1, float B_C_1, float CenterPoint_X_1, float CenterPoint_Y_1, float CenterPoint_Z_1,
		float R_E, float G_E, float B_E, float EndPoint_X, float EndPoint_Y, float EndPoint_Z);
	void CreateQuadrangle(
		float R_B, float G_B, float B_B, float A_B, float BeginPoint_X, float BeginPoint_Y, float BeginPoint_Z,
		float R_C_0, float G_C_0, float B_C_0, float A_C_0, float CenterPoint_X_0, float CenterPoint_Y_0, float CenterPoint_Z_0,
		float R_C_1, float G_C_1, float B_C_1, float A_C_1, float CenterPoint_X_1, float CenterPoint_Y_1, float CenterPoint_Z_1,
		float R_E, float G_E, float B_E, float A_E, float EndPoint_X, float EndPoint_Y, float EndPoint_Z);


	void CreateQuadrangle(ATATPOS2D BeginPoint, ATATPOS2D CenterPoint_0, ATATPOS2D CenterPoint_1, ATATPOS2D EndPoint);
	void CreateQuadrangle(
		ATATRGB ATAT_RGB_B, ATATPOS2D BeginPoint,
		ATATRGB ATAT_RGB_C_0, ATATPOS2D CenterPoint_0,
		ATATRGB ATAT_RGB_C_1, ATATPOS2D CenterPoint_1,
		ATATRGB ATAT_RGB_E, ATATPOS2D EndPoint);
	void CreateQuadrangle(
		ATATRGBA ATAT_RGB_B, ATATPOS2D BeginPoint,
		ATATRGBA ATAT_RGB_C_0, ATATPOS2D CenterPoint_0,
		ATATRGBA ATAT_RGB_C_1, ATATPOS2D CenterPoint_1,
		ATATRGBA ATAT_RGB_E, ATATPOS2D EndPoint);
	void CreateQuadrangle(ATATPOS3D BeginPoint, ATATPOS3D CenterPoint_0, ATATPOS3D CenterPoint_1, ATATPOS3D EndPoint);
	void CreateQuadrangle(
		ATATRGB ATAT_RGB_B, ATATPOS3D BeginPoint,
		ATATRGB ATAT_RGB_C_0, ATATPOS3D CenterPoint_0,
		ATATRGB ATAT_RGB_C_1, ATATPOS3D CenterPoint_1,
		ATATRGB ATAT_RGB_E, ATATPOS3D EndPoint);
	void CreateQuadrangle(
		ATATRGBA ATAT_RGB_B, ATATPOS3D BeginPoint,
		ATATRGBA ATAT_RGB_C_0, ATATPOS3D CenterPoint_0,
		ATATRGBA ATAT_RGB_C_1, ATATPOS3D CenterPoint_1,
		ATATRGBA ATAT_RGB_E, ATATPOS3D EndPoint);
public:
	/*
		int ID = ATENGINE->CreateDrawList(2);
		ATENGINE->EnableBase(GL_QUADS);
		ATENGINE->Color3F(ATATRGB(0.0f, 1.0f, 0.0f));
		ATENGINE->Draw_Points(ATATPOS2D(-50, +50));
		ATENGINE->Draw_Points(ATATPOS2D(-50, -50));
		ATENGINE->Draw_Points(ATATPOS2D(+50, -50));
		ATENGINE->Draw_Points(ATATPOS2D(+50, +50));
		ATENGINE->DrawEnd();
		ATENGINE->EnableBase(GL_QUADS);
		ATENGINE->Color3F(ATATRGB(1.0f, 1.0f, 0.0f));
		ATENGINE->Draw_Points(ATATPOS2D(-25, +25));
		ATENGINE->Draw_Points(ATATPOS2D(-25, -25));
		ATENGINE->Draw_Points(ATATPOS2D(+25, -25));
		ATENGINE->Draw_Points(ATATPOS2D(+25, +25));
		ATENGINE->DrawEnd();
		ATENGINE->EndDrawList();

		int ID2 = ATENGINE->CreateDrawList(1);
		glNewList(ID2, GL_COMPILE);
		ATENGINE->CreateTriangle(
		ATATRGB::RED, ATATPOS2D::ZERO,
		ATATRGB::GREEN, ATATPOS2D(0, 200),
		ATATRGB::BLUE, ATATPOS2D(200, 200));
		ATENGINE->DrawEnd();
		ATENGINE->EndDrawList();
	*/
	/*
		������	glBegin() �Ļ���
	*/
	//������ͼ�б�����
	unsigned int CreateDrawList(unsigned int Number);
	//������ͼ�б�����һ��
	unsigned int CreateDrawListAndDraw(unsigned int Number);
	//������ͼ�б����
	void DrawDrawList(unsigned int DrawListID);
	//�����ͼ�б����
	//GL_UNSIGNED_INT
	void DrawDrawList_s(unsigned int DrawListIDNum, unsigned int ArrType = GL_UNSIGNED_INT, unsigned int *Arr = NULL);
	//������ͼ�б�
	void EndDrawList();
	//ɾ����ͼ�б�
	void DeleteDrawList(unsigned int DrawListID, unsigned int Number);
public:
	/*
		//���float �ﲻ��Ҫ���������double
		:::::::::::::::::::::::::::::::::::::===>++++++d
	*/
	void Translate(float X, float Y, float Z);
	void Translate(ATATPOS3D ATATPos3D);
	void Rotate(float Angle, float X, float Y, float Z);
	void Rotate(float Angle, ATATPOS3D ATATPos3D);
	void SetScaleX(float X);
	void SetScaleY(float Y);
	void SetScaleZ(float Z);
	void SetScale(float X, float Y);
	void SetScale(float X, float Y, float Z);
	void SetScale(ATATSCALE2D ATATScale2D);
	void SetScale(ATATSCALE3D ATATScale3D);
};



/*

///	glScalef(0.5,0.5,0.0f);
///	glCallList(1);//���Ƶ�����ͼ�б�




*/