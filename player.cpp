//-----------------------------------------
//プレイヤーの処理
//	AT11B_36_柳澤優太

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define CONIOEX 
#include"conioex.h"
#include"common.h"
#include"character.h"
#include"player.h"
#include"key.h"
#include"main.h"
#include"title.h"
#include"dot.h"
#include"enemy.h"
#include"eff.h"
#include"background.h"

#define INITIAL_X 70.0f//初期座標
#define INITIAL_Y 15.0f
#define MOVE_UNIT 0.75f
#define INITIAL_ANGLE (float)(PI*2*3/4)
#define ANGLE_UNIT 0.05f
#define INITIAL_LENGTH 8.0f
#define EXTEND_MAX 20
#define EXTEND_HALF 10
#define ONETHIRD 13.3f
#define TWOTHIRD 26.6f

Character player;
extern Character enemy[ENEMY_MAX];
extern Character dot;
static float length = INITIAL_LENGTH;
static int reviveCount = 0;
extern bool bghantei;
extern bool chousei;
extern bool clear_once;
extern bool over_once;

floatPosition buff[EXTEND_MAX+1];
floatPosition savePosf[EXTEND_MAX];

int value = 1;

int eff = 0;
bool player_onece = false;
bool effbool = false;
static bool hp = false;
static int frame = 0;

enum direction {
	STAY,
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT
};
direction muki;

enum Range {
	BFIRST,
	BSECOND,
	BTHIRD
};
Range range;


static rangeData playerData[]
{
	{0,0},	//中心
	{-1,0},	//左
	{1,0},	//右
	{0,-1},	//上
//	{0,1},	//下
//	{1,1},	//右下
//	{1,-1},	//右上
//	{-1,1},	//左下
//	{-1,-1}	//左上
};
static int playerdatavalue = sizeof(playerData) / sizeof(rangeData);
static rangeData playerExtendData[]
{
/*-----x軸---------*
*	 ---*+++	   *
*	  *101*        *
*	 *21012*       *
*	  *101*        *
*	    *          *
*-----x軸----------*
*-----y軸----------*
*		*	-2     *
*	  *111*	-1     *
*	 *00000*0      *
*	  *111* +1     *
*		*   +2     *
*-----y軸----------*/					 		
//	{3,0},//いらない
	{2,-1},	//上
	{0,-2},	//上
	{-2,-1},//上
//	{-3,0},	//いらない
	{-2,1},	//下
	{0,2},	//下
	{2,1}	//下
};
static int playerExtendDataValue = sizeof(playerExtendData) / sizeof(rangeData);

void PlayerInit()
{
	srand((unsigned int)time(NULL));
	player.kind = Live;
	player.lastPos.x = player.realPos.x = INITIAL_X;
	player.lastPos.x = player.realPos.y = INITIAL_Y;
	player.lastAngle = player.angle = INITIAL_ANGLE;
	player.updated = true;

	player.width = 3;
	player.height = 3;

	player.HP = 3;
	setcursortype(NOCURSOR);

	muki = STAY;
	range = BFIRST;

	player_onece = true;

	for (int i = 0; i < EXTEND_MAX; i++)
	{
		savePosf[i].x = INITIAL_X;
		savePosf[i].y = INITIAL_Y;
	}
}

