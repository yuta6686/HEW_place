/*
*	AT11B_36_yuta_yanagisawa
*	HEW����ۑ�		�u�W�F�b�g=�`���E�A�E�i���\�X�^�[�v
*/

//�[�[�[�[�[�[�[�[�[�[�[�[�[�C���N���[�h
#include<stdio.h>
#include"conioex.h"
#include<string.h>
//�[�[�[�[�[�[�[�[�[�[�[�[�[����w�b�_�[�C���N���[�h
#include"main.h"
#include"key.h"
#include"character.h"
#include"title.h"
#include"common.h"
#include"dot.h"
#include"player.h"
#include"enemy.h"
#include"background.h"
#include"eff.h"
#include"menue.h"
//�[�[�[�[�[�[�[�[�[�[�[�[�[�O���[�o���ϐ�
bool exitFlag = false;//���[�v�G���h
int stageNo = 0;		//�X�e�[�W�i���o�[

//�h�b�g�t�@�C���p�ϐ�
char dot_file[][64] =
{
	{"�Q�n��.csv"},
	{"�W�F�b�g.csv"},
	{"�M���[�X�^�[.csv"},
	{"�󂫊�.csv"},
	{"��.csv"},
	{"gameover.csv"},
	{"sea.csv"},
	{"�����]�[�g.csv"},
	{"gameclear.csv"},
	{"�W�F�b�g�R�[�X�^�[.csv"},
	{"comprete.csv"}
};
extern int dotFileMax = sizeof(dot_file) / sizeof(dot_file[0]);
//�h�b�g�t�@�C���̐�

//�G�t�F�N�g�p�ϐ�
char eff_file[EFF_FILE_MAX][64] =
{
	{"eff1.csv"},
	{"ff2.csv"},
	{"ff3.csv"},
	{"ff4.csv"},
	{"ff5.csv"},
	{"ff6.csv"},
	{"ff7.csv"},
	{"ff8.csv"},
	{"ff9.csv"},
	{"ff10.csv"},
	{"ff11.csv"},
	{"ff12.csv"},
	{"ff13.csv"},
	{"ff14.csv"},
	{"ff15.csv"},
	{"ff16.csv"},
};

//���y�p�ϐ�
char musicFile[][64] =
{
	{"�V���C�j���O�X�^�[.mp3"},
	{"Stab-3.mp3"},
	{"��.mp3"},
	{"��.mp3"},
	{"gameover.mp3"},
	{"tokyo.wav"},
	{"splash.wav"},
	{"����A�{�^������20.mp3"},
	{"shinein.mp3"},
	{"shouri.mp3"},
	{"�u1,000�i����j�v.mp3"},
	{"�u200�v.mp3"},
	{"�u400�v.mp3"},
	{"�u600�v.mp3"},
	{"�u800�v.mp3"},
	{"�ukm�i�L�����[�g���j�v.mp3"},
	{"�u�����ꑧ�ł��v.mp3"},
	{"�u�c��v.mp3"}
};
int music[MUSIC_LAST];
//�[�[�[�[�[�[�[�[�[�[�[�[�[enum
extern GameScene Scene = TITLE;
//�[�[�[�[�[�[�[�[�[�[�[�[�[prototype declaration
void Init();
void Deinit();
void Update();
void Draw();
void fileInit();
//�[�[�[�[�[�[�[�[�[�[�[�[�[�\���̐錾
extern dotString print_enemy[];
extern dotString del_enemy[];

int main()
{
	//init processing
	Init();
	

	//	1/60�b�v���p�ϐ�	variable to measure 1 int 60 seconds
	int lastTime;//�Ō�Ɏ��s��������
	int currentTime;//���ݎ���

	//����\��ݒ�
	timeBeginPeriod(1);//1/1000�b�����ݒ�	
	//timeGetTime()�ň̂��鎞�Ԃ͂P��������P�~���b��1.0�~10~-3�@�b

	lastTime = timeGetTime();
	currentTime = 0;

	//loop of main game.
	while (!exitFlag)
	{
		currentTime = timeGetTime();

		if ((currentTime - lastTime) >= (1000 / 60))
		{
			//	1/60 seconds have passed.
			lastTime = currentTime;

			//update processing
			Update();
			//draw processing
			Draw();
		}
	}
	// finish the game.
	Deinit();
}

void Init()
{
	fileInit();
	dotInit();
	Titleinit();
	PlayerInit();
	EnemyInit();
	char buff[2] = "o";
	//void bgSquare(int x, int y,int width, int height,char cell[2],int color,int bold )
	bgSquare(14, 1, 54, 12, buff, YELLOW, 1);
	bgSquare(15, 2, 52, 10, buff, RED, 1);
	
}

void Deinit()
{
	for (int i = 0; i < MUSIC_LAST; i++)
	{
		closesound(music[i]);
	}
}

void Update()
{
	keyScan();

	//�������E
	if (keyPush(PK_ESC))
	{
		exitFlag = true;
		return;
	}

	//�Q�[���V�[���J��
	switch (Scene)
	{
	case TITLE:
		TitleUpdate();
		break;
	case MENUE:
		break;
	case GAME:
		BackGroundUpdate();
		PlayerUpdate();
		EnemyUpdate();
		break;
	case GAME_CLEAR:
		GameClearUpdate();
		break;
	case GAME_OVER:
		GameOverUpdate();
		break;
	case RESULT:
		break;
	case FREE:
		PlayerUpdate();
		break;
	}
}

void Draw()
{
	switch (Scene)
	{
	case TITLE:
		TitleDraw();
		break;
	case MENUE:
		break;
	case GAME:
		BackGroundDraw();
		PlayerDraw();
		EnemyDraw();
		break;
	case GAME_CLEAR:
		GameClearDraw();
		break;
	case GAME_OVER:
		GameOverDraw();
		break;
	case RESULT:
		break;
	case FREE:
		PlayerDraw();
		break;
	}
}

void fileInit()
{	
	//�h�b�g�t�@�C���ǂݍ���
	for (int i = 0; i < dotFileMax; i++)
	{
		filedl(dot_file[i], i);
		dotCat(i, DISPLAY);//�\��
		dotCat(i, DELL_DISPLAY);//����
	}
	//�G�t�F�N�g�t�@�C���ǂݍ���
	for (int i = 0; i < EFF_FILE_MAX; i++)
		effdl(eff_file[i], i);
	//���y�t�@�C���ǂݍ���
	for (int i = 0; i < MUSIC_LAST; i++)
	{
		music[i] = opensound(musicFile[i]);
		switch (i)
		{
		case SHAINING:
			setvolume(music[i], 50);
			break;
		case STAB:
			setvolume(music[i], 50);
			break;
		case FRAME:
			setvolume(music[i], 50);
			break;
		case WATER:
			setvolume(music[i], 50);
			break;
		case MGAMEOVER:
			setvolume(music[i], 50);
			break;
		case TOKYO:
			setvolume(music[TOKYO], 10);
			break;
		case SPLASH:
			setvolume(music[i], 50);
			break;
		case KETTEI:
			setvolume(music[i], 50);
			break;
		case TASSEI:
			setvolume(music[i], 50);
			break;
		case SHOURI:
			setvolume(music[i], 50);
			break;
		case SEN:
		case NIHYAKU:
		case YONHYAKU:
		case ROPPYAKU:
		case HAPPYAKU:
		case KIRO:
		case MOUHITO:
		case NOKORI:
			setvolume(music[i], 70);
			break;
		default:
			break;
		}	
	}
}