#pragma once
#include <iostream>
#include <vector>

#include "../Memory/Memory.h"//�ڴ��

#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"Ws2_32.lib")


#include "../Package/SendPackage.h"
#include "../Package/RecvPackage.h"
#include "../TCP/TCPPROTOCOLFAMILY.h"

typedef struct STATE
{
	int Connect = 0;
}States;

class TcpClient;
class Users
{
	SendPackage m_SendPackage;
	RecvPackage m_RecvPackage;


	States m_State;
public:


	void User_Dataed(const void *Data, int DataSize, TcpClient &Server);
	States *GetState();

	SendPackage *GetSendPackage();
	RecvPackage *GetRecvPackage();
private:
	void _Program();
};


class TcpClient
{

	SOCKET m_ListenSocket;
	sockaddr_in *m_Si = NULL;
	Users m_User;
	int m_MaxRecv = 1000;//�����ܳ���
public:
	BOOL InisSocket();
	SOCKET ConnectServer();
	void RunClient();
	void CloseSocket();
	void Sends(const void *Data, int Size);
	void Recvs(void *Data, int Size);
	Users *GetUsers();
private:
	SOCKET _Accept(SOCKET Socket);
	int _Recv(SOCKET Socket, char *Buf, int Len);
	int _Send(SOCKET Socket, char *Buf, int Len);



	//�ڴ��
	MemoryPool m_MemoryPool;
	//�������ݰ�
	struct SENDDATA
	{
		//�������ݵ��׵�ַ
		char* data = NULL;
		//�������ݵ��ܳ���
		int size = 0;
		//�Ѿ����͵ĳ���
		int send_size = 0;
	};
	//��������
	struct RECVDATA
	{
		char* recv_data = NULL;
		int recv_size = 0;
	};

	std::vector<SENDDATA> m_SendData;
	RECVDATA m_RecvData;

	//����-1�������������
    //����0�����ͻ�����������ʱ���ܷ�������
    //����>0���Ѿ������˶����ֽ�
	static int my_send(SOCKET sock, char* buf, int len);

	//����-2�����ջ������ǿյĵ�ǰ���ɶ�
    //����-1�������������
    //����0���Է����ŶϿ�
    //����>0����ȡ�˶����ֽ�
	static int my_recv(SOCKET sock, char* buf, int len);

	int _Send();
	int _Recv();



};


#define GETCLIENT_TCP                                                 Client::GetInstense()->GetTcpClient()
#define GETCLIENTSENDPACKAGE                                          GETCLIENT_TCP->GetUsers()->GetSendPackage()
#define GETCLIENTRECVPACKAGE                                           GETCLIENT_TCP->GetUsers()->GetRecvPackage()



class Client
{

	TcpClient m_TcpClient;

public:

	static Client *GetInstense();

	Client();
	void RunClient();//���������
	void CloseClient();
	TcpClient *GetTcpClient();
};

//=======================================================
