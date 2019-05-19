#include <iostream>
#include <map>
#include <Vector>
#include <winsock.h>
#pragma comment(lib,"wsock32.lib")
#include <Windows.h>
#include "ATBAudioEngine.h"

#define Main main

//GetCurrentProcess();//��ȡ��ǰ���̵ľ��
//
//CreateRemoteThread(/*ָ��ĳ�����̵ľ��*/, );//����Զ�̽���,����������ע��
//CreateThread();//����Զ�̽���
//
//OpenProcess();//ͨ������ID��ȡ�ý��̵ľ��
//
//LoadLibrary();
//
//WriteProcessMemory(/*ָ�����̵ľ����
//				   ָ��д���ڴ����ʼ��ַ
//				   ,ָ��Ҫд������ݵĻ�����,
//				   ָ��д�����ݵĳ���,
//				   ����ʵ��д�����ݵĳ���*/);//д��Ŀ�������
//
//VirtualAllocEx(/*
//			   ָ��Ҫ�����ڴ�Ľ��̾��,
//			   ָ���������ʼλ��,
//			   ָ�����볤��,
//			   ָ�������ڴ��״̬����,
//			   ָ�������ڴ���ڴ�����
//			   */);//��Ŀ����������ڴ�,�������뵽���ڴ�����ʼ��ַ
//BeginUpdateResourceA();
//UpdateResourceA();
//EndUpdateResourceA();


class Sort
{
public:
	void M(int *Arr, int Len)
	{
		for (int i = 0; i < Len; i++)
		{
			for (int j = i + 1; j < Len; j++)
			{
				if (Arr[i] > Arr[j])
				{
					Arr[i] = Arr[i] ^ Arr[j];
					Arr[j] = Arr[i] ^ Arr[j];
					Arr[i] = Arr[i] ^ Arr[j];
				}
			}
		}
	}
	void X(int *Arr, int Len)
	{
		int Temp = 0;
		for (int i = 0; i < Len - 1; i++)
		{
			Temp = i;
			for (int j = i + 1; j < Len; j++)
			{
				if (Arr[Temp] > Arr[j])
				{
					Temp = j;
				}
			}

			int temp = Arr[i];
			Arr[i] = Arr[Temp];
			Arr[Temp] = temp;
		}
	}
	void C(int *Arr, int Len)
	{
		int TempData = 0;
		int i = 0;
		int j = 0;
		for (i = 1; i < Len; i++)
		{
			j = i;
			TempData = *(Arr + i);
			while (j > 0 && TempData < Arr[j - 1])
			{
				Arr[j] = Arr[j - 1];
				j--;
			}
			Arr[j] = TempData;
		}
	}
	void T(int *Arr, int Len)
	{
		for (int n = 1; n <= 100; n *= 10)
		{
			int Temp[10][100] = { 0 };
			for (int i = 0; i < Len; i++)
			{
				int m = (Arr[i] / n) % 10;
				Temp[m][i] = Arr[i];
			}
			int k = 0;
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < Len; j++)
				{
					if (Temp[i][j] != 0)
					{
						Arr[k] = Temp[i][j];
						k++;
					}
				}
			}
		}
	}
	void K(int *Arr, int low, int high)
	{
		if (low >= high)
		{
			return;
		}
		int first = low;
		int last = high;
		int key = Arr[first];/*���ֱ�ĵ�һ����¼��Ϊ����*/

		while (first < last)
		{
			while (first < last && Arr[last] >= key)
			{
				--last;
			}

			Arr[first] = Arr[last];/*���ȵ�һ��С���Ƶ��Ͷ�*/

			while (first < last && Arr[first] <= key)
			{
				++first;
			}

			Arr[last] = Arr[first];
			/*���ȵ�һ������Ƶ��߶�*/
		}
		Arr[first] = key;/*�����¼��λ*/
		K(Arr, low, first - 1);
		K(Arr, first + 1, high);
	}
	void Z(int *Arr, int Len)
	{
		for (int i = 1; i < Len; i++)
		{
			int tmp = Arr[i];
			int low = 0;
			int high = i - 1;

			// �����۰룬Ѱ�Һ��ʵĲ���λ��  
			while (low <= high)
			{
				int mid = (low + high) / 2;

				if (tmp > Arr[mid])
				{
					low = mid + 1;
				}
				else
				{
					high = mid - 1;
				}
			}
			// ���ν�Ԫ�غ���  
			for (int j = i; j > low; j--)
			{
				Arr[j] = Arr[j - 1];
			}
			Arr[low] = tmp;
		}
	}
};

BOOL BASS_Init(const char *ProjectPath_Debug)
{
	char Str[256] = "copy C:\\Windows\\SysWOW64\\bass.dll ";
	strcat_s(Str, 256, ProjectPath_Debug);
	int State = system(Str);
	return TRUE;
}



void ComputerName_Ip(char *ch0, char *ch1)
{
	char buf[256] = "";
	hostent *ph = NULL;//struct hostent *ph = NULL;
	WSADATA w;
	WSAStartup(0x0101, &w);//��һ�б�����ʹ���κ�SOCKET����ǰд��


	gethostname(buf, 256);
	memcpy_s(ch0, 256, buf, 256);
	std::string hostName = buf;//�˴���ñ�������

	ph = gethostbyname(buf);
	const char *IP = inet_ntoa(*((struct in_addr *)ph->h_addr_list[0]));//�˴���ñ���IP
	memcpy_s(ch1, 256, IP, 256);

	std::cout << "���������" << hostName.c_str() << std::endl;
	std::cout << "�����IP��" << IP << std::endl;

	WSACleanup();
}

int Main()
{



	ATA->InitAudioEngine();
	ATA->PlayMusics_s("������۹�.mp3");
	std::cout << "��ʱ�䣺" << ATA->GetTimeMinute("������۹�.mp3") << std::endl;

	std::cout << "����ʱ�䣺" << ATA->GetCurTimeMinute("������۹�.mp3") << std::endl;

	ATA->SetTimeMinute("������۹�.mp3", 3.0);



	//wchar_t SelfName[] = L"C:\\Users\\Administrator\\Desktop\\Experiment\\Debug\\Experiment.exe";
	//wchar_t TargetName[] = L"C:\\Users\\Administrator\\Desktop\\Experiment\\Experiment\\exe.c";

	//CopyFile(SelfName,TargetName,FALSE);

	system("pause");
	return 0;
}
//GetModuleFileName(NULL,Buf,BufSize);��ȡ��ǰ���г���·��
//CopyFile(SelfName,TargetName,FALSE);�����ļ�,������,������������Name.Դ��׺,������
//GetSystemDirectory(Buf,BufSize);��ȡϵͳĿ¼

