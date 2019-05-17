#pragma once
#include "stdafx.h"
#include "Vector.h"
#define M_PI       3.14159265358979323846

//3x3�ľ���
class Matrix3:public XFORM//�̳�����ṹ��
{
public:
	//�����˾���ĸ�������ֵ
	union M33 {
		float m1[9];
		float m2[3][3];
		struct {
			float _11, _12, _13, _21, _22, _23, _31, _32, _33;
		};
	}mat3;
	Matrix3()
	{
		Identity();
	}
	//����ĵ�λ��
	void Identity()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (i == j) { mat3.m2[i][j] = 1; }
				else { mat3.m2[i][j] = 0; }
			}
		}
		//=================================================
		eM11 = eM22 = 1;
		eM12 = eM21 = eDx = eDy = 0;
	}

	//����ĳ˷�����
	Matrix3 operator * (const Matrix3& m)
	{
		Matrix3 tmp;
		tmp.mat3._11 = mat3._11*m.mat3._11 + mat3._12*m.mat3._21 + mat3._13*m.mat3._31;
		tmp.mat3._12 = mat3._11*m.mat3._12 + mat3._12*m.mat3._22 + mat3._13*m.mat3._32;
		tmp.mat3._13 = mat3._11*m.mat3._13 + mat3._12*m.mat3._23 + mat3._13*m.mat3._33;

		tmp.mat3._21 = mat3._21*m.mat3._11 + mat3._22*m.mat3._21 + mat3._23*m.mat3._31;
		tmp.mat3._22 = mat3._21*m.mat3._12 + mat3._22*m.mat3._22 + mat3._23*m.mat3._32;
		tmp.mat3._23 = mat3._21*m.mat3._13 + mat3._22*m.mat3._23 + mat3._23*m.mat3._33;

		tmp.mat3._31 = mat3._31*m.mat3._11 + mat3._32*m.mat3._21 + mat3._33*m.mat3._31;
		tmp.mat3._32 = mat3._31*m.mat3._12 + mat3._32*m.mat3._22 + mat3._33*m.mat3._32;
		tmp.mat3._33 = mat3._31*m.mat3._13 + mat3._32*m.mat3._23 + mat3._33*m.mat3._33;
		return tmp;
	}
	Matrix3& operator *= (const Matrix3& m)
	{
		Matrix3 tmp;
		tmp.mat3._11 = mat3._11*m.mat3._11 + mat3._12*m.mat3._21 + mat3._13*m.mat3._31;
		tmp.mat3._12 = mat3._11*m.mat3._12 + mat3._12*m.mat3._22 + mat3._13*m.mat3._32;
		tmp.mat3._13 = mat3._11*m.mat3._13 + mat3._12*m.mat3._23 + mat3._13*m.mat3._33;

		tmp.mat3._21 = mat3._21*m.mat3._11 + mat3._22*m.mat3._21 + mat3._23*m.mat3._31;
		tmp.mat3._22 = mat3._21*m.mat3._12 + mat3._22*m.mat3._22 + mat3._23*m.mat3._32;
		tmp.mat3._23 = mat3._21*m.mat3._13 + mat3._22*m.mat3._23 + mat3._23*m.mat3._33;

		tmp.mat3._31 = mat3._31*m.mat3._11 + mat3._32*m.mat3._21 + mat3._33*m.mat3._31;
		tmp.mat3._32 = mat3._31*m.mat3._12 + mat3._32*m.mat3._22 + mat3._33*m.mat3._32;
		tmp.mat3._33 = mat3._31*m.mat3._13 + mat3._32*m.mat3._23 + mat3._33*m.mat3._33;
		*this = tmp;
		//=============================================================
		eM11 = mat3._11; eM12 = mat3._12;
		eM21 = mat3._21; eM22 = mat3._22;
		eDx = mat3._31; eDy = mat3._32;
		return *this;
	}
	//�����ƽ�Ʊ任
	//���þ���Ϊһ��ƽ�ƾ���
	Matrix3& SetTranslate(float x, float y)
	{
		Identity();
		mat3._31 = x;
		mat3._32 = y;
		//=============================================================
		eM11 = mat3._11; eM12 = mat3._12;
		eM21 = mat3._21; eM22 = mat3._22;
		eDx = mat3._31; eDy = mat3._32;
		return *this;
	}
	//�ھ���Ļ�����ƽ��
	Matrix3& Translate(float x, float y)
	{
		Matrix3 tmp;
		tmp.mat3._31 = x;
		tmp.mat3._32 = y;
		(*this) *= tmp;
		//=============================================================
		eM11 = mat3._11; eM12 = mat3._12;
		eM21 = mat3._21; eM22 = mat3._22;
		eDx = mat3._31; eDy = mat3._32;
		return *this;
	}
	//��������ű任
	//����Ϊ���ž���
	Matrix3& SetScale(float x, float y)
	{
		Identity();
		mat3._11 = x;
		mat3._22 = y;
		//=============================================================
		eM11 = mat3._11; eM12 = mat3._12;
		eM21 = mat3._21; eM22 = mat3._22;
		eDx = mat3._31; eDy = mat3._32;
		return *this;
	}
	//�ھ���Ļ���������
	Matrix3& Scale(float x, float y)
	{
		Matrix3 temp;
		temp.mat3._11 = x;
		temp.mat3._22 = y;
		(*this) *= temp;
		//=============================================================
		eM11 = mat3._11; eM12 = mat3._12;
		eM21 = mat3._21; eM22 = mat3._22;
		eDx = mat3._31; eDy = mat3._32;
		return *this;
	}
	//�������ת�任
	//����Ϊ��ת����(�Ƕ�)
	Matrix3& SetRotate_d(float angle)
	{
		float a = angle / 180 * M_PI;
		return SetRotate_r(a);
	}
	//����Ϊ��ת����(����)
	Matrix3& SetRotate_r(float angle)
	{
		//c	 s	0
		//-s c  0
		//0  0  1
		Identity();
		mat3._11 = mat3._22 = cos(angle);
		mat3._12 = sin(angle);
		mat3._21 = -mat3._12;
		//=============================================================
		eM11 = mat3._11; eM12 = mat3._12;
		eM21 = mat3._21; eM22 = mat3._22;
		eDx = mat3._31; eDy = mat3._32;
	}
	//�ھ���Ļ�������ת(�Ƕ�)
	Matrix3& Rotate_d(float angle)
	{
		float a = angle / 180 * M_PI;
		return Rotate_r(a);
	}
	//�ھ���Ļ�������ת(����)
	Matrix3& Rotate_r(float angle)
	{
		Matrix3 tmp;
		tmp.mat3._11 = tmp.mat3._22 = cos(angle);
		tmp.mat3._12 = sin(angle);
		tmp.mat3._21 = -tmp.mat3._12;
		(*this) *= tmp;
		//=============================================================
		eM11 = mat3._11; eM12 = mat3._12;
		eM21 = mat3._21; eM22 = mat3._22;
		eDx = mat3._31; eDy = mat3._32;
		return *this;
	}
};

inline Vector2D operator*(const Vector2D& v, const Matrix3& m)
{
	float _v[3] = { v.x,v.y,1 };
	float _t[3];
	_t[0] = _v[0] * m.mat3._11 + _v[1] * m.mat3._21 + _v[2] * m.mat3._31;
	_t[1] = _v[0] * m.mat3._12 + _v[1] * m.mat3._22 + _v[2] * m.mat3._32;
	//_t[2]=_v[0]*m.mat3._13+_v[1]*m.mat3._23+_v[2]*m.mat3._33;
	//_t[0]/=_t[2];
	//_t[1]/=_t[2];
	return Vector2D(_t[0], _t[1]);
}
inline Vector2D& operator*=(Vector2D& v, const Matrix3& m)
{
	float _v[3] = { v.x,v.y,1 };
	float _t[3];
	v.x = _v[0] * m.mat3._11 + _v[1] * m.mat3._21 + _v[2] * m.mat3._31;
	v.y = _v[0] * m.mat3._12 + _v[1] * m.mat3._22 + _v[2] * m.mat3._32;
	return v;
}