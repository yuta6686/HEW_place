//----------------------------------------
//		AT11B_36_柳澤優太
//	敵の処理
#include<stdio.h>
#include<stdio.h>
#define CONIOEX 
#include"conioex.h"
#include"common.h"
#include"main.h"
#include"character.h"
#include"dot.h"
#include"enemy.h"
#include"background.h"
//-----------------------------------------------------------------------グローバル変数
//-------------------------構造体
Character enemy[ENEMY_MAX];

extern dotChar int_enemy[];
extern dotString print_enemy[];
extern dotString del_enemy[];
//-------------------------構造体
//-------------------------bool型
bool distance = false;
bool goal = false;
bool a = false;
extern bool chousei;
extern bool hp = false;
extern bool clear_once;
//-------------------------bool型
//-------------------------int型
static int currentEnemy = 0;
static int wallmax = 10;

static int currentIndex = 0;//現在データを指している場所
static int intervalCounter = 0;//出撃インターバル
static int wall_intervalCounter = 0;
static int enemyDestroyCount = 0;//撃破数
int lastTime;
int currentTime;
int goal_intervalCounter = 0;
//-------------------------int型
//---------------------------アイテム用
rangeData rupidata[] =
{
	{0,0},		//中心
	{1,0},		//右
	{-1,0},		//左
	{0,1},		//下
	{0,-1},		//上
	{1,1},		//右下
	{-1,1},		//左下
	{1,-1},		//右上
	{-1,-1},	//左上
	{0,-2},
	{0,2},
};
int rupivalue = sizeof(rupidata) / sizeof(rupidata[0]);
//---------------------------アイテム用
//-----------------------------エネミー表示用
rangeData enemydata[] = {
	{0,0},
//	{1,0},
//	{0,1},
//	{1,1},
//	{-1,0},
//	{0,-1},
	{-1,-1},
	{1,-1},
//	{-1,1},
};
int enemydatavalue = sizeof(enemydata) / sizeof(enemydata[0]);
rangeData enemySidedata[] =
{
	{0,0},
	{-1,-1},
	{-1,1}
};
int enemysidedatavalue = sizeof(enemySidedata) / sizeof(enemySidedata[0]);
//--------------------------------------------------エネミー表示用
//ーーーーーーーーーーーーーーーーーーーーーーーーー出現データ
struct AppearData {
	int interval;//出現までのインターバル （フレーム）
	float x;
	float y;
	float speedx;
	float speedy;
	int color;
	int kind;
};
AppearData appearData[] =
//	インターバル,x座標,y座標,xスピード,yスピード,色
//	エネミーの表示範囲は縦横5倍
{//1ステージ
	{30,80.0f,40.0f,2.0f,-0.2f,YELLOW,STATUS_ENEMY},						//0
	{60,45.0f,40.0f,0.3f,-0.15f,RED,STATUS_ENEMY},							//1
	{60,120.0f,40.0f,-0.25f,-0.5f,BLUE,STATUS_ENEMY},			//2
	{60,LIMIT_LEFT+1,LIMIT_DOWN-2.0f,0.0f,0.0f,LIGHTGRAY,STATUS_GOAL},		//3
	{30,40.0f,40.0f,0.0f,-0.1f,MAGENTA,STATUS_WALL},						//4
	{30,LIMIT_LEFT+20.0f,40.0f,0.0f,-0.1f,CYAN,STATUS_ENEMY},				//5
	{60,LIMIT_RIGHT-7.0f,20.0f,-0.5f,0.0f,RED,STATUS_ENEMY_SIDE},				//6

	
	//２ステージ
	{60,LIMIT_RIGHT - 7.0f,20.0f,-0.5f,0.0f,RED,STATUS_ENEMY_SIDE},		//7
	{60,100.0f,100.0f,0.0f,1.5f,BLUE,STATUS_ENEMY},		//8
	{60,100.0f,100.0f,0.0f,1.5f,GREEN,STATUS_ENEMY},		//9
	{60,100.0f,100.0f,0.0f,1.5f,MAGENTA,STATUS_ENEMY},	//10
	{60,100.0f,100.0f,0.0f,1.5f,CYAN,STATUS_ENEMY},		//11
	//３すてーじ
	{60,100.0f,100.0f,0.0f,1.5f,YELLOW,STATUS_ENEMY},	//12
	{60,100.0f,100.0f,0.0f,1.5f,RED,STATUS_ENEMY},		//13
	{60,100.0f,100.0f,0.0f,1.5f,BLUE,STATUS_ENEMY},		//14
	{60,100.0f,100.0f,0.0f,1.5f,GREEN,STATUS_ENEMY},		//15
	{60,100.0f,100.0f,0.0f,1.5f,MAGENTA,STATUS_ENEMY},	//16
	{60,100.0f,100.0f,0.0f,1.5f,CYAN,STATUS_ENEMY},		//17
	{60,100.0f,100.0f,0.0f,1.5f,YELLOW,STATUS_ENEMY},	//18
	{60,100.0f,100.0f,0.0f,1.5f,YELLOW,STATUS_ENEMY},	//19
	{60,100.0f,100.0f,0.0f,1.5f,YELLOW,STATUS_ENEMY},	//20
	{60,100.0f,100.0f,0.0f,1.5f,YELLOW,STATUS_ENEMY},	//21
	{60,100.0f,100.0f,0.0f,1.5f,YELLOW,STATUS_ENEMY},	//22
	{60,100.0f,100.0f,0.0f,1.5f,YELLOW,STATUS_ENEMY},	//23
	{60,100.0f,100.0f,0.0f,1.5f,YELLOW,STATUS_ENEMY},	//24
	{60,100.0f,100.0f,0.0f,1.5f,YELLOW,STATUS_ENEMY},	//25
	{60,100.0f,100.0f,0.0f,1.5f,YELLOW,STATUS_ENEMY},	//26
	{60,100.0f,100.0f,0.0f,1.5f,YELLOW,STATUS_ENEMY},	//27
	{60,100.0f,100.0f,0.0f,1.5f,YELLOW,STATUS_ENEMY},	//28
	{60,100.0f,100.0f,0.0f,1.5f,YELLOW,STATUS_ENEMY}		//29
};
static int maxAppearData = sizeof(appearData) / sizeof(AppearData);
//ーーーーーーーーーーーーーーーーーーーーーーーーー出現データ
//ーーーーーーーーーーステージのエネミー情報
struct Stage {
	//char music[256];
	//int bgcolor;
	int biginNo;
	int endNo;
};
//		↓
static Stage stage[] =
{
	{0,5},
	{6,11},
	{12,30}
};
//ーーーーーーーーーーステージのエネミー情報
//-----------------------------------------------------------------------グローバル変数

