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
    //////////////////
    //Create server///
    //////////////////
    Server& sv = Server::GetInstance();
    sv.CreateSocket(); //Create ListenSocket and ClientSocket later

    /*For a server to accept client connections,
    it must be bound to a network address within the system
    */
    int tmp = bind(sv.m_ListenSocket, sv.result->ai_addr, (int)sv.result->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(sv.result);
        closesocket(sv.m_ListenSocket);
        WSACleanup();
        return 1;
    }
    //the server must then listen on that IP address and port for incoming connection requests
    if (listen(sv.m_ListenSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        printf("Listen failed with error: %ld\n", WSAGetLastError());
        closesocket(sv.m_ListenSocket);
        WSACleanup();
        return 1;
    }

    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    // Receive until the peer shuts down the connection
    sv.AcceptClientSocket();
    do
    {
        iResult = recv(sv.m_ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0)
        {
            printf("Bytes received: %d\n", iResult);
            //Display the message
            for (size_t i = 0; i < iResult; i++)
            {
                cout << recvbuf[i] ;
            }
            cout << endl;

            // Echo the buffer back to the sender
            //int iSendResult = send(sv.m_ClientSocket, recvbuf, iResult, 0);
            //if (iSendResult == SOCKET_ERROR)
            //{
            //    printf("send failed: %d\n", WSAGetLastError());
            //    closesocket(sv.m_ClientSocket);
            //    WSACleanup();
            //    return 1;
            //}
            //printf("Bytes sent: %d\n", iSendResult);
        }
        //else if (iResult == 0)
        //    printf("Connection closing...\n");
        //else
        //{
        //    printf("recv failed: %d\n", WSAGetLastError());
        //    closesocket(sv.m_ClientSocket);
        //    WSACleanup();
        //    return 1;
        //}
        iResult = 0;
    } while (iResult > 0);

    char c;
    cin >> c;

    iResult = shutdown(sv.m_ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR)
    {
        printf("shutdown failed: %d\n", WSAGetLastError());
        closesocket(sv.m_ClientSocket);
        WSACleanup();
        return 1;
    }
    WSACleanup();

	return 0;
}