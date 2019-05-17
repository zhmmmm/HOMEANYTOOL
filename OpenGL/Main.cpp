#include "OpenGL_Class.h"
#include "CMyBass.h"
#include "TextureManager.h"


#ifndef _DEBUG
#pragma comment(linker,"/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#endif

float g_Angle = 0.0f;
float g_Camer_Y = 10;
int g_Width = 800;
int g_Height = 600;
unsigned char* pBmp = NULL;
unsigned char* pBmp2 = NULL;

GLuint tid[2];//���ڴ洢�����������ID������


//��������
float rc[] = {
	-20,+20,0,
	-20,-20,0,
	+20,-20,0,
	+20,+20,0
};
float cl[] = {
	255,0,0,
	255,255,255,
	0,0,255,
	0,255,0
};
//�������꣨uv������
float uv[] = {
	0,1,
	0,0,
	1,0,
	1,1
};

//��������ɫ����UV��Ϣ����һ��д��
float tg[] = {
	-20,+20,0,255,0,0,0,1,
	-20,-20,0,255,255,255,0,0,
	+20,-20,0,0,0,255,1,0,
	+20,+20,0,0,255,0,1,1
};
unsigned int index[] = {
	0,1,2,
	0,2,3
};

void Display()
{
	//�������õ���ɫ�������һ�ε���ɫ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//�м�ľ������ڻ��ƵĲ����ڴ���д����
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
	//GL_POLYGON			����Σ�>=3�����㣩

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, g_Camer_Y, 50, 0, 0, 0, 0, 1, 0);
	glRotated(g_Angle, 0, 1, 0);



	glTranslatef(-30, 0, 0);
	glVertexPointer(3, GL_FLOAT, 32, tg);
	glTexCoordPointer(2,GL_FLOAT,32,tg + 6);
	glBindTexture(GL_TEXTURE_2D, tid[0]);//���õ�ǰʹ�õ�����Ϊ��һ������
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, index);


	glLoadIdentity();
	gluLookAt(0, g_Camer_Y, 50, 0, 0, 0, 0, 1, 0);
	glTranslatef(+30, 0, 0);
	glVertexPointer(3, GL_FLOAT, 0, rc);
	glTexCoordPointer(2,GL_FLOAT,0,uv);
	glBindTexture(GL_TEXTURE_2D, tid[1]);//���õ�ǰʹ�õ�����Ϊ�ڶ�������
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, index);

	glutSwapBuffers();
}
//������Ǹı��Ĵ��ڴ�С�Ŀ��
void ReShape(int width, int height)
{
	//���õ�ǰ�����ľ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//��ͶӰ����λ��
	glViewport(0, 0, width, height);//Ҫ�������ڵĿ��
	gluPerspective(90.0,1,0.3,1000);//����͸��ͶӰ
	//gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);//��������ͶӰ
	//gluOrtho2D(0, width, 0, height); //��������ͶӰ
}
void Indle()
{
	float StartTime = GetTickCount();
	//system("cls");
	static float LastTime = 0;
	if (StartTime - LastTime >= 60.0f)
	{
		glutPostRedisplay();//Ͷ�����»��Ƶ���Ϣ
		LastTime = StartTime;
	}
}
void OrdinaryKeyDown(unsigned char Key, int Mouse_X, int Mouse_Y)
{
	if (Key == 13) { exit(0); }
	if (Key == 'W' || Key == 'w')
	{
		g_Camer_Y += 5.0f;
	}
	if (Key == 'S' || Key == 's')
	{
		g_Camer_Y -= 5.0f;
	}
	if (Key == 'A' || Key == 'a')
	{
		g_Angle += 2.0f;
	}
	if (Key == 'D' || Key == 'd')
	{
		g_Angle -= 2.0f;
	}
}
int main(int argc, char **argv)
{
	OPENGL->Init(&argc, argv);
	OPENGL->InitMode(GLUT_DOUBLE | GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL);
	OPENGL->InitWinPos(100, 100);
	OPENGL->InitWindSize(g_Width, g_Height);
	OPENGL->CreateWindows("OpenGL����");
	OPENGL->ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	OPENGL->SerDrawCallback(Display);
	OPENGL->WindSizeOractivation_Reshape(ReShape);
	OPENGL->OrdinaryKeyDown(OrdinaryKeyDown);
	OPENGL->WindIdle(Indle);
	OPENGL->EnableCullFace();
	//������������,��ɫ����,��Ȼ�����,֧������2D��ͼ,UV��������,������ɫ���,����ģ�建����
	OPENGL->Enable_Varied__Buffer__(1, 0, 1, 1, 1,0,0);
	glewInit();
	//============================================================

	glGenTextures(
		//Ҫ�������ٸ������id
		2,
		//���ڽ�������id��unsigned int����
		tid);

	//����Ĵ�������ָ��id������Ϊ��ǰ����
	glBindTexture(GL_TEXTURE_2D, tid[0]);
	//�������еĲ���������Ե�ǰ�����

	//��������Ĳ�����ʽ
	//GL_NEAREST������������Ч����Ч�ʸ�
	//GL_LINEAR�����Բ�ֵ������Ч����Ч�ʵ�
	//GL_TEXTURE_MIN_FILTER��ʾ���ֲ�����ʽ
	//��������С����������棬��ν��С����ָ
	//��ģ�������εĻ������С��������������
	//����ʱ��GL_TEXTURE_MAG_FILTER�ͱ�ʾ
	//���ֲ��������ڷŴ�����������棬��ģ��
	//�����εĻ�������������������������ʱ
	//��һ����˵��С���Ŵ��������Ҫ����
	glTexParameterf(
		GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER,
		GL_NEAREST);
	glTexParameterf(
		GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER,
		GL_NEAREST);




	//////////////////////////////////////////////////////////////////////////
	//����ͼƬ����
	FILE* pf = NULL;
	fopen_s(&pf, "res/2.bmp", "rb");
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;

	//�������ļ�ͷ
	fread(&bf, 1, sizeof(bf), pf);
	//��������Ϣͷ
	fread(&bi, 1, sizeof(bi), pf);
	//��ʣ�����ɫ����һ���Զ���
	pBmp2 = new unsigned char[bi.biSizeImage];
	fread(pBmp2, 1, bi.biSizeImage, pf);
	fclose(pf);



	//��������
	glTexImage2D(
		//GL_TEXTURE_2D��ʾ���ض�ά����
		GL_TEXTURE_2D,
		//0��ʾ�������༶��������
		0,
		//GL_RGB��ʾ������RGB��ɫģʽ
		GL_RGB,
		//�������ؿ�
		bi.biWidth,
		//�������ظ�
		bi.biHeight,
		//0��ʾ����������߽�
		0,
		//GL_BGR_EXT��ʾ�������صĸ�ʽΪB��G��R������
		GL_BGR_EXT,
		//GL_UNSIGNED_BYTE��ʾ����������ɫ�����ĸ�ʽΪunsigned char
		GL_UNSIGNED_BYTE,
		//����������ɫ����ʼ��ַ
		pBmp2);


	//���صڶ���ͼ
	//����Ĵ�������ָ��id������Ϊ��ǰ����
	glBindTexture(GL_TEXTURE_2D, tid[1]);
	//�������еĲ���������Ե�ǰ�����

	//��������Ĳ�����ʽ
	//GL_NEAREST������������Ч����Ч�ʸ�
	//GL_LINEAR�����Բ�ֵ������Ч����Ч�ʵ�
	//GL_TEXTURE_MIN_FILTER��ʾ���ֲ�����ʽ
	//��������С����������棬��ν��С����ָ
	//��ģ�������εĻ������С��������������
	//����ʱ��GL_TEXTURE_MAG_FILTER�ͱ�ʾ
	//���ֲ��������ڷŴ�����������棬��ģ��
	//�����εĻ�������������������������ʱ
	//��һ����˵��С���Ŵ��������Ҫ����
	glTexParameterf(
		GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexParameterf(
		GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);

	pf = NULL;
	fopen_s(&pf, "res/testDetail.bmp", "rb");

	fread(&bf, 1, sizeof(bf), pf);
	fread(&bi, 1, sizeof(bi), pf);
	pBmp = new unsigned char[bi.biSizeImage];
	fread(pBmp, 1, bi.biSizeImage, pf);
	fclose(pf);
	//��������
	glTexImage2D(
		//GL_TEXTURE_2D��ʾ���ض�ά����
		GL_TEXTURE_2D,
		//0��ʾ�������༶��������
		0,
		//GL_RGB��ʾ������RGB��ɫģʽ
		GL_RGB,
		//�������ؿ�
		bi.biWidth,
		//�������ظ�
		bi.biHeight,
		//0��ʾ����������߽�
		0,
		//GL_BGR_EXT��ʾ�������صĸ�ʽΪB��G��R������
		GL_BGR_EXT,
		//GL_UNSIGNED_BYTE��ʾ����������ɫ�����ĸ�ʽΪunsigned char
		GL_UNSIGNED_BYTE,
		//����������ɫ����ʼ��ַ
		pBmp);


	glBindTexture(GL_TEXTURE_2D, 0);//�ͷŲ���������Ŀ��

	delete[] pBmp2;
	pBmp2 = NULL;
	delete[] pBmp;
	pBmp = NULL;



	//============================================================

	OPENGL->MainWindLoop();
	glDeleteTextures(2, tid);
	return 0;
}