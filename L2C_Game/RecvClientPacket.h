#include "globalhandler.h"
#include "readPacket.h"
#include "SendServerPacket.h"
class RecvClientPacket:ReadPacket, SendServerPacket
{
public:
	
	bool ProtocolVersion();
	bool ReqestAuthLogin();
	bool CharSelected();
	bool CharacterCreate();
	bool EnterWorld();
	bool ValidatePosition();
	bool MoveBackwardToLocation();
	bool SendBypassBuildCmd();
	bool RequestItemList();
	bool Logout();
	bool RequestShowMiniMap();
	void TwoBytePacket();

	void CreateSocket(SOCKET clientS);
	void ZeroBufferRead();
	void GetPacketFromClient(byte* packet, int sizePacket);
	
};
void RecvClientPacket::CreateSocket(SOCKET clientS)
{
	clientSocket = clientS;
}
void RecvClientPacket::ZeroBufferRead()
{
	sizeRecv = 0;
	ZeroMemory(packetRecv, sizeof(packetRecv));
}
void RecvClientPacket::GetPacketFromClient(byte* packet, int sizePacket)
{
	ZeroBufferRead();
	ZeroBufferWrite();
	printf("pyte: %02X\n", packet[0]);
	memcpy(packetRecv, packet, sizePacket); sizeRecv = sizePacket;
	
	if ((byte)packet[0] == 0x0E) { printf("ProtocolVersion");        if (ProtocolVersion())        KeyInit();               }
	if ((byte)packet[0] == 0x2B) { printf("ReqAuthLogin");           if (ReqestAuthLogin())        CharSelectInfo();        }
	if ((byte)packet[0] == 0x13) { printf("NewCharacter");                                         NewCharacterSuccess();   }
	if ((byte)packet[0] == 0x0C) { printf("CharacterCreate");        if (CharacterCreate())   CharCreateOk(); else  CharCreateFalse();         }
	if ((byte)packet[0] == 0x12) { printf("CharSelected");           CharSelected();                                        }
	if ((byte)packet[0] == 0x11) { printf("EnterWorld");             EnterWorld();                                          }
	if ((byte)packet[0] == 0x59) { printf("ValidatePosition");       ValidatePosition();                                    }
	if ((byte)packet[0] == 0x0F) { printf("MoveBackwardToLocation"); if (MoveBackwardToLocation()) MoveToLocation();        }
	if ((byte)packet[0] == 0x74) { printf("SendBypassBuildCmd");     SendBypassBuildCmd();                                  }
	if ((byte)packet[0] == 0x14) { printf("RequestItemList");        if (RequestItemList()) ItemList();/*InventoryUpdate(); */             }
	if ((byte)packet[0] == 0x00) { printf("Logout");                 if (Logout()) LeaveWorld();                            }
	if ((byte)packet[0] == 0x6C) { printf("RequestShowMiniMap");     RequestShowMiniMap();                                  }
	if ((byte)packet[0] == 0xD0) { printf("TwoBytePacket");          TwoBytePacket();                                       }

}

