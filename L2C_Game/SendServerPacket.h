#include "globalhandler.h"

class SendServerPacket : WritePacket, Player
{
public:
	SOCKET clientSocket;
	void GetByteIp(byte*);
	PlayerInfo charInfoPackage;
	PlayerInfo InfoPlayer[MAXPLAYERACC];
	DefaultStats defaultStats;
	//Параметры, полученные от логин сервера
	wchar_t LSlogin[255];
	DWORD sessionId;
	int COUNTPLAYER;
	int characterSelected;
	wchar_t login[255];
	void ZeroBufferWrite();
	void SendPacketToClient();

	void KeyInit();
	void CharSelectInfo();
	void NewCharacterSuccess();
	void CharCreateOk();
	void CharCreateFalse();
	void CharSelectedSend();
	void UserInfo();
	void ValidateLocation();
	void MoveToLocation();
	void ChangeMoveType();
	void ItemList();
	void InventoryUpdate();
	void LeaveWorld();
	void CreatureSay(int, wchar_t*);
	void ShowMiniMap();
	void Previous();//Откас создания персонажа
	void SystemMessage(int id);
	
};


void SendServerPacket::SendPacketToClient()
{
	Sleep(110);
	send(clientSocket , (char*)SendPacketBuffer , size, 0);
	ZeroBufferWrite();
}
void SendServerPacket::ZeroBufferWrite()
{
	size = 0;
	ZeroMemory(SendPacketBuffer, 10240);
}
void SendServerPacket::GetByteIp(byte* but)
{
	//char* pch = strtok(server[0].ip, ".");
	//for(int i = 0;pch != NULL;i++)
	//{
	//	int id = atoi(pch);
	//	//printf("%d ", id);
	//	but[i] = id;
	//	pch = strtok(NULL, ".");
	//}
}

