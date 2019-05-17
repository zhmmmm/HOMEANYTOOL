#ifndef __HEIGHT_MAP_H__
#define __HEIGHT_MAP_H__
#include <iostream>
#include <gl/glew.h>
#include <gl/glut.h>

class HeightMap
{
public:
	HeightMap();
	~HeightMap();

	bool CreateFromBMP(
		const char* bmpfile,//�Ҷ�ͼ·��
		float h,//���ɵ��ε����Yֵ
		int xwidth,//x�����������
		int zwidth,//z�����������
		float space//��ʾ��λ���ӵĿ�
		);

	void DrawMap();//���Ƶ���
protected:
private:
	float* mVertext;//��������
	unsigned int* mIndex;//��������
	unsigned int mVertextCount;//�������
	unsigned int mIndexCount;//������
};
#endif