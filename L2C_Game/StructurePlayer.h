#pragma once
#include <Windows.h>
#include "DefaultStats.h"

class Player
{
public:
	struct PlayerInfo
	{
		wchar_t login[255];
		DWORD sessionId;

		DWORD X;
		DWORD Y;
		DWORD Z;
		DWORD Heaidng;
		DWORD isInAirShip;
		DWORD ObjectID;
		wchar_t Name[255];
		DWORD Race;
		DWORD Sex;
		DWORD ClassID;
		DWORD lvl;
		long Exp;
		int STR;
		int DEX;
		int CON;
		int INT;
		int WIT;
		int MEN;
		double MaxHp;
		double CurHp;
		double MaxMp;
		double CurMp;
		DWORD Sp;
		DWORD CurLoad;
		DWORD MaxLoad;
		DWORD isWeapEquip; // 40yes 20no

		DWORD Under  [2];//0 - ID, 1 - OID                 0
		DWORD REar   [2];//0 - ID, 1 - OID			       1
		DWORD LEar   [2];//0 - ID, 1 - OID			       2
		DWORD Neck   [2];//0 - ID, 1 - OID			       3
		DWORD RRing  [2];//0 - ID, 1 - OID			       4
		DWORD LRing  [2];//0 - ID, 1 - OID			       5
		DWORD Head   [2];//0 - ID, 1 - OID Броня	       6
		DWORD RHand  [2];//0 - ID, 1 - OID Оружие          7
		DWORD LHand  [2];//0 - ID, 1 - OID Броня	       8
		DWORD Gloves [2];//0 - ID, 1 - OID Броня	       9
		DWORD Chest  [2];//0 - ID, 1 - OID Броня	       10
		DWORD legs   [2];//0 - ID, 1 - OID Броня	       11
		DWORD Feet   [2];//0 - ID, 1 - OID Броня	       12
		DWORD Back   [2];//0 - ID, 1 - OID Броня	       13
		DWORD LRHand [2];//0 - ID, 1 - OID оружие          14
		DWORD Hair   [2];//0 - ID, 1 - OID			       15
		DWORD Hair2  [2];//0 - ID, 1 - OID			       16
		DWORD RBrace [2];//0 - ID, 1 - OID			       17
		DWORD LBrace [2];//0 - ID, 1 - OID			       18
		DWORD DEC1   [2];//0 - ID, 1 - OID			       19
		DWORD DEC2   [2];//0 - ID, 1 - OID			       20
		DWORD DEC3   [2];//0 - ID, 1 - OID			       21
		DWORD DEC4   [2];//0 - ID, 1 - OID			       22
		DWORD DEC5   [2];//0 - ID, 1 - OID			       23
		DWORD DEC6   [2];//0 - ID, 1 - OID			       24
		DWORD Belt   [2];//0 - ID, 1 - OID			       25
		

		DWORD talismanSlots;
		bool cloakStatus;

		DWORD PAtk;        //Физ атака
		DWORD PDef;        //Физ защита
		DWORD Accuracy;    //Точность
		DWORD Critical;    //Сила крита
		DWORD AtkSpd;      //Скорость атаки
		DWORD MAtk;        //Маг атака
		DWORD MDef;        //Маг защита
		DWORD Evasion;     
		DWORD Speed;       //Скорость бега
		DWORD CastSpd;     //Скорость каст

		DWORD pvpFlag;
		DWORD Karma;
		DWORD RunSpd;
		DWORD WalkSpd;
		DWORD SwimRunSpd;
		DWORD SwimWalkSpd;
		DWORD Unk0;
		DWORD Unk1;
		DWORD FlyRunSpd;
		DWORD FlyWalkSpd;
		double MoveMul;
		double AtkSpdMul;
		double ColRadius;
		double ColHeight;

		DWORD HairStule;
		DWORD HairColor;
		DWORD Face;
		
		DWORD isGM;
		wchar_t title[255];
		DWORD ClanID;
		DWORD ClanCrestID;
		DWORD AllyID;
		DWORD AllyCrestID;
		DWORD Relation;
		char mountTupe;
		char privateStoreType;
		bool isCrystalize;

		DWORD pkKill;
		DWORD PvPKill;

		WORD cubicsSize;
		char findParty;
		DWORD abnormalEffect;
		char isFlyingMounted;
		DWORD clanPrivs;
		WORD recomLeft;
		WORD recomHave;
		DWORD mountNpcID;
		WORD inventoryLimit;
		DWORD ClassID2;
		DWORD specEffcts;
		DWORD MaxCP;
		DWORD CurCP;
		double ExpPercent;
		char isMounted;
		char Team;
		DWORD ClanCrestLangeID;
		char isNoble;
		char isHero;
		char isFishing;
		DWORD fishX;
		DWORD fishY;
		DWORD fishZ;
		DWORD nameColor;
		char isRunning;
		DWORD PledgeClass;
		DWORD PledgeType;
		DWORD titleColor;
		DWORD cursedWeap;
		DWORD Transformation;

		WORD AttackElem;
		WORD AttackElemPower;
		WORD DefFire;
		WORD DefWater;
		WORD DefWind;
		WORD DefEarth;
		WORD DefHoly;
		WORD DefUnholy;

		DWORD AgathionId;
		DWORD Fame;
		DWORD mmapAllowed;
		DWORD Vitality;
		DWORD specEffects;
		DWORD DestX, DestY,DestZ;

		DWORD AccessLevel;

		int ActiveSkill[255];
		int PassiveSkill[255];
		//int SubClass[3];

		
	};
};

