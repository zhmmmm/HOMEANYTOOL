#include "Client.h"

Client *Client::GetInstense()
{
	static Client Obj;

	return &Obj;
}

Client::Client()
{
	m_TcpClient.InisSocket();
}
void Client::RunClient()
{
	m_TcpClient.RunClient();
}
void Client::CloseClient()
{
	m_TcpClient.CloseSocket();
}
TcpClient *Client::GetTcpClient()
{
	return &m_TcpClient;
}


BOOL TcpClient::InisSocket()
{
	//�������绷��
	WSADATA wd;
	WSAStartup(0x0202, &wd);
	//�������ֽ�
	m_ListenSocket = socket(
		AF_INET,
		SOCK_STREAM,
		IPPROTO_TCP);

	//����������ַ��Ϣ�ṹ��
	char Server_ip[256] = "127.0.0.1";
	m_Si = new sockaddr_in;
	m_Si->sin_family = AF_INET;
	m_Si->sin_port = htons(12345);//���������ŵ��Ŀ�
	//m_Si->sin_addr.S_un.S_addr = inet_addr(Server_ip);
	if (inet_pton(AF_INET, Server_ip, (void*)&m_Si->sin_addr) < 0)
	{
		CloseSocket();
		return FALSE;
	}
	if (TcpClient::ConnectServer() == 0)
	{
		CloseSocket();
		return FALSE;
	}
	return TRUE;
}
SOCKET TcpClient::ConnectServer()
{
	if (0 != connect(m_ListenSocket, (sockaddr*)m_Si, sizeof(*m_Si)))
	{
		closesocket(m_ListenSocket);
		WSACleanup();
		return 0;
	}
	return m_ListenSocket;
}
void TcpClient::RunClient()
{

	TcpClient::_Send();//�з��͵ķ���

	TcpClient::_Recv();//�н��յĽ���
	
}
void TcpClient::Sends(const void *Data, int Size)
{
	SENDDATA sd;
	sd.size = sizeof(int) + Size;
	sd.data = (char*)m_MemoryPool.Allocate(sd.size);
	*((int*)sd.data) = Size;
	memcpy(sd.data + sizeof(int), Data, Size);
	sd.send_size = 0;

	m_SendData.push_back(sd);
}
void TcpClient::Recvs(void *Data,int Size)
{
	m_User.User_Dataed(Data,Size,*this);
}
int TcpClient::my_send(SOCKET sock, char* buf, int len)
{
	fd_set fs;
	FD_ZERO(&fs);
	FD_SET(sock, &fs);
	timeval t = { 0, 0 };

	//��·�����жϿ�д��
	select(0, 0, &fs, 0, &t);

	//�������д
	if (0 == fs.fd_count)
		return 0;
	else
	{
		//send�����ķ���ֵ�����SOCKET_ERROR�ͱ�ʾ
		//��ǰ����������ˣ�Ӧ�ùر��׽��֣�������
		//����ֵ��ʾ�������������˶����ֽڣ������
		//��ֵ���ܻ��lenС
		return send(sock, buf, len, 0);
	}
}
int TcpClient::my_recv(SOCKET sock, char* buf, int len)
{
	fd_set fs;
	FD_ZERO(&fs);
	FD_SET(sock, &fs);
	timeval t = { 0, 0 };

	//��·�����жϿɶ���
	select(0, &fs, 0, 0, &t);

	//������ɶ�
	if (0 == fs.fd_count)
		return -2;
	else
	{
		//recv�������Ϊ0���ʾ�Է����ŶϿ�������
		//SOCKET_ERROR��ʾ��������ˣ������������
		//���ǿͻ����Ѿ��Ͽ��ˣ����ǲ���ʹ�������
		//�����ˣ���Ӧ�ùر��׽��֣����򷵻�ֵ�ͱ�
		//ʾ�յ��˶����ֽ�
		return recv(sock, buf, len, 0);
	}
}
int TcpClient::_Send()
{
	for (std::vector<SENDDATA>::iterator it = m_SendData.begin(); it != m_SendData.end();)
	{
		if (it->size == 0)//û�����ݿ��Է���
		{
			return 0;
		}
		else//�����ݿ��Է���
		{
			//�˳���־
			//0�������������
			//1����ʱ���ܷ���
			//2�������������
			int qf = 0;

			//�õ���0�����ݰ�
			SENDDATA* sd = &(*(it));

			//ѭ����������
			while (sd->send_size < sd->size)
			{
				//���ͱ�������
				int r = my_send(
					m_ListenSocket,
					sd->data + sd->send_size,
					sd->size - sd->send_size);

				//��������ʧ��
				if (r <= 0)
				{
					//��ʱ���ܷ���
					if (0 == r)
					{
						qf = 1;
						break;
					}
					//�����������
					else
					{
						qf = 2;
						break;
					}
				}
				else
				{
					//�Ѿ����͵��ֽ����ۻ���send_size��
					sd->send_size += r;
				}
			}

			//��������ѭ���Ĳ�ͬ���з��������
			if (0 == qf)
			{
				//�ͷŸð�ռ�ݵĶ��ڴ�
				m_MemoryPool.Free(sd->data);

				//�����꽫�ð��ӱ����Ƴ�
				it = m_SendData.erase(it);
				//����
				//++it;
			}
			else if (1 == qf)
			{
				//����
				++it;
			}
			else
			{
				//�ӱ���ɾ��
				it = m_SendData.erase(it);
			}
		}
	}
	return 1;
}
int TcpClient::_Recv()
{
	if (m_RecvData.recv_data == NULL)
	{
		m_RecvData.recv_data = (char*)m_MemoryPool.Allocate(m_MaxRecv);

		for (int i = 0; i < m_MaxRecv; i++)
		{
			m_RecvData.recv_data[i] = 0;
		}

		int len = my_recv(m_ListenSocket, m_RecvData.recv_data, 4);
		//*((int*)m_RecvData.recv_data)
		if (len >= 4)
		{
			int AllData = *((int*)m_RecvData.recv_data); //�ٽ�����ô����ֽ����ݾ������
			int len = my_recv(m_ListenSocket, m_RecvData.recv_data, AllData);//���Ž���
			if (len == AllData)//���ݽ�������
			{
				m_RecvData.recv_size = AllData;
				TcpClient::Recvs(m_RecvData.recv_data, m_RecvData.recv_size);
			}
			else
			{
				//���Ƕ����ǰ�������
				exit(0);
			}
		}
	}
	else
	{
		for (int i = 0; i < m_MaxRecv; i++)
		{
			m_RecvData.recv_data[i] = 0;
		}

		int len = my_recv(m_ListenSocket, m_RecvData.recv_data, 4);
		//*((int*)m_RecvData.recv_data)
		if (len >= 4)
		{
			int AllData = *((int*)m_RecvData.recv_data); //�ٽ�����ô����ֽ����ݾ������
			int len = my_recv(m_ListenSocket, m_RecvData.recv_data, AllData);//���Ž���
			if (len == AllData)//���ݽ�������
			{
				m_RecvData.recv_size = AllData;
				TcpClient::Recvs(m_RecvData.recv_data, m_RecvData.recv_size);
			}
			else
			{
				//���Ƕ����ǰ�������
				exit(0);
			}
		}
	}


	return 1;
}
Users *TcpClient::GetUsers()
{
	return &m_User;
}






