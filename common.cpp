//----------------------------
//共通の便利関数
//	AT11B_36_yuta_yanagisawa

#include<stdio.h>
#define CONIOEX 
#include"conioex.h"
#include"common.h"

#define DEBUG_PRINT

//内部座標を表示座標に変換する
void floatToInt(floatPosition f, intPosition* i)
{
	i->x = (int)(f.x + 0.5f);
	i->y = (int)(f.y + 0.5f);
}

void DebugPrint(const char* mes, float n)
{
#ifdef DEBUG_PRINT
	char m[256];
	sprintf(m, "%s=%f\n", mes, n);
	OutputDebugString((LPCSTR)m);
#endif
}
