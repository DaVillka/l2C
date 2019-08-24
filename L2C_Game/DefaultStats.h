#pragma once
#include <Windows.h>

#define HUMAN_FIGHTER 0

struct DefaultStats
{
	int classBaseLevel;
	int raceId;
	int profId;
	double MaxHP;	
	double MaxMP;
	double MaxCP;
	double HpReg;
	double MpReg;
	double CpReg;

	int PAtk;           //Физ атака
	int PDef;           //Физ защита
	int Accuracy;       //Точность
	int Critical;       //Сила крита
	int AtkSpd;         //Скорость атаки
					    
	int MAtk;           //Маг атака
	int MDef;           //Маг защита
	int Evasion;        //Точность
	int CastSpd;        //Скорость каст
	int baseCritRate;
	int	baseWalkSpd;
	int	baseRunSpd;
	int	baseShldDef;
	int	baseShldRate;
	int	baseAtkRange;

	double lvlHpAdd;
	double lvlHpMod;
	double lvlCpAdd;
	double lvlCpMod;
	double lvlMpAdd;
	double lvlMpMod;


	int STR;
	int DEX;
	int CON;
	int INT;
	int WIT;
	int MEN;

	int Ves;
	bool Crystalize;

	DWORD defX;
	DWORD defY;
	DWORD defZ;

	WORD  DefFire      ;
	WORD  DefWater	   ;
	WORD  DefWind	   ;
	WORD  DefEarth	   ;
	WORD  DefHoly	   ;
	WORD  DefUnholy	   ;
	WORD AttackElem    ;

	
	float male_collision_radius   ;
	float male_collision_height	  ;
	float female_collision_radius ;
	float female_collision_height ;

	bool isRunning;
};
struct DefaultStatsAllClass
{
	
	double mSTR[255]; 
	double mDEX[255];
	double mCON[255];
	double mINT[255];
	double mWIT[255];
	double mMEN[255];

	WORD  DefFire      ;
	WORD  DefWater	   ;
	WORD  DefWind	   ;
	WORD  DefEarth	   ;
	WORD  DefHoly	   ;
	WORD  DefUnholy	   ;
	WORD AttackElem   ;
	int LvL;
	int Vitality;
};
DefaultStatsAllClass defaultStatAllClass;

DefaultStats HumanFighter, Warrior, Gladiator, Warlord, HumanKnight, Paladin, DarkAvenger, Rogue, TreasureHunter, Hawkeye, HumanMage, HumanWizard, Sorcerer, Necromancer, Warlock, Cleric, HumanProphet, Bishop, Adventurer, Sagittarius, Soultaker, Archmage, DreadNought, Duelist, HellKnight, PhoenixKnight, Hierophant, ArcanaLord, Cardinal;

