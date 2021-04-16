#pragma once
//	AT11B_36_柳澤優太
//	ドットヘッダー
//定義色々

#define DOT_WIDTH_MAX 64	//ドット読み込みの幅
#define DOT_HEIGHT_MAX 64	//ドット表示のときの高さ
#define DOT_AREA_MAX 4160	//
#define DOT_MAX 9	//エネミーの数
#define ENEMY_MAX 30
#define EFF_FILE_MAX 16

#define CWHITE textcolor(WHITE)
#define CBLACK textcolor(BLACK)
#define CBLUE textcolor(BLUE)
#define CRED textcolor(RED)
#define CGREEN textcolor(GREEN)
#define CCYAN textcolor(CYAN)
#define CMAGENTA textcolor(MAGENTA)
#define CYELLOW textcolor(YELLOW)
#define CDARKGRAY textcolor(DARKGRAY)
#define CBROWN textcolor(BROWN)

#define BGWHITE textattr(0xFF)
#define BGBLACK textattr(0x00)
#define BGCYAN textattr(0x33)
#define BGRED textattr(0x44)
#define BGGREEN textattr(0x22)
#define BGYELLOW textattr(0xEE)
#define BGBROWN textattr(0x66)
#define BGMAGENTA textattr(0x55)
#define BGBLUE textattr(0x11)
#define BGRESET textattr(0x0F)

#define MUSIC_NON_LOOP 0
#define MUSIC_LOOP 1



enum Enemy {
	GUNMA,
	JET,
	GYO,
	AKIKAN,
	SAKANA,
	DOTGAMEOVER,
	SEA,
	SEA_RESORT,
	GAMECLEAR,
	JET_COARSTER,
	COMPRETE,
	ENEMY_LAST
};
extern Enemy name;


enum D_D {
	DISPLAY,
	DELL_DISPLAY 
};
extern D_D;

struct dotChar
{
	int dot[DOT_HEIGHT_MAX][DOT_WIDTH_MAX];
	int status;	//ダメージを食らった時とかに使う
};

struct dotCharinh {
	int inhdot[128][128];
	int status;
};

struct dotString {
	char dotC[DOT_AREA_MAX];
	int value;
};

struct dotRange {
	int top;
	int down;
	int right;
	int left;
};

void dotInit();
void filedl(char _dotfile[64],int int_value);
void dotCat(int int_value,int DOE_value);
void dotDraw(int int_value, int DOE_value,int _top,int _down,int _right,int _left);
void GameOverDisplay(int _int_value);
void Sea(int _int_value);
void SeaResort(int _int_value);
void GameClear(int _int_value);
void JetCoarster(int _int_value);
void Complete(int _int_value);