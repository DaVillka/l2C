#pragma once
#pragma comment (lib, "Ws2_32.lib")       // либа винсок
#include <WinSock2.h>                     // Должна подключатся раньше windows.h
#include <iostream>                       // для вывода инfормации
//#include <Windows.h>
#include <WS2tcpip.h>                     // Дополнительные fункции для подключения и  получениии инfормации о сервере
#pragma once
#include <conio.h>
#include <thread>
#include <fstream>
#include <stdio.h>
#include <string>
#include <iostream>
#include <Windows.h>
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
#include <stdio.h>
#include <WinUser.h>
#include <string>
#include "HookHelper.h"
#include "structure.h"



void ConsoleCreate()
{
	int hConHandle = 0;
	FILE *fp = 0;
	AllocConsole();
	SetConsoleTitle("Hooked GS with NGSM v0.1");
	HANDLE lStdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle(PtrToUlong(lStdHandle), 0);
	fp = _fdopen(hConHandle, "w");
	*stdout = *fp;
	setvbuf(stdout, NULL, _IONBF, 0);
}


HMODULE hMod = NULL;
HMODULE hEngine = NULL;
HMODULE hWs2_32 = NULL;
SOCKET s_kproxyN = NULL;
void* ThisSendPacket = NULL;
void* ThisAddPacket = NULL;
unsigned char* trampoline[25] = {nullptr};

namespace l2native 
{
	class FMalloc 
	{
	public:
		virtual void* Allocate(size_t sizen, int unk_zero) = 0;
	private:
		virtual void unk_0() = 0;
	public:
		virtual void Free(void* block) = 0;
	};
}

void writebyte(DWORD* eventy, BYTE jmp[8], int bytecount)
{
	if (bytecount == 1)
	{
		memset((char*)&eventy[0],   jmp[0], sizeof(jmp[0]));
		memset((char*)&eventy[0]+1, jmp[1], sizeof(jmp[0]));
		memset((char*)&eventy[0]+2, jmp[2], sizeof(jmp[0]));
		memset((char*)&eventy[0]+3, jmp[3], sizeof(jmp[0]));
		memset((char*)&eventy[0]+4, jmp[4], sizeof(jmp[0]));
	}
	if (bytecount == 2)
	{
		memset((char*)&eventy[0],   jmp[0], sizeof(jmp[0]));
		memset((char*)&eventy[0]+1, jmp[1], sizeof(jmp[0]));
		memset((char*)&eventy[0]+2, jmp[2], sizeof(jmp[0]));
		memset((char*)&eventy[0]+3, jmp[3], sizeof(jmp[0]));
		memset((char*)&eventy[0]+4, jmp[4], sizeof(jmp[0]));
		memset((char*)&eventy[0]+5, jmp[5], sizeof(jmp[0]));
		memset((char*)&eventy[0]+6, jmp[6], sizeof(jmp[0]));
		memset((char*)&eventy[0]+7, jmp[7], sizeof(jmp[0]));
	}
	if (bytecount == 3)
	{
		memset((char*)&eventy[0],   jmp[0], sizeof(jmp[0]));
		memset((char*)&eventy[0]+1, jmp[1], sizeof(jmp[0]));
		memset((char*)&eventy[0]+2, jmp[2], sizeof(jmp[0]));
		memset((char*)&eventy[0]+3, jmp[3], sizeof(jmp[0]));
		memset((char*)&eventy[0]+4, jmp[4], sizeof(jmp[0]));
		memset((char*)&eventy[0]+5, jmp[5], sizeof(jmp[0]));

	}
}


typedef void(_cdecl * UNetworkHandler_SendMessage)(void* This, const char *Format, ...);
typedef void (__fastcall *UNetworkHandler_AddNetworkQueue)(void*, int, NetworkPacket *);
typedef int (WINAPI*  my_sock)( SOCKET s,const char *buf,int len, int flags);
typedef void (__fastcall *UNetworkHandler_RequestAuthLogin)(void* This, int i, wchar_t const *, wchar_t const  *, int but);
typedef void (__fastcall *UNetworkHandler_Tick)(void* This, int i, float flo);
typedef int (WINAPI * my_WSAStartup)(WORD wVersionRequested, LPWSADATA lpWSAData);
typedef SOCKET (WINAPI*my_socket)(int af,int type, int protocol);
typedef int (WSAAPI* my_connect)(SOCKET s, sockaddr_in * name, int namelen);
typedef void (__fastcall *UNetworkHandler_Init)(void*, int, int,class UGameEngine *);

UNetworkHandler_SendMessage USendMessageLogin;
UNetworkHandler_SendMessage USendMessageGame;
UNetworkHandler_AddNetworkQueue UAddNetworkQueue;
UNetworkHandler_Init Init;
my_connect myConnect;
my_socket mysocket;
my_WSAStartup myWSAStartup;
UNetworkHandler_RequestAuthLogin RequestAuthLogin;
UNetworkHandler_Tick Tick;

DWORD returnValueAsm = NULL;
wchar_t  myLogin[255] = L"123";
wchar_t  myPassw[255] = L"123";

my_sock mysend; byte recvByte[5] = {0x8B, 0xFF, 0x55, 0x8B, 0xEC};
my_sock myrecv;

BOOL isAutorise = FALSE;