void PlayerUpdate()
{
	if (player_onece == true)
	{
		char cell[2] = " ";
		//void bgSquare(int x, int y, int width, int height, char cell[2], int color, int bold)
		bgSquare(LIMIT_LEFT, LIMIT_UP, LIMIT_RIGHT - LIMIT_LEFT, ONETHIRD, cell, BLACK, 1);
		bgStatusUpdata(player);
		player_onece = false;
	}

	//qが押されたら強制終了
	if (keyPush(PK_Q))
	{
		Scene=TITLE;
		clrscr();
		dot.updated = true;
	}

	//player.realPos.y += (MOVE_UNIT / 2);
	//player.updated = true;
	if (player.realPos.y >= LIMIT_DOWN / Y_HOSEI_RATIO)
	{
		player.realPos.y = LIMIT_DOWN / Y_HOSEI_RATIO;
	}

	if (keyPress(PK_W))
	{
		float range_onethird = ONETHIRD;
		float range_twothird = TWOTHIRD;
		//player.realPos.y -= MOVE_UNIT-(MOVE_UNIT/2);
		if (player.realPos.y >= LIMIT_UP &&
			player.realPos.y*Y_HOSEI_RATIO < range_onethird)
		{
			player.realPos.y -= (MOVE_UNIT/4);
			range = BFIRST;
		}
		if (player.realPos.y * Y_HOSEI_RATIO >= range_onethird &&
			player.realPos.y * Y_HOSEI_RATIO < range_twothird)
		{
			player.realPos.y -= MOVE_UNIT;
			range = BSECOND;
		}
		if (player.realPos.y * Y_HOSEI_RATIO >= range_twothird &&
			player.realPos.y * Y_HOSEI_RATIO <= LIMIT_DOWN)
		{
			player.realPos.y -= (MOVE_UNIT*4);
			range = BTHIRD;
		}


		if (player.realPos.y <= LIMIT_UP)
		{
			player.realPos.y = LIMIT_UP;
		}
		player.updated = true;
		muki = DIRECTION_UP;
	}

	if (keyPress(PK_S))
	{
		float range_onethird = ONETHIRD;
		float range_twothird = TWOTHIRD;
		//player.realPos.y -= MOVE_UNIT-(MOVE_UNIT/2);
		if (player.realPos.y >= LIMIT_UP &&
			player.realPos.y * Y_HOSEI_RATIO < range_onethird)
		{
			player.realPos.y += (MOVE_UNIT * 4);
			range = BFIRST;
		}
		if (player.realPos.y * Y_HOSEI_RATIO >= range_onethird &&
			player.realPos.y * Y_HOSEI_RATIO < range_twothird)
		{
			player.realPos.y += MOVE_UNIT;
			range = BSECOND;
		}
		if (player.realPos.y * Y_HOSEI_RATIO >= range_twothird &&
			player.realPos.y * Y_HOSEI_RATIO <= LIMIT_DOWN)
		{
			player.realPos.y += (MOVE_UNIT / 4);
			range = BTHIRD;
		}

		if (player.realPos.y >= LIMIT_DOWN/Y_HOSEI_RATIO)
		{
			player.realPos.y = LIMIT_DOWN/Y_HOSEI_RATIO;
		}
		player.updated = true;
		muki = DIRECTION_DOWN;
	}

	if (keyPress(PK_A))
	{
		player.realPos.x -= MOVE_UNIT;

		
		if (player.realPos.x <= LIMIT_LEFT)
		{
			player.realPos.x = LIMIT_LEFT;
		}
		player.updated = true;
		muki = DIRECTION_LEFT;
	}

	if (keyPress(PK_D))
	{
		player.realPos.x += MOVE_UNIT;

		if (player.realPos.x >= LIMIT_RIGHT)
		{
			player.realPos.x = LIMIT_RIGHT;
	
		}
		player.updated = true;
		muki = DIRECTION_RIGHT;
	}
	if (keyRelease(PK_W) || keyRelease(PK_S) || keyRelease(PK_D) || keyRelease(PK_A))
	{
		muki = STAY;
	}

	

	if (EnemyHitCheck(player.realPos))
	{
		if (frame >= 16)
		{
			frame = 0;
		}
		else if(frame==1){
			player.HP--;
			hp = true;
			player_onece=true;
			playsound(music[WATER], MUSIC_NON_LOOP);
			messMake();
			frame++;
		}
		else {
			frame++;
		}
	}

	if (hp && player.HP > 0) {
		//エフェクト表示関数
		if (eff >= 16)
		{
			
			eff = 0;
			hp = false;
			bghantei = false;
			chousei = false;
			player_onece = true;
			//Scene = GAME_OVER;
			//return;
		}
		else {

			effAnimation(player, eff);
			eff++;
		}
	}

	if (EnemyHitCheck(player.realPos) || (eff > 0) && (eff <= 16))
	{
		if (player.HP <= 0)
		{
			floatPosition f;
			intPosition i;
			f.x = player.realPos.x;
			f.y = player.realPos.y;
			floatToInt(f, &i);
			gotoxy(i.x, i.y);
			

			//エフェクト表示関数
			if (eff >= 16)
			{
				eff = 0;
				playsound(music[MGAMEOVER], MUSIC_NON_LOOP);
				Scene = GAME_OVER;
				over_once = false;
				clrscr();
				stopsound(music[TOKYO]);
				return;
			}
			else if(eff==1){
				playsound(music[WATER], MUSIC_NON_LOOP);
				effAnimation(player, eff);
				eff++;
			}
			else {
				/*if (eff % 4 == 0)
				{
					effAnimation(player, eff / 4);
				}*/
				effAnimation(player, eff);
				eff++;
			}
		}
	}

	if (keyPress(PK_R) || (eff > 0) && (eff <= 16))
	{
		if (eff >= 16)
		{
			eff = 0;
			return;
		}
		else {
			/*if (eff % 4 == 0)
			{
				effAnimation(player, eff / 4);
			}*/
			effAnimation(player, eff);
			eff++;
		}
	}
	if (keyPress(PK_O))
	{
		Scene = GAME_OVER;
		over_once = false;
		clrscr();
		stopsound(music[TOKYO]);
		playsound(music[MGAMEOVER], MUSIC_NON_LOOP);
		return;
	}

	if (keyPress(PK_C))
	{
		Scene = GAME_CLEAR;
		clear_once = false;
		clrscr();
		stopsound(music[TOKYO]);
		//playsound(music[]);
		return;
	}
}

