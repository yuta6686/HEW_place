/*
*	ドット絵の情報をエクセルから読み込んで表示
*			AT11B＿３６＿柳澤優太
* 
*/

#include<stdio.h>
#define CONIOEX 
#include"conioex.h"
#include"character.h"
#include"dot.h"
#include<string.h>



dotChar int_enemy[ENEMY_LAST];
dotCharinh gamescene[ENEMY_LAST];
dotString print_enemy[ENEMY_LAST];
dotString del_enemy[ENEMY_LAST];
dotRange dotrange;

void dotInit()
{
	dotrange.down = 0;
	dotrange.top = 0;
	dotrange.left = 0;
	dotrange.right = 0;
}

void filedl(char _dotfile[16],int int_value) {
	//ドット情報読み込み用変数
	//  ditubf[行][列]
	//int dotinfo[64][40];


	FILE* dotFile;

	dotFile = fopen(_dotfile, "r");

	if (dotFile == NULL)
	{
		printf("%sが開けませんでした\n", _dotfile);

		fclose(dotFile);
		return;
	}

	switch (int_value)
	{
	case SAKANA:
		for (int i = 0; i < 34; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				if (fscanf(dotFile, "%d,", &int_enemy[int_value].dot[j][i]) != '\0');
			}
		}
		break;
	case AKIKAN:
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				if (fscanf(dotFile, "%d,", &int_enemy[int_value].dot[j][i]) != '\0');
			}
		}
		break;

	case DOTGAMEOVER:
	case SEA:
	case SEA_RESORT:
	case GAMECLEAR:
	case JET_COARSTER:
	case COMPRETE:
		for (int i = 0; i < 64; i++) {
			for (int j = 0; j < 128; j++) {
				if (fscanf(dotFile, "%d,", &gamescene[int_value].inhdot[j][i]) != '\0');
			}
		}
		break;

	default:
		for (int i = 0; i < 64; i++)
		{
			for (int j = 0; j < 64; j++)
			{
				if (fscanf(dotFile, "%d,", &int_enemy[int_value].dot[j][i]) != '\0');
			}
		}
		break;
	}
	

	fclose(dotFile);

}

//単色運用
//ドットデータを表示用変数と消去用変数にまとめる関数
//print_enemy->表示用
//del_enemy->消去用
void dotCat(int int_value,int DOE_value)
			//(キャラの種類,Diplay Or Erase	->表示:0 削除:1）
{
	switch (DOE_value)
	{
	case 0://描画処理
		switch (int_value)
		{
		case GUNMA:
			for (int i = 0; i < 64; i++) {
				for (int j = 0; j < 64; j++) {
					switch (int_enemy[int_value].dot[j][i])
					{
					case 0:
					case 5:
						strcat(print_enemy[int_value].dotC, "　");
						break;

					default:
						strcat(print_enemy[int_value].dotC, "■");
						break;
					}
				}
				strcat(print_enemy[int_value].dotC, "\n");
			}
			break;
		case JET:
			break;

		case GYO:
			break;

		case AKIKAN:
			for (int i = 0; i < 16; i++) {
				for (int j = 0; j < 16; j++) {
					switch (int_enemy[int_value].dot[j][i])
					{
					case 0:
						strcat(print_enemy[int_value].dotC, "　");
						break;

					default:
						strcat(print_enemy[int_value].dotC, "■");
						break;
					}
				}
				strcat(print_enemy[int_value].dotC, "\n");
			}
			break;

		case SAKANA:
			for (int i = 0; i < 34; i++) {
				for (int j = 0; j < 16; j++) {

					switch (int_enemy[int_value].dot[j][i])
					{
					case 0:
					case 1:
						strcat(print_enemy[int_value].dotC, "　");
						break;

					default:
						strcat(print_enemy[int_value].dotC, "■");
						break;
					}
				}
				strcat(print_enemy[int_value].dotC, "\n");
			}
			break;

		}
		break;
	case 1://消去処理
		switch (int_value)
		{
		case JET:
		case GUNMA:
		case GYO:
			for (int i = 0; i < 64; i++) {
				for (int j = 0; j < 64; j++) {
					switch (int_enemy[int_value].dot[j][i])
					{
					case 0:
					case 5:
						strcat(del_enemy[int_value].dotC, "　");
						break;

					default:
						strcat(del_enemy[int_value].dotC, "　");
						break;
					}
				}
				strcat(del_enemy[int_value].dotC, "\n");
			}
			break;
		}
		break;
	case AKIKAN:
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 16; j++) {
				switch (int_enemy[int_value].dot[j][i])
				{
				case 0:
				case 5:
					strcat(del_enemy[int_value].dotC, "　");
					break;

				default:
					strcat(del_enemy[int_value].dotC, "　");
					break;
				}
			}
			strcat(del_enemy[int_value].dotC, "\n");
		}
		break;
	case SAKANA:
		for (int i = 0; i < 34; i++) {
			for (int j = 0; j < 16; j++) {
				switch (int_enemy[int_value].dot[j][i])
				{
				case 0:
				case 5:
					strcat(del_enemy[int_value].dotC, "　");
					break;

				default:
					strcat(del_enemy[int_value].dotC, "　");
					break;
				}
			}
			strcat(del_enemy[int_value].dotC, "\n");
		}
		break;
	}
}

