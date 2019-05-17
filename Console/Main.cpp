#include <iostream>
#include <map>
#include <Vector>
#include <winsock.h>
#pragma comment(lib,"wsock32.lib")
#include <Windows.h>
#include "PASSWORD.h"

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

class PASS
{
	char m_Password[256] = { 0 };
	bool m_True = false;
	bool m_Exit = false;
	int m_Number = 0;
	bool m_PassOk = false;
	const char m_Account[30][256] = {
		"( Account:  c18c15f6e5cbffa1740ac956331c2c23" ,//1979304986
		"( Account: bc1350b3f195f4ccc830130ea6196f32",//2540326113
		"( Account: 27e6521069f26c5e087ed6bb97c79119",//2013534308
		"( Account: 2875af0624e386c3f461f073b9d3d10c",//1405898636
		"( Account: 17150657dfc85a6359aa206d90fd9427",//1428231203
		"( Account: 3e3643a9f0d2d5a7eb038eeca9edea23",//3519165647
		"( Account: 2c993a7c5b0439245dfd9b1b1f297c39",//2996525939
		"( Account: 7d1055319072572c2958125cb8a89b56",//15982683979
		"( Account:7d1055319072572c2958125cb8a89b56@163.com ",//
		"( Account:7d1055319072572c2958125cb8a89b56@163.com ",//
		"( Account:zhm520bn@gmail.com ",//
		"( Account: 1493065d281ef387b7aecf0e48d71d46",//YFKZHM
		"( Account:zhm520bn@yahoo.com ",//
		"(�� " };