void PlayerDraw()
{
	if (!player.updated)return;
	

	//前回消去

	floatPosition f;
	intPosition i;

	floatPosition fe;
	intPosition ie;

	floatPosition fex;
	intPosition iex;

	f.x = savePosf[EXTEND_MAX-1].x;
	f.y = savePosf[EXTEND_MAX-1].y *Y_HOSEI_RATIO;

	fe.x = savePosf[EXTEND_HALF].x;
	fe.y = savePosf[EXTEND_HALF].y*Y_HOSEI_RATIO;

	fex.x = savePosf[0].x;
	fex.y = savePosf[0].y * Y_HOSEI_RATIO;

	floatToInt(f, &i);
	floatToInt(fe, &ie);
	floatToInt(fex, &iex);
	
	for (int index = 0; index < playerdatavalue; index++)
	{
		//----------------------------リアルポジション描画
		gotoxy(i.x + (playerData[index].x), i.y + (playerData[index].y));
		printf(" ");
		//----------------------------リアルポジション描画
		//----------------------------拡張ポジション描画
		gotoxy(ie.x + (playerData[index].x), ie.y + (playerData[index].y));
		switch (muki)
		{
		case STAY:
			BGBLUE;
			break;
		case DIRECTION_UP:
			switch (range)
			{
			case BFIRST:
				BGRED;
				break;
			case BSECOND:
				BGYELLOW;
				break;
			case BTHIRD:
				BGGREEN;
				break;
			default:
				break;
			}
			break;
		case DIRECTION_DOWN:
			switch (range)
			{
			case BFIRST:
				BGRED;
				break;
			case BSECOND:
				BGYELLOW;
				break;
			case BTHIRD:
				BGGREEN;
				break;
			default:
				break;
			}
			break;
		case DIRECTION_LEFT:
			BGBLUE;
			break;
		case DIRECTION_RIGHT:
			BGBLUE;
			break;
		default:
			break;
			//----------------------------拡張ポジション描画
		}
		
		printf(" ");
		BGRESET;
	}
	for (int index = 0; index < playerExtendDataValue; index++)
	{
		for (int j = 1; j < 4; j++)
		{
			if (range == BFIRST || range == BTHIRD || range == BSECOND) {
				gotoxy(iex.x + (playerExtendData[index].x), iex.y + (playerExtendData[index].y)*j);
				//textattr(0xBB);
				printf(" ");
			}
		}
	}
		

	//現在表示
	floatPosition fl;
	intPosition in;

	fl.x = player.realPos.x;
	fl.y = player.realPos.y*Y_HOSEI_RATIO;
	floatToInt(fl, &in);

	CCYAN;
	
	for (int index = 0; index < playerdatavalue; index++)
	{
		if (EnemyHitCheck(player.realPos))
		{
			switch (index)
			{
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:

				CMAGENTA;
				gotoxy(in.x + (playerData[index].x), in.y + (playerData[index].y));
				printf(" ");
				CCYAN;
				break;
			default:
				gotoxy(in.x + (playerData[index].x), in.y + (playerData[index].y));
				printf(" ");
				break;
			}
		}
		else {
			switch (index)
			{
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
				switch (muki)
				{
				case STAY:
					BGBLUE;
					break;
				case DIRECTION_UP:
					BGRED;
					break;
				case DIRECTION_DOWN:
					BGCYAN;
					break;
				case DIRECTION_LEFT:
					BGBLUE;
					break;
				case DIRECTION_RIGHT:
					BGBLUE;
					break;
				default:
					break;
				}
				gotoxy(in.x + (playerData[index].x), in.y + (playerData[index].y));
				printf("@");
				BGRESET;
				CCYAN;
				break;
			default:
				gotoxy(in.x + (playerData[index].x), in.y + (playerData[index].y));
				BGRED;
				printf("@");
				BGRESET;
				break;
			}
		}
	}

	if (range == BFIRST) {
		for (int index = 3; index < playerExtendDataValue; index++)
		{
			for (int j = 1; j < 4; j++)
			{
				gotoxy(in.x + (playerExtendData[index].x), in.y + (playerExtendData[index].y)*j);
				textattr(0xBB);
				printf("@");
			}
		}
	}
		
	if (range == BTHIRD) {
		for (int index = 0; index < 3; index++)
		{
			for (int j = 1; j < 4; j++)
			{
				gotoxy(in.x + (playerExtendData[index].x), in.y + (playerExtendData[index].y)*j);
				BGRED;
				printf("@");
			}
		}
	}
	

	BGRESET;
//	player.lastAngle = player.angle;
	savePosf[0] = player.realPos;

	for (int i = 0; i < EXTEND_MAX; i++)
	{
		buff[i+1] = savePosf[i];
	}
	for (int i = 0; i < EXTEND_MAX-1; i++)
	{
		savePosf[i+1] = buff[i+1];
	}

	player.updated = false;
	
}

void messMake()
{
	int ransuu1;
	int ransuu2;
	char mess1[][32] =
	{
		{"エネミーに衝突したかもね"},
		{"もっと○んでいってね"},
		{"迷えば敗れる"},
		{"左下行ってみてね"},
		{"バグ修正難しい"},
		{"3回衝突したら負けですよ"},
		{"1度死んだら爆発して開始されます"}
	};
	int mess1value = sizeof(mess1) / sizeof(mess1[0]);
	char mess2[][32] =
	{
		{"今日はいい天気ですね"},
		{"ビーム撃ちたい"},
		{"ゲームって作るの大変なんですね"},
		{"スプラトゥーン３おめでと！"},
		{"敵に衝突すると...？"},
		{"回避モーション付けたかった"},
		{"上下移動でスピードが違いますね"},
		{"時間あれば次のステージ作ります"},
		{"左下に行くと稀にクリアできます"}
	};
	int mess2value = sizeof(mess2) / sizeof(mess2[0]);

	ransuu1 = rand() % mess1value;
	ransuu2 = rand() % mess2value;

	sprintf(player.mess, "%s", mess1[ransuu1]);
	sprintf(player.mess2, "%s", mess2[ransuu2]);
}