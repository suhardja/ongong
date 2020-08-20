#pragma once


typedef struct _MAGIC MAGIC;


#define MAX_MAGIC_LIST	10


typedef struct _CHARACTER {

	int id;

	char name[16];
	int lv;

	int hp;
	int mp;

	int max_hp;
	int max_mp;

	

	int exp;

	
	int magicIDList[MAX_MAGIC_LIST];

} CHARACTER;


#define MAX_LEVEL	99

typedef struct {

	struct {
		int exp;		
		int hp;			
		int mp;			
		int magicID;	
	} lv[MAX_LEVEL];

} CHARACTER_LVUP;


extern CHARACTER gCharaMaster[];
extern CHARACTER_LVUP gCharLvupMaster[];

void Character_RecoverHpMax(CHARACTER*);
void Character_RecoverMpMax(CHARACTER* pCh);

void Character_RecoverHp(CHARACTER* pCh, int value);
void Character_ConsumeMp(CHARACTER* pCh, int value);

void Character_GetExp(CHARACTER* pCh, int exp);
void Character_Lvup(CHARACTER* pCh);
void Character_LearnMagic(CHARACTER* pCh, int magicID);

void Character_PrintStatus(CHARACTER* pCh);