	const char m_Password_[30][256] = {
		" Password:zhm.@.723d505516e0c197e42a6be3c0af910e.@ )",
		" Password:zhm.@.723d505516e0c197e42a6be3c0af910e.X )",
		" Password:1155.665.zhm )",
		" Password:zhanghaoman.1314 )",
		" Password:1155.665.@. )",
		" Password:zhm.@.723d505516e0c197e42a6be3c0af910e.W )",
		" Password:zhm.@.723d505516e0c197e42a6be3c0af910e )",
		" Password:zhm.@.723d505516e0c197e42a6be3c0af910e.c )",
		" Password:zhm.@.723d505516e0c197e42a6be3c0af910e.y )",
		" Password:zhm.@.723d505516e0c197e42a6be3c0af910e.C )",
		" Password:zhm.@.723d505516e0c197e42a6be3c0af910e.c )",
		" Password:YFK520UIZHMzhm )",
		" Password:zhm.@.723d505516e0c197e42a6be3c0af910e.c )",
		" �� )" };
public:
	bool EnterPassword()
	{
		std::cout << "����Password��";
		std::cin >> m_Password;

		int len = 0;
		len = strlen(_password);
		for (int i = 0; i <= len; i++)
		{
			if (m_Password[i] != _password[i])
			{
				m_True = false;
				return false;
				break;
			}
		}
		m_True = true;
		return true;
	}
	bool Run()
	{
		while (true)
		{
			if (!m_Exit)
			{
				if (m_True)
				{
					if (m_PassOk == false)
					{
						std::cout << "������ȷ" << std::endl;
						Sleep(500);
					}
					system("cls");
					_PasswordList();
				}
				else
				{
					std::cout << "���벻��ȷ���������룡" << std::endl;
					Sleep(500);
					system("cls");
					EnterPassword();
				}
			}
		}
		return true;
	}
private:
	void _InsetInfo_End(const char *Buf, FILE *File)
	{
		fwrite(Buf, strlen(Buf), 1, File);
		fclose(File);
		File = NULL;
	}
	FILE *_InsetFile_Begin(const char *Account, const char *Password)
	{
		FILE *File = NULL;
		fopen_s(&File, "Text.txt", "w+");
		if (File)
		{
			fwrite(Account, strlen(Account), 1, File);
			fwrite(Password, strlen(Password), 1, File);
			fwrite("\r\n", sizeof("\r\n"), 1, File);
		}
		return File;
	}
	int _PasswordList()
	{
		m_PassOk = true;
		std::cout << " 1979304986 ������Ϣ ��ȡ��Ϣ��1�����ļ����" << std::endl;
		std::cout << " 2540326113 ������Ϣ ��ȡ��Ϣ��2�����ļ����" << std::endl;
		std::cout << " 2013534308 ������Ϣ ��ȡ��Ϣ��3�����ļ����" << std::endl;
		std::cout << " 1405898636 ������Ϣ ��ȡ��Ϣ��4�����ļ����" << std::endl;
		std::cout << " 1428231203 ������Ϣ ��ȡ��Ϣ��5�����ļ����" << std::endl;
		std::cout << " 3519165647 ������Ϣ ��ȡ��Ϣ��6�����ļ����(�˺Ų�����ʹ��)" << std::endl;
		std::cout << " 2996525939 ������Ϣ ��ȡ��Ϣ��7�����ļ����" << std::endl;
		std::cout << " ΢���˺�   ������Ϣ ��ȡ��Ϣ��8�����ļ����" << std::endl;
		std::cout << " 163�ʼ�    ������Ϣ ��ȡ��Ϣ��9�����ļ����" << std::endl;
		std::cout << " Adobe      ������Ϣ ��ȡ��Ϣ��10�����ļ����" << std::endl;
		std::cout << " Google Email ������Ϣ ��ȡ��Ϣ��11�����ļ����" << std::endl;
		std::cout << "�ս�֧������,Bank������Ϣ��5000�����ļ��������ֱ����ʾ" << std::endl;
		std::cout << "˿��֮· 3.1 ������Ϣ ��ȡ��Ϣ��12�����ļ����" << std::endl;
		std::cout << "Yahoo Email ������Ϣ ��ȡ��Ϣ��13�����ļ����" << std::endl;
		std::cout << "�������е�14" << std::endl;
		std::cout << "                                          " << std::endl;
		std::cout << " 5176 / 0(�˳�)����������Ϣ������ţ�";
		std::cin >> m_Number;

		switch (m_Number)
		{
		case 1: {_1979304986(m_Account[0], m_Password_[0]); }; break;
		case 2: {_2540326113(m_Account[1], m_Password_[1]); }; break;
		case 3: {_2013534308(m_Account[2], m_Password_[2]); }; break;
		case 4: {_1405898636(m_Account[3], m_Password_[3]); }; break;
		case 5: {_1428231203(m_Account[4], m_Password_[4]); }; break;
		case 6: {_3519165647(m_Account[5], m_Password_[5]); }; break;
		case 7: {_2996525939(m_Account[6], m_Password_[6]); }; break;
		case 8: {_MicrosoftAccount(m_Account[7], m_Password_[7]); }; break;
		case 9: {_163EmailAccount(m_Account[8], m_Password_[8]); }; break;
		case 10: {_AdobeAccount(m_Account[9], m_Password_[9]); }; break;
		case 11: {_GoogleAccount(m_Account[10], m_Password_[10]); }; break;
		case 12: {_Silk_Road(m_Account[11], m_Password_[11]); }; break;
		case 13: {_YahooAccount(m_Account[12], m_Password_[12]); }; break;
		case 14: {_Any(m_Account[13], m_Password_[13]); }; break;
		case 0: {exit(0); }; break;
		case 5000: {__Password__(); }; break;
		case 5176: {exit(0); }; break;
		}
		return -1;
	}
	//���¶����ֵܺ�
	void _1979304986(const char *Account, const char *Password)
	{
		FILE *File = _InsetFile_Begin(Account, Password);
		const char *Buf = "2010������,5e30d7a2f1825abb3ef4a72d78430ebeΪ��ʱ��һ������,��ǰ�ʼ��ͲƸ�ͨ����,΢�ƶ�������Ϊ��aad3b6efbea6ac3d2fa97e14098f8eed.@.723d505516e0c197e42a6be3c0af910e.M\r\n \
���֤�ţ��ҵ�,�Ƹ�ͨ��֧��Ϊ1f51e4ba2df7f5f3b239126a0398f03d.���ù�������:5e30d7a2f1825abb3ef4a72d78430ebe zhm.@.5201314.c zhm.@.5201314.m \r\n \
��ǰ�ĲƸ�ͨ����������֤Ϊ:cpy.zhanghaoman ������ zhanghaoman.cpy\r\n \
��ǰ�󶨵��ֻ�����Ϊ��7d1055319072572c2958125cb8a89b56 ��Щ��Ϣͷ����ʵ��";
		_InsetInfo_End(Buf, File);
		ExportFunction();
	}
	void _2540326113(const char *Account, const char *Password)
	{
		FILE *File = _InsetFile_Begin(Account, Password);
		const char *Buf = "2012�����룬�ù������룺cpy.zhanghaoman zhm.@.5201314.x zhm.@.5201314.X �Ѱ��ֻ�\r\n \
�ҵ����֤��Ϣ���ߣ�δ�����������ܣ��󶨵��ֻ��ţ�7d1055319072572c2958125cb8a89b56";
		_InsetInfo_End(Buf, File);
		ExportFunction();
	}
	void _2013534308(const char *Account, const char *Password)
	{
		FILE *File = _InsetFile_Begin(Account, Password);
		const char *Buf = "2014�����룬�ù������룺1155.665.zhm ����ʱ������,����һֱδ����Ŷ �Ѱ��ֻ�\r\n \
�ҵ����֤��Ϣ���ߣ�δ�����������ܣ��󶨵��ֻ��ţ�7d1055319072572c2958125cb8a89b56";
		_InsetInfo_End(Buf, File);
		ExportFunction();
	}
	void _1405898636(const char *Account, const char *Password)
	{
		FILE *File = _InsetFile_Begin(Account, Password);
		const char *Buf = "2014�����룬�ù������룺zhanghaoman.1314  ����ʱ������,����һֱδ����Ŷ δ���ֻ�\r\n \
�ҵ����֤��Ϣ���ߣ�δ������������";
		_InsetInfo_End(Buf, File);
		ExportFunction();
	}
	void _1428231203(const char *Account, const char *Password)
	{
		FILE *File = _InsetFile_Begin(Account, Password);
		const char *Buf = "2014�����룬�ù������룺1155.665.cha ����ʱ������ �Ѱ��ֻ�\r\n \
�ҵ����֤��Ϣ���ߣ�δ�����������ܣ��󶨵��ֻ��ţ�7d1055319072572c2958125cb8a89b56";
		_InsetInfo_End(Buf, File);
		ExportFunction();
	}
	void _3519165647(const char *Account, const char *Password)
	{
		FILE *File = _InsetFile_Begin(Account, Password);
		const char *Buf = "2017�����룬�ù������룺zhm.@.5201314.W ,�Ѱ��ֻ�\r\n \
�ҵ����֤��Ϣ���ߣ�δ�����������ܣ��󶨵��ֻ��ţ�7d1055319072572c2958125cb8a89b56";
		_InsetInfo_End(Buf, File);
		ExportFunction();
	}
	void _2996525939(const char *Account, const char *Password)
	{
		FILE *File = _InsetFile_Begin(Account, Password);
		const char *Buf = "2015�����룬�ù������룺zhm.@.5201314 ,����һֱδ����Ŷ �Ѱ��ֻ�\r\n \
�ҵ����֤��Ϣ���ߣ�δ�����������ܣ��󶨵��ֻ��ţ�7d1055319072572c2958125cb8a89b56";
		_InsetInfo_End(Buf, File);
		ExportFunction();
	}
	void _MicrosoftAccount(const char *Account, const char *Password)
	{
		FILE *File = _InsetFile_Begin(Account, Password);
		const char *Buf = "2018���� �󶨵��ֻ��ţ�15982683979 �󶨵��ʼ���15982683979@163.com";
		_InsetInfo_End(Buf, File);
		ExportFunction();
	}
	void _163EmailAccount(const char *Account, const char *Password)
	{
		FILE *File = _InsetFile_Begin(Account, Password);
		const char *Buf = "2014���� �󶨵��ֻ��ţ�15982683979 ������ֻ���Ȩ���룺��Ϊzhm520";
		_InsetInfo_End(Buf, File);
		ExportFunction();
	}
	void _AdobeAccount(const char *Account, const char *Password)
	{
		FILE *File = _InsetFile_Begin(Account, Password);
		const char *Buf = "2018���� �󶨵��ֻ��ţ�15982683979";
		_InsetInfo_End(Buf, File);
		ExportFunction();
	}
	void _GoogleAccount(const char *Account, const char *Password)
	{
		FILE *File = _InsetFile_Begin(Account, Password);
		const char *Buf = "2016���� �󶨵��ֻ��ţ�15982683979";
		_InsetInfo_End(Buf, File);
		ExportFunction();
	}
	void __Password__()
	{
		std::cout << "    926498    " << std::endl;
		std::cout << "����ɹ���" << std::endl;
		Sleep(2000);
		m_Number = 0;
	}
	void _Silk_Road(const char *Account, const char *Password)
	{
		FILE *File = _InsetFile_Begin(Account, Password);
		const char *Buf = "2019.217 ���� �ָ�pin:926498 \r\n \
һЩ��ַ��https://xtg6zekabihp7sol.onion/ \r\n \
http://k4btcoezc5tlxyaf.onion/";
		_InsetInfo_End(Buf, File);
		ExportFunction();
	}
	void _YahooAccount(const char *Account, const char *Password)
	{
		FILE *File = _InsetFile_Begin(Account, Password);
		const char *Buf = "2017���� �󶨵��ֻ��ţ�15982683979";
		_InsetInfo_End(Buf, File);
		ExportFunction();
	}
	void _Any(const char *Account, const char *Password)
	{
		FILE *File = _InsetFile_Begin(Account, Password);
		const char *Buf = "OCT 3Dmax ��Ƶ����HitFilm �ȸ� ���� �Ż� NordVPN Bestgor ΢�źʹ�ŵ�����һ��,ͬ����  ���붼�ǣ�zhm.@.723d505516e0c197e42a6be3c0af910e.c \r\n \
         ���رҵĵڶ�������Ҳ�� pinһ�� ����Ҳ�� ����Ҳ�� CSDN�Ǵ�д��C ����Ҳ�� ��ͨ:cpy.zhm zhm.1f51e4ba2df7f5f3b239126a0398f03d 163�ʼ�����Ȩ\r\n \
         Ϊzhm520 \r\n \
         Unity:15982683979@163.com/zhm520 zhm.@.723d505516e0c197e42a6be3c0af910e.Unity\r\n \
         cocos:zhmmmm zhm520\r\n \
         GITTHUB zhmmmm zhm.@.723d505516e0c197e42a6be3c0af910e.c\r\n \
         �Ĵ���������:15982683979/15982683979@163.com  1f51e4ba2df7f5f3b239126a0398f03d\r\n \
         Codewarrior���: 15982683979@163.com zhm.@.723d505516e0c197e42a6be3c0af910e.c\r\n \
         �ٶ���:15982683979 17856af0ef8cd344480bc9c1d6683622\r\n \
         ֧����:15982683979 15982683979.1\r\n \
         �ſ�:15982683979@163.com zhm.@.723d505516e0c197e42a6be3c0af910e.Y \r\n \
         ���п�������Ϊ�Ǽ�λ����\r\n \
         6688����:zhmmmm zhm520\r\n \
         6m5m�ز���:zhmmmm zhm520 \r\n \r\n \
         name,url,username,password\r\n \r\n \
         dl.reg.163.com, https://dl.reg.163.com/webzj/m163_1.0.1/pub/index_dl.html, \r\n \
		15982683979,zhanghaoman.1314 \r\n \
         webzj.reg.163.com, https ://webzj.reg.163.com/v1.0.1/pub/index_dl.html,\r\n \
		15982683979,zhm.@.5201314. \r\n \
         gps.66ve.com, http ://gps.66ve.com/reg.asp,\r\n \
		zhmmmm,zhm.@.520 \r\n \
         www.6m5m.com, http ://www.6m5m.com/register.html,\r\n \
			 zhmmmm,zhm520 \r\n \
         adobeid - na1.services.adobe.com, https ://adobeid-na1.services.adobe.com/renga-idprovider/pages/login.do,\r\n \
			 15982683979@163.com,zhm.@.5201314.C \r\n \
         www.bestgore.com, http ://www.bestgore.com/wp-login.php,\r\n \
			 zhm520bnmmm,zhm.@.5201314. \r\n \
         www.bestgore.com, https ://www.bestgore.com/wp-login.php,\r\n \
			 zhm520bnmmm,zhm.@.5201314. \r\n \
         blockchain.info, https ://blockchain.info/wallet/,\r\n \
			 41c1b0e8-0deb-4c71-b5d6-997b7a29cf35,yangyu.5201314 \r\n \
         www.break.com, http ://www.break.com/user/register,\r\n \
			 zhm520bn@gmail.com,zhm.@.5201314.c \r\n \
         cocos2d - x.org, https ://cocos2d-x.org/u/login,\r\n \
			 15982683979@163.com,zhm520 \r\n \
         www.facebook.com, https ://www.facebook.com/login/,\r\n \
			 15982683979,zhm.@.5201314.c \r\n \
         fxhome.com, https ://fxhome.com/getting-started,\r\n \
			 yanpingZha,zhm.@.5201314.c \r\n \
         fxhome.com, https ://fxhome.com/express,\r\n \
			 zhm520bn@gmail.com,zhm.@.5201314.c \r\n \
         github.com, https ://github.com/login,\r\n \
			 zhm520bn@gmail.com,zhm.@.5201314.c \r\n \
         www.incredibuild.com, https ://www.incredibuild.com/FreeVisualStudioLicense,\r\n \
			 zhmmmm,zhmmmm520 \r\n \
         www.instagram.com, https ://www.instagram.com/accounts/signup,\r\n \
			 chayanping,zhm.@.5201314.c \r\n \
         signup.jp.leagueoflegends.com, https ://signup.jp.leagueoflegends.com/ja/signup/index,\r\n \
			 zhmmmm,zhm520 \r\n \
         login.live.com, https ://login.live.com/oauth20_authorize.srf,\r\n \
			 15982683979@163.com,zhm.@.5201314.c \r\n \
         localbitcoins.com, https ://localbitcoins.com/accounts/login/,\r\n \
			 zhm520bn@gmail.com,zhm.mmmmm 41c1b0e8-0deb-4c71-b5d6-997b7a29cf35 \r\n \
           \
         41c1b0e8 - 0deb - 4c71 - b5d6 - 997b7a29cf35 \r\n \
         qzhlk9jfq0um44dfqa3t249swm2talepxqsxm8tsrx \r\n \
         yangyu.5201314 \r\n \
         zhm.@.5201314.c ���ε�½һ�������� \r\n \
           \
         www.miscopy.com, http://www.miscopy.com/wp-login.php,\r\n \
			 zhm520bnmmm,zhm.@.5201314. \r\n \
         myspace.com, https ://myspace.com/zhm520bnmmm,\r\n \
			 zhm520bn@gmail.com,zhm.@.5201314.c \r\n \
         neowallet.cn, https ://neowallet.cn/,,\r\n \
			 zhm.@.5201314.c \r\n \
         ucp.nordvpn.com, https ://ucp.nordvpn.com/login/,\r\n \
			 zhm520bn@gmail.com,zhm.@.5201314.c \r\n \
         www.nxp.com, https ://www.nxp.com/,\r\n \
			 15982683979@163.com,zhm.@.5201314.c \r\n \
         otcbtc.com, https ://otcbtc.com/,\r\n \
			 15982683979@163.com,zhm.@.5201314.c \r\n \
         api.paymentwall.com, https ://api.paymentwall.com/pwaccount/signup,\r\n \
			 zhm520bn@gmail.com,zhm.@.5201314.c \r\n \
         www.paypal.com, https ://www.paypal.com/signin,\r\n \
			 zhm520bn@gmail.com,zhm.@.5201314.c \r\n \
         www.pornhub.com, https ://www.pornhub.com/signup,\r\n \
			 zhmmmm,zhm520 \r\n \
         auth.quakenet.org, https ://auth.quakenet.org/create_account,\r\n \
			 ANGyu12,zhm520 \r\n \
         auth.quakenet.org, https ://auth.quakenet.org/create_account,\r\n \
			 ZHMmmm,[zhm520] \r\n \
         auth.riotgames.com, https ://auth.riotgames.com/authorize,\r\n \
			 zhmmmm,zhm520 \r\n \
         www.shiyanlou.com, https ://www.shiyanlou.com/courses/605,\r\n \
			 15982683979@163.com,zhm.@.5201314.c \r\n \
         twitter.com, https ://twitter.com/signup,\r\n \
			 +8615982683979,zhm.@.5201314.c \r\n \
         id.unity.com, https ://id.unity.com/ja/conversations/7d6cc20e-c90b-4388-9ba5-1c7f3135854d00df,\r\n \
			 15982683979@163.com,zhm.@.5201314.Unity \r\n \
         login.yahoo.com, https ://login.yahoo.com/account/challenge/password,\r\n \
			 zhm520bn,zhm.@.5201314.c \r\n \
         login.yahoo.com, https ://login.yahoo.com/account/challenge/password,\r\n \
			 zhm520bn@yahoo.com,zhm.@.5201314.c \r\n ";
		_InsetInfo_End(Buf, File);
		ExportFunction();
	}


