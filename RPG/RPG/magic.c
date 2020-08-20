#include "magic.h"
#include "character.h"




MAGIC gMagicMaster[] = {

	{ "" },  
	{ "�t�@�C�A�[�{�[��", MTYPE_ATTACK, 10, FIRE, 3, 1 },
	{ "���̂��", MTYPE_ATTACK, 30, LIGHT, 40, 4 },
	{ "����", MTYPE_ATTACK, 300, WIND, 30, 34 },
	{ "�A�[�X�X�p�C�N", MTYPE_ATTACK, 150, EARTH, 40, 34 },
	{ "�w�[��", MTYPE_RECOVER, 20, LIGHT, 10, 2 },
	{ "�\�[�h�X���b�V��", MTYPE_ATTACK, 15, NOELEMENT, 15, 5 },
	
};



void Magic_Use(MAGIC * pMg, CHARACTER * pChOwner, CHARACTER * pChTarget)
{
	switch (pMg->type) {
	case MTYPE_ATTACK:
		
		break;

	case MTYPE_RECOVER:
		Character_ConsumeMp(pChOwner, pMg->mp);
		Character_RecoverHp(pChTarget, pMg->value);
		break;
	}
}

int GetNumberOfMagicMaster(void)
{
	return sizeof(gMagicMaster) / sizeof(MAGIC);
}


MAGIC * GetMagic(int id)
{
	return gMagicMaster + id;
}
