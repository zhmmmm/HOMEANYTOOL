#include "HeightMap.h"
#include "TextureManager.h"
#include <Windows.h>


HeightMap::HeightMap()
{
	mVertext=NULL;//��������
	
	mIndex=NULL;//��������
	mVertextCount=0;//�������
	mIndexCount=0;//������
}
HeightMap::~HeightMap()
{
	if (mVertext)
	{
		delete [] mVertext;
		mVertext = NULL;
	}
	if (mIndex)
	{
		delete [] mIndex;
		mIndex = NULL;
	}
	mVertextCount = mIndexCount = 0;
}

bool HeightMap::CreateFromBMP(
				   const char* bmpfile,//�Ҷ�ͼ·��
				   float h,//���ɵ��ε����Yֵ
				   int xwidth,//x�����������
				   int zwidth,//z�����������
				   float space//��ʾ��λ���ӵĿ�
				   )
{
	if (!bmpfile)
	{
		return false;
	}
	
	FILE* pf=NULL;
	fopen_s(&pf,bmpfile,"rb");
	if (!pf)
	{
		return false;
	}

	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;
	fread(&bf,sizeof(bf),1,pf);
	fread(&bi,sizeof(bi),1,pf);

	if (bf.bfType !=0x4d42||bi.biBitCount!=24)
	{
		fclose(pf);
		return false;
	}

	unsigned char* pColor=new unsigned char[bi.biSizeImage];
	fread_s(pColor, bi.biSizeImage,1,bi.biSizeImage,pf);
	fclose(pf);

	float wantedx = xwidth * space;
	float wantedz = zwidth * space;

	if (xwidth+1<bi.biWidth)
	{
		xwidth = bi.biWidth-1;
	}
	float spacex = wantedx/xwidth;
	

	if (zwidth+1<bi.biHeight)
	{
		zwidth = bi.biHeight-1;
	}
	float spacey = wantedz/zwidth;

	int realx = xwidth + 1;
	int realz = zwidth + 1;

	mVertextCount = realx*realz;
	mVertext = new float[mVertextCount*3];
	mIndexCount = xwidth*zwidth*2*3;
	mIndex = new unsigned int[mIndexCount];

	int lineCount = bi.biSizeImage/bi.biHeight;

	for (int i=0;i<realz;i++)
	{
		//���㵱ǰ�ǵڼ���
		int lineindex = i/float(realz-1)*(bi.biHeight-1);

		//�����м�������ɫ��ָ��
		unsigned char* pLine = pColor+lineCount*lineindex;

		for (int j=0;j<realx;j++)
		{
			int rowindex = j/float(realx-1)*(bi.biWidth-1);
			//ȡ�����ж�Ӧ����ɫ���ص�ָ��
			unsigned char* pix = pLine+rowindex*3;
			//��Ӧ�����ָ��
			float* point = mVertext + (i*realx + j)*3;

			//���㶥��x,y,z
			point[0] = -wantedx/2+j*spacex;
			point[1] = h* pix[0]/255.0f;
			point[2] = -wantedz/2+i*spacey;
		}
	}

	delete [] pColor;
	int qindex = 0;
	for (int i=0;i<xwidth;i++)
	{
		for (int j=0;j<zwidth;j++)
		{
			unsigned int* pindex = mIndex + qindex*6;
			//һ����������������
			pindex[0] = i*realx+j;
			pindex[1] = (i+1)*realx + j;
			pindex[2] = (i+1)*realx + j+1;

			pindex[3] = i*realx+j;
			pindex[4] = (i+1)*realx + j+1;
			pindex[5] = i*realx+j+1;
			qindex++;
		}
	}
	return true;
}

void HeightMap::DrawMap()//���Ƶ���
{
	//�����ģʽ��ǰ���߿�
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glVertexPointer(3,GL_FLOAT,0,mVertext);
	glDrawElements(GL_TRIANGLES,mIndexCount,GL_UNSIGNED_INT,mIndex);
}