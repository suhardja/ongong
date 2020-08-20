#pragma once


typedef struct _CHARACTER CHARACTER;


typedef struct _MAGIC {

	char name[20];  

	int type;  

	int value;  

	int element;  

	int mp;  

	int masteryLevel;  

} MAGIC;





enum MTYPE {   

	MTYPE_ATTACK,
	MTYPE_RECOVER,
	MTYPE_BUFF,
	MTYPE_DEBUFF

};


enum ELTYPE {

	NOELEMENT,  
	FIRE,
	WATER,
	EARTH,
	WIND,
	DARK,
	LIGHT

};


extern MAGIC gMagicMaster[];



void Magic_Use(MAGIC* pMg, CHARACTER* pChOwner, CHARACTER* pChTarget);

int GetNumberOfMagicMaster(void);

MAGIC* GetMagic(int id);
