#include "character.h"
#include "magic.h"
#include <stdio.h>


	
	CHARACTER gCharaMaster[] = {

		{
			0, 
			"—EŽÒ",
			1,		
			50,		
			15,		
			50,		
			15,		
			0,		

			{ 1 }  
		},

		{
			1, 


			"Œ•Žm",
			1,		
			100,		
			0,		
			100,		
			0,		
			0,		

			{ 0 }  
		},

		{
			2, 


			"–‚–@Žg‚¢",
			1,
			30,
			80,
			30,
			80,
			0,

			{ 4 }
		},
	};


CHARACTER_LVUP gCharLvupMaster[] = {
	{	
		{
			{ 0 },  
			{ 10, 50, 15, 1 }, 
			{ 20, 52, 16, 0 }, 
			{ 30, 54, 17, 2 }, 
			{ 40, 56, 18, 0 }, 
			{ 50, 58, 20, 0 }, 
		}
	},

	{
		{
			{ 0 },
			{ 10, 100, 0, 0 },
			{ 50, 105, 0, 0 },
			{ 30, 110, 0, 0 },
			{ 40, 115, 0, 0 },
			{ 50, 120, 0, 0 },
		}
	},

	{	
		{
			{ 0 },  
			{ 10, 30, 80, 0 }, 
			{ 20, 42, 90, 0 }, 
			{ 30, 55, 100, 0 },
			{ 40, 57, 120, 0 },
			{ 50, 70, 150, 0 }, 
		}
	}

	
};



void Character_RecoverHpMax(CHARACTER* pCh) {
	pCh->hp = pCh->max_hp;
}


void Character_RecoverMpMax(CHARACTER * pCh)
{
	pCh->mp = pCh->max_mp;
}


void Character_RecoverHp(CHARACTER * pCh, int value)
{
	pCh->hp += value;

	if (pCh->hp > pCh->max_hp) {
		pCh->hp = pCh->max_hp;
	}
}

void Character_ConsumeMp(CHARACTER * pCh, int value)
{
	pCh->mp -= value;

	if (pCh->mp < 0) {
		pCh->mp = 0;
	}
}


void Character_GetExp(CHARACTER * pCh, int exp)
{
	pCh->exp += exp;
	Character_Lvup(pCh);
}


void Character_Lvup(CHARACTER * pCh)
{
	const int nextLv = pCh->lv + 1;

	if (pCh->exp > gCharLvupMaster[pCh->id].lv[nextLv].exp) {  
		pCh->lv++;
		pCh->max_hp = gCharLvupMaster[pCh->id].lv[nextLv].hp;
		pCh->max_mp = gCharLvupMaster[pCh->id].lv[nextLv].mp;

		if (gCharLvupMaster[pCh->id].lv[nextLv].magicID != 0) {
			Character_LearnMagic(pCh, gCharLvupMaster[pCh->id].lv[nextLv].magicID);
		}
	}
}

void Character_LearnMagic(CHARACTER * pCh, int magicID)
{
	for (int i = 0; i < MAX_MAGIC_LIST; i++) {  
		if (pCh->magicIDList[i] == magicID) {  
			break;
		}
		else if (pCh->magicIDList[i] == 0) { 
			pCh->magicIDList[i] = magicID;  
			break;
		}
	}
}


void Character_PrintStatus(CHARACTER * pCh)
{
	printf("%s\n", pCh->name);

	printf("LV: %d\n", pCh->lv);

	
	if (pCh->hp < pCh->max_hp / 3) {  
		if (pCh->hp < pCh->max_hp / 5) {  
			printf("\x1b[33m");  
		}
		else {
			printf("\x1b[36m"); 
		}
	}

	printf("HP: %d / %d\n", pCh->hp, pCh->max_hp);

	printf("\x1b[40m"); 

	printf("MP: %d / %d\n", pCh->mp, pCh->max_mp);
}


