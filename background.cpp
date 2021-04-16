//
//	AT11B_36_柳澤優太
//	背景処理

//-------------------------インクルード
#include<stdio.h>
//-------------------------ヘッダーファイルインクルード
#include "dot.h"
#include "background.h"
#include "character.h"
#include "common.h"
#include "main.h"
#define CONIOEX 
#include "conioex.h"
#include"player.h"
#include"enemy.h"
//-------------------------ヘッダーファイルインクルード
//-------------------------グローバル変数
bool bghantei = false;
static bool kakuho = false;
extern Character player;
extern int goal_intervalCounter;
extern bool distance;
//-------------------------グローバル変数

void BackGroundUpdate()
{
	if (stageNo)bghantei = true;
}

void BackGroundDraw()
{
	if (bghantei)return;
	distance = false;

	switch (stageNo)
	{
	case 0:
		bgDelete();
		CCYAN;
		bgPrint();
		CWHITE;
		break;
	case 1:
		break;
	case 2:
		break;
	}
	bghantei = true;
}

void bgDelete()
{
	int hosei = 3;
	gotoxy(1, 1);
	for (int i = 0; i <= LIMIT_DOWN+hosei; i++)
	{
		for (int j = 0; j <= LIMIT_LEFT; j++)
		{
			printf(" ");
		}
		gotoxy(1, wherey() + 1);
	}

	gotoxy(LIMIT_LEFT, LIMIT_UP);
	for (int i = 0; i < LIMIT_DOWN+hosei; i++)
	{
		for (int j = LIMIT_RIGHT; j < MAX_RIGHT; j++)
		{
			printf(" ");
		}
		gotoxy(0, wherey() + 1);
	}
}
void bgPrint()
{
	float y_hosei = 3.0f;
	float x_left_hosei = 3.0f;
	float x_right_hosei = 2.0f;
	
	BGGREEN;

	gotoxy(1, 1);
	for (int i = 0; i <= LIMIT_DOWN; i++)
	{
		for (int j = 0; j < LIMIT_LEFT-x_left_hosei; j++)
		{
			printf("0");
		}
		gotoxy(1, wherey() + 1);
	}

	gotoxy(LIMIT_RIGHT+x_right_hosei, LIMIT_UP);
	for (int i = 0; i < LIMIT_DOWN+y_hosei; i++)
	{
		for (int j = LIMIT_RIGHT + x_right_hosei; j < MAX_RIGHT; j++)
		{
			printf("0");
		}
		gotoxy(LIMIT_RIGHT+x_right_hosei, wherey()+1);
	}
	BGRESET;
	CCYAN;

	gotoxy(BACKGROUND_X, BACKGROUND_Y);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 32; j++) {
			printf(" ");
		}
		gotoxy(BACKGROUND_X, wherey() + 1);
	}
	bgStatusUpdata(player);
	CWHITE;
}

void bgStatusUpdata(Character playerStatus)
{
	char cell[2] = "%";
	char cell2[2] = "=";
	char buff[32];
	bgSquare(BACKGROUND_X, BACKGROUND_Y-4,32,20,cell,CYAN,1);
	bgSquare(BACKGROUND_X + 2, BACKGROUND_Y-1, 6, 4, cell2, MAGENTA, 1);
	bgSquare(BACKGROUND_X + 7, BACKGROUND_Y - 1, 6, 4, cell2, MAGENTA, 1);
	bgSquare(BACKGROUND_X + 12, BACKGROUND_Y - 1, 6, 4, cell2, MAGENTA, 1);
	gotoxy(BACKGROUND_X+2, BACKGROUND_Y-2);
	sprintf(buff, "プレイヤーのHP:残り%d", playerStatus.HP);
	printf(buff);


	gotoxy(BACKGROUND_X+3, BACKGROUND_Y);
	//printf("　　");
	for (int i = 0; i < playerStatus.HP; i++)
	{
		switch (i)
		{
		case 0:
			CRED;
			break;
		case 1:
			CYELLOW;
			break;
		case 2:
			CGREEN;
			break;
		default:
			CGREEN;
			break;
		}
		printf("■■");
		gotoxy(wherex()-4, wherey() + 1);
		printf("■■");
		gotoxy(wherex() + 1, wherey()-1);
	}
	BGRESET;
	gotoxy(BACKGROUND_X + 3, BACKGROUND_Y+3);
	printf(player.mess);
	gotoxy(BACKGROUND_X + 3, BACKGROUND_Y + 5);
	printf(player.mess2);
	//bgdistance();
}