	void ExportFunction()
	{
		std::cout << "����ɹ���" << std::endl;
		Sleep(500);
		m_Number = 0;
	}
	const char *_password = "themyqq321";
};

int Main()
{
	//PASS Obj;
	//Obj.EnterPassword();
	//Obj.Run();


	PASSENGINE Obj;
	Obj.Run();

	//2010������, 5e30d7a2f1825abb3ef4a72d78430ebeΪ��ʱ��һ������, ��ǰ�ʼ��ͲƸ�ͨ����, ΢�ƶ�������Ϊ��aad3b6efbea6ac3d2fa97e14098f8eed.@.723d505516e0c197e42a6be3c0af910e.M\n���֤�ţ��ҵ�, �Ƹ�ͨ��֧��Ϊ1f51e4ba2df7f5f3b239126a0398f03d.���ù�������:5e30d7a2f1825abb3ef4a72d78430ebe zhm.@.5201314.c zhm.@.5201314.m

	//һ������ĳ���

	//wchar_t SelfName[] = L"C:\\Users\\Administrator\\Desktop\\Experiment\\Debug\\Experiment.exe";
	//wchar_t TargetName[] = L"C:\\Users\\Administrator\\Desktop\\Experiment\\Experiment\\exe.c";


	//CopyFile(SelfName,TargetName,FALSE);

	system("pause");
	return 0;
}
//GetModuleFileName(NULL,Buf,BufSize);��ȡ��ǰ���г���·��
//CopyFile(SelfName,TargetName,FALSE);�����ļ�,������,������������Name.Դ��׺,������
//GetSystemDirectory(Buf,BufSize);��ȡϵͳĿ¼