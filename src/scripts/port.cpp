#include "./port.h"

bool isPortInUse(int port)
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET)
        return true; 

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    bool inUse = bind(sock, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR;

    closesocket(sock);
    WSACleanup();

    return inUse;
}