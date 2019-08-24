#include "global.h"

 int start_client();
 int cheksock = 0;
  int MyAddMessage (char* buffer);

void _fastcall SendMessage_hook(void* This, const char *Format, ...)
{
	//if (strlen(Format) == 3)  return ((UNetworkHandler_SendMessage)trampol2)(This, Format);
	ThisSendPacket = This;
	//printf("\nThis -> %X\n", This);
	
	printf("Data-> %s: ", Format);
	char buf[10240];
	int size = 0, len;
	wchar_t *wstr;

	va_list args;
	va_start(args, Format);
 
	while (*Format != 0)
	{
		switch (*Format)
		{
		case 'c':
			*(unsigned char*)(buf + size) = va_arg(args, unsigned char);
			size++;
			break;
		case 'h':
			*(unsigned short int*) (buf + size) = va_arg(args, unsigned short int);
			size += 2;
			break;
		case 'd':
			*(unsigned int*)(buf + size) = va_arg(args, unsigned int);
			size += 4;
			break;
		case 'Q':
			*(unsigned __int64*)(buf + size) = va_arg(args, unsigned __int64);
			size += 8;
			break;
		case 'b':
			len = va_arg(args, unsigned int);
			memcpy(buf + size, va_arg(args, void*), len);
			size += len;
			break;
		case 'x':
			{
				DWORD addrLogin = 0x20787F04;//0x20786F04;
				DWORD addrPassw = 0x20787F86;//0x20786F22;
				wchar_t* login = (wchar_t *)((DWORD)addrLogin);
				wchar_t* passw = (wchar_t *)((DWORD)addrPassw);
				len = wcslen(login) * 2 + 2;
				memcpy(buf + size, login, len);
				size += len;

				len = wcslen(passw) * 2 + 2;
				memcpy(buf + size, passw, len);
				size += len;
				wprintf(L"Login: %ls | Password: %ls", login, passw);
			}
			break;
		case 'S':
			wstr = va_arg(args, wchar_t*);
			if (wstr == 0)
			{
				len = 2;
				*(unsigned short int*) (buf + size) = 0;
			}
			else
			{
				len = wcslen(wstr) * 2 + 2;
				memcpy(buf + size, wstr, len);
			}
			size += len;
			break;
		}
		Format++;
	}
 
	va_end(args);
	//byte sev[1024] = {0};
	
	
	//for (int g = 0; g < size; g++) sev[g] = buf[g];

	//if (sev[0] == 0x12) {for (int g = 0; g < size; g++) printf("%02X ", sev[g]);printf("\n");}
	//for (int g = 0; g < size; g++) printf("%02X ", sev[g]);printf("\n");
	//return _SendMessage2(This, "b", size, buf);
	char sendpck[20480] = {"c>"};
	for (int h=0; h < size; h++)
	{
		char hhh[1024] = {0};
		sprintf(hhh, "%02X ", (byte)buf[h]);//выводим по байту
		char* fff = new char[strlen(hhh)];
		sprintf(fff,hhh);
		strcat(sendpck, fff);
		delete fff;
		//printf("%02X ", buf[h]);//выводим по байту
	}
	printf("SPack-> %s\n", sendpck);

	//if (sev[0] == 0xD0) return;
	
	send(s_kproxyN, buf, size, 0);
	
}
void __fastcall UNetworkHandler_AddNetworkQueue_hook(void* This, int i, NetworkPacket* packet)
{
	
	char ty[5];
	//This_Call = This;
	sprintf(ty, "%02X ", packet->id);
	
	char sendpck[20480] = {"s>"};
	strcat(sendpck, ty);
	for (int h=0; h < packet->size; h++)
	{
		char hhh[1024] = {0};
		sprintf(hhh, " %02X", packet->data[h]);//выводим по байту
		char* fff = new char[strlen(hhh)];
		sprintf(fff,hhh);
		strcat(sendpck, fff);
		delete fff;
		//printf("%02X ", buf[h]);//выводим по байту
	}
	printf("AddN-> %s\n", sendpck);
	return ((UNetworkHandler_AddNetworkQueue)trampoline[1])(This, i, packet);
	
}
int WINAPI Hook_send(SOCKET s, const char *buf,int  len,int  flags)
{
	return ((my_sock)trampoline[2])(s, buf, len, flags);
}

