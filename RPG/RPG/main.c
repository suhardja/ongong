#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>


#include "player.h"  
#include "magic.h"
#include "item.h"
#include "character.h"



enum GAMESTATUS {
	GS_APP_END,
	GS_TITLE,
	GS_OPENING,
	GS_TOWN,
	GS_SHOP,
	GS_SHOP_BUY,
	GS_SHOP_SELL,
	GS_STATUS,

	GS_DUNGEON,
	GS_BATTLE,
	GS_TREASURE,
	GS_STAIRS,

	GS_GAMEOVER,

	GS_ITEM_USE,
	GS_MAGIC_USE,

	GS_IIN,
	GS_LOADING

};

void ShowTownBilboard(void);
void ShowShopBilboard(int);
void ShowDungeonBillboard(void);
void WaitForEnter(void);
void ShowMessage(int);
void PrintAlignedStr(const char* str, int maxlen);

int Get1of3(int, int, int);
int Get1of4(int, int, int, int);

void save(void);
void load(void);

void GsTitle(void);
void GsOpening(void);
void GsTown(void);
void GsShop(void);
void GsShopBuy(void);
void GsShopSell(void);
void GsDungeon(void);
void GsBattle(void);
void GsTreasure(void);
void GsStairs(void);
void GsGameOver(void);
void GsStatus(void);
void GsItemUse(void);
void GsMagicUse(void);
void GsIin(void);
void GsLoading(void);

char* gMsgMaster[] = {
	"!!!!戦闘開始!!!!",
	"宝箱を見つけた！",
	"階段を見つけた！",
	"【ゲームオーバー】"

};

typedef struct {
	ITEM* item[4];
} TREASURE_ITEM;

TREASURE_ITEM gTreasureItemMaster[] = {
	{ NULL },  
	{ &gItemMaster[0], &gItemMaster[3], &gItemMaster[6], &gItemMaster[1] },
	{ &gItemMaster[0], &gItemMaster[3], &gItemMaster[8], &gItemMaster[1] },
	{ &gItemMaster[0], &gItemMaster[3], &gItemMaster[5], &gItemMaster[1] },
	{ &gItemMaster[0], &gItemMaster[4], &gItemMaster[7], &gItemMaster[1] },
};



int gGameStatus = GS_TOWN;

PLAYER gPlayer;


#define MAX_PARTY_MEMBER 3
CHARACTER gParty[MAX_PARTY_MEMBER];

unsigned int gStartTime;


void main(void) {
	for (int i = 0; i < GetNumberOfItemMaster(); i++) {
		gPlayer.inventory[i] = 0;
	}

	gPlayer.gold = 500;
	
	gParty[0] = gCharaMaster[0];
	gParty[1] = gCharaMaster[1];
	gParty[2] = gCharaMaster[2];

	srand((unsigned int)time(NULL));
	load();



	while (gGameStatus != GS_APP_END) {

		switch (gGameStatus) {
		case GS_TITLE:
			GsTitle();
			break;

		case GS_OPENING:
			GsOpening();
			break;

		case GS_TOWN:
			GsTown();
			break;

		case GS_SHOP:
			GsShop();
			break;

		case GS_SHOP_BUY:
			GsShopBuy();
			break;

		case GS_SHOP_SELL:
			GsShopSell();
			break;

		case GS_STATUS:
			GsStatus();
			break;

		case GS_DUNGEON:
			GsDungeon();
			break;

		case GS_BATTLE:
			GsBattle();
			break;

		case GS_MAGIC_USE:
			GsMagicUse();
			break;

		case GS_STAIRS:
			GsStairs();
			break;

		case GS_GAMEOVER:
			GsGameOver();
			break;

		case GS_ITEM_USE:
			GsItemUse();
			break;

		case GS_IIN:
			GsIin();
			break;

		case GS_LOADING:
			GsLoading();
			break;

		
		}
	}

}

void GsTitle(void) {

	system("cls");
	printf("DRAGON MASTER ONLINE\n\n");
	WaitForEnter();
	gGameStatus = GS_OPENING;

}

void GsOpening(void) {

	system("cls");
	printf("名前を入力してください。>>>>>>> ");
	scanf_s("%s", gPlayer.myName, 40);
	printf("ようこそ！　DRAGON MASTER ONLINE へ!!! \n");
	gGameStatus = GS_TOWN;

}