void CreateStatMod(double* STR, double* INT, double* CON, double* DEX, double* WIT, double* MEN )
{
	// 1	0.46	21	0.82	41	1.48
	// 2	0.47	22	0.85	42	1.53
	// 3	0.48	23	0.87	43	1.58
	// 4	0.50	24	0.90	44	1.62
	// 5	0.51	25	0.93	45	1.67
	// 6	0.53	26	0.95	46	1.72
	// 7	0.54	27	0.98	47	1.77
	// 8	0.56	28	1.01	48	1.83
	// 9	0.58	29	1.04	49	1.88
	// 10	0.59	30	1.07	50	1.94
	// 11	0.61	31	1.10	51	2.00
	// 12	0.63	32	1.14	52	2.06
	// 13	0.65	33	1.17	53	2.12
	// 14	0.67	34	1.21	54	2.18
	// 15	0.69	35	1.24	55	2.25
	// 16	0.71	36	1.28	56	2.31
	// 17	0.73	37	1.32	57	2.38
	// 18	0.75	38	1.36	58	2.45
	// 19	0.77	39	1.40	59	2.53
	// 20	0.80	40	1.44	
	
	//CON[1]  = 0.46 ; CON[21] = 0.82 ; CON[41] = 1.48 ; 
	//CON[2]  = 0.47 ; CON[22] = 0.85 ; CON[42] = 1.53 ; 
	//CON[3]  = 0.48 ; CON[23] = 0.87 ; CON[43] = 1.58 ; 
	//CON[4]  = 0.50 ; CON[24] = 0.90 ; CON[44] = 1.62 ; 
	//CON[5]  = 0.51 ; CON[25] = 0.93 ; CON[45] = 1.67 ; 
	//CON[6]  = 0.53 ; CON[26] = 0.95 ; CON[46] = 1.72 ; 
	//CON[7]  = 0.54 ; CON[27] = 0.98 ; CON[47] = 1.77 ; 
	//CON[8]  = 0.56 ; CON[28] = 1.01 ; CON[48] = 1.83 ; 
	//CON[9]  = 0.58 ; CON[29] = 1.04 ; CON[49] = 1.88 ; 
	//CON[10] = 0.59 ; CON[30] = 1.07 ; CON[50] = 1.94 ; 
	//CON[11] = 0.61 ; CON[31] = 1.10 ; CON[51] = 2.00 ; 
	//CON[12] = 0.63 ; CON[32] = 1.14 ; CON[52] = 2.06 ; 
	//CON[13] = 0.65 ; CON[33] = 1.17 ; CON[53] = 2.12 ; 
	//CON[14] = 0.67 ; CON[34] = 1.21 ; CON[54] = 2.18 ; 
	//CON[15] = 0.69 ; CON[35] = 1.24 ; CON[55] = 2.25 ; 
	//CON[16] = 0.71 ; CON[36] = 1.28 ; CON[56] = 2.31 ; 
	//CON[17] = 0.73 ; CON[37] = 1.32 ; CON[57] = 2.38 ; 
	//CON[18] = 0.75 ; CON[38] = 1.36 ; CON[58] = 2.45 ; 
	//CON[19] = 0.77 ; CON[39] = 1.40 ; CON[59] = 2.53 ; 
	//CON[20] = 0.80 ; CON[40] = 1.44 ; CON[0]  = 0.45;

	double str_bonus[100] = {-70,-69,-68,-66,-65,-64,-63,-61,-60,-58,-57,-55,-54,-52,-50,-49,-47,-45,-43,-41,-39,-37,-34,-32,-29,-27,-24,-22,-19,-16,-13,-10,-6,-3,1,4,8,12,16,20,24,29,33,38,43,48,54,59,65,71,77,83,90,97,104,111,119,127,135,143,152,161,171,180,191,201,212,223,235,247,259,272,286,299,314,329,344,360,377,394,412,430,449,469,489,511,533,555,579,603,629,655,682,710,739,770,801,833,867		};
	double int_bonus[100] = {-45,-44,-43,-42,-41,-39,-38,-37,-36,-35,-33,-32,-31,-29,-28,-26,-25,-23,-22,-20,-19,-17,-15,-14,-12,-10,-8,-6,-5,-3,-1,1,3,5,7,10,12,14,16,19,21,23,26,28,31,34,36,39,42,45,47,50,53,57,60,63,66,69,73,76,80,83,87,91,95,99,102,107,111,115,119,124,128,133,137,142,147,152,157,162,167,173,178,184,189,195,201,207,213,219,226,232,239,246,253,260,267,274,282                   		};
	double con_bonus[100] = {-54,-53,-52,-50,-49,-47,-46,-44,-42,-41,-39,-37,-35,-33,-31,-29,-27,-25,-23,-20,-18,-15,-13,-10,-7,-5,-2,1,4,7,10,14,17,21,24,28,32,36,40,44,48,53,58,62,67,72,77,83,88,94,100,106,112,118,125,131,138,145,153,160,168,176,184,193,202,211,220,230,240,250,260,271,282,294,306,318,330,343,356,370,384,399,414,429,445,461,478,496,513,532,551,570,590,611,633,654,677,700,724    		};
	double dex_bonus[100] = {-15,-14,-14,-13,-12,-11,-10,-10,-9,-8,-7,-6,-6,-5,-4,-3,-2,-1,0,1,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,24,25,26,27,28,29,30,32,33,34,35,36,38,39,40,41,43,44,45,47,48,49,51,52,53,55,56,57,59,60,62,63,65,66,68,69,71,72,74,75,77,78,80,82,83,85,87,88,90,92,93,95,97,99,100,102,104                                                                          		};
	double wit_bonus[100] = {-60,-58,-56,-54,-52,-49,-47,-44,-42,-39,-36,-32,-29,-25,-22,-18,-14,-9,-5,0,5,10,16,22,28,34,41,48,55,63,71,80,89,98,108,118,129,141,153,165,179,193,207,223,239,256,273,292,312,332,354,376,400,425,452,479,508,539,570,604,639,676,715,756,799,843,891,940,992,1047,1104,1164,1227,1294,1364,1437,1514,1594,1679,1768,1861,1959,2062,2170,2284,2403,2528,2660,2798,2943,3095,3255,3422,3598,3783,3977,4181,4395,4620	};	
	double men_bonus[100] = {1,2,3,4,5,6,7,8,9,11,12,13,14,15,16,17,19,20,21,22,23,25,26,27,28,30,31,32,34,35,36,38,39,40,42,43,45,46,48,49,50,52,53,55,57,58,60,61,63,65,66,68,70,71,73,75,76,78,80,82,84,85,87,89,91,93,95,97,99,101,103,105,107,109,111,113,115,117,120,122,124,126,129,131,133,135,138,140,143,145,147,150,152,155,158,160,163,165,168};
	
	for (int i = 0; i < 100; i++)
	{
		int_bonus[i] = (100 + int_bonus[i]) / 100;
		con_bonus[i] = (100 + con_bonus[i]) / 100;
		dex_bonus[i] = (100 + dex_bonus[i]) / 100;
		wit_bonus[i] = (100 + wit_bonus[i]) / 100;
		men_bonus[i] = (100 + men_bonus[i]) / 100;
	}
	memcpy(STR, str_bonus, sizeof(str_bonus));
	memcpy(INT, int_bonus, sizeof(int_bonus));
	memcpy(CON, con_bonus, sizeof(con_bonus));
	memcpy(DEX, dex_bonus, sizeof(dex_bonus));
	memcpy(WIT, wit_bonus, sizeof(wit_bonus));
	memcpy(MEN, men_bonus, sizeof(men_bonus));
}
int DefaultStatsAllClassCreate()
{
	
	//Создаем статический массив множителей CON
	CreateStatMod(defaultStatAllClass.mSTR,defaultStatAllClass.mINT,defaultStatAllClass.mCON,defaultStatAllClass.mDEX,defaultStatAllClass.mWIT,defaultStatAllClass.mMEN );

	//Статический показатель защиты от стихий
	defaultStatAllClass.DefFire     = 0;
	defaultStatAllClass.DefWater	= 0;
	defaultStatAllClass.DefWind	    = 0;
	defaultStatAllClass.DefEarth	= 0;
	defaultStatAllClass.DefHoly	    = 0;
	defaultStatAllClass.DefUnholy	= 0;
	defaultStatAllClass.AttackElem  = -2; //статик ид атакующего елемента стихии класса (-1 - отсутствует)
	//Левел, при создании чара
	defaultStatAllClass.LvL         = 1;
	//Виталити
	//{ 240, 2000, 13000, 17000, 20000 };
	defaultStatAllClass.Vitality    = 240;
	return true;
}
int CreateDefaultHumanFighterStats()
{
	//int zeroX = -71340; int radiusX = 323;
	//int zeroY = 258393; int radiusY = 132;
	//srand((unsigned int)time(0));
	//HumanFighter.defX       = (rand() % 2) == 0 ? (zeroX + (rand() % radiusX - (radiusX*2))) : (zeroX + (rand() % radiusX));
	//HumanFighter.defY       = (rand() % 2) == 0 ? (zeroY + (rand() % radiusY - (radiusY*2))) : (zeroY + (rand() % radiusY));;
	//HumanFighter.defZ       = -3105;
	

	//HumanFighter.MaxHP = HumanFighter.MaxHP * (float)defaultStatAllClass.mCON[HumanFighter.CON];

	HumanFighter.raceId                   = 0;
	HumanFighter.Ves                      = 81900;
	HumanFighter.Crystalize               = false;							              
	HumanFighter.DefFire                  = defaultStatAllClass.DefFire ; 
	HumanFighter.DefWater	              = defaultStatAllClass.DefWater;
	HumanFighter.DefWind	              = defaultStatAllClass.DefWind;
	HumanFighter.DefEarth	              = defaultStatAllClass.DefEarth;
	HumanFighter.DefHoly	              = defaultStatAllClass.DefHoly;
	HumanFighter.DefUnholy	              = defaultStatAllClass.DefUnholy;
	HumanFighter.AttackElem               = defaultStatAllClass.AttackElem;
	HumanFighter.defX                     = -71338;
	HumanFighter.defY                     = 258271;
	HumanFighter.defZ                     = -3104;
	HumanFighter.male_collision_radius    = 9.0;
	HumanFighter.male_collision_height    = 23.0;
	HumanFighter.female_collision_radius  = 8.0; 
	HumanFighter.female_collision_height  = 23.5;	  
	HumanFighter.isRunning  = true;

	HumanFighter.profId                   = 0;
	HumanFighter.classBaseLevel           = 1;
	HumanFighter.MaxHP                    = 80.f;
	HumanFighter.MaxMP                    = 38.f;
	HumanFighter.MaxCP                    = 32.f;
	HumanFighter.HpReg                    = 0.01;
	HumanFighter.MpReg                    = 0.01;
	HumanFighter.CpReg                    = 0.01;					              
	HumanFighter.PAtk                     = 4;
	HumanFighter.PDef                     = 72;
	HumanFighter.Accuracy                 = 33;
	HumanFighter.Critical                 = 44;
	HumanFighter.AtkSpd                   = 330;
	HumanFighter.MAtk                     = 3;
	HumanFighter.MDef                     = 41;
	HumanFighter.Evasion                  = 33;
	HumanFighter.CastSpd                  = 333;								          
	HumanFighter.baseCritRate             = 44;
	HumanFighter.baseWalkSpd	          = 80;
	HumanFighter.baseRunSpd		          = 115;
	HumanFighter.baseShldDef	          = 0;
	HumanFighter.baseShldRate	          = 0;
	HumanFighter.baseAtkRange	          = 40;								          
	HumanFighter.lvlHpAdd                 = 11.7;
	HumanFighter.lvlHpMod		          = 0.13;
	HumanFighter.lvlCpAdd		          = 4.68;
	HumanFighter.lvlCpMod		          = 0.05;
	HumanFighter.lvlMpAdd		          = 5.4;
	HumanFighter.lvlMpMod                 = 0.06;					    		          
	HumanFighter.STR                      = 40;
	HumanFighter.DEX                      = 30;
	HumanFighter.CON                      = 43;
	HumanFighter.INT                      = 21;
	HumanFighter.WIT                      = 11;
	HumanFighter.MEN                      = 25;							              
	
	
	return true;

}
bool CreateDefaultStats()
{
	if (!DefaultStatsAllClassCreate()) { printf("Error Created defaultStatAllClass\n");       return false;}
	if (!CreateDefaultHumanFighterStats())    { printf("Error Created HumanFighter DefaultStats\n"); return false;}
	return true;
}


int GetDefaultStats(DefaultStats* def, int race, int special, int sex, DWORD* HairStule, DWORD* HairColor, DWORD* Face)
{
	//Человек - 0, Ельф -1, Темный эльф - 2, Орк - 3, Гном - 4, Камаель - 5
	switch (race)
	{
	case 0://
		if (special == HUMAN_FIGHTER)
		{
			if (sex == 0) 
			{
				*def = HumanFighter;
			}
			else 
			{
				if (*HairStule < 0 || *HairStule > 6) *HairStule = 0;
				if (*HairColor < 0 || *HairColor > 3) *HairColor = 0;
				if (*Face      < 0 || *Face      > 2) *Face      = 0;
				*def = HumanFighter;
			}
		}
		else return -1;
		break;
	
	default:
		return -1;
		break;
	}
	return 0;
}