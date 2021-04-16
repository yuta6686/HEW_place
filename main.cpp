/*
*	AT11B_36_yuta_yanagisawa
*	HEW制作課題		「ジェット=チン・ア・ナ魚―スター」
*/

//ーーーーーーーーーーーーーインクルード
#include<stdio.h>
#include"conioex.h"
#include<string.h>
//ーーーーーーーーーーーーー自作ヘッダーインクルード
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
//ーーーーーーーーーーーーーグローバル変数
bool exitFlag = false;//ループエンド
int stageNo = 0;		//ステージナンバー

//ドットファイル用変数
char dot_file[][64] =
{
	{"群馬県.csv"},
	{"ジェット.csv"},
	{"ギョースター.csv"},
	{"空き缶.csv"},
	{"魚.csv"},
	{"gameover.csv"},
	{"sea.csv"},
	{"リリゾート.csv"},
	{"gameclear.csv"},
	{"ジェットコースター.csv"},
	{"comprete.csv"}
};
extern int dotFileMax = sizeof(dot_file) / sizeof(dot_file[0]);
//ドットファイルの数

//エフェクト用変数
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

//音楽用変数
char musicFile[][64] =
{
	{"シャイニングスター.mp3"},
	{"Stab-3.mp3"},
	{"炎.mp3"},
	{"水.mp3"},
	{"gameover.mp3"},
	{"tokyo.wav"},
	{"splash.wav"},
	{"決定、ボタン押下20.mp3"},
	{"shinein.mp3"},
	{"shouri.mp3"},
	{"「1,000（せん）」.mp3"},
	{"「200」.mp3"},
	{"「400」.mp3"},
	{"「600」.mp3"},
	{"「800」.mp3"},
	{"「km（キロメートル）」.mp3"},
	{"「もう一息です」.mp3"},
	{"「残り」.mp3"}
};
int music[MUSIC_LAST];
//ーーーーーーーーーーーーーenum
extern GameScene Scene = TITLE;
//ーーーーーーーーーーーーーprototype declaration
void Init();
void Deinit();
void Update();
void Draw();
void fileInit();
//ーーーーーーーーーーーーー構造体宣言
extern dotString print_enemy[];
extern dotString del_enemy[];

int main()
{
	//init processing
	Init();
	

	//	1/60秒計測用変数	variable to measure 1 int 60 seconds
	int lastTime;//最後に実行した時間
	int currentTime;//現在時間

	//分解能を設定
	timeBeginPeriod(1);//1/1000秒測れる設定	
	//timeGetTime()で偉える時間は１だったら１ミリ秒＝1.0×10~-3　秒

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

	//強制離脱
	if (keyPush(PK_ESC))
	{
		exitFlag = true;
		return;
	}

	//ゲームシーン遷移
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
	//ドットファイル読み込み
	for (int i = 0; i < dotFileMax; i++)
	{
		filedl(dot_file[i], i);
		dotCat(i, DISPLAY);//表示
		dotCat(i, DELL_DISPLAY);//消去
	}
	//エフェクトファイル読み込み
	for (int i = 0; i < EFF_FILE_MAX; i++)
		effdl(eff_file[i], i);
	//音楽ファイル読み込み
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