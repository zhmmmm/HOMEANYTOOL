#ifndef __CVECTOR_3D_H__
#define __CVECTOR_3D_H__
#include <math.h>
#include <cmath>
#define PI 3.14159265358979323846
//1e-5//��ѧ������ 1*10^(-5) 0.00001
#define ISFLOATZERO(x)	abs(x)<1e-5

#define EXPORTDLL        _declspec(dllexport)

class EXPORTDLL CVector3D
{
public:
	float x, y, z;
	CVector3D() {}
	CVector3D(float _x, float _y, float _z) :x(_x), y(_y), z(_z) {}

	void SetCVector3D(double x, double y, double z);
	double Dot(const CVector3D& v);//����
	double Mod();//��ģ
	double GetAngle(CVector3D& v);//��н�
	CVector3D UnitVictor();//��λ����
	CVector3D normalize();
	CVector3D& normalized();

	CVector3D  operator+(const CVector3D& v); //����+���������
	CVector3D  operator-(const CVector3D& v); //����-���������
	CVector3D  operator*(const CVector3D& v); //����*���������
	CVector3D  operator/(const CVector3D& v); //����/���������

	CVector3D  operator+=(const CVector3D& v); //����+=���������
	CVector3D  operator-=(const CVector3D& v); //����-=���������
	CVector3D  operator*=(const CVector3D& v); //����*=���������
	CVector3D&  operator/=(const CVector3D& v); //����/=���������

	CVector3D  operator+(double v);
	CVector3D  operator-(double v);
	CVector3D  operator*(double v);
	CVector3D  operator/(double v);

	CVector3D  operator+=(double v);
	CVector3D  operator-=(double v);
	CVector3D  operator*=(double v);
	CVector3D&  operator/=(double v);

	CVector3D  operator=(const CVector3D& v);
	CVector3D  operator=(double v);

	CVector3D Cross(const CVector3D& v);//3ά�������

};
#endif