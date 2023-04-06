#include "stdafx.h"
#include "Client.h"

void Client::Run()
{
	m_IPAddress = "192.168.1.123";
	Init();

	SendAndReceiveData();

	Terminate();
}

bool Client::Init()
{
	int res = 0;
	res = WSAStartup(MAKEWORD(2, 2), &m_WsaData);
	if (res != 0)
	{
		printf("WSAStartup failed: %d\n", res);
		return false;
	}

	ZeroMemory(&m_AddrinfoHints, sizeof(m_AddrinfoHints));
	{
		m_AddrinfoHints.ai_family = AF_INET;
		m_AddrinfoHints.ai_socktype = SOCK_STREAM;
		m_AddrinfoHints.ai_protocol = IPPROTO_TCP;
	}

	res = getaddrinfo(m_IPAddress.c_str(), DEFAULT_PORT, &m_AddrinfoHints, &m_AddrinfoResult); // "192.168.1.123"
	if (res != 0) 
	{
		printf("getaddrinfo failed: %d\n", res);
		WSACleanup();
		return false;
	}

	m_Socket = INVALID_SOCKET;
	m_Socket = socket(m_AddrinfoResult->ai_family, m_AddrinfoResult->ai_socktype, m_AddrinfoResult->ai_protocol);
	if (m_Socket == INVALID_SOCKET)
	{
		printf("socket failed: %d\n", WSAGetLastError());
		freeaddrinfo(m_AddrinfoResult);
		WSACleanup();
		return false;
	}
	m_AddrinfoPtr = m_AddrinfoResult;
	freeaddrinfo(m_AddrinfoResult);

	res = connect(m_Socket, m_AddrinfoPtr->ai_addr, (int)m_AddrinfoPtr->ai_addrlen);
	if (res == SOCKET_ERROR)
	{
		printf("connect failed: %d\n", WSAGetLastError());
		closesocket(m_Socket);
		WSACleanup();
		return false;
	}

	return true;
}

bool Client::SendAndReceiveData()
{
	
	std::string sendString = "dcdlose";
	send(m_Socket, sendString.c_str(), sendString.size() + 1, 0);
	
	int amountBytesRecv;
	bool running = true;
	while (running)
	{
		running = false;

		char receivingBuffer[DEFAULT_BUFLEN];
		amountBytesRecv = recv(m_Socket, receivingBuffer, DEFAULT_BUFLEN, 0); // if success, amountBytesRecv is amount of bytes received from the server

		if (amountBytesRecv > 0)
		{
			// we got something from the server.
			// this->HandleFromServer(receivingBuffer, amountBytesRecv);
		}
		else if (amountBytesRecv == -1)
		{
			// we disconnected (server closed).
			running = false;
		}
		else
		{
			// we didnt get something from the server.
		}
	}



	return true;
}

void Client::Terminate()
{
	if (m_Socket)
	{
		send(m_Socket, "close", 6, 0);
	}

	closesocket(m_Socket);
	WSACleanup();
}
