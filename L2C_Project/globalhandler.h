#pragma once
#pragma comment (lib, "Ws2_32.lib")       // либа винсок
#include <WinSock2.h>                     // Должна подключатся раньше windows.h
#include <iostream>                       // для вывода инfормации
//#include <Windows.h>
#include <WS2tcpip.h>                     // Дополнительные fункции для подключения и  получениии инfормации о сервере
#include <conio.h>
#include <thread>
#include <fstream>
#include <stdio.h>
#include <Windows.h>
#include "writePacket.h"
#include "Config.h"

SOCKET ClientSocket[MAX_PACKET_SIZE];
int AllUserConnectToLoginServer = 0;

