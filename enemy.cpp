//----------------------------------------
//		AT11B_36_���V�D��
//	�G�̏���
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
//-----------------------------------------------------------------------�O���[�o���ϐ�
//-------------------------�\����
Character enemy[ENEMY_MAX];

extern dotChar int_enemy[];
extern dotString print_enemy[];
extern dotString del_enemy[];
//-------------------------�\����
//-------------------------bool�^
bool distance = false;
bool goal = false;
bool a = false;
extern bool chousei;
extern bool hp = false;
extern bool clear_once;
//-------------------------bool�^
//-------------------------int�^
static int currentEnemy = 0;
static int wallmax = 10;

static int currentIndex = 0;//���݃f�[�^���w���Ă���ꏊ
static int intervalCounter = 0;//�o���C���^�[�o��
static int wall_intervalCounter = 0;
static int enemyDestroyCount = 0;//���j��
int lastTime;
int currentTime;
int goal_intervalCounter = 0;
//-------------------------int�^
//---------------------------�A�C�e���p
rangeData rupidata[] =
{
	{0,0},		//���S
	{1,0},		//�E
	{-1,0},		//��
	{0,1},		//��
	{0,-1},		//��
	{1,1},		//�E��
	{-1,1},		//����
	{1,-1},		//�E��
	{-1,-1},	//����
	{0,-2},
	{0,2},
};
int rupivalue = sizeof(rupidata) / sizeof(rupidata[0]);
//---------------------------�A�C�e���p
//-----------------------------�G�l�~�[�\���p
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
//--------------------------------------------------�G�l�~�[�\���p
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�o���f�[�^
struct AppearData {
	int interval;//�o���܂ł̃C���^�[�o�� �i�t���[���j
	float x;
	float y;
	float speedx;
	float speedy;
	int color;
	int kind;
};
AppearData appearData[] =
//	�C���^�[�o��,x���W,y���W,x�X�s�[�h,y�X�s�[�h,�F
//	�G�l�~�[�̕\���͈͂͏c��5�{
{//1�X�e�[�W
	{30,80.0f,40.0f,2.0f,-0.2f,YELLOW,STATUS_ENEMY},						//0
	{60,45.0f,40.0f,0.3f,-0.15f,RED,STATUS_ENEMY},							//1
	{60,120.0f,40.0f,-0.25f,-0.5f,BLUE,STATUS_ENEMY},			//2
	{60,LIMIT_LEFT+1,LIMIT_DOWN-2.0f,0.0f,0.0f,LIGHTGRAY,STATUS_GOAL},		//3
	{30,40.0f,40.0f,0.0f,-0.1f,MAGENTA,STATUS_WALL},						//4
	{30,LIMIT_LEFT+20.0f,40.0f,0.0f,-0.1f,CYAN,STATUS_ENEMY},				//5
	{60,LIMIT_RIGHT-7.0f,20.0f,-0.5f,0.0f,RED,STATUS_ENEMY_SIDE},				//6

	
	//�Q�X�e�[�W
	{60,LIMIT_RIGHT - 7.0f,20.0f,-0.5f,0.0f,RED,STATUS_ENEMY_SIDE},		//7
	{60,100.0f,100.0f,0.0f,1.5f,BLUE,STATUS_ENEMY},		//8
	{60,100.0f,100.0f,0.0f,1.5f,GREEN,STATUS_ENEMY},		//9
	{60,100.0f,100.0f,0.0f,1.5f,MAGENTA,STATUS_ENEMY},	//10
	{60,100.0f,100.0f,0.0f,1.5f,CYAN,STATUS_ENEMY},		//11
	//�R���ā[��
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
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�o���f�[�^
//�[�[�[�[�[�[�[�[�[�[�X�e�[�W�̃G�l�~�[���
struct Stage {
	//char music[256];
	//int bgcolor;
	int biginNo;
	int endNo;
};
//		��
static Stage stage[] =
{
	{0,5},
	{6,11},
	{12,30}
};
//�[�[�[�[�[�[�[�[�[�[�X�e�[�W�̃G�l�~�[���
//-----------------------------------------------------------------------�O���[�o���ϐ�

//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�ȉ��֐�
void EnemyInit()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{//-----------------------------------------------�S�G�l�~�[���ʏ�����
		enemy[i].status = Dead;
		enemy[i].lastPos.x = enemy[i].realPos.x = 100.0f;
		enemy[i].lastPos.y = enemy[i].realPos.y = 50.0f;
		enemy[i].speedx = 0.0f;
		enemy[i].speedy = 0.0f;
		enemy[i].angle = 0.0f;
	//-----------------------------------------------�S�G�l�~�[���ʏ�����
	//-----------------------------------------------�G�l�~�[�ʏ�����
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
	//-----------------------------------------------�G�l�~�[�ʏ�����

	//------------------------------------���[�v�O����������
	intervalCounter = 0;
	currentIndex = 0;
	currentEnemy = 0;

	goal = false;

	timeBeginPeriod(1);			//	1/1000�b�����
	lastTime = timeGetTime();	//���������lastTime�ɓ����
	currentTime = 0;
	//------------------------------------���[�v�O����������
}

void EnemyUpdate()
{
	//�G��|���Ƃ����T�O���Ȃ����ߎg��Ȃ��̂ŃR�����g�ɂ����
	//�����u���X��f���ݒ������
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
		// intervalCounter->>>���t���[�����Z����Ă���
		// appearData	  ->>>�o���f�[�^
		// currentIndex   ->>>��������t���[�����Z����Ă�����
		//						��������0�ɖ߂�Ǝv��
	{
		//�o�����邽�߂̏���
		//----------------�G�l�~�[�̏o���f�[�^��enemy�f�[�^�ɓ���Ďg�p�ł���悤�ɂ��Ă���
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

		//--------------------------------------------�G�l�~�[�̎�ʊǗ�
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
		//--------------------------------------------�G�l�~�[�̎�ʊǗ�
		//----------------�G�l�~�[�̏o���f�[�^��enemy�f�[�^�ɓ���Ďg�p�ł���悤�ɂ��Ă���

	//--------------appeardata�̃f�[�^��endNo��biginNo���g���ăX�e�[�W���Ƃɂ܂킵�Ă���
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
	//--------------appeardata�̃f�[�^��endNo��biginNo���g���ăX�e�[�W���Ƃɂ܂킵�Ă���

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[����ł��甲����
		if (enemy[i].status == Dead)continue;
		//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[����ł��甲����
		//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[���݂̈ʒu�ύX����
		enemy[i].realPos.x = enemy[i].lastPos.x + enemy[i].speedx;
		enemy[i].realPos.y = enemy[i].lastPos.y + enemy[i].speedy;
		enemy[i].updated = true;
		//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[���݂̈ʒu�ύX����
		//-----------------------------------�G�l�~�[�͈̔͐ݒ�
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
		//-----------------------------------�G�l�~�[�͈̔͐ݒ�
	}
	//----------------------------------�G�l�~�[�̈ړ�������
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
	//----------------------------------�G�l�~�[�̈ړ�������

	//----------------------------------�w�i�����������ł���Ă���
	if (distance == true)
	{
		bgdistance();
		distance = false;
	}
	//----------------------------------�w�i�����������ł���Ă���
}
//--------------------------------------------�G�l�~�[�`�揈��
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
//--------------------------------------------�G�l�~�[�`�揈��
//--------------------------------------------�G�l�~�[�\���֐�
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
			printf("�[");
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
				printf("��");
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
				printf("��");
			}
		}
	}
	else return;
}
//--------------------------------------------�G�l�~�[�\���֐�
//--------------------------------------------�G�l�~�[�����֐�
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
				printf("�@");
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
				printf("�@");
			}
		}
	}
	else return;
	//printf(del_enemy[SAKANA].dotC);
	//dotDraw(SAKANA,DELL_DISPLAY, 0, 34, 30, 0);
}
//--------------------------------------------�G�l�~�[�����֐�

bool EnemyHitCheck(floatPosition pos)
{
	bool anyoneHit = false;//�N���ƏՓ˂���
	float plusx;	//�E
	float plusy;	//��
	float minusx;	//��
	float minusy;	//��
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