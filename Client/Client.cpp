#include "pch.h"

Client::Client()
{
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
}

void Client::ResolveServerAddress()
{// Resolve the server address and port
    int iResult = getaddrinfo("localhost", DEFAULT_PORT, &hints, &result);
    if (iResult != 0)
    {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
    }
    ptr = result;
}

bool Client::InitConnectSocket()
{
    m_ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
        ptr->ai_protocol);
    if (m_ConnectSocket == INVALID_SOCKET)
    {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return false;
    }
    return true;
}

void Client::CreateSocket()
{
    if (!InitConnectSocket())
        cout << "Failed to initialize server's connect socket" << endl;
}

void Client::ConnectSocket(const sockaddr* addr, int addrlen)
{// Connect to server
    int iResult = connect(m_ConnectSocket, addr, (int)addrlen);
    if (iResult == SOCKET_ERROR)
    {
        closesocket(m_ConnectSocket);
        m_ConnectSocket = INVALID_SOCKET;
    }
    if (m_ConnectSocket == INVALID_SOCKET)
    {
        printf("Unable to connect to server!\n");
        WSACleanup();
    }
}
