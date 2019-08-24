#include "globalhandler.h"
#include "RecvClientPacket.h"
class SendServerPacket : RecvClientPacket , WritePacket
{
public:
	void GetPacketFromClient(byte* packet, int sizePacket);
	void ZeroBuffer();
	void GetByteIp(byte*);
	SOCKET clientSocket;

	void Init(DWORD);
	void GGAutch();
	void LoginOk();
	void ServerList();
	void PlayOk();

};
void AddGameServer()
{
	
	sprintf( server[COUNTSERVER].ip, "%s", "127.0.0.1");
	server[COUNTSERVER].port = 7777;
	server[COUNTSERVER].ageLimit = 18;
	server[COUNTSERVER].pvp = true;
	server[COUNTSERVER].testServ = 0x00;
	server[COUNTSERVER].countUser = 1;
	server[COUNTSERVER].maxUser = 10;
	server[COUNTSERVER].idServ = COUNTSERVER;
	server[COUNTSERVER].status = true;
	server[COUNTSERVER].brackets = true;
	server[COUNTSERVER].type = 0x01;
	COUNTSERVER++;
}
void SendServerPacket::ZeroBuffer()
{
	size = 0;
	ZeroMemory(SendPacketBuffer, 10240);
}

void SendServerPacket::GetPacketFromClient(byte* packet, int sizePacket)
{
	printf("pyte: %02X\n", packet[0]);
	if ((byte)packet[0] == 0x07) {printf("RequestGGAutch");    if (RequestGGAutch(packet)) GGAutch();    }
	if ((byte)packet[0] == 0x00) {printf("RequestAutchLogin"); if (RequestAutchLogin(packet)) LoginOk();    }
	if ((byte)packet[0] == 0x05) {printf("RequestServerList"); if (RequestServerList(packet)) ServerList(); }
	if ((byte)packet[0] == 0x02) {printf("RequestServerLogin"); PlayOk();     }
}
void SendServerPacket::GetByteIp(byte* but)
{
	char ipb[25] = "";
	sprintf(ipb, "%s", server[0].ip);
	char* pch = strtok(ipb, ".");
	for(int i = 0;pch != NULL;i++)
	{
		int id = atoi(pch);
		//printf("%d ", id);
		but[i] = id;
		pch = strtok(NULL, ".");
	}
}

void SendServerPacket::Init(DWORD sessionId)
{
	/**
	* Format: dd b dddd s
	* d: session id
	* d: protocol revision
	* b: 0x90 bytes : 0x80 bytes for the scrambled RSA public key
	* 0x10 bytes at 0x00
	* d: unknow
	* d: unknow
	* d: unknow
	* d: unknow
	* s: blowfish key
	*/
	BYTE zerokey[] = {0x00, 0x00,0x00, 0x00,0x00,0x00};
	writeC(0x00); // init packet id
	writeD(sessionId); // session id
	writeD(revision); // protocol revision
	writeB(zerokey, sizeof(zerokey)); // RSA Public Key
	writeD(0);
	writeD(0);
	writeD(0);
	writeD(0);
	writeB(zerokey, sizeof(zerokey)); // BlowFish key
    writeC(0x00);
	send(clientSocket , (char*)SendPacketBuffer , size, 0);
}
void SendServerPacket::GGAutch()
{
	writeC(0x0B);
	writeD(0x00000000);
	writeD(0x00000000);

	send(clientSocket , (char*)SendPacketBuffer , size, 0);
}
void SendServerPacket::LoginOk()
{
	byte unk[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	_loginOk1 = 0x12345678;
	_loginOk2 = 0x87654321;

	writeC(0x03);
	writeD(_loginOk1);
	writeD(_loginOk2);
	writeD(0x00);
	writeD(0x00);
	writeD(0x000003ea);
	writeD(0x00);
	writeD(0x00);
	writeD(0x00);
	writeB(unk, 16);
	
	send(clientSocket , (char*)SendPacketBuffer , size, 0);
}
void SendServerPacket::ServerList()
{
	/**
	* ServerList
	* Format: cc [cddcchhcdc]
	*
	* c: server list size (number of servers)
	* c: last server
	* [ (repeat for each servers)
	* c: server id (ignored by client?)
	* d: server ip
	* d: server port
	* c: age limit (used by client?)
	* c: pvp or not (used by client?)
	* h: current number of players
	* h: max number of players
	* c: 0 if server is down
	* d: 2nd bit: clock
	*    3rd bit: wont dsiplay server name
	*    4th bit: test server (used by client?)
	* c: 0 if you dont want to display brackets in front of sever name
	* ]
	*
	* Server will be considered as Good when the number of  online players
	* is less than half the maximum. as Normal between half and 4/5
	* and Full when there's more than 4/5 of the maximum number of players
	*/
	writeC(0x04);
	writeC(COUNTSERVER);//Количество гейм серверов
	writeC(0x01);//Номер последнего сервера, на который заходило тело
	for (int i = 0; i < COUNTSERVER; i++) {
		writeC(0x01/*server[i].idServ*/);
		byte raw[3];
		GetByteIp(raw);
		writeC(raw[0]);
		writeC(raw[1]);
		writeC(raw[2]);
		writeC(raw[3]);
		writeD(server[i].port);
		writeC(server[i].ageLimit); // age limit
		writeC(server[i].pvp ? 0x01 : 0x00);
		writeH(server[i].countUser);
		writeH(server[i].maxUser);
		writeC(server[i].status ? 0x01 : 0x00);
		writeD(server[i].type);
		writeC(server[i].brackets ? 0x01 : 0x00);
		
	}

	writeH(0x00); // -??
	writeC(0x01);

	writeC(0x01);
	writeC(0); // acc player size
	writeC(0x00);
	//writeC(0x01);
	//writeC(0x01);
	//writeC(0x00);
	//sprintf(bufferPacket, "040101017F000001611E00001201010002000100017F000001611E000012000100020000");
	send(clientSocket , (char*)SendPacketBuffer , size, 0);
}
void SendServerPacket::PlayOk()
{
	//printf("070000000000000000");
	writeC(0x07);
	writeD(0x00000000);
	writeD(0x00000000);
	send(clientSocket , (char*)SendPacketBuffer , size, 0);
}