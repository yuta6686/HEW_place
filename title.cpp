//--------------------------------------------
//		�^�C�g���\��
//	AT11B_36_���V�D��

#include<stdio.h>
#define CONIOEX 
#include"conioex.h"
#include"key.h"
#include"main.h"
#include"title.h"
#include"dot.h"
#include"character.h"
#include"title.h"
#include"player.h"
#include"common.h"
#include"enemy.h"
#include"background.h"

#define INITIAL_X 40.0f//�������W
#define INITIAL_Y 15.0f
#define MOVE_UNIT 0.5f
#define INITIAL_ANGLE (float)(PI*2*3/4)
#define ANGLE_UNIT 0.05f
#define INITIAL_LENGTH 8.0f

Character dot;
extern dotChar int_enemy[];
extern dotString print_enemy[];
extern dotString del_enemy[];
//extern int music[];
static float length = INITIAL_LENGTH;

extern bool bghantei;

bool hantei = false;
bool chousei = false;


//floatPosition f;
//intPosition i;



void Titleinit()
{
	//fileDraw(0);
	dot.lastPos.x = dot.realPos.x = INITIAL_X;
	dot.lastPos.y = dot.realPos.y = INITIAL_Y;
	dot.lastAngle = dot.angle = INITIAL_ANGLE;
	dot.updated = true;

	/*f.x = 0.0f;
	f.y = 0.0f;*/
}

void TitleUpdate()
{
	if (keyPush(PK_SP) || keyPush(PK_ENTER))
	{
		if (hantei == true)
		{
			Scene = GAME;
			bghantei = false;
			stopsound(music[SHAINING]);
			clrscr();//��ʏ���
			playsound(music[SPLASH], MUSIC_NON_LOOP);
		//	playsound(music[TOKYO],MUSIC_LOOP);
			setvolume(music[TOKYO], 20);
			return;
		}
		else {
			hantei = true;
		}
	}
	if (keyPush(PK_SP) || keyPush(PK_ENTER))
	{
		playsound(music[KETTEI], MUSIC_NON_LOOP);
		hantei = true;
		clrscr();
	}
	//dot.realPos.x += 1.0f;
	//dot.realPos.y += 1.0f;
	
	if (keyPush(PK_1))
	{
		Scene = FREE;
		clrscr();
	}
}

void TitleDraw()
{
	floatPosition f;
	intPosition i;
	

	if (dot.updated == false )
	{
		if (hantei == true && chousei==false)
		{
			/*gotoxy(INITIAL_X-25, INITIAL_Y);
	
			dotDraw(GUNMA, DISPLAY, 0, 0, 0, 0);*/
			gotoxy(1,1);
			dotDraw(JET_COARSTER, DISPLAY, 0, 0, 0, 0);

			gotoxy(INITIAL_X-25, INITIAL_Y);
			
			dotDraw(JET, DISPLAY, 0, 49, 0, 0);
			
			gotoxy(INITIAL_X - 25, INITIAL_Y+15);
			dotDraw(GYO, DISPLAY, 0, 50, 0, 0);
			normvideo();
			textbackground(BLACK);
			chousei = true;
		}
		
		return;
		
	}


	int sentence = 20;

	//�\������

	//printf(print_enemy[0].dotC);
	PlayerInit();
	EnemyInit();
	Titleinit();
	char buff[2] = "o";
	//void bgSquare(int x, int y,int width, int height,char cell[2],int color,int bold )
	bgSquare(14, 1, 54, 12, buff, YELLOW, 1);
	bgSquare(15, 2, 52, 10, buff, RED, 1);
	
	playsound(music[SHAINING], MUSIC_LOOP);
	gotoxy(sentence, 5);
	printf("����̃v���p�e�B����");
	gotoxy(sentence, wherey() + 1);
	printf("�t�H���g�T�C�Y��18�A�c�̃T�C�Y��46�ɐݒ�");
	gotoxy(sentence, wherey() + 1);
	printf("�S��ʕ\���ɂ���(F11��������)�V��ł�");
	gotoxy(sentence, wherey() + 1);
	printf("�������ł�����ENTER�L�[��SPACE�L�[�������Ă�");


	dot.updated = false;
}