bool RecvClientPacket::ProtocolVersion()
{
	return true;
}
bool RecvClientPacket::ReqestAuthLogin()
{
	sessionId = 0x01020304;
	sizeP++;
	
	swprintf_s(login, 255, L"%ls", packetRecv+sizeP);
	wprintf(L"%ReqLogin: %ls\n", login);
	swprintf_s(LSlogin, 255, L"%ls", login);

	dStagePlayer = STAGE_REQUESTAUTCHLOGIN;
	return true;
}
bool RecvClientPacket::CharSelected()
{
	sizeP = 1;
	characterSelected = readD();
	if (characterSelected > COUNTPLAYER || COUNTPLAYER == 0) return false;
	CharSelectedSend();
	return true;
}
bool RecvClientPacket::CharacterCreate()
{
	if (COUNTPLAYER >= MAXPLAYERACC) return false;
	sizeP = 1;
	wchar_t nameChar[255];
	readS(nameChar);
	//swprintf_s(nameChar, 255, L"%ls", packetRecv+sizeP);
	//sizeP+=(wcslen(nameChar)*2+2);
	//wprintf(L"Name ->%ls | SizeP: %d\n", nameChar, sizeP);
	//swprintf_s(charInfoPackage.login, login);
	
	DWORD Race                         = readD(); 
	DWORD Sex                          = readD(); 
	DWORD ClassID                      = readD(); 
	for(int i = 0; i < 6; i++)           readD();
	DWORD HairStule                    = readD();
	DWORD HairColor	                   = readD();
	DWORD Face     	                   = readD();
	//wprintf(L"HairStule ->%d | HairColor ->%d | Face ->%d | \n", HairStule, HairColor, Face);
	int code                           = GetDefaultStats(&defaultStats, charInfoPackage.Race, ClassID , Sex, &HairStule, &HairColor,  &Face);
	if (code == -1) {printf("Error Create Character\n"); return false;}

	charInfoPackage.Race               = Race;							   
	charInfoPackage.sessionId          = sessionId;
	charInfoPackage.X                  = defaultStats.defX;
	charInfoPackage.Y                  = defaultStats.defY;
	charInfoPackage.Z                  = defaultStats.defZ;
	charInfoPackage.isInAirShip        = 0;
	charInfoPackage.ObjectID           = ObjectID;
	swprintf_s(charInfoPackage.Name,   255, L"%ls",  nameChar);
	charInfoPackage.Sex                = Sex;
	charInfoPackage.ClassID            = ClassID;
	charInfoPackage.lvl                = defaultStatAllClass.LvL;
	charInfoPackage.Exp                = 0;//defaultStats.Exp;
	charInfoPackage.STR                = defaultStats.STR;
	charInfoPackage.DEX                = defaultStats.DEX;
	charInfoPackage.CON                = defaultStats.CON;
	charInfoPackage.INT                = defaultStats.INT;
	charInfoPackage.WIT                = defaultStats.WIT;
	charInfoPackage.MEN                = defaultStats.MEN;
	charInfoPackage.MaxHp              = defaultStats.MaxHP;
	charInfoPackage.CurHp              = defaultStats.MaxHP;
	charInfoPackage.MaxMp              = defaultStats.MaxMP;
	charInfoPackage.CurMp              = defaultStats.MaxMP;
	charInfoPackage.MaxCP              = (int)defaultStats.MaxCP;
	charInfoPackage.CurCP              = (int)defaultStats.MaxCP;
	charInfoPackage.CurMp              = defaultStats.MaxMP;
	charInfoPackage.Sp                 = 0;
	charInfoPackage.CurLoad            = 0;
	charInfoPackage.MaxLoad            = defaultStats.Ves;
	charInfoPackage.PAtk               = defaultStats.PAtk;
	charInfoPackage.PDef    	       = defaultStats.PDef;
	charInfoPackage.Accuracy	       = defaultStats.Accuracy;
	charInfoPackage.Critical	       = defaultStats.Critical;
	charInfoPackage.AtkSpd  	       = defaultStats.AtkSpd;
	charInfoPackage.MAtk    	       = defaultStats.MAtk;
	charInfoPackage.MDef    	       = defaultStats.MDef;
	charInfoPackage.Evasion 	       = defaultStats.Evasion;
	charInfoPackage.Speed   	       = defaultStats.baseRunSpd;
	charInfoPackage.WalkSpd            = defaultStats.baseWalkSpd; //Начальная скорость перемещения (старт)
	charInfoPackage.CastSpd 	       = defaultStats.CastSpd;
	charInfoPackage.DefFire            = defaultStats.DefFire;
	charInfoPackage.DefWater	       = defaultStats.DefWater;
	charInfoPackage.DefWind		       = defaultStats.DefWind;
	charInfoPackage.DefEarth	       = defaultStats.DefEarth;
	charInfoPackage.DefHoly		       = defaultStats.DefHoly;
	charInfoPackage.DefUnholy	       = defaultStats.DefUnholy;
									   
									   
	charInfoPackage.isWeapEquip        = 40;


	charInfoPackage.Under   [0]  = 0;   charInfoPackage.Under   [1]  = 0;  charInfoPackage.Under    [2]  = 0;
	charInfoPackage.REar	[0]	 = 0;  	charInfoPackage.REar	[1]	 = 0;  charInfoPackage.REar	    [2]	 = 0;
	charInfoPackage.LEar	[0]	 = 0;  	charInfoPackage.LEar	[1]	 = 0;  charInfoPackage.LEar	    [2]	 = 0;
	charInfoPackage.Neck	[0]	 = 0;  	charInfoPackage.Neck	[1]	 = 0;  charInfoPackage.Neck	    [2]	 = 0;
	charInfoPackage.RRing	[0]	 = 0;  	charInfoPackage.RRing	[1]	 = 0;  charInfoPackage.RRing    [2]	 = 0;
	charInfoPackage.LRing	[0]	 = 0;  	charInfoPackage.LRing	[1]	 = 0;  charInfoPackage.LRing    [2]	 = 0;
	charInfoPackage.Head	[0]	 = 0;  	charInfoPackage.Head	[1]	 = 0;  charInfoPackage.Head	    [2]	 = 0;
	charInfoPackage.RHand	[0]	 = 0;  	charInfoPackage.RHand	[1]	 = 0;  charInfoPackage.RHand    [2]	 = 0;
	charInfoPackage.LHand	[0]	 = 0;  	charInfoPackage.LHand	[1]	 = 0;  charInfoPackage.LHand	[2]	 = 0;
	charInfoPackage.Gloves	[0]	 = 0;  	charInfoPackage.Gloves	[1]	 = 0;  charInfoPackage.Gloves	[2]	 = 0;
	charInfoPackage.Chest	[0]	 = 0;  	charInfoPackage.Chest	[1]	 = 0;  charInfoPackage.Chest	[2]	 = 0;
	charInfoPackage.legs	[0]	 = 0;  	charInfoPackage.legs	[1]	 = 0;  charInfoPackage.legs	    [2]	 = 0;
	charInfoPackage.Feet	[0]	 = 0;  	charInfoPackage.Feet	[1]	 = 0;  charInfoPackage.Feet	    [2]	 = 0;
	charInfoPackage.Back	[0]	 = 0;  	charInfoPackage.Back	[1]	 = 0;  charInfoPackage.Back	    [2]	 = 0;
	charInfoPackage.LRHand	[0]	 = 2;   charInfoPackage.LRHand	[1]	 = 22; charInfoPackage.LRHand	[2]	 = 64;//(DWORD)64 << 1;
	charInfoPackage.Hair	[0]	 = 0;  	charInfoPackage.Hair	[1]	 = 0;  charInfoPackage.Hair	    [2]	 = 0;
	charInfoPackage.Hair2	[0]	 = 0;  	charInfoPackage.Hair2	[1]	 = 0;  charInfoPackage.Hair2	[2]	 = 0;
	charInfoPackage.RBrace	[0]	 = 0;  	charInfoPackage.RBrace	[1]	 = 0;  charInfoPackage.RBrace	[2]	 = 0;
	charInfoPackage.LBrace	[0]	 = 0;  	charInfoPackage.LBrace	[1]	 = 0;  charInfoPackage.LBrace	[2]	 = 0;
	charInfoPackage.DEC1	[0]	 = 0;  	charInfoPackage.DEC1	[1]	 = 0;  charInfoPackage.DEC1	    [2]	 = 0;
	charInfoPackage.DEC2	[0]	 = 0;  	charInfoPackage.DEC2	[1]	 = 0;  charInfoPackage.DEC2	    [2]	 = 0;
	charInfoPackage.DEC3	[0]	 = 0;  	charInfoPackage.DEC3	[1]	 = 0;  charInfoPackage.DEC3	    [2]	 = 0;
	charInfoPackage.DEC4	[0]	 = 0;  	charInfoPackage.DEC4	[1]	 = 0;  charInfoPackage.DEC4	    [2]	 = 0;
	charInfoPackage.DEC5	[0]	 = 0;  	charInfoPackage.DEC5	[1]	 = 0;  charInfoPackage.DEC5	    [2]	 = 0;
	charInfoPackage.DEC6	[0]	 = 0;  	charInfoPackage.DEC6	[1]	 = 0;  charInfoPackage.DEC6	    [2]	 = 0;
	charInfoPackage.Belt	[0]	 = 0; 	charInfoPackage.Belt	[1]	 = 0;  charInfoPackage.Belt	    [2]	 = 0;


	charInfoPackage.recomLeft          = 0;
	charInfoPackage.recomHave          = 0;
	charInfoPackage.ExpPercent         = 0.5;
	charInfoPackage.Karma              = 0;
	charInfoPackage.pkKill             = 0;
	charInfoPackage.PvPKill            = 0;
	charInfoPackage.AttackElem         = defaultStats.AttackElem;
	charInfoPackage.AttackElemPower    = 0;
	charInfoPackage.isRunning          = defaultStats.isRunning ? 1 : 0; //0-Ходьба, 1-Бег
	charInfoPackage.HairStule          = HairStule;
	charInfoPackage.HairColor          = HairColor;
	charInfoPackage.Face               = Face;
	charInfoPackage.Fame               = 0;
	charInfoPackage.Vitality           = defaultStatAllClass.Vitality;//20000
	charInfoPackage.ColHeight          = Sex ? defaultStats.female_collision_height : defaultStats.male_collision_height;
	charInfoPackage.ColRadius          = Sex ? defaultStats.female_collision_radius : defaultStats.male_collision_radius;
	charInfoPackage.Heaidng            = 25662;
								       
	charInfoPackage.nameColor          = 16777215;
	charInfoPackage.recomLeft          = 20;
	charInfoPackage.MoveMul            = 1.0;//1.1;
	charInfoPackage.AtkSpdMul          = 1.0;
	charInfoPackage.SwimRunSpd         = 55;
	charInfoPackage.SwimWalkSpd        = 55;
	charInfoPackage.PledgeType         = -128;
	charInfoPackage.titleColor         = 16777079;
	charInfoPackage.inventoryLimit     = 80;
	charInfoPackage.isFlyingMounted    = 0;
	charInfoPackage.isGM               = true;
	charInfoPackage.isCrystalize       = defaultStats.Crystalize;
	charInfoPackage.DestX              = charInfoPackage.X;
	charInfoPackage.DestY              = charInfoPackage.Y;
	charInfoPackage.DestZ              = charInfoPackage.Z;

	charInfoPackage.AccessLevel        = 0;
	InfoPlayer[COUNTPLAYER]            = charInfoPackage;
	COUNTPLAYER++;
	dStagePlayer = STAGE_CHARACTERCREATE;
	return true;
}
bool RecvClientPacket::EnterWorld()
{
	for (int i = 0;; i++, Sleep(150))
	{
		switch (i)
		{
			case 0: UserInfo();                      break;
			case 1:	MoveToLocation();                break;
			case 2: ItemList();                      break;
			case 3:	SystemMessage(34);               break;
			case 4: CreatureSay(10, L"Hello World"); break;
			default: return true;break;
		}
	}
	return true;
}
bool RecvClientPacket::ValidatePosition()
{
	sizeP=1;
	charInfoPackage.X       = readD();
	charInfoPackage.Y       = readD();
	charInfoPackage.Z       = readD();
	charInfoPackage.Heaidng = readD();
	DWORD Data    = readD();

	return true;
}
bool RecvClientPacket::MoveBackwardToLocation()
{
	sizeP=1;
	
	charInfoPackage.DestX       = readD();
	charInfoPackage.DestY       = readD();
	charInfoPackage.DestZ       = readD() + 27;

	charInfoPackage.X           = readD();
	charInfoPackage.Y           = readD();
	charInfoPackage.Z           = readD();
	readD();
	return true;
}
bool RecvClientPacket::SendBypassBuildCmd()
{
	sizeP = 1;
	if (sizeRecv < 2) return false;
	wchar_t command[255];
	swprintf_s(command, 255, L"%ls", packetRecv+sizeP);
	wprintf(L"command: %ls\n", command);
	if (wstrstr(command, L"respawn"))
	{
		printf("Respawn\n");
		srand((unsigned int)time(0));
		charInfoPackage.X = (rand() % 2) == 0 ? (-71340 + (rand() % -323)) : (-71340 + (rand() % 323));
		charInfoPackage.Y = (rand() % 2) == 0 ? (258393 + (rand() % -132)) : (258393 + (rand() % 132));
		charInfoPackage.Z = -3105;
		ValidateLocation();
	}
	return true;
}
bool RecvClientPacket::RequestItemList()
{
	return true;
}
bool RecvClientPacket::Logout()
{
	return true;
}
bool RecvClientPacket::RequestShowMiniMap()
{
	ShowMiniMap();
	return true;
}
void RecvClientPacket::TwoBytePacket()
{
	printf("SizeRecv: %d\n", sizeRecv);
	switch (packetRecv[1])
	{
		case 0x36:{if (sizeRecv == 3) printf("Previous\n");Previous();}break;
	}
}