//ーーーーーーーーーーーーーーーーーー以下関数
void EnemyInit()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{//-----------------------------------------------全エネミー共通初期化
		enemy[i].status = Dead;
		enemy[i].lastPos.x = enemy[i].realPos.x = 100.0f;
		enemy[i].lastPos.y = enemy[i].realPos.y = 50.0f;
		enemy[i].speedx = 0.0f;
		enemy[i].speedy = 0.0f;
		enemy[i].angle = 0.0f;
	//-----------------------------------------------全エネミー共通初期化
	//-----------------------------------------------エネミー別初期化
		switch (enemy[i].kind)
		{
		case STATUS_ENEMY:
		case STATUS_ENEMY_SIDE:
			enemy[i].width = 12.0f;
			enemy[i].height = 4.0f;
			break;
		case STATUS_WALL:
			enemy[i].width = 15.0f;
			enemy[i].height = 2.0f;
			break;
		case STATUS_GOAL:
			enemy[i].width= 0.0f;
			enemy[i].height = 0.0f;
			break;
		}
		enemy[i].hit = false;
	}
	//-----------------------------------------------エネミー別初期化

	//------------------------------------ループ外初期化処理
	intervalCounter = 0;
	currentIndex = 0;
	currentEnemy = 0;

	goal = false;

	timeBeginPeriod(1);			//	1/1000秒測れる
	lastTime = timeGetTime();	//測ったやつをlastTimeに入れる
	currentTime = 0;
	//------------------------------------ループ外初期化処理
}

