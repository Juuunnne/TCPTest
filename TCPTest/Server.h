#pragma once

class Server
{
public:
    Server()
    {
        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;
        CreateSocket();
    }
    ~Server() {}

    static Server& GetInstance()
    {
        static Server instance;
        return instance;
    }

    bool InitializeServerAddress();
    void CreateSocket();
    void InitListenSocket();
    void AcceptClientSocket();

    SOCKET m_ListenSocket = INVALID_SOCKET;
    SOCKET m_ClientSocket = INVALID_SOCKET;
    struct addrinfo
        * result = NULL,
        * ptr = NULL,
        hints;
};