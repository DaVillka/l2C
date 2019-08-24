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
#include <conio.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <thread>
#include <TlHelp32.h>
#include <windows.h>
#include <Tlhelp32.h>
#include <tchar.h>
#include <conio.h>
#include <WinUser.h>
#include <string>
#include <Windows.h>
#include <random>
#include "writePacket.h"
#include "StructurePlayer.h"

#define MAX_PACKET_SIZE    (1024)
#define MAX_USER        5

#define STAGE_ZERO              0
#define STAGE_REQUESTAUTCHLOGIN 1
#define STAGE_CHARACTERCREATE   2
#define MAXPLAYERACC            7


SOCKET ClientSocket[MAX_PACKET_SIZE];
int AllUserConnectToLoginServer = 0;
DWORD ObjectID = 270000000;
DWORD dStagePlayer = STAGE_ZERO;
SYSTEMTIME sysTime;