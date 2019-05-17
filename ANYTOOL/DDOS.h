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
	char *GetSendData() { return m_Sendto_Buffer; }
private:
	void CloseSocket();
	//CheckSum:����У��͵��Ӻ��� 
	USHORT checksum(USHORT *buffer, int size);
	void CheckSum();
};