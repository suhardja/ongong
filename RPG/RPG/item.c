#include "item.h"


ITEM gItemMaster[] = {
	{ ITYPE_HPRECOVER, 0, "レッドポーション", 10, 10 },			
	{ ITYPE_MPRECOVER, 1, "ブルーポーション", 10, 50 },
	{ ITYPE_WEAPON, 2, "木刀", 30, 150 },
	{ ITYPE_ETC, 3, "しびりポーション", 10, 100 },
	{ ITYPE_ETC, 4, "YGGDRASIL", 10, 15000 },
	{ ITYPE_ETC, 5, "毒けしポーション", 10, 150 },			
	{ ITYPE_ETC, 6, "眠りけしポーショ", 10, 200 },
	{ ITYPE_WEAPON, 7, "ドラゴンバスター", 10, 4000 },
	{ ITYPE_WEAPON, 8, "大剣", 10, 30 },			
};


int GetNumberOfItemMaster(void)
{
	return sizeof(gItemMaster) / sizeof(ITEM);
}