void EnemyUpdate()
{
	//敵を倒すという概念がないため使わないのでコメントにするね
	//いつかブレスを吐く設定入れるよ
	/*if (enemyDestroyCount >= 3)
	{
		stageNo++;
		if (stageNo >= FINAL_STAGE) {
			stageNo = 0;
		}
		currentIndex = stage[stageNo].biginNo;
		enemyDestroyCount = 0;
	}*/

	
	if (intervalCounter == appearData[currentIndex].interval)
		// intervalCounter->>>毎フレーム加算されていく
		// appearData	  ->>>出現データ
		// currentIndex   ->>>これも毎フレーム加算されていくが
		//						こっちは0に戻ると思う
	{
		//出現するための処理
		//----------------エネミーの出現データをenemyデータに入れて使用できるようにしている
		enemy[currentEnemy].status = Live;

		enemy[currentEnemy].lastPos.x =
			enemy[currentEnemy].realPos.x =
			appearData[currentIndex].x;

		enemy[currentEnemy].lastPos.y =
			enemy[currentEnemy].realPos.y =
			appearData[currentIndex].y;

		enemy[currentEnemy].speedx = appearData[currentIndex].speedx;
		enemy[currentEnemy].speedy = appearData[currentIndex].speedy;
		enemy[currentEnemy].color = appearData[currentIndex].color;
		enemy[currentEnemy].hit = false;
		enemy[currentEnemy].kind = appearData[currentIndex].kind;

		//--------------------------------------------エネミーの種別管理
		switch (enemy[currentEnemy].kind)
		{
		case STATUS_ENEMY:
		case STATUS_ENEMY_SIDE:
			enemy[currentEnemy].updated = true;
			enemy[currentEnemy].width = 12.0f;
			enemy[currentEnemy].height = 4.0f;
			break;
		case STATUS_WALL:
			enemy[currentEnemy].updated = true;
			enemy[currentEnemy].width = 15.0f;
			enemy[currentEnemy].height = 2.0f;
			break;
		case STATUS_GOAL:
			if (goal_intervalCounter == 6)
			{
				enemy[currentEnemy].updated = true;
				goal_intervalCounter = 0;
				enemy[currentEnemy].width = 115.0f;
				enemy[currentEnemy].height = 2.0f;
				goal = true;
				//enemy[currentEnemy].updated = false;
			}
			else {
				goal_intervalCounter++;
				distance = true;
			}
			break;
		}
		//--------------------------------------------エネミーの種別管理
		//----------------エネミーの出現データをenemyデータに入れて使用できるようにしている

	//--------------appeardataのデータをendNoとbiginNoを使ってステージごとにまわしていく
		currentIndex++;

		if (currentIndex > stage[stageNo].endNo)
		{
			currentIndex = stage[stageNo].biginNo;
		}
		intervalCounter = 0;
		currentEnemy++;

		if (currentEnemy >= ENEMY_MAX) {
			currentEnemy = 0;
		}
	}
	else
	{
		intervalCounter++;
	}
	//--------------appeardataのデータをendNoとbiginNoを使ってステージごとにまわしていく

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		//ーーーーーーーーーーーーーーーーー死んでたら抜ける
		if (enemy[i].status == Dead)continue;
		//ーーーーーーーーーーーーーーーーー死んでたら抜ける
		//ーーーーーーーーーーーーーーーーー現在の位置変更処理
		enemy[i].realPos.x = enemy[i].lastPos.x + enemy[i].speedx;
		enemy[i].realPos.y = enemy[i].lastPos.y + enemy[i].speedy;
		enemy[i].updated = true;
		//ーーーーーーーーーーーーーーーーー現在の位置変更処理
		//-----------------------------------エネミーの範囲設定
		if (enemy[i].realPos.y <= LIMIT_UP)
		{
			enemy[i].status = Dead;
			EnemyErase(i);
		}
		if (enemy[i].kind == STATUS_ENEMY_SIDE)
		{
			if (enemy[i].realPos.x <= LIMIT_LEFT+3.0f)
			{
				enemy[i].status = Dead;
				EnemyErase(i);
			}
		}
		else {
			if (enemy[i].realPos.x <= LIMIT_LEFT)
			{
				enemy[i].status = Dead;
				EnemyErase(i);
			}
		}
		if (enemy[i].realPos.x >= LIMIT_RIGHT-7)
		{
			enemy[i].status = Dead;
			EnemyErase(i);
		}
		if (enemy[i].realPos.y >= LIMIT_DOWN+7)
		{
			enemy[i].status = Dead;
			EnemyErase(i);
		}
		//-----------------------------------エネミーの範囲設定
	}
	//----------------------------------エネミーの移動実験所
	if (a == false)
	{
		enemy[0].angle += (1.0f / 30.0f);
		if (enemy[0].angle > 1.0f)
		{
			a = true;
		}
		enemy[0].realPos.x = enemy[0].lastPos.x + enemy[0].speedx;
	}
	else
	{
		enemy[0].angle += ((1.0f / 30.0f) * (-1.0f));
		if (enemy[0].angle < -1.0f)
		{
			a = false;
		}
		enemy[0].speedx = enemy[0].speedx * (-1.0f);
	}
	//----------------------------------エネミーの移動実験所

	//----------------------------------背景処理をここでやっている
	if (distance == true)
	{
		bgdistance();
		distance = false;
	}
	//----------------------------------背景処理をここでやっている
}
//--------------------------------------------エネミー描画処理
void EnemyDraw()
{
	
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemy[i].status == Dead)continue;
		if (!enemy[i].updated)continue;

		EnemyErase(i);
		EnemyProt(i);

		enemy[i].lastAngle = enemy[i].angle;
		enemy[i].lastPos = enemy[i].realPos;
		enemy[i].updated = false;
	}
}
//--------------------------------------------エネミー描画処理
//--------------------------------------------エネミー表示関数
void EnemyProt(int n)
{
	floatPosition f;
	intPosition i;

	f.x = enemy[n].realPos.x;
	f.y = enemy[n].realPos.y;
	floatToInt(f, &i);

	textcolor(enemy[n].color);

	if (enemy[n].kind == STATUS_GOAL && goal == true)
	{
		gotoxy(i.x, i.y);
		for (int index = 0; index < (LIMIT_RIGHT - LIMIT_LEFT) / 2; index++)
		{
			printf("ー");
		}
		//enemy[n].updated = false;
		goal = false;
	}
	else if (enemy[n].kind == STATUS_WALL)
	{

		gotoxy(i.x, i.y);
		BGGREEN;
		for (int index = 0; index < 2; index++)
		{
			for (int j = 0; j < 15; j++)
			{
				printf("*");
			}
			gotoxy(i.x, wherey() + 1);
		}
		BGRESET;
	}
	else if (enemy[n].kind == STATUS_ENEMY) {
		for (int index = 0; index < enemydatavalue; index++)
		{
			for (int j = 1; j < 6; j++)
			{
				gotoxy(i.x + ((enemydata[index].x) * j), i.y + ((enemydata[index].y) * j * Y_HOSEI_RATIO));
				printf("■");
			}
		}
	}
	else if (enemy[n].kind == STATUS_ENEMY_SIDE)
	{
		for (int index = 0; index < enemysidedatavalue; index++)
		{
			for (int j = 1; j < 6; j++)
			{
				gotoxy(i.x + ((enemySidedata[index].x) * j), i.y + (enemySidedata[index].y * j * Y_HOSEI_RATIO));
				printf("■");
			}
		}
	}
	else return;
}
//--------------------------------------------エネミー表示関数
//--------------------------------------------エネミー消去関数
void EnemyErase(int n)
{
	floatPosition f;
	intPosition i;
	f.x = enemy[n].lastPos.x;
	f.y = enemy[n].lastPos.y;
	floatToInt(f, &i);
	if (enemy[n].kind == STATUS_GOAL && goal == true)
	{
		gotoxy(i.x, i.y);
		for (int index = 0; index < (LIMIT_RIGHT - LIMIT_LEFT) / 2; index++)
		{
			printf(" ");
		}
	}
	else if (enemy[n].kind == STATUS_WALL) {
		gotoxy(i.x, i.y);
		for (int index = 0; index < 2; index++)
		{
			for (int j = 0; j < 15; j++)
			{
				printf(" ");
			}
			gotoxy(i.x, wherey() + 1);
		}
	}
	else if (enemy[n].kind == STATUS_ENEMY) {
		for (int index = 0; index < enemydatavalue; index++)
		{
			for (int j = 1; j < 6; j++)
			{
				gotoxy(i.x + ((enemydata[index].x) * j), i.y + ((enemydata[index].y) * j * Y_HOSEI_RATIO));
				printf("　");
			}
		}
	}
	else if (enemy[n].kind == STATUS_ENEMY_SIDE)
	{
		for (int index = 0; index < enemysidedatavalue; index++)
		{
			for (int j = 1; j < 6; j++)
			{
				gotoxy(i.x + ((enemySidedata[index].x) * j), i.y + (enemySidedata[index].y * j * Y_HOSEI_RATIO));
				printf("　");
			}
		}
	}
	else return;
	//printf(del_enemy[SAKANA].dotC);
	//dotDraw(SAKANA,DELL_DISPLAY, 0, 34, 30, 0);
}
//--------------------------------------------エネミー消去関数

