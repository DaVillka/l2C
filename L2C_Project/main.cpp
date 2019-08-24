#include<io.h>
#include<stdio.h>
#include<winsock2.h>
#include <thread>
#include "globalhandler.h"
#include "SendServerPacket.h"

#pragma comment(lib,"ws2_32.lib") //Winsock Library


void ClientThread(int SocketID)
{
	printf("SocketID: %d\n", SocketID);
	SendServerPacket* ServerPacket = new SendServerPacket();
	
	ServerPacket->ZeroBuffer();
	ServerPacket->clientSocket = ClientSocket[SocketID];
	ServerPacket->Init(SocketID);

	char rvBuffer[MAX_PACKET_SIZE];
	int len = 0;
	for(;;Sleep(100))
	{
		len = recv (ClientSocket[SocketID], rvBuffer, sizeof(rvBuffer), 0);
		if (len == SOCKET_ERROR || ClientSocket[SocketID] == INVALID_SOCKET || ClientSocket[SocketID] == NULL || len == 0)
		{
			int res = WSAGetLastError ();

			printf ("Error : Server Close\n");
			closesocket(ClientSocket[SocketID]);
			//FreeConsole();
			//ExitProcess(1337);
			break;

		}
		else
		{
			char buffer[MAX_PACKET_SIZE] = {0};
			for (int i = 0; i < len; i++)
			{
				if (i >= MAX_PACKET_SIZE) break;
				char gh[2] = {0};
				sprintf (gh, "%02X", (byte)rvBuffer[i]);
				strcat(buffer, gh);
			}
			printf("\nBYFFER -> %s\n",buffer);//suspend
			ServerPacket->ZeroBuffer();
			ServerPacket->GetPacketFromClient((byte*)rvBuffer, len);

		}
	}
	delete ServerPacket;
	closesocket(ClientSocket[SocketID]);
	ClientSocket[SocketID] = NULL;
	AllUserConnectToLoginServer--;
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
		printf("Could not create sockett : %d" , WSAGetLastError());
	}

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(IP);
	server.sin_port = htons(PORT);


	//Bind
	if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d" , WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	
	//Listen to incoming connections
	listen(s , MAX_USER);

	//Accept and incoming connection
	int c = sizeof(struct sockaddr_in);

	AddGameServer();

	for(AllUserConnectToLoginServer = 0; AllUserConnectToLoginServer != MAX_USER; Sleep(100))
	{
		if ((new_socket = accept(s , (struct sockaddr *)&client, &c)) != INVALID_SOCKET )
		{
			puts("Connection accepted");
			for (int i = 0; i < MAX_USER; i++)
			{
				if (ClientSocket[i] == NULL) 
				{
					printf ("Client IP %s, Client Port %d CountUSer %d:\n", inet_ntoa ((in_addr) client.sin_addr), 
						ntohs (client.sin_port),AllUserConnectToLoginServer );
					//char* bb = "123|312";
					//send(new_socket, bb, strlen( bb), 0);
					ClientSocket[i] = new_socket;
					std::thread clientThr(ClientThread, AllUserConnectToLoginServer);
					clientThr.detach();
					AllUserConnectToLoginServer++;
					break;
				}
			}
		}
		else
		{
			printf("accept failed with error code : %d" , WSAGetLastError());
		}
		
	}
	

	closesocket(s);
	WSACleanup();
	printf("LoginServer Closed\n");
	_getch();
	return 0;
}



int maint()
{
	int ip[3];
	int io[3] = {3,3};
	memcpy(ip, io, sizeof(io));
	printf("I %d : %d\n", ip[0], ip[1]);
	_getch();
}