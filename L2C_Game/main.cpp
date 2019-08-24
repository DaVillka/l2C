#include<io.h>
#include<stdio.h>
#include<winsock2.h>
#include <thread>
#include "globalhandler.h"
#include "RecvClientPacket.h"

#pragma comment(lib,"ws2_32.lib") //Winsock Library


void ClientThread(int SocketID)
{
	printf("SocketID: %d\n", SocketID);
	RecvClientPacket* ServerPacket = new RecvClientPacket();
	ServerPacket->CreateSocket(ClientSocket[SocketID]);

	char rvBuffer[MAX_PACKET_SIZE];
	int len = 0;
	for(;;Sleep(1))
	{
		len = 0;
		//ZeroMemory(rvBuffer, MAX_PACKET_SIZE);
		len = recv (ClientSocket[SocketID], rvBuffer, sizeof(rvBuffer), 0);
		if (len == SOCKET_ERROR || ClientSocket[SocketID] == INVALID_SOCKET || ClientSocket[SocketID] == NULL || len == 0)
		{
			int res = WSAGetLastError ();

			printf ("Server Close\n");
			closesocket(ClientSocket[SocketID]);
			//FreeConsole();
			//ExitProcess(1337);
			break;

		}
		else
		{
			char buffer[MAX_PACKET_SIZE] = {0};
			ZeroMemory(buffer, MAX_PACKET_SIZE);
			for (int i = 0; i<len; i++)
			{
				char gh[2] = {0};
				sprintf (gh, "%02X", (byte)rvBuffer[i]);
				strcat(buffer, gh);
			}
			printf("\nBYFFER -> %s\n",buffer);//suspend
			ServerPacket->GetPacketFromClient((byte*)rvBuffer, len);
		}
	}
	delete ServerPacket;
	closesocket(ClientSocket[SocketID]);
	ClientSocket[SocketID] = NULL;
	AllUserConnectToLoginServer--;
}

bool InitGameServer()
{
	printf("InitGameServer\n");
	if (!CreateDefaultStats()) {printf("Error Created Default Stats\n");return false;}
	
	return true;
}
int main(int argc , char *argv[])
{
	WSADATA wsa;
	SOCKET s , new_socket;
	struct sockaddr_in server , client;
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}

	//Create a socket
	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d" , WSAGetLastError());
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(7777);

	if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d" , WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	//Listen to incoming connections
	listen(s , MAX_USER);
	int c = sizeof(struct sockaddr_in);

	if (!InitGameServer()) {printf("Error Created  Config Game Server\n");return 0; }
	for(AllUserConnectToLoginServer = 0; AllUserConnectToLoginServer != MAX_USER; Sleep(100))
	{
		if ((new_socket = accept(s , (struct sockaddr *)&client, &c)) != INVALID_SOCKET )
		{
			for (int i = 0; i < MAX_USER; i++)
			{
				if (ClientSocket[i] == NULL) 
				{
					printf ("Client IP %s, Client Port %d CountUSer %d:\n", inet_ntoa ((in_addr) client.sin_addr), 
						ntohs (client.sin_port),AllUserConnectToLoginServer );
					ClientSocket[i] = new_socket;
					std::thread clientThr(ClientThread, AllUserConnectToLoginServer);
					clientThr.detach();
					AllUserConnectToLoginServer++;
					break;
				}
			}
		}
	}
	if (new_socket == INVALID_SOCKET)
	{
		printf("accept failed with error code : %d" , WSAGetLastError());
		return 1;
	}

	closesocket(s);
	WSACleanup();

	return 0;
}



int maint()
{
	SYSTEMTIME sysTime;
	GetSystemTime(&sysTime);

	printf("Time: %d\n", sysTime.wSecond);
	
	_getch();
}