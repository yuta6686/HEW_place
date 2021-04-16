#pragma once
/*
*	AT11B_36_yuta_yanagisawa
*
*/
#define PI 3.1415926535897932
#define LIMIT_RIGHT 155.0f
#define LIMIT_LEFT 40.0f
#define LIMIT_UP 1.0f
#define LIMIT_DOWN 40.0f

#define MAX_RIGHT 159.0f

#define LIMIT_ANGLE_RIGHT (PI*2)
#define LIMIT_ANGLE_LEFT  (PI)

#define Y_HOSEI_RATIO 0.5f

enum Music {
	SHAINING,
	STAB,
	FRAME,
	WATER,
	MGAMEOVER,
	TOKYO,
	SPLASH,
	KETTEI,
	TASSEI,
	SHOURI,
	SEN,
	NIHYAKU,
	YONHYAKU,
	ROPPYAKU,
	HAPPYAKU,
	KIRO,
	MOUHITO,
	NOKORI,
	MUSIC_LAST
};
extern Music;

extern int music[MUSIC_LAST];

struct floatPosition {
	float x;
	float y;
};

struct intPosition {
	int x;
	int y;
};



void floatToInt(floatPosition f, intPosition* i);
void DebugPrint(const char* mes, float n);




