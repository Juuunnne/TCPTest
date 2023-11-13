#pragma once

class Client
{
public:
    Client();
    ~Client() {}

    void ResolveServerAddress();

    void CreateSocket();
    void ConnectSocket(const sockaddr* addr, int addrlen);

    struct addrinfo
        * result = NULL,
        * ptr = NULL,
        hints;
    SOCKET m_ConnectSocket = INVALID_SOCKET;
private:
    bool InitConnectSocket();
};