//3�׷���
#ifndef _CMATRIX3_H_
#define _CMATRIX3_H_
#include <iostream>
using namespace std;
#include <math.h>
#include "CVictor2D.h"
typedef struct _CMATRIX3 {//3�׷���ṹ��
	union {
		struct {
			double        _11, _12, _13;
			double        _21, _22, _23;
			double        _31, _32, _33;
		};
		double m[3][3];
	};
}CMATRIX3D,*LPCMATRIX3D;

class CMatrix3
{
public:
	//==================================����=========================
	CMatrix3();
	CMatrix3(const CMatrix3& old);
	CMatrix3(double _11,double _12,double _13,double _21,double _22,double _23,double _31,double _32,double _33);
	CMatrix3(double m[3][3]);
	CMatrix3(double** m);

	double GetDet();
	CMatrix3 Transpose();//��ת�þ���
	CMatrix3 Adjoint();//��������
	CMatrix3 Inverse(bool &IsInverse);//�������//����һ���߼����ò��������ж��Ƿ����
	static CMatrix3 GetScaleMtr(double x_ratio,double y_ratio);//�����任����
	static CMatrix3 GetEqlScaleMtr(double s_ratio);//�ȱ����任����
	static CMatrix3 GetRotateMtr(double angle);//��ת����
	static CMatrix3 GetTranslationMtr(double x_m,double y_n);//ƽ��
	static CMatrix3 GetX_Symmetry();//X�ԳƱ任
	static CMatrix3 GetY_Symmetry();//Y�ԳƱ任
	static CMatrix3 GetO_Symmetry();//ԭ��ԳƱ任
	static CMatrix3 Get45_Symmetry();//+45��ԳƱ任
	static CMatrix3 Get_45_Symmetry();//-45��ԳƱ任
	static CMatrix3 Get_Angle_Symmetry(double angle);//���ڹ�ԭ������Ƕ�ֱ�ߵĶԳƱ任
	static CMatrix3 GetX_TiltMtr(double angle);//X���б任
	static CMatrix3 GetY_TiltMtr(double angle);//Y���б任
	CMatrix3 operator + (const CMatrix3& other);
	CMatrix3 operator - (const CMatrix3& other);
	CMatrix3 operator * (const double k);
	CVictor2D operator * (CVictor2D& p);
	CMatrix3 operator * (const CMatrix3& other);
	CMatrix3& operator += (const CMatrix3& other);
	CMatrix3& operator -= (const CMatrix3& other);
	CMatrix3& operator *= (const double k);
	CMatrix3& operator *= (const CMatrix3& other);

	void ShowData(char* MatrixName);
	//==================================����=========================
	_CMATRIX3 m_Matrix;

protected:
private:
};
#endif