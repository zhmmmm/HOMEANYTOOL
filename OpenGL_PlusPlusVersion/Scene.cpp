#include "Scene.h"

void Scene::Start()
{
	S = new Sprite("1.bmp");

	m_Windows_X = 10;
	m_Windows_Y = 10;


}

void Scene::Update()
{
	Camera::CameraToWorld(this);
	AT->Rotate(Angle++,0,0,1);
	AT->CreateQuadrangle(
		ATATRGB::RED, ATATPOS3D(-105, +105, 0),
		ATATRGB::YELLOW, ATATPOS3D(-105, -105, 0),
		ATATRGB::GREEN, ATATPOS3D(+105, -105, 0),
		ATATRGB::WHITE, ATATPOS3D(+105, +105, 0));
	AT->DrawEnd();
	AT->Rotate(Angle++, 1, 0, 0);

	//上
	glBegin(GL_QUADS);
	glColor3ub(255, 0, 0);
	glVertex3f(-50, +50, -50);
	glVertex3f(-50, +50, +50);
	glVertex3f(+50, +50, +50);
	glVertex3f(+50, +50, -50);
	glEnd();

	//下
	glBegin(GL_QUADS);
	glColor3ub(0, 255, 0);
	glVertex3f(-50, -50, -50);
	glVertex3f(+50, -50, -50);
	glVertex3f(+50, -50, +50);
	glVertex3f(-50, -50, +50);
	glEnd();

	//左
	glBegin(GL_QUADS);
	glColor3ub(0, 0, 255);
	glVertex3f(-50, +50, -50);
	glVertex3f(-50, -50, -50);
	glVertex3f(-50, -50, +50);
	glVertex3f(-50, +50, +50);
	glEnd();

	//右
	glBegin(GL_QUADS);
	AT->Color3(0, 255, 255);
	glVertex3f(+50, +50, -50);
	glVertex3f(+50, +50, +50);
	glVertex3f(+50, -50, +50);
	glVertex3f(+50, -50, -50);
	glEnd();

	//后
	glBegin(GL_QUADS);
	glColor3ub(255, 0, 255);
	glVertex3f(-50, +50, -50);
	glVertex3f(+50, +50, -50);
	glVertex3f(+50, -50, -50);
	glVertex3f(-50, -50, -50);
	glEnd();

	//前
	glBegin(GL_QUADS);
	glColor3ub(255, 255, 0);
	glVertex3f(-50, +50, +50);
	glVertex3f(-50, -50, +50);
	glVertex3f(+50, -50, +50);
	glVertex3f(+50, +50, +50);
	glEnd();
	AT->SetCamer(45,1,0.3,1000);
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