//多色運用

void dotDraw(int int_value, int DOE_value,int _top,int _down ,int _right,int _left)
{
	int x = wherex();
	int y = wherey();
	dotrange.top = _top;
	dotrange.down = _down;
	dotrange.right = _right;
	dotrange.left = _left;

	switch (DOE_value)
	{
	case DISPLAY://描画処理 0

		switch (int_value)
		{
		case GUNMA:
			for (int i = dotrange.top; i < DOT_HEIGHT_MAX-dotrange.down; i++) {
				for (int j = dotrange.left; j < DOT_WIDTH_MAX-dotrange.right; j++) {
					switch (int_enemy[int_value].dot[j][i])
					{

					case 0:
					case 5:
						gotoxy(wherex() + 2, wherey());
						break;
					default:
						CWHITE;
						textbackground(BROWN);
						printf("　");
						textbackground(BLACK);
						break;
					}
					
				}
				gotoxy(x, wherey() + 1);
			}
			break;
		case JET:
			for (int i = dotrange.top; i < DOT_HEIGHT_MAX - dotrange.down; i++) {
				for (int j = dotrange.left; j < DOT_WIDTH_MAX - dotrange.right; j++) {
					switch (int_enemy[int_value].dot[j][i])
					{

					case 0:
						gotoxy(wherex() + 2, wherey());
						break;

					case 2:
					case 4:
					case 5:
					case 6:
					case 7:
					case 8:
						highvideo();
						textattr(0x99);
						printf("■");
						break;
					default:
						highvideo();
						BGCYAN;
						printf("■");
						break;
					}

				}
				gotoxy(x, wherey() + 1);
			}
			normvideo();
			BGRESET;
			break;
		case GYO:
			for (int i = dotrange.top; i < DOT_HEIGHT_MAX - dotrange.down; i++) {
				for (int j = dotrange.left; j < DOT_WIDTH_MAX - dotrange.right; j++) {
					switch (int_enemy[int_value].dot[j][i])
					{

					case 0:
						gotoxy(wherex() + 2, wherey());
						break;

					case 1:
					case 2:
					case 4:
					case 5:
					case 6:
					case 7:
						textattr(0x99);
						printf("■");
						break;
					default:
						BGCYAN;
						printf("■");
						break;
					}

				}
				gotoxy(x, wherey() + 1);
			}
			BGRESET;
			break;
		case SAKANA:
			for (int i = dotrange.top; i < DOT_HEIGHT_MAX - dotrange.down; i++) {
				for (int j = dotrange.left; j < DOT_WIDTH_MAX - dotrange.right; j++) {
					switch (int_enemy[int_value].dot[j][i])
					{

					case 0:
					case 1:
						gotoxy(wherex() + 2, wherey());
						break;

					default:
						CCYAN;
						printf("■");
						CWHITE;
						break;
					}

				}
				gotoxy(x, wherey() + 1);
			}
			break;

		case DOTGAMEOVER:
			GameOverDisplay(int_value);
			break;

		case SEA:
			Sea(int_value);
			break;
		case SEA_RESORT:
			SeaResort(int_value);
			break;
		case GAMECLEAR:
			GameClear(int_value);
			break;
		case JET_COARSTER:
			JetCoarster(int_value);
			break;

		case COMPRETE:
			Complete(int_value);
			break;
		}
		break;
	case DELL_DISPLAY://消去処理 1
		for (int i = dotrange.top; i < DOT_HEIGHT_MAX - dotrange.down; i++) {
			for (int j = dotrange.left; j < DOT_WIDTH_MAX - dotrange.right; j++) {
				switch (int_enemy[int_value].dot[j][i])
				{

				case 0:
				case 5:
					printf("　");
					break;

				default:
					printf("　");
					break;
				}
			}
			gotoxy(x, wherey() + 1);
		}
		break;
	}	
}

