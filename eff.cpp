//	AT11B_36_柳澤優太
//		エフェクト処理
//

#include<stdio.h>
#define CONIOEX 
#include"common.h"
#include"conioex.h"
#include"main.h"
#include"eff.h"
#include"dot.h"
#include"player.h"
#include"character.h"

dotChar eff_intValue[EFF_FILE_MAX];


void effdl(char _efffile[16], int eff_value) {
	//ドット情報読み込み用変数
	//  ditubf[行][列]
	//int dotinfo[64][40];


	FILE* effFile;

	effFile = fopen(_efffile, "r");

	if (effFile == NULL)
	{
		printf("%sが開けませんでした\n", _efffile);

		fclose(effFile);
		return;
	}

	switch (eff_value)
	{
	case 1:
		for (int i = 0; i < 32; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				if (fscanf(effFile, "%d,", &eff_intValue[eff_value].dot[j][i]) != '\0');
			}
		}
		break;
	case 2:
		for (int i = 0; i < 32; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				if (fscanf(effFile, "%d,", &eff_intValue[eff_value].dot[j][i]) != '\0');
			}
		}
		break;

	default:
		for (int i = 0; i < 32; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				if (fscanf(effFile, "%d,", &eff_intValue[eff_value].dot[j][i]) != '\0');
			}
		}
		break;
	}

	fclose(effFile);
}

//	　縦23	横20
// 23456789012345678901234567890
//1
//2      oooooooooooooooooo <-18回
//3      oooooooooooooooooo
//4		 oooooooooooooooooo
//:				:
//:				:
//29     oooooooooooooooooo

//表示範囲 縦ー＞2～26	横ー＞8～27
//int i=2;i<=29;i++	
//int j=8;j<=27;j++

void effUpdate()
{

}

void effDraw(int int_value, int DOE_value,intPosition _first)
{
	int first_x =wherex();
	int first_y =wherey();
	
	switch (DOE_value)
	{
	case DISPLAY://描画処理 0

		for (int i = 0; i < 29; i++) {
			if (_first.y <= LIMIT_UP) {
				_first.y++;
				continue;
			}
			else if (wherey() >= LIMIT_DOWN)continue;

			for (int j = 8; j < 27; j++) {
				if (wherex() <= LIMIT_LEFT) {
					gotoxy(wherex() + 1, wherey());
					continue;
				}
				else if(wherex() >= LIMIT_RIGHT){
					continue;
				}
				switch (int_value)
				{
				case 0:
					eff_flame0(int_value,i,j);
					break;
				case 1:
					eff_flame1(int_value, i, j);
					break;
				case 2:
					eff_flame2(int_value, i, j);
					break;
				case 3:
					eff_flame3(int_value, i, j);
					break;
				case 4:
					eff_flame4(int_value, i, j);
					break;
				case 5:
					eff_flame5(int_value, i, j);
					break;
				case 6:
					eff_flame6(int_value, i, j);
					break;
				case 7:
					eff_flame7(int_value, i, j);
					break;
				case 8:
					eff_flame8(int_value, i, j);
					break;
				case 9:
					eff_flame9(int_value, i, j);
					break;
				case 10:
					eff_flame10(int_value, i, j);
					break;
				case 11:
					eff_flame11(int_value, i, j);
					break;
				case 12:
					eff_flame12(int_value, i, j);
					break;
				case 13:
					eff_flame13(int_value, i, j);
					break;
				case 14:
					eff_flame14(int_value, i, j);
					break;
				case 15:
					eff_flame15(int_value, i, j);
					break;
				default:

					break;
				}
			}
			_first.y++;
			gotoxy(first_x,_first.y);
		}
		break;

	case DELL_DISPLAY://消去処理 1
		for (int i = 0; i < 29; i++) {
			if ( _first.y <= LIMIT_UP) {
				_first.y++;
				continue;
			}
			else if (wherey() >= LIMIT_DOWN)
			{
				continue;
			}

			for (int j = 8; j < 27; j++) {
				if (wherex() <= LIMIT_LEFT) {
					gotoxy(wherex() + 1, wherey());
					continue;
				}
				else if (wherex() >= LIMIT_RIGHT) {
					continue;
				}
				switch (eff_intValue[int_value].dot[j][i])
				{
				case 0:
				case 5:
				printf(" ");
					break;

				default:
					printf(" ");
					break;
				}
			}
			_first.y++;
			gotoxy(first_x,_first.y);
		}
		break;
		
	}
}