bool EnemyHitCheck(floatPosition pos)
{
	bool anyoneHit = false;//誰かと衝突した
	float plusx;	//右
	float plusy;	//下
	float minusx;	//左
	float minusy;	//上
	floatPosition fp;
	fp.x = pos.x;
	fp.y = pos.y*Y_HOSEI_RATIO;
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		plusx = enemy[i].width/2;
		plusy = enemy[i].height / 2;
		minusx = (-1) * plusx;
		minusy = (-1) * plusy;
		//enemy[i].realPos.y += 4.0f;

		if (enemy[i].status == Dead)continue;

		if (enemy[i].kind == STATUS_GOAL || enemy[i].kind==STATUS_WALL)
		{
			if ((enemy[i].realPos.x <=fp.x) &&
				(fp.x <= enemy[i].realPos.x + enemy[i].width) &&
				(enemy[i].realPos.y <= fp.y) &&
				(fp.y <= enemy[i].realPos.y + enemy[i].height))
			{
				anyoneHit = true;
				enemy[i].hit = true;
				if (enemy[i].kind == STATUS_GOAL)
				{
					Scene = GAME_CLEAR;
					clear_once = false;
					anyoneHit = false;
					clrscr();
					stopsound(music[TOKYO]);
					playsound(music[TASSEI], MUSIC_NON_LOOP);
					playsound(music[SHOURI], MUSIC_NON_LOOP);
					return anyoneHit;
				}
				else return anyoneHit;

				return anyoneHit;
			}
		}
		else {
			if ((enemy[i].realPos.x + minusx <= fp.x) &&
				(fp.x <= enemy[i].realPos.x + plusx) &&
				(enemy[i].realPos.y + minusy <= fp.y) &&
				(fp.y <= enemy[i].realPos.y + plusy)) {
				anyoneHit = true;
				//enemy[i].hit = true;
			}
		}
	}
	return anyoneHit;
}