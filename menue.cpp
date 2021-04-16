/*
*	メニュー作成
*		B_36_柳澤優太
* 
*/
//ーーーーーーーーーーーーーーーーーヘッダーインクルード
#include<stdio.h>
//ーーーーーーーーーーーーーーーーー自作ヘッダーファイルインクルード
#define CONIOEX 
#include"conioex.h"
#include"key.h"
#include"main.h"
#include"title.h"
#include"dot.h"
#include"character.h"
#include"background.h"
//ーーーーーーーーーーーーブール
bool clear_once = false;	//clearDraw関数を１度使用するため
bool over_once=false;		//overDraw関数を１度使用するため
extern bool hantei;			//TitleUpdate関数をいじるためのやつ（１回目の操作）
extern bool chousei;		//TitleUpdate関数をいじるためのやつ（２回目の操作）
//ーーーーーーーーーーーーー構造体
extern Character dot;		

//ーーーーーーーーーーーーーーーーー以下関数
void MenueUpdate()
{
	if (keyPush(PK_SP) || keyPush(PK_ENTER))
	{
		clrscr();//画面消去
		Scene = MENUE;//メニューへ
		return;
	}
}

void GameClearUpdate()
{
	if (keyPush(PK_ENTER) || keyPush(PK_SP))
	{
		Scene = TITLE;
		clrscr();
		stopsound(music[SHOURI]);
		//bool調整
		dot.updated = true;
		hantei = false;
		chousei = false;
		return;
	}
}
void GameClearDraw() 
{
	if (clear_once == true)
	{//１回だけ通れるようにする
		return;
	}
	else {
		gotoxy(15, 1);
		dotDraw(GAMECLEAR, DISPLAY, 0, 0, 0, 0);
		gotoxy(15, 15);
		dotDraw(COMPRETE, DISPLAY, 0, 0, 0, 0);
		clear_once = true;
	}
}

void GameOverUpdate()
{
	if (keyPush(PK_ENTER) || keyPush(PK_SP))
	{
		Scene = TITLE;			//シーンをタイトルへ
		clrscr();
		stopsound(music[MGAMEOVER]);
		//ーーーーーーーーーーーーーーーbool調整
		dot.updated = true;
		hantei = false;
		chousei = false;
		return;
	}
}

void GameOverDraw()
{//１回だけ通れるようにする
	if (over_once == true) {
		return;
	}
	else {
		char cell[2] = "/";	//次の関数で使う用の変数
		//bgSquare(int x, int y, int width, int height, char cell[2], int color, int bold);
		bgSquare(10, 4, 138, 40, cell, RED, 1);

		gotoxy(15, 5);
		//dotDraw(int int_value, int DOE_value, int _top, int _down, int _right, int _left);
		dotDraw(DOTGAMEOVER, DISPLAY, 5, 0, 0, 0);
		over_once = true;
	}
}