int WINAPI Hook_recv(SOCKET s,const char *buf, int  leng,int  flags)
{
	writebyte((DWORD*)myrecv, recvByte, 1);
	char buff [10240] = {0};
	int len = 0;

	if (SOCKET_ERROR == (len = recv (s, buff, 1024, 0) ) )
	{
		int res = WSAGetLastError ();
		if (res!=WSAEWOULDBLOCK)
		{
			printf ("Error : Server Close\n");
			closesocket(2);
			return 0;
		}
	}
	else
	{

		char buffer[10240] = {0};
		for (int i = 0; i<len; i++)
		{
			char gh[255] = {0};
			sprintf (gh, "%02X", (byte)buff[i]);
			strcat(buffer, gh);
			//char buff[255] =  "c>1FCF494D1089CFFFFF87E20100DCF3FFFF00";
		}
		printf("recv->%s | Size->%d\n", buffer, len);
		MyAddMessage(buffer);
	}

	HookHelper::HookFunctionWithTrampoline(reinterpret_cast<unsigned char*> (myrecv), reinterpret_cast<unsigned char*> (&Hook_recv), trampoline[3]);
	printf("EndRecv\n");
	return ((my_sock)trampoline[3])(s, buf, leng, flags);
}

int WINAPI Hook_WSAStartup(WORD wVersionRequested,LPWSADATA lpWSAData)
{
	printf("Hook_WSAStartup\n");
	//return ((my_WSAStartup)trampoline[4])(wVersionRequested, lpWSAData);
	MessageBox(NULL, "KKK", "", MB_OK);
	return -1;
}

int WSAAPI Hook_Connect(SOCKET s, sockaddr_in* name, int namelen)
{
	printf("Connect: port %d\n", htons(name->sin_port) );
	s_kproxyN = s;
	name->sin_addr.s_addr = inet_addr("127.0.0.1");
	return ((my_connect)trampoline[7])(s, name, namelen);
}