//==============================================================================

void Users::User_Dataed(const void *Data, int DataSize, TcpClient &Server)
{

	m_RecvPackage.set_data(Data, DataSize);

	int DATAID = INITAGREEMENT;

	if (m_RecvPackage.get_int(&DATAID))
	{
		switch (DATAID)
		{
		case CLIENTEXIT: 
		{
			Users::_Program();
		}break;
		case USER_CLIENTCONNECT:
		{

			char buf[256] = { 0 };
			m_RecvPackage.get_string(buf);

			std::cout << buf << std::endl;
			m_State.Connect = USER_CLIENTCONNECT;
		}break;
		}
	}

}
States *Users::GetState()
{
	return &m_State;
}

SendPackage *Users::GetSendPackage()
{
	return &m_SendPackage;
}
RecvPackage *Users::GetRecvPackage()
{
	return &m_RecvPackage;
}
//=========================================================�ص�
void Users::_Program()
{
	exit(0);
}





SOCKET TcpClient::_Accept(SOCKET Socket)
{
	fd_set Ls;
	FD_ZERO(&Ls);
	FD_SET(Socket, &Ls);
	timeval Time = { 0,0 };
	select(0, &Ls, 0, 0, &Time);
	if (Ls.fd_count > 0)
	{
		sockaddr_in Client_Si;
		int Client_si_Size = sizeof(Client_Si);

		SOCKET Data_Socket = accept(Socket, (sockaddr*)&Client_Si, &Client_si_Size);

		printf("���յ����ԣ���ַ = %d.%d.%d.%d �� �˿ڣ� %d �Ŀͻ�������\n",
			Client_Si.sin_addr.S_un.S_un_b.s_b1,
			Client_Si.sin_addr.S_un.S_un_b.s_b2,
			Client_Si.sin_addr.S_un.S_un_b.s_b3,
			Client_Si.sin_addr.S_un.S_un_b.s_b4,
			Client_Si.sin_port);
		return Data_Socket;
	}
	return INVALID_SOCKET;
}
int TcpClient::_Recv(SOCKET Socket, char *Buf, int Len)
{
	fd_set Rs;
	FD_ZERO(&Rs);
	FD_SET(Socket, &Rs);
	timeval Time = { 0,0 };
	select(0, &Rs, 0, 0, &Time);
	if (Rs.fd_count > 0)
	{
		/*
		//���û�д���recv���ؽ��յ����ֽ���
		If no error occurs, recv returns the number of bytes received.
		//������ӱ����ŵĶϿ�������0
		If the connection has been gracefully closed, the return value is zero.
		//���򽫷���һ��SOCKET_ERROR��-1��
		Otherwise, a value of SOCKET_ERROR is returned,
		//�������ǿ���ͨ��WSAGetLastError����ȡ���Ĵ������
		and a specific error code can be retrieved by calling WSAGetLastError.
		*/
		return recv(Socket, Buf, Len, 0);
	}
	return -2;//��ʾû�н��ܵ����ݣ������׽�����������
}
int TcpClient::_Send(SOCKET Socket, char *Buf, int Len)
{
	fd_set Rs;
	FD_ZERO(&Rs);
	FD_SET(Socket, &Rs);
	timeval Time = { 0,0 };
	select(0, 0, &Rs, 0, &Time);
	if (Rs.fd_count > 0)
	{
		/*
		//���û�д�����ô���ص��Ǳ����Ѿ����͵����ֽ���
		If no error occurs, send returns the total number of bytes sent,
		//��������ֽ������ܱ�Ԥ�ڵ��١��������ܷ���0��
		//�����׽��ֻ��������ģ�ֻ����һ��û�з���ȥ��
		which can be less than the number indicated by len.
		//����Ļ�����һ���׽��ִ���SOCKET_ERROR��-1�����׽��ֱ��Ͽ�����
		Otherwise, a value of SOCKET_ERROR is returned,
		//�������ǿ���ͨ��WSAGetLastError����ȡ���Ĵ������
		and a specific error code can be retrieved by calling WSAGetLastError.
		*/

		return send(Socket, Buf, Len, 0);
	}
	return 0;//��ʾ���߱���д��
}
void TcpClient::CloseSocket()
{
	//�ر��׽���
	closesocket(m_ListenSocket);
	WSACleanup();
	delete m_Si;
	m_Si = NULL;
}