void bgSquare(int x, int y,int width, int height,char cell[2],int color,int bold )
{//x座標,y座標,幅,高さ,表示する文字,色,太さ
	textcolor(color);
	gotoxy(x, y);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			printf("%s", cell);
		}
		gotoxy(x, wherey() + 1);
	}
	CWHITE;
	int bold_y = y + bold;
	int bold_x = x + bold;
	gotoxy(bold_x, bold_y);

	for (int i = 0+bold; i < height - (bold); i++) {
		for (int j = 0+bold; j < width - (bold); j++) {
			printf(" ");
		}
		gotoxy(bold_x, wherey() + 1);
	}
}

void bgdistance()
{
	char cell[2] = "%";
	char cell2[2] = "=";
	bgSquare(BACKGROUND_X, BACKGROUND_Y - 12, 32,8, cell, BLUE, 1);

	char buff[32];
	char buff2[32];
	char buff3[] = "　　　　　　　　　　　　";
	int meter;
	switch (goal_intervalCounter)
	{
	case 0:meter = 999;
		setvolume(music[SEN], 70);
		//playsound(music[NOKORI], MUSIC_NON_LOOP);
		playsound(music[SEN], MUSIC_NON_LOOP);
		//playsound(music[KIRO], MUSIC_NON_LOOP);
		sprintf(buff2, "■■■■■■■■■■■■" );
		break;
	case 1:meter = 800;
		//playsound(music[NOKORI], MUSIC_NON_LOOP);
		playsound(music[HAPPYAKU], MUSIC_NON_LOOP);
		setvolume(music[SEN], 70);
		//playsound(music[KIRO], MUSIC_NON_LOOP);
		sprintf(buff2, "■■■■■■■■■■");
		break;
	case 2:meter = 600;
		//playsound(music[NOKORI], MUSIC_NON_LOOP);
		playsound(music[ROPPYAKU], MUSIC_NON_LOOP);
		//playsound(music[KIRO], MUSIC_NON_LOOP);
		sprintf(buff2, "■■■■■■■■");
		break;
	case 3:meter = 400;
		//playsound(music[NOKORI], MUSIC_NON_LOOP);
		playsound(music[YONHYAKU], MUSIC_NON_LOOP);
		//playsound(music[KIRO], MUSIC_NON_LOOP);
		sprintf(buff2, "■■■■■■");
		break;
	case 4:meter = 200;
		//playsound(music[NOKORI], MUSIC_NON_LOOP);
		playsound(music[NIHYAKU], MUSIC_NON_LOOP);
		//playsound(music[KIRO], MUSIC_NON_LOOP);
		sprintf(buff2, "■■■■");
		break;
	case 5:meter = 100;
		playsound(music[MOUHITO], MUSIC_NON_LOOP);
		sprintf(buff2, "■■" );
		break;
	default:meter = 000;
		sprintf(buff2, "もうすぐゴールです" );
		break;
	}
	sprintf(buff, "残り距離%dメートル", meter);
	CRED;
	gotoxy(BACKGROUND_X + 2, BACKGROUND_Y - 10);
	printf(buff);
	

	//BGBROWN;
	/*gotoxy(BACKGROUND_X+2, BACKGROUND_Y - 9);
	printf(buff3);*/
	bgSquare(BACKGROUND_X + 3, BACKGROUND_Y - 8, 25, 3, cell2, CYAN, 1);
	gotoxy(BACKGROUND_X+4, BACKGROUND_Y - 7);
	printf(buff2);

	BGRESET;
}