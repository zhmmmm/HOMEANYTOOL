//4�׷���
#ifndef _CMATRIX4_H_
#define _CMATRIX4_H_
#include <iostream>
#include <math.h>
using namespace std;

typedef struct _CMATRIX4 {//4�׷���ṹ��
	union {
		struct {
			double        _11, _12, _13, _14;
			double        _21, _22, _23, _24;
			double        _31, _32, _33, _34;
			double        _41, _42, _43, _44;
		};
		double m[4][4];
	};
}CMATRIX4D,*LPCMATRIX4D;

class CMatrix4
{
public:
	//==================================����=========================
	CMatrix4();
	CMatrix4(const CMatrix4& old);
	CMatrix4(double _11,double _12,double _13,double _14,
		double _21,double _22,double _23,double _24,
		double _31,double _32,double _33,double _34,
		double _41,double _42,double _43,double _44
		);
	CMatrix4(double m[4][4]);
	CMatrix4(double** m);

	double GetDet();
	CMatrix4 Transpose();//��ת�þ���
	CMatrix4 Adjoint();//��������
	CMatrix4 Inverse(bool &IsInverse);//�������//����һ���߼����ò��������ж��Ƿ����

	CMatrix4 operator + (const CMatrix4& other);
	CMatrix4 operator - (const CMatrix4& other);
	CMatrix4 operator * (const double k);
	CMatrix4 operator * (const CMatrix4& other);
	CMatrix4& operator += (const CMatrix4& other);
	CMatrix4& operator -= (const CMatrix4& other);
	CMatrix4& operator *= (const double k);
	CMatrix4& operator *= (const CMatrix4& other);

	void ShowData(char* MatrixName);
	//==================================����=========================
	_CMATRIX4 m_Matrix;
protected:
private:
};
#endif