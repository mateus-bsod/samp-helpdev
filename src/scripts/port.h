#ifndef PORT_H
#define PORT_H

#include <string.h>
#include <iostream>

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

bool isPortInUse(int port);

#endif