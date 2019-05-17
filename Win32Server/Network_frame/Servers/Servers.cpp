#include "Servers.h"



Server::Server()
{
	m_TcpServer.Init(12345, 10, 1024);
}
void Server::RunServer()
{
	m_TcpServer.Run();//tcp������������

	TcpServer::EVENT Event;//�¼�

	while (m_TcpServer.GetEvent(&Event))
	{
		switch (Event.type)
		{
		case _TSE_CONNECTED://�ͻ������ӻص�
		{
			m_User.User_Connected(Event.sock, m_TcpServer);
		}break;
		case _TSE_DISCONNECTED://�ͻ��˶Ͽ��ص�
		{
			m_User.User_Disconnected(Event.sock, m_TcpServer);
		}break;
		case _TSE_DATA://�ͻ������ݻص�
		{
			m_User.User_Dataed(Event.sock, Event.data, Event.size, m_TcpServer);
		}break;
		}
	}

}
void Server::CloseServer()
{
	m_TcpServer.End();
}



SOCKET TcpServer::my_accept(SOCKET listen_sock)
{
	//�����׽��ּ��ϣ����׽��ּ���
	//�з�������׽��֣�Ȼ���ж���
	//�Ƿ�ɶ�
	fd_set fs;
	FD_ZERO(&fs);
	FD_SET(listen_sock, &fs);
	timeval t = { 0, 0 };

	//��·����
	select(0, &fs, 0, 0, &t);

	//����fs�ĳ����жϵ�ǰ�Ƿ�����
	//������������
	if (0 == fs.fd_count)
		return INVALID_SOCKET;
	else
	{
		sockaddr_in si;
		int si_size = sizeof(si);
		SOCKET sock = accept(
			fs.fd_array[0],
			(sockaddr*)&si,
			&si_size);
		return sock;
	}
}
int TcpServer::my_send(SOCKET sock, char* buf, int len)
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
int TcpServer::my_recv(SOCKET sock, char* buf, int len)
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
void TcpServer::_Delete(CLIENT* client)
{
	//�ͷŷ�������
	for (int i = 0; i < (int)client->send_data.size(); ++i)
		m_MemoryPool.Free(client->send_data[i].data);

	//�ͷŽ�������
	m_MemoryPool.Free(client->recv_data);

	//�ر��׽���
	closesocket(client->sock);
}
void TcpServer::_Accept()
{
	//�жϵ�ǰ�����Ƿ�����
	if (m_Max == m_Clients.size())
		return;

	//��������
	SOCKET sock = my_accept(m_Listen);
	if (INVALID_SOCKET == sock)
		return;

	//�ͻ������
	CLIENT client;
	client.sock = sock;
	client.recv_data = (char*)m_MemoryPool.Allocate(sizeof(int) + m_MaxRecv);
	client.recv_size = 0;
	m_Clients.push_back(client);

	//Ͷ��"�ͻ������ӽ��������"�¼�
	EVENT e;
	e.type = _TSE_CONNECTED;
	e.sock = sock;
	e.data = 0;
	e.size = 0;
	m_Events.push_back(e);
}
void TcpServer::_Send()
{
	//������
	std::vector<CLIENT>::iterator it;

	//�������пͻ��˷������ǵ�����
	for (it = m_Clients.begin(); it != m_Clients.end(); )
	{
		//û�з��͵�����
		if (it->send_data.size() == 0)
			++it;
		//�д����͵�����
		else
		{
			//�˳���־
			//0�������������
			//1����ʱ���ܷ���
			//2�������������
			int qf = 0;

			//�õ���0�����ݰ�
			SENDDATA* sd = &it->send_data[0];

			//ѭ����������
			while (sd->send_size < sd->size)
			{
				//���ͱ�������
				int r = my_send(
					it->sock,
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
				it->send_data.erase(it->send_data.begin());

				//����
				++it;
			}
			else if (1 == qf)
			{
				//����
				++it;
			}
			else
			{
				//ɾ�������������Ϣ
				_Delete(&(*it));

				//Ͷ��"�ͻ��˶Ͽ�����"�¼�
				EVENT e;
				e.type = _TSE_DISCONNECTED;
				e.sock = it->sock;
				e.data = 0;
				e.size = 0;
				m_Events.push_back(e);

				//�ӱ���ɾ��
				it = m_Clients.erase(it);
			}
		}
	}
}
void TcpServer::_Recv()
{
	//������
	std::vector<CLIENT>::iterator it;

	//�������пͻ��˽�������
	for (it = m_Clients.begin(); it != m_Clients.end(); )
	{
		//���ڵõ�����recv����Ҫ���ն೤������
		int len;

		//���ν��վͽ��ճ���
		if (it->recv_size < sizeof(int))
		{
			//֮���recv����len��ô��
			len = sizeof(int) - it->recv_size;
		}
		//���ν��վͽ�������
		else
		{
			//�õ��������ݰ����ܳ���
			int all_len = *((int*)it->recv_data);

			//֮���recv����len��ô��
			len = all_len - (it->recv_size - sizeof(int));
		}

		//��������
		int r = my_recv(
			it->sock,
			it->recv_data + it->recv_size,
			len);

		//��������������
		if (r > 0)
		{
			//�ܽ��ճ��ȵ���
			it->recv_size += r;

			//���һ�����ĳ��Ƚ������
			if (it->recv_size > sizeof(int))
			{
				//�õ��������ݰ����ܳ���
				int all_len = *((int*)it->recv_data);

				//���������Ѿ��������
				if (it->recv_size - sizeof(int) == all_len)
				{
					//Ͷ��"�ͻ��˷��͹�������"�¼�
					EVENT e;
					e.type = _TSE_DATA;
					e.sock = it->sock;
					e.data = (char*)m_MemoryPool.Allocate(all_len);
					memcpy(e.data, it->recv_data + sizeof(int), all_len);
					e.size = all_len;
					m_Events.push_back(e);

					//�������ݸ�����������
					it->recv_size = 0;
				}
			}

			//����
			++it;
		}
		else if (-2 == r)
		{
			//����
			++it;
		}
		else if (-1 == r || 0 == r)
		{
			//ɾ�������������Ϣ
			_Delete(&(*it));

			//Ͷ��"�ͻ��˶Ͽ�����"�¼�
			EVENT e;
			e.type = _TSE_DISCONNECTED;
			e.sock = it->sock;
			e.data = 0;
			e.size = 0;
			m_Events.push_back(e);

			//�ӱ���ɾ��
			it = m_Clients.erase(it);
		}
	}
}
bool TcpServer::Init(unsigned short port, int max, int max_recv)
{
	//�������
	if (port <= 1024 || max < 1 || max_recv < 1)
		return false;

	//�õ�����
	m_Max = max;
	m_MaxRecv = max_recv;

	//�������绷��
	WSADATA wd;
	WSAStartup(0x0101, &wd);

	//���������׽���
	m_Listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//����ַ��Ϣ�ṹ��
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(port);
	si.sin_addr.S_un.S_addr = ADDR_ANY;

	//�󶨼����׽��ֺ͵�ַ��Ϣ�ṹ��
	bind(m_Listen, (sockaddr*)&si, sizeof(si));

	//���ü����׽���Ϊ��������ģʽ
	listen(m_Listen, 10);

	return true;
}
void TcpServer::Run()
{
	//��������
	_Accept();

	//��������
	_Send();

	//��������
	_Recv();
}
bool TcpServer::GetEvent(EVENT* e)
{
	if (m_Events.size() == 0)
		return false;

	//�õ��¼�
	*e = m_Events[0];

	//ɾ���¼�
	m_Events.erase(m_Events.begin());

	return true;
}
void TcpServer::FreeEventMemory(EVENT* e)
{
	if (_TSE_DATA == e->type)
		m_MemoryPool.Free(e->data);
}
bool TcpServer::Send(SOCKET sock, const void* data, int size)
{
	//����ָ���׽���
	int index = 0;
	for (; index < (int)m_Clients.size(); ++index)
	{
		if (m_Clients[index].sock == sock)
			break;
	}

	//û���ҵ�ָ���ͻ���
	if (index == (int)m_Clients.size())
		return false;

	//������������
	SENDDATA sd;
	sd.size = sizeof(int) + size;
	sd.data = (char*)m_MemoryPool.Allocate(sd.size);
	*((int*)sd.data) = size;
	memcpy(sd.data + sizeof(int), data, size);
	sd.send_size = 0;

	m_Clients[index].send_data.push_back(sd);

	return true;
}
bool TcpServer::Disconnect(SOCKET sock)
{
	//����ָ���׽���
	int index = 0;
	for (; index < (int)m_Clients.size(); ++index)
	{
		if (m_Clients[index].sock == sock)
			break;
	}

	//û���ҵ�ָ���ͻ���
	if (index == (int)m_Clients.size())
		return false;

	//�Ͽ�����
	_Delete(&m_Clients[index]);

	//Ͷ��"�ͻ��˶Ͽ�����"�¼�
	EVENT e;
	e.type = _TSE_DISCONNECTED;
	e.sock = sock;
	e.data = 0;
	e.size = 0;
	m_Events.push_back(e);

	//�ӱ���ɾ��
	m_Clients.erase(m_Clients.begin() + index);

	return true;
}
void TcpServer::End()
{
	//�Ͽ��������
	for (int i = 0; i < (int)m_Clients.size(); ++i)
		_Delete(&m_Clients[i]);
	m_Clients.clear();

	//�ͷż����׽���
	closesocket(m_Listen);

	//�ر����绷��
	WSACleanup();
}


//=============================================
SOCKET _Accept(SOCKET Socket)
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
int _Recv(SOCKET Socket, char *Buf, int Len)
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
int _Send(SOCKET Socket, char *Buf, int Len)
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




//==============================================================================
void User::User_Connected(SOCKET Socket, TcpServer &Server)
{
	std::cout <<" "<< Socket << " �û�����" << std::endl;


	m_SendPackage.clear();
	m_SendPackage.add_int(USER_CLIENTCONNECT);
	m_SendPackage.add_string("���,��ϲ�����ӳɹ���");
	Server.Send(Socket, m_SendPackage.data(), m_SendPackage.size());


	//char buf[256] = { 0 };
	//recvfrom(Socket,buf,256,2,NULL,NULL);
	//if (buf)
	//{
	//	int var = 0;
	//}
}
void User::User_Disconnected(SOCKET Socket, TcpServer &Server)
{
	std::cout <<" "<< Socket << " �û��Ͽ�" << std::endl;
}
void User::User_Dataed(SOCKET Socket, const void *Data, int DataSize, TcpServer &Server)
{
	//std::cout << "�û����ַ������ݣ�"<<*((int*)(char*)Data + 4)<<std::endl;

	m_RecvPackage.set_data(Data, DataSize);

	int DATAID = INITAGREEMENT;

	if (m_RecvPackage.get_int(&DATAID))//ǰ�ĸ��ֽ�Ϊ���ݵ��ܳ�,���ĸ��ֽ�Ϊ���ݵ�Э��,�ٺ���Ϊ����
	{
		switch (DATAID)
		{
		case SERVEREXIT:
		{
			User::_Program();
		}break;
		case 123:
		{
			int temp = 0;
			m_RecvPackage.get_int(&temp);
			std::cout << temp << std::endl;
		
		}break;
		}
	}

}
























//=========================================================�ص�
void User::_Program()
{
	exit(0);
}