void GsTown(void) {
	int command;

	
	system("cls");

	ShowTownBilboard();

	printf("今日は何をしますか！>>\n");
	printf("1. お店に行く\n");
	printf("2. ダンジョンに行く\n");
	printf("3. 宿に行く\n");
	printf("4. ステータス\n");
	printf("0. ゲーム終了\n");
	printf(">>>");

	scanf_s("%d", &command);

	if (command == 1) {
		gGameStatus = GS_SHOP;
	}
	else if (command == 2) {
		gGameStatus = GS_LOADING;
		gStartTime=(unsigned int)time(NULL);
		gPlayer.floorNo = 1;
	}
	else if (command == 3) {
		gGameStatus = GS_LOADING;
		gStartTime = (unsigned int)time(NULL);

		Character_RecoverHpMax(&gParty[0]);
		Character_RecoverMpMax(&gParty[0]);
		Character_RecoverHpMax(&gParty[1]);
		Character_RecoverMpMax(&gParty[1]);
		gGameStatus = GS_IIN;

	}
	else if (command == 4) {
		gGameStatus = GS_STATUS;
	}
	else if (command == 0) {
		gGameStatus = GS_APP_END;
	}
}

void GsShop(void) {
	int command;
	system("cls");

	ShowShopBilboard(gPlayer.gold);

	printf("いらしゃいませ！！用は何ですか！！\n");
	printf("1. 買う\n");
	printf("2. 売る\n");
	printf("3. 戻る\n");
	printf(">>>");
	scanf_s("%d", &command);

	if (command == 1) {
		gGameStatus = GS_SHOP_BUY;
	}
	else if (command == 2) {
		gGameStatus = GS_SHOP_SELL;
	}
	else if (command == 3) {
		gGameStatus = GS_TOWN;
	}
}

void GsShopBuy(void) {
	int command;
	
	system("cls");
	ShowShopBilboard(gPlayer.gold);
	printf("商品\n");

	for (int i = 0; i < GetNumberOfItemMaster(); i++) {
		printf("%d %s  %d GOLD\n", i + 1, gItemMaster[i].name, gItemMaster[i].price);
	}

	printf("0. もどる\n");

	printf("どれを購入しますか？ >>>");
	scanf_s("%d", &command);
	if (command == 0) {  
		gGameStatus = GS_SHOP;
	}
	else if (command <= GetNumberOfItemMaster()) {  
		gPlayer.gold -= gItemMaster[command - 1].price;  
		gPlayer.inventory[command - 1]++;  
	}
}

void GsShopSell(void) {
	int command;

	system("cls");
	ShowShopBilboard(gPlayer.gold);
	printf("アイテムリスト？\n");


	for (int i = 0; i < GetNumberOfItemMaster(); i++) {

		if (gPlayer.inventory[i] > 0) {

			printf("%d %s   %d GOLD\n", i + 1, gItemMaster[i].name, gItemMaster[i].price / 2);
		}
	}


	printf("0. もどる\n");

	printf("どれを売りますか？>>>");
	scanf_s("%d", &command);

	if (command == 0) { 
		gGameStatus = GS_SHOP;
	}
	else if (command <= GetNumberOfItemMaster()) {  
		if (gPlayer.inventory[command - 1] > 0) {  
			gPlayer.inventory[command - 1]--;  
			gPlayer.gold += gItemMaster[command - 1].price / 2;  
		}
	}
}

void GsDungeon(void) {
	int command;  

	system("cls");
	ShowDungeonBillboard();

	printf("1. 進む\n");
	printf("2. アイテムを使う\n");
	printf("3. 魔法を使う\n");
	printf("0. 町に戻る\n");

	printf(">>>");

	scanf_s("%d", &command);

	if (command == 1) {
		
		int result = Get1of3(50, 45, 5);

		switch (result) {
		case 1:  
			gGameStatus = GS_BATTLE;
			break;
		case 2:  
			gGameStatus = GS_TREASURE;
			break;
		case 3:  
			gGameStatus = GS_STAIRS;
			break;
		}
	}
	else if (command == 2) {
		gGameStatus = GS_ITEM_USE;
	}
	else if (command == 3) {
		gGameStatus = GS_MAGIC_USE;
	}
	else if (command == 0) {
		gGameStatus = GS_TOWN;
	}
}

