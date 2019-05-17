#include "CMatrix3.h"
CMatrix3::CMatrix3()
{
	memset(m_Matrix.m,0,sizeof(double)*9);
}
CMatrix3::CMatrix3(const CMatrix3& old)
{
	memcpy(m_Matrix.m,old.m_Matrix.m,sizeof(double)*9);
}
CMatrix3::CMatrix3(double _11,double _12,double _13,double _21,double _22,double _23,double _31,double _32,double _33)
{
	m_Matrix._11=_11;m_Matrix._12=_12;m_Matrix._13=_13;
	m_Matrix._21=_21;m_Matrix._22=_22;m_Matrix._23=_23;
	m_Matrix._31=_31;m_Matrix._32=_32;m_Matrix._33=_33;
}
CMatrix3::CMatrix3(double m[3][3])
{
	memcpy(m_Matrix.m,m,sizeof(double)*9);
}
CMatrix3::CMatrix3(double** m)
{
	memcpy(m_Matrix.m[0],m[0],sizeof(double)*3);
	memcpy(m_Matrix.m[1],m[1],sizeof(double)*3);
	memcpy(m_Matrix.m[2],m[2],sizeof(double)*3);
}
double CMatrix3::GetDet()
{
	double det=m_Matrix._11*m_Matrix._22*m_Matrix._33 
		+ m_Matrix._12*m_Matrix._23*m_Matrix._31 
		+ m_Matrix._13*m_Matrix._21*m_Matrix._32
		- m_Matrix._13*m_Matrix._22*m_Matrix._31
		- m_Matrix._12*m_Matrix._21*m_Matrix._33
		- m_Matrix._11*m_Matrix._23*m_Matrix._32;
	return det;
}
double GetDetRank2(double src[2][2])//��2������ʽֵ
{
	double det=src[0][0]*src[1][1]- src[0][1]*src[1][0];
	return det;
}
double GetCofactor(int Row,int Col,_CMATRIX3 src)//ȡ��������2�״�������ʽ
{
	double temp[4]={};
	double det=0;
	int index=0;
	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			if (i!=Row&&j!=Col)
			{
				temp[index++]=src.m[i][j];
			}
		}
	}
	det=temp[0]*temp[3]-temp[1]*temp[2];
	det*=pow(double(-1),Row+Col);
	return det;	
}
CMatrix3 CMatrix3::Transpose()//��ת�þ���
{
	CMatrix3 temp;
	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			temp.m_Matrix.m[i][j]=m_Matrix.m[j][i];
		}
	}
	return temp;
}
CMatrix3 CMatrix3::Adjoint()//��������
{
	CMatrix3 temp;
	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			temp.m_Matrix.m[j][i]=GetCofactor(i,j,m_Matrix);
		}
	}
	return temp;
}
CMatrix3 CMatrix3::Inverse(bool &IsInverse)//�������//����һ���߼����ò��������ж��Ƿ����
{
	CMatrix3 temp;//��ʼΪ0����
	double det=GetDet();
	if (det!=0)
	{
		IsInverse=true;
		temp=Adjoint();
		temp*=(1/det);
		return temp;
	}
	IsInverse=false;
	return temp;
}
CMatrix3 CMatrix3::GetScaleMtr(double x_ratio,double y_ratio)//�����任����
{
CMatrix3 T(x_ratio,0,0,
		   0,y_ratio,0,
		   0,0,1);
return T;
}
CMatrix3 CMatrix3::GetEqlScaleMtr(double s_ratio)//�ȱ����任����
{
CMatrix3 T(1/s_ratio,0,0,
		   0,1/s_ratio,0,
		   0,0,1);//���������ǲ�ϣ��Ҫ������ж�H�Ƿ�Ϊ1
return T;
}
CMatrix3 CMatrix3::GetRotateMtr(double angle)//��ת����
{
CMatrix3 T(cos(angle),sin(angle),0,
		   -sin(angle),cos(angle),0,
		   0,0,1
		   );
return T;
}
CMatrix3 CMatrix3::GetTranslationMtr(double x_m,double y_n)//ƽ��
{
CMatrix3 T(1,0,0,
		   0,1,0,
		   x_m,y_n,1
		   );
return T;
}
CMatrix3 CMatrix3::GetX_Symmetry()//X�ԳƱ任
{
CMatrix3 T(1,0,0,
		   0,-1,0,
		   0,0,1
		   );
return T;
}
CMatrix3 CMatrix3::GetY_Symmetry()//Y�ԳƱ任
{
	CMatrix3 T(-1,0,0,
		0,1,0,
		0,0,1
		);
	return T;
}
CMatrix3 CMatrix3::GetO_Symmetry()//ԭ��ԳƱ任
{
	CMatrix3 T(-1,0,0,
		0,-1,0,
		0,0,1
		);
	return T;
}
CMatrix3 CMatrix3::Get45_Symmetry()//+45��ԳƱ任
{
	CMatrix3 T( 0,1,0,
				1,0,0,
				0,0,1
		);
	return T;
}
CMatrix3 CMatrix3::Get_45_Symmetry()//-45��ԳƱ任
{
	CMatrix3 T(0,-1,0,
		-1,0,0,
		0,0,1
		);
	return T;
}
CMatrix3 CMatrix3::Get_Angle_Symmetry(double angle)//���ڹ�ԭ������Ƕ�ֱ�ߵĶԳƱ任
{
CMatrix3 T(cos(2*angle),sin(2*angle),0,
		   sin(2*angle),-cos(2*angle),0,
		   0,0,1);
return T;
}
CMatrix3 CMatrix3::GetX_TiltMtr(double angle)//X���б任
{
	CMatrix3 T(1,tan(angle),0,
		0,1,0,
		0,0,1
		);
	return T;
}
CMatrix3 CMatrix3::GetY_TiltMtr(double angle)//Y���б任
{
	CMatrix3 T(1,0,0,
		tan(angle),1,0,
		0,0,1
		);
	return T;
}
CMatrix3 CMatrix3::operator + (const CMatrix3& other)
{
	CMatrix3 temp;
	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			temp.m_Matrix.m[i][j]=m_Matrix.m[i][j]+other.m_Matrix.m[i][j];
		}
	}
	return temp;
}
CMatrix3 CMatrix3::operator - (const CMatrix3& other)
{
	CMatrix3 temp;
	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			temp.m_Matrix.m[i][j]=m_Matrix.m[i][j]-other.m_Matrix.m[i][j];
		}
	}
	return temp;
}
CMatrix3 CMatrix3::operator * (const double k)
{
	CMatrix3 temp;
	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			temp.m_Matrix.m[i][j] = m_Matrix.m[i][j]*k;
		}
	}
	return temp;
}
CVictor2D CMatrix3::operator * (CVictor2D& p)
{
	CMatrix3 O(p.GetX(),p.GetY(),1,0,0,0,0,0,0);
	O*=(*this);
	CVictor2D ret(O.m_Matrix._11,O.m_Matrix._12);
	return ret;
}
CMatrix3 CMatrix3::operator * (const CMatrix3& other)
{
	CMatrix3 temp;
	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			for (int k=0;k<3;k++)
			{
				temp.m_Matrix.m[i][j]+=m_Matrix.m[i][k]*other.m_Matrix.m[k][j];
			}
		}
	}
	return temp;
}
CMatrix3& CMatrix3::operator += (const CMatrix3& other)
{
	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			m_Matrix.m[i][j]+=other.m_Matrix.m[i][j];
		}
	}
	return *this;
}
CMatrix3& CMatrix3::operator -= (const CMatrix3& other)
{
	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			m_Matrix.m[i][j]-=other.m_Matrix.m[i][j];
		}
	}
	return *this;
}
CMatrix3& CMatrix3::operator *= (const double k)
{
	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			m_Matrix.m[i][j]*=k;
		}
	}
	return *this;
}
CMatrix3& CMatrix3::operator *= (const CMatrix3& other)
{
	CMatrix3 temp;
	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			for (int k=0;k<3;k++)
			{
				temp.m_Matrix.m[i][j]+=m_Matrix.m[i][k]*other.m_Matrix.m[k][j];
			}
		}
	}
	memcpy(m_Matrix.m,temp.m_Matrix.m,sizeof(double)*9);
	return *this;
}
void CMatrix3::ShowData(char* MatrixName)
{
	if (MatrixName!=NULL)
	{
		cout<<MatrixName<<"[3��3] = \n";
	}else
	{
		cout<<"A[3��3] = \n";
	}
	cout<<"�q                                      �r\n";
	for (int i=0;i<3;i++)
	{
		cout<<"��";
		for (int j=0;j<3;j++)
		{
			printf("%12.6lf",m_Matrix.m[i][j]);
			if (j<2)
			{
				cout<<",";
			}
		}
		cout<<"��"<<endl;
	}
	cout<<"�t                                      �s\n";
}