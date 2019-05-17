#include "OpenGL_Class.h"

#pragma comment(lib, "glew32.lib")

OpenGL::OpenGL() {}
OpenGL *OpenGL::Interface()
{
	static OpenGL opengl;
	return &opengl;
}
//��ʼ��_glut��
void OpenGL::Init(int *argc, char **argv)
{
	glutInit(argc, argv);

}
//��ʼ��_OpenGL����ʾģʽ
void OpenGL::InitMode(unsigned int Define)
{
	glutInitDisplayMode(Define);
}
//��ʼ��_���ô��ڿͻ���������������Ͻǵ�λ��
void OpenGL::InitWinPos(int W, int H)
{
	glutInitWindowPosition(W, H);
}
//��ʼ��_���ô��ڵ����ؿ��(Ҳ���ǿͻ����Ŀ��)
void OpenGL::InitWindSize(int Size_W, int Size_H)
{
	glutInitWindowSize(Size_W, Size_H);
}
//��ʼ��_�������ڣ���д���ڱ�����������
void OpenGL::CreateWindows(const char *WindName)
{
	glutCreateWindow(WindName);
}
//��ʼ��_���õ����������һ�λ��Ƶ���ɫ���ݵ���ɫ���൱�ڱ�����ɫ��
void OpenGL::ClearColor(float R, float G, float B, float Alpha)//Alpha Ϊ͸����
{
	glClearColor(R, G, B, Alpha);
}
//=======================================================
//��ʼ��_���û��ƻص�����
void OpenGL::SerDrawCallback(void(*Func)())
{
	glutDisplayFunc(Func);
}
//��ʼ��_�����ڴ�С�ͼ���״̬�ı��ʱ�����õĺ���
void OpenGL::WindSizeOractivation_Reshape(void(*Func)(int Width, int Height))
{
	glutReshapeFunc(Func);
}

//�ü�������(3D��)
void OpenGL::EnableCullFace()
{
	glEnable(GL_CULL_FACE);//����ü�
	glCullFace(GL_BACK);//�ü���һ��
}
//������������,��ɫ����,��Ȼ�����,֧������2D��ͼ,UV��������,������ɫ���,����ģ�建����
void OpenGL::Enable_Varied__Buffer__(int Vertex, int Color, int DepthBuffer, int Texture2D, int UVCoordArray,int ColorBlend,int Template)
{
	if (Vertex == 1) { glEnableClientState(GL_VERTEX_ARRAY); }
	if (Color == 1) { glEnableClientState(GL_COLOR_ARRAY); }
	if (DepthBuffer == 1) { glEnable(GL_DEPTH_TEST); }
	if (Texture2D == 1) { glEnable(GL_TEXTURE_2D); }
	if (UVCoordArray == 1) { glEnableClientState(GL_TEXTURE_COORD_ARRAY); }
	if(ColorBlend == 1){ glEnable(GL_BLEND); }
	if(Template == 1)
	{
		glClearStencil(0);
		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	}
}
//�����Ҷ�ͼ����
void OpenGL::CreateFromBmp(
	const char* BmpFile,//�Ҷ�ͼ·��
	float H,//���ɵ��ε����Yֵ
	int Xwidth,//x�����������
	int Zwidth,//z�����������
	float Space)//��ʾ��λ���ӵĿ�
{
	Map.CreateFromBMP(BmpFile, H, Xwidth, Zwidth, Space);
}
//���ƻҶ�ͼ����
void OpenGL::DrawMap()
{
	Map.DrawMap();
}

//��ͨ���̻ص�����
void OpenGL::OrdinaryKeyDown(void(*KeyDown)(unsigned char Key, int Mouse_X, int Mouse_Y))
{
	glutKeyboardFunc(KeyDown);
}
void OpenGL::OrdinaryKeyUp(void(*KeyUp)(unsigned char Key, int Mouse_X, int Mouse_Y))
{
	glutKeyboardUpFunc(KeyUp);
}
//���ܼ��ص�����
void OpenGL::SpecialKeyDown(void(*KeyDown)(int Key, int Mouse_X, int Mouse_Y))
{
	glutSpecialFunc(KeyDown);

}
void OpenGL::SpecialKeyUp(void(*KeyUp)(int Key, int Mouse_X, int Mouse_Y))
{
	glutSpecialUpFunc(KeyUp);
}
//���ص�����
//��갴��/̧��
void OpenGL::MouseDown(void(*Mouse_Down)(int Button, int State, int Mouse_X, int Mouse_Y))
{
	//Button:
	//0 ������
	//1 ����м�
	//2 ����Ҽ�
	//3 ��������ǰ
	//4 ���������
	//State:0 ����,1 ̧��
	glutMouseFunc(Mouse_Down);
}
//��껬��
void OpenGL::MosueMove(void(*Mouse_Move)(int Mouse_X, int Mouse_Y))
{
	glutPassiveMotionFunc(Mouse_Move);
}
//�����ק
void OpenGL::MousePassive(void(*Mouse_Passive)(int Mouse_X, int Mouse_Y))
{
	glutMotionFunc(Mouse_Passive);
}
//��ʱ��
void OpenGL::Timer_(unsigned int Millis, void(*Timer)(int Value), int Value)
{
	//���ٺ�����ú�����ֻ����һ��
	glutTimerFunc(2000, Timer, Value);
}
//���ڴ��ڿ��е�ʱ�����
void OpenGL::WindIdle(void(*Indle)())
{
	glutIdleFunc(Indle);
}

//=====================================
//��ʼ��_����ѭ��
void OpenGL::MainWindLoop()
{
	glutMainLoop();
}