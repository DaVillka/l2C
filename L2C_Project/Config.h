//LoginServer
#define IP                 "127.0.0.1"
#define PORT               2106

#define MAX_PACKET_SIZE    1024
#define MAX_USER           5

//GameServer
#define MAXCOUNTGAMESERVER 15;
int  COUNTSERVER =         0;
DWORD revision = 0;//0x00000621;
struct ConfigServer
{
	char ip[16];
	DWORD port;
	int idServ;
	int  ageLimit;
	bool pvp;
	WORD countUser;
	WORD maxUser;
	char testServ;
	bool status;
	bool brackets;
	int type;
};
ConfigServer server[15];