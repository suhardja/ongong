#include "item.h"


ITEM gItemMaster[] = {
	{ ITYPE_HPRECOVER, 0, "���b�h�|�[�V����", 10, 10 },			
	{ ITYPE_MPRECOVER, 1, "�u���[�|�[�V����", 10, 50 },
	{ ITYPE_WEAPON, 2, "�ؓ�", 30, 150 },
	{ ITYPE_ETC, 3, "���т�|�[�V����", 10, 100 },
	{ ITYPE_ETC, 4, "YGGDRASIL", 10, 15000 },
	{ ITYPE_ETC, 5, "�ł����|�[�V����", 10, 150 },			
	{ ITYPE_ETC, 6, "���肯���|�[�V��", 10, 200 },
	{ ITYPE_WEAPON, 7, "�h���S���o�X�^�[", 10, 4000 },
	{ ITYPE_WEAPON, 8, "�匕", 10, 30 },			
};


int GetNumberOfItemMaster(void)
{
	return sizeof(gItemMaster) / sizeof(ITEM);
}