/*
 SOCKET WINAPI Hook_socket(int af,int type, int protocol)
 {
	 printf("socket\n");
	 if (cheksock == 0)
	 {
		 //std::thread thr (start_client);
		 //thr.detach();
		 cheksock++;
		 Sleep(100);
		 return start_client();
	 }
	 return ((my_socket)trampoline[5])(af, type, protocol);
	 
 }*/
 /*
 void Recv()
{
	char buff [10240] = {0};
	int len = 0;
	do
	{
		if (SOCKET_ERROR == (len = recv (s_kproxyN, buff, 10240, 0) ) )
		{
			int res = WSAGetLastError ();
			if (res!=WSAEWOULDBLOCK)
			{
				printf ("Error : Server Close\n");
				closesocket(s_kproxyN);
				cheksock = 0;
				//FreeConsole();
				//ExitProcess(1337);
				return;
			}
			else len = 1;
		}
		else
		{
			char buffer[10240] = {0};
			for (int i = 0; i<len; i++)
			{
				char gh[10240] = {0};
				sprintf (gh, "%c", buff [i]);
				strcat(buffer, gh);
			}
			MyAddMessage(buffer);
			printf("\nBYFFER -> %s\n",buffer);//suspend
		}
	}
	while (len != 0);
}

 int start_client()
{
	/*
	WSADATA wsaData;
	if( !WSAStartup (MAKEWORD(2,2), &wsaData) )
	{
		s_kproxyN = socket ( AF_INET,SOCK_STREAM, 0 );
		if( s_kproxyN != SOCKET_ERROR )
		{
			sockaddr_in proxy;
			proxy.sin_family      = AF_INET;
			proxy.sin_port        = htons(2106); // 65000 40049
			proxy.sin_addr.s_addr = inet_addr("127.0.0.1");

			if( connect ( s_kproxyN, (sockaddr*)&proxy, sizeof(proxy)) != SOCKET_ERROR )
			{
				char rvBuffer[10240] = {0};
				printf ("Connect to server  NG\n");
				BOOL l = TRUE;
				if (SOCKET_ERROR == ioctlsocket (s_kproxyN, FIONBIO, (unsigned long* ) &l))
				{
					// Error
					int res = WSAGetLastError ();
					printf("WSAGetLastError: %d\n", res);
				}
				cheksock = 0;
				std::thread g (Recv);
				g.detach();

			} else {printf ("Error connect to server NG\n"); }


		}  else printf ("Error create socket\n");
		//closesocket(s_kproxyN);
	//}
	printf ("Exit\n");
	cheksock = 0;
	return 0;
}
 */
 void __fastcall MyInit(void* This, int i, int b, class UGameEngine * cl)
{
	printf("Init\n");
	ThisAddPacket = This;
	return ((UNetworkHandler_Init)trampoline[6])(This, i, b, cl);
}

 int MyAddMessage (char* buffer)
{
	std::string str_hex;
	unsigned char df[10240];
	char bud[10240] = {0};
	for (int i = 0, d = 0; i < (int)strlen(buffer); i++, d++)
	{
		bud[0] = buffer[i];bud[1] = buffer[i+1];i++;
		str_hex = bud;
		//std::cout << str_hex << std::endl;
		unsigned int hx = std::stol(str_hex,nullptr,16);
		df[d] = hx;
	}
	int size = strlen(buffer) / 2 - 1;
	try
	{
		NetworkPacket* saveuserinfo;
		HMODULE hCore = NULL;
		hCore = GetModuleHandleA("Core.dll");
		if (hCore == NULL) MessageBox(NULL, "Error Core dll", "Error", MB_OK);
		l2native::FMalloc* pMalloc = NULL;
		pMalloc = *(l2native::FMalloc**)(GetProcAddress(hCore, "?GMalloc@@3PAVFMalloc@@A"));
		if (pMalloc == NULL) MessageBox(NULL, "Error pMalloc", "Error", MB_OK);
		saveuserinfo = (NetworkPacket*)pMalloc->Allocate(sizeof(NetworkPacket), 0);
		saveuserinfo->id = df[0]; 
		saveuserinfo->size = size;
		saveuserinfo->data = (uint8_t*)pMalloc->Allocate(size, 0);
		std::memcpy(saveuserinfo->data, df+1, size);
		//printf("id -> %02X size data -> %d realysize -> %d\n", saveuserinfo->id, saveuserinfo->size, sizeof(saveuserinfo->data));
		
		//UNetworkHandler_AddNetworkQueue_hook(settings.This_call1, settings.chacint, saveuserinfo);
		UNetworkHandler_AddNetworkQueue_hook(ThisAddPacket, 0, saveuserinfo);
		//if (CHRONICLE == 0)  ((UNetworkHandler_UNetworkHandler)trampol)(This_call1, chacint, saveuserinfo);
		//if (CHRONICLE == 1)  (*UNetworkHandler_AddNetworkQueue)(This_call1, chacint, saveuserinfo);
		return TRUE;
	}
	catch(int g)
	{
		g = 0;
		MessageBox(NULL, "Ошибка отправки AddNetwork", " Error", MB_OK | MB_ICONERROR);
		return FALSE;
	}
}

 void __fastcall UNetworkHandler_AuthLogin(void* This, int i, wchar_t const  * login, wchar_t const  * pass, int but)
{
	printf("AUTOLOGIN: Login -> %ls -- Password  -> %ls\n", login, pass);
	return ((UNetworkHandler_RequestAuthLogin)trampoline[8])(This, i, login, pass, but);
}

void __fastcall UNetworkHandler_TickHook(void* This, int i, float tick)
{
	if (!isAutorise) {isAutorise = TRUE;RequestAuthLogin(This, 0, myLogin, myPassw, 0);}
	return((UNetworkHandler_Tick)trampoline[9])(This, i, tick);
}