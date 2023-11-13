#include "pch.h"

bool Server::InitializeServerAddress()
{
    int iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0)
    {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return false;
    }
    return true;
}

void Server::CreateSocket()
{
    if (!InitializeServerAddress())
        cout << "Failed to initialize server address" << endl;
    InitListenSocket();
}

void Server::InitListenSocket()
{
    m_ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (m_ListenSocket == INVALID_SOCKET)
    {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
    }
}

void Server::AcceptClientSocket()
{
    m_ClientSocket = accept(m_ListenSocket, NULL, NULL);
    if (m_ClientSocket == INVALID_SOCKET)
    {
        printf("accept failed: %d\n", WSAGetLastError());
        closesocket(m_ListenSocket);
        WSACleanup();
    }
}