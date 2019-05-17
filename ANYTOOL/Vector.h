#pragma once
#include "stdafx.h"
#include <cmath>
#include <cassert>

#define ISFloatZero(x)	abs(x)<=0.00001f
//��ά������
class Vector2D
{
public:
	float x, y;
public:
	Vector2D() :x(0), y(0) {}
	Vector2D(int n) :x(n), y(n) {}
	Vector2D(float n) :x(n), y(n) {}
	Vector2D(int _x, int _y) :x(float(_x)), y(float(_y)) {}
	Vector2D(float _x, float _y) :x(_x), y(_y) {}
	Vector2D(int _x, float _y) :x(float(_x)), y(_y) {}
	Vector2D(float _x, int _y) :x(_x), y(float(_y)) {}
	//��Ϊ��Ա�Ǵ���ֵ�ģ�û���漰���ڴ棬���Կ���
	//��д���������ͬ�ำֵ����������ͬ��

	//����������
	//������ģ
	float length()
	{
		return sqrtf(x*x + y * y);
	}
	float lengthSquare()
	{
		return x * x + y * y;
	}
	//�����ĵ�λ��
	Vector2D& Normalized()
	{
		float len = sqrtf(x*x + y * y);
		assert(!ISFloatZero(len));
		x /= len;
		y /= len;
		return *this;
	}
	//��һ����λ����
	Vector2D Normalize()
	{
		float len = sqrtf(x*x + y * y);
		assert(!ISFloatZero(len));
		Vector2D temp(x / len, y / len);
		return temp;
	}

	//�����ӷ�
	Vector2D operator + (const Vector2D& t)
	{
		Vector2D temp(x + t.x, y + t.y);
		return temp;
	}
	//+=
	Vector2D& operator += (const Vector2D& t)
	{
		x += t.x;
		y += t.y;
		return *this;
	}
	//-
	Vector2D operator - (const Vector2D& t)
	{
		Vector2D temp(x - t.x, y - t.y);
		return temp;
	}
	//-=
	Vector2D& operator -= (const Vector2D& t)
	{
		x -= t.x;
		y -= t.y;
		return *this;
	}
	//*k(����)
	Vector2D operator * (float k) const
	{
		Vector2D temp(x*k, y*k);
		return temp;
	}
	///k(����)
	Vector2D operator / (float k) const
	{
		assert(!ISFloatZero(k));
		Vector2D temp(x / k, y / k);
		return temp;
	}
	//*=k(����)
	Vector2D& operator *= (float k)
	{
		x *= k, y *= k;
		return *this;
	}
	///=k(����)
	Vector2D& operator /= (float k)
	{
		assert(!ISFloatZero(k));
		x /= k, y /= k;
		return *this;
	}

	//���|a|��|b|cos(ab)
	float dot(const Vector2D& t)
	{
		return x * t.x + y * t.y;
	}
	//���|a|��|b|sin(ab)
	float cross(const Vector2D& t)
	{
		return x * t.y - t.x*y;
	}
	//��Ƕ�
	float angle_r(const Vector2D& t)
	{
		float len1 = sqrtf(x*x + y * y);//���ģ
		float len2 = sqrtf(t.x*t.x + t.y*t.y);//���ģ
		len1 *= len2;
		assert(!ISFloatZero(len1));
		float dt = x * t.x + y * t.y;//���dot	
		float c = dt / len1;//�������ֵ
		float a = acosf(c);//�����Ǻ�����Ƕ�
		return a;//����ֵ��
	}
	//��ͶӰ
	Vector2D project(const Vector2D& t)
	{
		float dt = dot(t);
		float sqt = t.x*t.x + t.y*t.y;
		Vector2D temp = t * dt / sqt;
		return temp;
	}
};