void GsBattle(void) {
	system("cls");
	ShowMessage(0);

	gGameStatus = GS_DUNGEON;

	
	for (;;) {  
		CHARACTER* pTarget = &gParty[rand() % 2];

		if (pTarget->hp > 0) {  
			pTarget->hp -= rand() % (pTarget->max_hp / 4); 

			if (pTarget->hp < 0) {  
				pTarget->hp = 0;
			}

			break;  
		}
	}

	
	if (gParty[0].hp <= 0) {  
		if (gParty[1].hp <= 0) {  
			gGameStatus = GS_GAMEOVER;  
			return;  
		}
	}


	int exp = rand() % 10 + 2;
	printf("EXPを%d獲得した！\n", exp);

	if (gParty[0].hp > 0) {
		Character_GetExp(&gParty[0], exp);
	}
	if (gParty[0].hp > 1) {
		Character_GetExp(&gParty[1], exp);
	}

	WaitForEnter();
}

void GsTreasure(void) {
	system("cls");
	ShowMessage(1);

	ITEM* getItem;
	int result;

	result = Get1of3(50, 20, 10) - 1;

	getItem = gTreasureItemMaster[gPlayer.floorNo].item[result];

	printf("\n\n\n\n\n");
	printf("【%s】を手に入れた！！\n", getItem->name);

	gPlayer.inventory[getItem->itemNo]++;

	WaitForEnter();
	gGameStatus = GS_DUNGEON;

}

void GsStairs(void) {
	system("cls");
	ShowMessage(2);
	WaitForEnter();
	gGameStatus = GS_DUNGEON;
	gPlayer.floorNo++;
}

void GsGameOver(void) {
	system("cls");
	ShowMessage(3);
	WaitForEnter();
	gGameStatus = GS_TITLE;
}

void PrintNumber(int number) {
	if (number < 10) {
		printf(" ");
	}
	if (number < 100) {
		printf(" ");
	}
	if (number < 1000) {
		printf(" ");
	}

	printf("%d", number);
}

void GsIin(void) {
	system("cls");

	printf("お休みなさい!!\n");
	system("cls");
	printf("HP 回復しました！！\n");
	printf("MP 回復しました！！\n");

	WaitForEnter();
	gGameStatus = GS_TOWN;

}

void GsStatus(void) {
	system("cls");

	printf("\n\n\n\n\n\n");
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("ステータス\n");
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

	printf("[Gold: %d]\n", gPlayer.gold);

	for (int i = 0; i < MAX_PARTY_MEMBER; i++) {
		printf("%s\n", gParty[i].name);
		printf("LV: %d\n", gParty[i].lv);
		printf("HP: %d  /  %d\n", gParty[i].hp, gParty[i].max_hp);

		printf("MP: ");
		PrintNumber(gParty[i].mp);
		printf("  /  ");
		PrintNumber(gParty[i].max_mp);
		printf("\n");
	}
	WaitForEnter();
	gGameStatus = GS_TOWN;

}

void GsItemUse(void) {
	int command;
	system("cls");

	printf("\n\n\n\n\n\n\n");
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("バック\n");
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");

	for (int i = 0; i < GetNumberOfItemMaster(); i++) {
		if (gPlayer.inventory[i] > 0) {
			printf("%d %s x %d \n", i + 1, gItemMaster[i].name, gPlayer.inventory[i]);
		}

	}
	printf("0. 戻る\n");

	printf("どれを使いますか？>>>");
	scanf_s("%d", &command);
	if (command == 0) {  
		gGameStatus = GS_DUNGEON;
	}
	else if (command <= GetNumberOfItemMaster()) {
		if (gPlayer.inventory[command - 1] > 0) {
			if (gItemMaster[command - 1].type == ITYPE_HPRECOVER) {
				gPlayer.inventory[command - 1]--;


				printf("誰に使いますか？ [0.%s 1.%s 2.%s] >>>", gParty[0].name, gParty[1].name,gParty[2].name);
				int charNo;
				scanf_s("%d", &charNo);

				gParty[charNo].hp += gItemMaster[command - 1].value;

				if (gParty[charNo].hp > gParty[charNo].max_hp) {
					gParty[charNo].hp = gParty[charNo].max_hp;
				}
			}
			else if (gItemMaster[command - 1].type == ITYPE_MPRECOVER) {
				gPlayer.inventory[command - 1]--;
			}
		}
	}
}