void SendServerPacket::KeyInit                              ()
{
	//KeyInit:c(isOk)q(KeyL)q(KeyH)c(c)d(seed)
	writeC(0x2E);
	writeQ(0x0000000000000000);
	writeQ(0x0000000000000000);
	writeC(0x00);
	writeC(0x00);
	writeD(0x000000000);
	SendPacketToClient();
}
void SendServerPacket::CharSelectInfo                       ()
{
	writeC(0x09); //Ид пакета
	writeD(COUNTPLAYER); //Количество чаров
	writeD(MAXPLAYERACC); //Максимальное количество чаров на аккаунте
	writeC(0x00); //хз

	for (int i = 0; i < COUNTPLAYER; i++) {
	
		writeS(InfoPlayer[i].Name);
		writeD(InfoPlayer[i].ObjectID); // ?
		writeS(InfoPlayer[i].login);
		writeD(sessionId);
		writeD(InfoPlayer[i].ClanID);
		writeD(0x00); // ??
	
		writeD(InfoPlayer[i].Sex);
		writeD(InfoPlayer[i].Race);
		writeD(InfoPlayer[i].ClassID);
	
		writeD(0x00); // active ??
	
		writeD(InfoPlayer[i].X);
		writeD(InfoPlayer[i].Y);
		writeD(InfoPlayer[i].Z);
	
		writeF(InfoPlayer[i].CurHp);
		writeF(InfoPlayer[i].CurMp);
	
		writeD(InfoPlayer[i].Sp);
		writeQ(InfoPlayer[i].Exp);
		
		writeF(0.5);
		writeD(InfoPlayer[i].lvl);
	
		writeD(InfoPlayer[i].Karma);
		writeD(InfoPlayer[i].pkKill);
		writeD(InfoPlayer[i].PvPKill);
		
		writeD(0x00);
		writeD(0x00);
		writeD(0x00);
		writeD(0x00);
		writeD(0x00);
		writeD(0x00);
		writeD(0x00);
	
		//for (int h = 0; h < 26; h++) 
		//{
		//	//9 перчи
		//	//7 пуха
		//	if ( h == 7)
		//	{
		//		writeD(2);
		//	}
		//	else writeD(0x00);
		//}
		writeD(charInfoPackage.Under    [0]);
		writeD(charInfoPackage.REar	    [0]);
		writeD(charInfoPackage.LEar	    [0]);
		writeD(charInfoPackage.Neck	    [0]);
		writeD(charInfoPackage.RRing	[0]);
		writeD(charInfoPackage.LRing	[0]);
		writeD(charInfoPackage.Head	    [0]);
		writeD(charInfoPackage.RHand	[0]);
		writeD(charInfoPackage.LHand	[0]);
		writeD(charInfoPackage.Gloves	[0]);
		writeD(charInfoPackage.Chest	[0]);
		writeD(charInfoPackage.legs	    [0]);
		writeD(charInfoPackage.Feet	    [0]);
		writeD(charInfoPackage.Back	    [0]);
		writeD(charInfoPackage.LRHand	[0]);
		writeD(charInfoPackage.Hair	    [0]);
		writeD(charInfoPackage.Hair2	[0]);
		writeD(charInfoPackage.RBrace	[0]);
		writeD(charInfoPackage.LBrace	[0]);
		writeD(charInfoPackage.DEC1	    [0]);
		writeD(charInfoPackage.DEC2	    [0]);
		writeD(charInfoPackage.DEC3	    [0]);
		writeD(charInfoPackage.DEC4	    [0]);
		writeD(charInfoPackage.DEC5	    [0]);
		writeD(charInfoPackage.DEC6	    [0]);
		writeD(charInfoPackage.Belt	    [0]);

		
		writeD(InfoPlayer[i].HairStule);
		writeD(InfoPlayer[i].HairColor);
		writeD(InfoPlayer[i].Face     );
	
		writeF(InfoPlayer[i].MaxHp); // hp max
		writeF(InfoPlayer[i].MaxMp); // mp max
	
		writeD(InfoPlayer[i].AccessLevel);
		writeD(InfoPlayer[i].ClassID    );
		writeD(0x01);//i == lastUsed ? 1 : 0);
	
		writeC(16); //Уровень заточки
		writeH(0x0000);//Аугментация
		writeH(0x0000);//Ид проклятой пушки, если нет - 0
		
		writeD(0);//Виталити
		
		//TODO: Pet info?
		writeD(0x00);
		writeD(0x00);
		writeD(0x00);
		writeD(0x00);
		writeF(0x00);
		writeF(0x00);
		writeD(InfoPlayer[i].Vitality);
	
	}
	SendPacketToClient();
}
void SendServerPacket::NewCharacterSuccess                  ()
{
	writeC(0x0D);
	writeD(0x01000000);
	writeD(0x01000000);
	writeD(0x01000000);

	writeD(99);
	writeD(0x01000000);
	writeD(1);

	writeD(99);
	writeD(0x01000000);
	writeD(1);

	writeD(99);
	writeD(0x01000000);
	writeD(1);

	writeD(99);
	writeD(0x01000000);
	writeD(1);

	writeD(99);
	writeD(0x01000000);
	writeD(1);

	writeD(99);
	writeD(0x01000000);
	writeD(1);
	SendPacketToClient();
}
void SendServerPacket::CharCreateOk                         ()
{
	writeC(0x0F);
	writeD(0x01);
	SendPacketToClient();
	ZeroBufferWrite();
	Sleep(100);
	CharSelectInfo();
}
void SendServerPacket::CharCreateFalse                      ()
{
	writeC(0x10);
	writeD(1);
	SendPacketToClient();
}
void SendServerPacket::CharSelectedSend                     ()
{
	if (characterSelected < 0) return;
	writeC(0x0B);
	writeS(InfoPlayer[characterSelected].Name);
	writeD(InfoPlayer[characterSelected].ClassID);
	writeS(L"");
	
	writeD(sessionId);
	writeD(InfoPlayer[characterSelected].ClanID);
	writeD(0x00); //??
	writeD(InfoPlayer[characterSelected].Sex);
	writeD(InfoPlayer[characterSelected].Race);
	writeD(InfoPlayer[characterSelected].ClassID);
	writeD(0x01); // active ??
	writeD(InfoPlayer[characterSelected].X);
	writeD(InfoPlayer[characterSelected].Y);
	writeD(InfoPlayer[characterSelected].Z);
	
	writeF(InfoPlayer[characterSelected].CurHp);
	writeF(InfoPlayer[characterSelected].CurMp);
	
	writeD(InfoPlayer[characterSelected].Sp);
	writeQ(InfoPlayer[characterSelected].Exp);
	
	writeD(InfoPlayer[characterSelected].lvl);
	writeD(InfoPlayer[characterSelected].Karma); //?
	writeD(InfoPlayer[characterSelected].pkKill);

	writeD(InfoPlayer[characterSelected].STR);
	writeD(InfoPlayer[characterSelected].DEX);
	writeD(InfoPlayer[characterSelected].CON);
	writeD(InfoPlayer[characterSelected].INT);
	writeD(InfoPlayer[characterSelected].WIT);
	writeD(InfoPlayer[characterSelected].MEN);
	// extra info
	writeD(0x00);//GameTimeManager.getInstance().getGameTime()); // in-game time
	writeD(0x00);
	writeD(InfoPlayer[characterSelected].ClassID);
	writeD(0x00);
	writeD(0x00);
	writeD(0x00);
	writeD(0x00);
	byte g[64]; for (int i = 0; i < 64; i++){g[i] = 0x00;}
	writeB(g, 64);
	writeD(0x00);
	SendPacketToClient();
}
void SendServerPacket::UserInfo                             ()
{
	size = 0;
	
	printf("UserInfo\ncharInfoPackage.X: %d", charInfoPackage.X);
	writeC(0x32);

	writeD(charInfoPackage.X);
	writeD(charInfoPackage.Y);
	writeD(charInfoPackage.Z);
	writeD(0x00);//clanBoatObjectId);
	writeD(charInfoPackage.ObjectID);
	writeS(charInfoPackage.Name);
	writeD(charInfoPackage.Race);
	writeD(charInfoPackage.Sex);
	writeD(charInfoPackage.ClassID);
	writeD(charInfoPackage.lvl);
	writeQ(charInfoPackage.Exp);
	writeF(charInfoPackage.ExpPercent);
	writeD(charInfoPackage.STR);
	writeD(charInfoPackage.DEX);
	writeD(charInfoPackage.CON);
	writeD(charInfoPackage.INT);
	writeD(charInfoPackage.WIT);
	writeD(charInfoPackage.MEN);
	writeD((int)charInfoPackage.MaxHp);
	writeD((int)charInfoPackage.CurHp);
	writeD((int)charInfoPackage.MaxMp);
	writeD((int)charInfoPackage.CurMp);
	writeD(charInfoPackage.Sp);
	writeD(charInfoPackage.CurLoad);
	writeD(charInfoPackage.MaxLoad);
	writeD(charInfoPackage.isWeapEquip);

	for (int i = 0, h = 1; i != 2; i++)
	{
		if ( i == 0) h = 1;
		if ( i == 1) h = 0;
		writeD(charInfoPackage.Under    [h]);
		writeD(charInfoPackage.REar	    [h]);
		writeD(charInfoPackage.LEar	    [h]);
		writeD(charInfoPackage.Neck	    [h]);
		writeD(charInfoPackage.RRing	[h]);
		writeD(charInfoPackage.LRing	[h]);
		writeD(charInfoPackage.Head	    [h]);
		writeD(charInfoPackage.RHand	[h]);
		writeD(charInfoPackage.LHand	[h]);
		writeD(charInfoPackage.Gloves	[h]);
		writeD(charInfoPackage.Chest	[h]);
		writeD(charInfoPackage.legs	    [h]);
		writeD(charInfoPackage.Feet	    [h]);
		writeD(charInfoPackage.Back	    [h]);
		writeD(charInfoPackage.LRHand	[h]);
		writeD(charInfoPackage.Hair	    [h]);
		writeD(charInfoPackage.Hair2	[h]);
		writeD(charInfoPackage.RBrace	[h]);
		writeD(charInfoPackage.LBrace	[h]);
		writeD(charInfoPackage.DEC1	    [h]);
		writeD(charInfoPackage.DEC2	    [h]);
		writeD(charInfoPackage.DEC3	    [h]);
		writeD(charInfoPackage.DEC4	    [h]);
		writeD(charInfoPackage.DEC5	    [h]);
		writeD(charInfoPackage.DEC6	    [h]);
		writeD(charInfoPackage.Belt	    [h]);
	}
	for (int i = 0; i < 26; i++)writeD(0);

	writeD(charInfoPackage.talismanSlots);
	writeD(charInfoPackage.cloakStatus);
	
	writeD(charInfoPackage.PAtk);
	writeD(charInfoPackage.AtkSpd);
	writeD(charInfoPackage.PDef);
	writeD(charInfoPackage.Evasion);
	writeD(charInfoPackage.Accuracy);
	writeD(charInfoPackage.Critical);
	writeD(charInfoPackage.MAtk);
	writeD(charInfoPackage.CastSpd);
	writeD(charInfoPackage.AtkSpd);
	writeD(charInfoPackage.MDef);
	writeD(charInfoPackage.pvpFlag);
	writeD(charInfoPackage.Karma);
	writeD(charInfoPackage.Speed);
	writeD(charInfoPackage.WalkSpd);
	writeD(charInfoPackage.SwimRunSpd); // swimspeed
	writeD(charInfoPackage.SwimWalkSpd); // swimspeed
	writeD(charInfoPackage.FlyRunSpd);//charInfoPackage.flRunSpd);
	writeD(charInfoPackage.FlyWalkSpd);//charInfoPackage.flWalkSpd);
	writeD(charInfoPackage.FlyRunSpd);
	writeD(charInfoPackage.FlyWalkSpd);
	writeF(charInfoPackage.MoveMul);
	writeF(charInfoPackage.AtkSpdMul);
	writeF(charInfoPackage.ColRadius);
	writeF(charInfoPackage.ColHeight);
	writeD(charInfoPackage.HairStule);
	writeD(charInfoPackage.HairColor);
	writeD(charInfoPackage.Face);
	writeD(charInfoPackage.isGM);
	writeS(charInfoPackage.title);
	writeD(charInfoPackage.ClanID);
	writeD(charInfoPackage.ClanCrestID);
	writeD(charInfoPackage.AllyID);
	writeD(charInfoPackage.AllyCrestID);
	writeD(charInfoPackage.Relation);
	writeC(charInfoPackage.mountTupe); // mount type
	writeC(charInfoPackage.privateStoreType);
	writeC(charInfoPackage.isCrystalize);//charInfoPackage.can_crystalize);
	writeD(charInfoPackage.pkKill);
	writeD(charInfoPackage.PvPKill);
	writeH(0x00);//charInfoPackage.cubics.length);
	//for(EffectCubic cubic : cubics)
	//	writeH(cubic == null ? 0 : cubic.getId());
	writeC(0x00);//charInfoPackage.partyRoom ? 0x01 : 0x00); //1-find party members
	writeD(charInfoPackage.abnormalEffect);
	writeC(charInfoPackage.isFlyingMounted);
	writeD(charInfoPackage.clanPrivs);
	writeH(charInfoPackage.recomLeft);
	writeH(charInfoPackage.recomHave);
	writeD(charInfoPackage.mountNpcID);
	writeH(charInfoPackage.inventoryLimit);
	writeD(charInfoPackage.ClassID);
	writeD(0x00); // special effects? circles around player...
	writeD(charInfoPackage.MaxCP);
	writeD(charInfoPackage.CurCP);
	writeC(20);//charInfoPackage.enchant);
	writeC(0x00);//charInfoPackage.team.ordinal());
	writeD(0x00);//charInfoPackage.large_clan_crest_id);
	writeC(charInfoPackage.isNoble);
	writeC(charInfoPackage.isHero);
	writeC(0x00);
	writeD(charInfoPackage.fishX);
	writeD(charInfoPackage.fishY);
	writeD(charInfoPackage.fishZ);
	writeD(charInfoPackage.nameColor);
	writeC(charInfoPackage.isRunning);
	writeD(charInfoPackage.PledgeClass);
	writeD(charInfoPackage.PledgeType);
	writeD(charInfoPackage.titleColor);
	writeD(0x00);//charInfoPackage.cw_level);
	writeD(charInfoPackage.Transformation); // Transformation id
	writeH(charInfoPackage.AttackElem);   // AttackElement (0 - Fire, 1 - Water, 2 - Wind, 3 - Earth, 4 - Holy, 5 - Dark, -2 - None)
	writeH(charInfoPackage.AttackElemPower); // AttackElementValue
	writeH(charInfoPackage.DefFire  ); // DefAttrFire
	writeH(charInfoPackage.DefWater ); // DefAttrWater
	writeH(charInfoPackage.DefWind  ); // DefAttrWind
	writeH(charInfoPackage.DefEarth ); // DefAttrEarth
	writeH(charInfoPackage.DefHoly  ); // DefAttrHoly
	writeH(charInfoPackage.DefUnholy); // DefAttrUnholy
	writeD(charInfoPackage.AgathionId);
	writeD(charInfoPackage.Fame); // Fame
	writeD(1);//charInfoPackage.activeRelation);  // if 1 the relation flag is grey
	writeD(charInfoPackage.Vitality); // Vitality Points
	writeF(0x00);//charInfoPackage.abnormalEffect2);
	writeD(0x01);
	writeD(0x00);
	printf("Size -> %d\n", size);

	SendPacketToClient();
	
	/*
	char buffer[10240] = "3298C3FFFF58E40100E0F3FFFF0000000053D2181030007800300035004400450046000000000000000100000000000000550000004F2E9E11030000000000000000000000280000001E0000002B000000150000000B000000190000006C0900006C0900007D0300007D030000102700005802000006D3A5001400000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000D0000006B0100009900000089000000890000003000000005000000D50000006B0100005B0000000000000000000000730000005000000037000000370000000000000000000000000000000000000018F7EB92CA87F13F5C8FC2F5285CF33F00000000000020400000000000803740050000000100000000000000000000004C00320053006B00690072006D006900730068000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001400000000000000C80000000000000000005A0300005A030000000000000000000000000000000000000000000000FFFFFF00010000000080FFFFFF77FFFF000000000000000000FEFF0000000000000000000000000000000000000000000001000000204E000000000000";
	
	std::string str_hex;
	char df[10240];
	char bud[10240] = {0};
	for (int i = 0, d = 0; i < (int)strlen(buffer); i++, d++)
	{
		bud[0] = buffer[i];bud[1] = buffer[i+1];i++;
		str_hex = bud;
		//std::cout << str_hex << std::endl;
		unsigned int hx = std::stol(str_hex,nullptr,16);
		df[d] = hx;
	}
	int sizet = strlen(buffer) / 2 - 1;

	send(clientSocket , df , sizet, 0); //*/

	//
}
void SendServerPacket::ValidateLocation                     ()
{
	writeC(0x79);
	writeD(charInfoPackage.ObjectID);

	writeD(charInfoPackage.X);
	writeD(charInfoPackage.Y);
	writeD(charInfoPackage.Z + 20);
	writeD(charInfoPackage.Heaidng);

	SendPacketToClient();
}
void SendServerPacket::MoveToLocation                       ()
{
	size = 0;
	//2F=MoveToLocation:d(ObjectID)d(DestX)d(DestY)d(DestZ)d(CurX)d(CurY)d(CurZ)
	writeC(0x2F);
	writeD(charInfoPackage.ObjectID);

	
	writeD(charInfoPackage.DestX);
	writeD(charInfoPackage.DestY);
	writeD(charInfoPackage.DestZ);

	writeD(charInfoPackage.X);
	writeD(charInfoPackage.Y);
	writeD(charInfoPackage.Z);
	

	SendPacketToClient();
}
void SendServerPacket::ChangeMoveType                       ()
{
	writeC(0x28);
	writeD(charInfoPackage.ObjectID);
	writeD(1);
	writeD(0);

	SendPacketToClient();
}
void SendServerPacket::ItemList                             ()
{
	writeC(0x11);
	writeH(0); //showWindow (Если 1 - то открывается инвентарь)
	writeH(1); //Количество итемов в инвентаре 
	/*
	0006 d  ObjectID: 270062169 (0x1018D259)
	000A d  ItemID: Адена ID:57 (0x0039)
	000E d  LocationSlot: 0 (0x00000000)
	0012 q  Count: 100000000
	001A h  ItemType2: 4 (0x0004)
	001C h  CustomType1: 0 (0x0000)
	001E h  isEquipped: 0 (0x0000)
	0020 d  BodyPart: 0 (0x00000000)
	0024 h  EnchantLevel: 0 (0x0000)
	0026 h  CustType2: 0 (0x0000)
	0028 d  AugmentID: 0
	002C d  Mana: 0 (0x00000000)
	0030 d  remainTime: 0 (0x00000000)
	0034 h  AttackElem: 65534 (0xFFFE)
	0036 h  AttackElemVal: 0 (0x0000)
	0038 h  DefAttrFire: 0 (0x0000)
	003A h  DefAttrWater: 0 (0x0000)
	003C h  DefAttrWind: 0 (0x0000)
	003E h  DefAttrEarth: 0 (0x0000)
	0040 h  DefAttrHoly: 0 (0x0000)
	0042 h  DefAttrUnholy: 0 (0x0000)
	0044 h  EnchEff1: 0 (0x0000)
	0046 h  enchEff2: 0 (0x0000)
	0048 h  enchEff3: 0 (0x0000)
	*/
	for (int i = 0; i < 1; i++)
	{
		//writeD(270062169);//Оид
		//writeD(57);       //Ид итема
		//writeD(0);//Номер слота в инвентаре
		//writeQ(1000000);//Количество
		//writeH(4);
		//writeH(0);
		//writeH(0);//Одеваемый?(одет?)
		//writeD(0); 
		//writeH(0);//Уровень заточки
		//writeH(0);
		//writeD(0);//Ид аугментации
		//writeD(0);//Мана
		//writeD(0);//Время, по которое живет
		//writeH(65534);
		//writeH(0);
		//writeH(0);
		//writeH(0);
		//writeH(0);
		//writeH(0);
		//writeH(0);
		//writeH(0);
		//writeH(0);
		//writeH(0);
		//writeH(0);

		writeD(270000000);//Оид
		writeD(2);       //Ид итема
		writeD(1);//Номер слота в инвентаре
		writeQ(1);//Количество
		writeH(0); //Тип итема ?
		writeH(0); //Кастом тип?
		writeH(1);//Одеваемый?(одет?)
		writeD(64<<1); //Боди парт
		writeH(20);//Уровень заточки
		writeH(0);
		writeD(0);//Ид аугментации
		writeD(0);//Мана
		writeD(0);//Время, по которое живет
		writeH(1);//Стихия
		writeH(300);//Сила стихии
		writeH(0); //Защита от стихий
		writeH(0); //Защита от стихий
		writeH(0); //Защита от стихий
		writeH(0); //Защита от стихий
		writeH(0); //Защита от стихий
		writeH(0); //Защита от стихий
		writeH(24); //Какие то эфекты заточки
		writeH(24); //Какие то эфекты заточки
		writeH(24); //Какие то эфекты заточки



	}
	writeH(0); //Какой то блок итемов

	SendPacketToClient();
}
void SendServerPacket::InventoryUpdate                      ()
{
	writeC(0x21);
	writeH(0); //Количество обновляемых предметов
	SendPacketToClient();
}
void SendServerPacket::LeaveWorld                           ()
{
	writeC(0x84);
	SendPacketToClient();
}
void SendServerPacket::CreatureSay(int type, wchar_t* message)
{
	writeC(0x4A);
	if (type = 10)
	{
		writeD(0);
		writeD(10);
		writeS(charInfoPackage.Name);
		writeD(0xFFFFFFFF);
		writeS(message);
		writeD(0);
		writeD(0);
	}
	SendPacketToClient();
}
void SendServerPacket::ShowMiniMap                          ()
{
	//A3 00 00 00 00 00 
	writeC(0xA3);
	writeD(0);
	writeC(0x00);
	SendPacketToClient();
}
void SendServerPacket::Previous                             ()
{
	switch (dStagePlayer)
	{
	case STAGE_REQUESTAUTCHLOGIN:
		CharSelectInfo();
		break;
	case STAGE_CHARACTERCREATE:
		dStagePlayer = STAGE_REQUESTAUTCHLOGIN;
		break;
	}
	
}
void SendServerPacket::SystemMessage(int id)
{
	writeC(0x62);
	writeD(id);
	SendPacketToClient();
}