#pragma once


typedef struct {
	int type;
	int itemNo;		
	char name[32];  
	int value;
	int price;  
} ITEM;


enum ITYPE {

	ITYPE_HPRECOVER,
	ITYPE_MPRECOVER,
	ITYPE_WEAPON,
	ITYPE_ARMOR,
	ITYPE_ETC

};


extern ITEM gItemMaster[];



int GetNumberOfItemMaster(void);