void GsMagicUse(void) {
	int command;
	MAGIC* pMagicUse; 
	CHARACTER* pCharOwner;  
	CHARACTER* pCharTarget;  

	system("cls");
	printf("\n\n\n\n\n\n\n");
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("スキル\n");
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");

	printf("魔法を使いますか？ [1.%s 2.%s 3.%s 0.戻る] >>>", gParty[0].name, gParty[1].name,gParty[2].name);
	scanf_s("%d", &command);

	if (command == 0) {
		gGameStatus = GS_DUNGEON;
		return;
	}
	else if (command > 2) { 
		return;
	}
	
	

	pCharOwner = &gParty[command - 1];
	for (int i = 0; i < MAX_MAGIC_LIST; i++) {
		
		if (pCharOwner->magicIDList[i] != 0) {  
			MAGIC* pMagic = GetMagic(pCharOwner->magicIDList[i]);
			
			printf("%d. ", i + 1);
			PrintAlignedStr(pMagic->name, 12);
			printf("MP %d\n", pMagic->mp);
		}
	}

	printf("0. 戻る\n");

	printf("どれを使いますか？ >>>");
	scanf_s("%d", &command);

	pMagicUse = GetMagic(pCharOwner->magicIDList[command - 1]);

	if (command == 0) {  
		return;
	}
	else if (command <= MAX_MAGIC_LIST) {
		if (pMagicUse->type == MTYPE_RECOVER) {  
			printf("誰に使いますか？ [1.%s 2.%s 3.%s] >>>", gParty[0].name, gParty[1].name, gParty[2].name);
			scanf_s("%d", &command);

			pCharTarget = &gParty[command - 1];  

			if (pCharOwner->mp >= pMagicUse->mp) {  
				Magic_Use(pMagicUse, pCharOwner, pCharTarget);
			}
			else {
				printf("MPが足りない！\n");
				WaitForEnter();
			}
		}
		else {
			printf("その魔法はここでは使えない！\n");
			WaitForEnter();

		}
	}

	
	

}



void GsLoading(void)
{
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\n");  
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("『』Now Loading ...『』 \n");
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

	if (time(NULL) > gStartTime + 1) { 
		gGameStatus = GS_DUNGEON;
		
		save();
	}
}


void ShowMessage(int msgNo) {
	printf("\n\n\n\n\n\n\n\n\n\n");  
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf(gMsgMaster[msgNo]);
	printf("\n");
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
}


void PrintAlignedStr(const char * str, int maxlen){
	printf(str);

	for (int i = 0; i < maxlen - (int)strlen(str); i++) {
		putc(' ', stdout);
	}
}

void ShowTownBilboard(void) {
	printf("\n\n\n\n\n\n\n\n\n\n");  
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("Dragon町です \n");
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
}


void ShowShopBilboard(int myGold) {

		printf("\n\n\n\n\n\n\n\n\n\n");   
		printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
		printf("EARTH店です    所持金：%d GOLD\n", myGold);
		printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
}


void ShowDungeonBillboard(void) {
	printf("\n\n\n\n\n\n\n\n\n\n");  
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("ダンジョン    %d 階\n", gPlayer.floorNo);
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

	printf("\n\n");

	printf("ステータス\n");

	Character_PrintStatus(&gParty[0]);
	printf("\n\n");
	Character_PrintStatus(&gParty[1]);
	printf("\n\n");
	Character_PrintStatus(&gParty[2]);
	printf("\n\n");
}


void WaitForEnter(void) {
	printf("『PRESS ENTER KEY...』");
	rewind(stdin);
	getchar();
}




int Get1of3(int per1, int per2, int per3) {
	return Get1of4(per1, per2, per3, 0);
}



int Get1of4(int per1, int per2, int per3, int per4) {
	int number = rand() % (per1 + per2 + per3 + per4);  

	if (number < per1) {  
		return 1;
	}
	else if (number < per1 + per2) {  
		return 2;
	}
	else if (number < per1 + per2 + per3) {  
		return 3;
	}
	else {  
		return 4;
	}
}

void save(void)
{
	FILE* fp;
	errno_t isOpen = fopen_s(&fp, "save.dat", "wb");  

	if (isOpen == 0) {  

		
		fwrite(&gGameStatus, sizeof(gGameStatus), 1, fp);

		
		fwrite(&gPlayer, sizeof(gPlayer), 1, fp);

		
		fwrite(&gParty[0], sizeof(CHARACTER), 2, fp);

		fclose(fp);

		printf("オートセーブ完了！");
	}
	else {
		printf("オートセーブ失敗！");
	}
}

void load(void)
{
	FILE* fp;
	errno_t isOpen = fopen_s(&fp, "save.dat", "rb");  

	if (isOpen == 0) {  

		
		fread(&gGameStatus, sizeof(gGameStatus), 1, fp);

		
		fread(&gPlayer, sizeof(gPlayer), 1, fp);

		
		fread(&gParty[0], sizeof(CHARACTER), 2, fp);

		fclose(fp);

		printf("オートロード完了！");
	}
	else {
		printf("オートロード失敗！");
	}
}




