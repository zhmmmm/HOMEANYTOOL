#ifndef _CVICTOR2D_H_
#define _CVICTOR2D_H_
#include <math.h>
#include <cmath>
#define PI 3.14159265358979323846

#define EXPORTDLL        _declspec(dllexport)

class EXPORTDLL CVictor2D
{
public:
	CVictor2D();
	CVictor2D(double x,double y);
	CVictor2D(const CVictor2D& old);

	void SetVictor(double x,double y);
	double GetX();
	double GetY();
	double Dot(const CVictor2D& cvct2d);//����
	double Mod();//��ģ
	double GetAngle(CVictor2D& cvct2d);//��н�

	CVictor2D UnitVictor();//��λ����
	CVictor2D GetShadow(const CVictor2D& cvct2d);
	CVictor2D  operator+(const CVictor2D& cvct2d); //����+���������
	CVictor2D&  operator+=(const CVictor2D& cvct2d);//����+=���������
	CVictor2D  operator-(const CVictor2D& cvct2d); //����-���������
	CVictor2D&  operator-=(const CVictor2D& cvct2d); //����-=���������
	CVictor2D  operator*(double);//��������
	CVictor2D&  operator*=(double);//��������
	double  operator*(const CVictor2D& cvct2d);//�����,����2D�����ؽ����ģ

protected:
private:
	double m_X;
	double m_Y;
};
#endif