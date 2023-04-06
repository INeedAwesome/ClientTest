#pragma once

#include <iostream>

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512

#pragma comment (lib, "Ws2_32.lib")

class Client
{
public:
	Client() = default;
	~Client() = default;

	void Run();
	bool Init();

	bool SendAndReceiveData();

	void Terminate();
private:
	WSAData m_WsaData = {};

	struct addrinfo* m_AddrinfoResult = NULL;
	struct addrinfo* m_AddrinfoPtr = NULL;
	struct addrinfo m_AddrinfoHints;

	std::string m_IPAddress;

	SOCKET m_Socket;
};

