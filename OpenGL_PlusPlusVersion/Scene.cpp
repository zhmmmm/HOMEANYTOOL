/*
场景说明:==>
*/
#include "Scene.h"

void Scene::Start()
{
	S = new Sprite("1.bmp");

	this->m_Windows_X = 10;
	this->m_Windows_Y = 10;
	this->m_WindowsWidth = 800;
	this->m_WindowsHeight = 600;

}


static int W = 3;
static int WSpace = 1;
static int Y = 190;

void Scene::Update()
{
	ATA->PlayMusics_s("res\\Audio\\Musics\\舞曲大帝国.mp3");
	Camera::CameraToWorld(this);
	this->m_CameraPos_Y = 0;

	CLS;
	std::cout << "总时间："<<ATA->GetTimeMinute("res\\Audio\\Musics\\舞曲大帝国.mp3") << std::endl;
	std::cout <<"进度时间："<<ATA->GetCurTimeMinute("res\\Audio\\Musics\\舞曲大帝国.mp3")<< std::endl;

	int X = -200;
	static float Buf[128] = { 0 };
	ATA->GetAudioStreamData("res\\Audio\\Musics\\舞曲大帝国.mp3", Buf);
	for (int i = 0; i < 128; i++)
	{

		Y = Buf[i] * 1000;

		AT->CreateQuadrangle(
			ATATRGB::GREEN, ATATPOS3D(X, Y, 0),
			ATATRGB::WHITE, ATATPOS3D(X, 0, 0),
			ATATRGB::WHITE, ATATPOS3D(X + W, 0, 0),
			ATATRGB::GREEN, ATATPOS3D(X + W, Y, 0));

		X = X + W + WSpace;
		Y = 190;

	}
	AT->DrawEnd();
	ZeroMemory(Buf, 128);


}

void Scene::OnOrdinaryKeyboardDownEvent(unsigned char Key, int X, int Y)
{
	CVector3D T(m_LookAt_X,m_LookAt_Y,m_LookAt_Z);
	CVector3D C(m_CameraPos_X,m_CameraPos_Y,m_CameraPos_Z);

	CVector3D n = (T - C).normalized();

	std::cout << "普通按下！" << Key << " X = " << X << " Y = " << Y << std::endl;
	if (Key == 'w' || Key == 'W')
	{
		//m_CameraPos_Z -= m_MoveSpeed_Z;
		CVector3D t(m_CameraPos_X, m_CameraPos_Y, m_CameraPos_Z);
		t += n * m_MoveSpeed_Z;
		m_CameraPos_Z = t.z;
	}
	if (Key == 's' || Key == 'S')
	{
		//m_CameraPos_Z += m_MoveSpeed_Z;
		CVector3D t(m_CameraPos_X, m_CameraPos_Y, m_CameraPos_Z);
		t -= n * m_MoveSpeed_Z;
		m_CameraPos_Z = t.z;
	}
	if (Key == 'a' || Key == 'A')
	{
		m_CameraPos_X -= m_MoveSpeed_X;
	}
	if (Key == 'd' || Key == 'D')
	{
		m_CameraPos_X += m_MoveSpeed_X;
	}
	if (Key == '\r')
	{
		exit(0);
	}
}
void Scene::OnSpecialKeyboardDownEvent(int Key, int X, int Y)
{
	std::cout << "功能按下！" << Key << " X = " << X << " Y = " << Y << std::endl;
	if (Key == 101)
	{
		ATA->VolumeAdd();
	}
	if (Key == 103)
	{
		ATA->VolumeReduce();
	}
}
void Scene::OnMouseMoveEvent(int Mouse_X, int Mouse_Y)
{
	std::cout << "鼠标移动 " << "X = " << Mouse_X << " Y = " << Mouse_Y << std::endl;
	m_LookAt_X = Mouse_X - m_WindowsWidth / 2;
	m_LookAt_Y = -(Mouse_Y - m_WindowsHeight / 2);
}

void Scene::End()
{
	delete S;
	S = NULL;
}