void GameOverDisplay(int _int_value)
{
	int x = wherex();
	for (int i =8; i <44 ; i++) {
		for (int j = 0; j < 128; j++) {
			switch (gamescene[_int_value].inhdot[j][i])
			{

			case 0:
			case 1:
			case 2:
			case 3:
				CBLACK;
				printf(" ");
				CWHITE;
				break;
			case 4:
			case 6:
			case 5:
			case 7:
			case 8:
			case 10:
			case 11:
			case 12:
				CRED;
				printf("#");
				CWHITE;
				break;

			default:
				printf(" ");
				break;
			}

		}
		gotoxy(x, wherey() + 1);
	}
}

void Sea(int _int_value)
{
	int x = wherex();
	for (int i = 0; i < 43; i++) {
		for (int j = 0; j < 128; j++) {
			switch (gamescene[_int_value].inhdot[j][i])
			{
			case 0:
			case 6:
			case 9:
			case 11:
			case 14:
				CGREEN;
				printf("#");
				CWHITE;
				break;
			case 1:
				CMAGENTA;
				printf("#");
				CWHITE;
				break;
			case 2:
			case 3:
				CBLUE;
				printf("#");
				CWHITE;
				break;
			case 4:
				printf("#");
				break;
			case 5:
				CCYAN;
				printf("#");
				CWHITE;
				break;
			case 7:
			case 8:
			case 10:
			case 13:
				CBROWN;
				printf("#");
				CWHITE;
				break;
			case 12:
				CBLACK;
				printf(" ");
				CWHITE;
				break;

			}
		}
		gotoxy(x, wherey() + 1);
	}
}

void SeaResort(int _int_value)
{
	int x = wherex();
	for (int i = 18; i < 64; i++) {
		for (int j = 0; j < 68; j++) {
			switch (gamescene[_int_value].inhdot[j][i])
			{
			case 0:
				BGBLUE;
				printf("■");
				BGRESET;
				break;
			case 1:
				textattr(0x88);
				printf("■");
				BGRESET;
				break;
			case 2:
				textattr(0xBB);
				printf("■");
				BGRESET;
				break;
			case 4:
				BGWHITE;
				printf("■");
				BGRESET;
				break;
			case 5:
			case 8:
			case 9:
				BGBROWN;
				printf("■");
				BGRESET;
				break;
			case 6:
			case 7:
				BGGREEN;
				printf("■");
				BGRESET;
				break;
			case 10:
				BGYELLOW;
				printf("■");
				BGRESET;
				break;
			case 11:
			case 3:
				BGCYAN;
				printf("■");
				BGRESET;
				break;
			case 12:
			case 13:
			case 14:
				BGMAGENTA;
				printf("■");
				BGRESET;
				break;
			}
		}
		gotoxy(x, wherey() + 1);
	}
}

void GameClear(int _int_value)
{
	int x = wherex();
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 128; j++) {
			switch (gamescene[_int_value].inhdot[j][i])
			{
			case 0:
			case 13:
				gotoxy(wherex() + 1, wherey());
				break;
			case 1:
			case 2:
			case 3:
				BGRED;
				printf("*");
				BGRESET;
				break;
			case 4:
			case 5:
				BGYELLOW;
				printf("*");
				BGRESET;
				break;
			case 6:
				BGGREEN;
				printf("*");
				BGRESET;
				break;
			case 7:
			case 11:
				BGMAGENTA;
				printf("*");
				BGRESET;
				break;
			case 8:
			case 10:
			case 9:
			case 12:
				BGCYAN;
				printf("*");
				BGRESET;;
				break;
			case 14:
				BGMAGENTA;
				printf("*");
				BGRESET;
				break;
			}
		}
		gotoxy(x, wherey() + 1);
	}
}

void JetCoarster(int _int_value) {
	int x = wherex();
	for (int i = 0; i < 45; i++) {
		for (int j = 0; j < 158; j++) {
			switch (gamescene[_int_value].inhdot[j][i])
			{
			case 1:
			default:
				BGWHITE;
				printf(" ");
				break;
			}
		}
		gotoxy(x, wherey() + 1);
	}
	BGRESET;
}

void Complete(int _int_value) {
	int x = wherex();
	for (int i = 0; i < 35; i++) {
		for (int j = 0; j < 128; j++) {
			switch (gamescene[_int_value].inhdot[j][i])
			{
			case 0:
				gotoxy(wherex() + 1, wherey());
				break;
			case 1:
			case 2:
				textattr(0xBB);
				printf(" ");
				BGRESET;
				break;
			}
		}
		gotoxy(x, wherey() + 1);
	}
}