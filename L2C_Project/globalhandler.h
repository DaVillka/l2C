#pragma once
#pragma comment (lib, "Ws2_32.lib")       // ���� ������
#include <WinSock2.h>                     // ������ ����������� ������ windows.h
#include <iostream>                       // ��� ������ ��f�������
//#include <Windows.h>
#include <WS2tcpip.h>                     // �������������� f������ ��� ����������� �  ���������� ��f������� � �������
#include <conio.h>
#include <thread>
#include <fstream>
#include <stdio.h>
#include <Windows.h>
#include "writePacket.h"
#include "Config.h"

SOCKET ClientSocket[MAX_PACKET_SIZE];
int AllUserConnectToLoginServer = 0;