void effAnimation(Character characterData,int _value)
{
	floatPosition f;
	intPosition i;
	intPosition zahyou;


	f.x = (characterData.realPos.x);
	f.y = ((characterData.realPos.y)*Y_HOSEI_RATIO)-10.0f;
	floatToInt(f, &zahyou);
	//if (characterData.realPos.x < LIMIT_LEFT)f.x = LIMIT_LEFT;
	if (characterData.realPos.y < 1.0f)f.y = LIMIT_UP;
	floatToInt(f, &i);
	gotoxy(i.x,i.y);

	
	if (_value < EFF_FILE_MAX-1)
	{
		effDraw(_value, DISPLAY,zahyou);
	}
	else {
		effDraw(_value, DISPLAY,zahyou);
		gotoxy(i.x, i.y);
		effDraw(_value, DELL_DISPLAY,zahyou);
	}
	
	

}

void eff_flame0(int _int_value,int _i,int _j)
{//xlsx 1
	switch(eff_intValue[_int_value].dot[_j][_i])
	{
	case 0:
		printf(" ");
		break;
	case 1:
		CDARKGRAY;
		printf("#");
		CWHITE;
		break;
	case 2:
		CYELLOW;
		printf("#");
		CWHITE;
		break;
	case 3:
	case 4:
		CRED;
		printf("#");
		CWHITE;
		break;
	default:
		printf(" ");
		break;
	}
}void eff_flame1(int _int_value, int _i, int _j) {
	//xlsx 2
	switch (eff_intValue[_int_value].dot[_j][_i])
	{
	case 0:
	case 1:
	case 5:
		printf(" ");
		break;
	case 2:
	case 3:
	case 4:
		CDARKGRAY;
		printf("#");
		CWHITE;
		break;
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
		CRED;
		printf("#");
		CWHITE;
		break;
	default:
		printf(" ");
		break;
	}
}
void eff_flame2(int _int_value, int _i, int _j) {
	//xlsx 3
	switch (eff_intValue[_int_value].dot[_j][_i])
	{
	case 0:
	case 2:
		printf(" ");
		break;
	case 1:
	case 3:
	case 5:
		CDARKGRAY;
		printf("#");
		CWHITE;
		break;
	case 4:
	case 9:
	case 12:
	/*	CGREEN;
		printf("#");
		CWHITE;
		break;*/

	case 11:
		CYELLOW;
		printf("#");
		CWHITE;
		break;
	case 6:
	case 7:
	case 8:
	case 10:
	case 13:
	case 14:
		CRED;
		printf("#");
		CWHITE;
		break;
	default:
		printf(" ");
		break;
	}
}
void eff_flame3(int _int_value, int _i, int _j) {
	//xlsx 4
	switch (eff_intValue[_int_value].dot[_j][_i])
	{
	case 0:
	case 5:
	case 10:
		printf(" ");
		break;
	case 1:
	case 2:
	case 3:
	case 4:
		CDARKGRAY;
		printf("#");
		CWHITE;
		break;
	case 6:
	case 9:
	case 12:
	case 14:
		CRED;
		printf("#");
		CWHITE;
		break;
	case 7:
	case 11:
	case 13:
	/*	CGREEN;
		printf("#");
		CWHITE;
		break;*/
	case 8:
		CYELLOW;
		printf("#");
		CYELLOW;
		break;
	default:
		CMAGENTA;
		printf("#");
		CWHITE;
		break;
	}
}
void eff_flame4(int _int_value, int _i, int _j) {
	//xlsx 5
	switch (eff_intValue[_int_value].dot[_j][_i])
	{
	case 0:
	case 2:
	case 7:
	case 14:
		printf(" ");
		break;
	case 1:
	case 8:
		CDARKGRAY;
		printf("#");
		CWHITE;
		break;
	case 6:
	case 9:
	case 10:
	case 12:
		CRED;
		printf("#");
		CWHITE;
		break;
	case 5:
		/*CGREEN;
		printf("#");
		CWHITE;
		break;*/
	case 4:
	case 3:
		CYELLOW;
		printf("#");
		CYELLOW;
		break;
	case 11:
	default:
		CMAGENTA;
		printf("#");
		CWHITE;
		break;
	}
}
void eff_flame5(int _int_value, int _i, int _j) {
	//xlsx 6
	switch (eff_intValue[_int_value].dot[_j][_i])
	{
	case 0:
	case 2:
	case 3:
		printf(" ");
		break;
	case 1:
	case 7:
		CDARKGRAY;
		printf("#");
		CWHITE;
		break;
	case 6:
	case 9:
	case 10:
	case 11:
	case 12:
		CRED;
		printf("#");
		CWHITE;
		break;
	case 5:
		/*CGREEN;
		printf("#");
		CWHITE;
		break;*/
	case 4:
	case 8:
		CYELLOW;
		printf("#");
		CYELLOW;
		break;
	case 13:
	default:
		CMAGENTA;
		printf("#");
		CWHITE;
		break;
	}
}
void eff_flame6(int _int_value, int _i, int _j) {
	//xlsx 7
	switch (eff_intValue[_int_value].dot[_j][_i])
	{
	case 0:
	case 2:
	case 7:
	case 14:
		printf(" ");
		break;
	case 1:
		CDARKGRAY;
		printf("#");
		CWHITE;
		break;
	case 6:
	case 9:
	case 10:
	case 11:
	case 12:
		CRED;
		printf("#");
		CWHITE;
		break;
	case 5:
		/*CGREEN;
		printf("#");
		CWHITE;
		break;*/
	case 4:
	case 3:
	case 8:
		CYELLOW;
		printf("#");
		CYELLOW;
		break;
	case 13:
	default:
		CMAGENTA;
		printf("#");
		CWHITE;
		break;
	}
}
void eff_flame7(int _int_value, int _i, int _j) {
	//xlsx 8
	switch (eff_intValue[_int_value].dot[_j][_i])
	{
	case 0:
	case 1:
	case 3:
	case 13:
		printf(" ");
		break;
	case 2:
		CDARKGRAY;
		printf("#");
		CWHITE;
		break;
	case 6:
	case 10:
	case 11:
	case 12:
		CRED;
		printf("#");
		CWHITE;
		break;
	case 14:
	case 9:
		/*CGREEN;
		printf("#");
		CWHITE;
		break;*/
	case 4:
	case 5:
	case 8:
		CYELLOW;
		printf("#");
		CYELLOW;
		break;
	case 7:
	default:
		CMAGENTA;
		printf("#");
		CWHITE;
		break;
	}
}
void eff_flame8(int _int_value, int _i, int _j) {
	//xlsx 9
	switch (eff_intValue[_int_value].dot[_j][_i])
	{
	case 0:
	case 3:
		printf(" ");
		break;
	case 1:
	case 7:
	case 9:
		CDARKGRAY;
		printf("#");
		CWHITE;
		break;
	case 6:
	case 10:
	case 11:
	case 12:
	case 13:
		CRED;
		printf("#");
		CWHITE;
		break;
	default:
		CMAGENTA;
		printf(" ");
		CWHITE;
		break;
	}
}
void eff_flame9(int _int_value, int _i, int _j) {
	switch (eff_intValue[_int_value].dot[_j][_i])
	{
	case 0:
	case 3:
		printf(" ");
		break;
	case 1:
	case 7:
	case 9:
		CDARKGRAY;
		printf("#");
		CWHITE;
		break;
	case 6:
	case 10:
	case 11:
	case 12:
	case 13:
		CRED;
		printf("#");
		CWHITE;
		break;
	default:
		CMAGENTA;
		printf(" ");
		CWHITE;
		break;
	}
}
void eff_flame10(int _int_value, int _i, int _j) {
	switch (eff_intValue[_int_value].dot[_j][_i])
	{
	case 0:
	case 3:
		printf(" ");
		break;
	case 1:
	case 7:
	case 9:
		CDARKGRAY;
		printf("#");
		CWHITE;
		break;
	case 6:
	case 10:
	case 11:
	case 12:
	case 13:
		CRED;
		printf("#");
		CWHITE;
		break;
	default:
		CMAGENTA;
		printf(" ");
		CWHITE;
		break;
	}
}
void eff_flame11(int _int_value, int _i, int _j) {
	switch (eff_intValue[_int_value].dot[_j][_i])
	{
	case 0:
	case 3:
		printf(" ");
		break;
	case 1:
	case 7:
	case 9:
		CDARKGRAY;
		printf("#");
		CWHITE;
		break;
	case 6:
	case 10:
	case 11:
	case 12:
	case 13:
		CRED;
		printf("#");
		CWHITE;
		break;
	default:
		CMAGENTA;
		printf(" ");
		CWHITE;
		break;
	}
}
void eff_flame12(int _int_value, int _i, int _j) {
	switch (eff_intValue[_int_value].dot[_j][_i])
	{
	case 0:
	case 3:
		printf(" ");
		break;
	case 1:
	case 7:
	case 9:
		CDARKGRAY;
		printf("#");
		CWHITE;
		break;
	case 6:
	case 10:
	case 11:
	case 12:
	case 13:
		CRED;
		printf("#");
		CWHITE;
		break;
	default:
		CMAGENTA;
		printf(" ");
		CWHITE;
		break;
	}
}
void eff_flame13(int _int_value, int _i, int _j) {
	switch (eff_intValue[_int_value].dot[_j][_i])
	{
	case 0:
	case 3:
		printf(" ");
		break;
	case 1:
	case 7:
	case 9:
		CDARKGRAY;
		printf("#");
		CWHITE;
		break;
	case 6:
	case 10:
	case 11:
	case 12:
	case 13:
		CRED;
		printf("#");
		CWHITE;
		break;
	default:
		CMAGENTA;
		printf(" ");
		CWHITE;
		break;
	}
}
void eff_flame14(int _int_value, int _i, int _j) {
	switch (eff_intValue[_int_value].dot[_j][_i])
	{
	case 0:
	case 3:
		printf(" ");
		break;
	case 1:
	case 7:
	case 9:
		CDARKGRAY;
		printf("#");
		CWHITE;
		break;
	case 6:
	case 10:
	case 11:
	case 12:
	case 13:
		CRED;
		printf("#");
		CWHITE;
		break;
	default:
		CMAGENTA;
		printf(" ");
		CWHITE;
		break;
	}
}
void eff_flame15(int _int_value, int _i, int _j) {
	switch (eff_intValue[_int_value].dot[_j][_i])
	{
	case 0:
	case 3:
		printf(" ");
		break;
	case 1:
	case 7:
	case 9:
		CDARKGRAY;
		printf("#");
		CWHITE;
		break;
	case 6:
	case 10:
	case 11:
	case 12:
	case 13:
		CRED;
		printf("#");
		CWHITE;
		break;
	default:
		CMAGENTA;
		printf(" ");
		CWHITE;
		break;
	}
}