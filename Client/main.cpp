#include "pch.h"

int main()
{
	WSADATA wsaData;
	int iResult;

    //Initializing Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        printf("WSAStartup failed: %d\n", iResult);
        WSACleanup();
        return 1;
    }
    ////////////////////////
    /////Create Client//////
    ////////////////////////
    Client* cl = new Client();
    cl->ResolveServerAddress();
    cl->CreateSocket();
    cl->ConnectSocket(cl->ptr->ai_addr, cl->ptr->ai_addrlen);

    int recvbuflen = DEFAULT_BUFLEN;
    const char* sendbuf = "this is a test";
    char recvbuf[DEFAULT_BUFLEN];

    // Send an initial buffer
    iResult = send(cl->m_ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(cl->m_ConnectSocket);
        WSACleanup();
        return 1;
    }

    printf("Bytes Sent: %ld\n", iResult);

    do {
        iResult = recv(cl->m_ConnectSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0)
            printf("Bytes received: %d\n", iResult);
        else if (iResult == 0)
            printf("Connection closed\n");
        else
            printf("recv failed: %d\n", WSAGetLastError());
    } while (iResult > 0);
	return 0;
}