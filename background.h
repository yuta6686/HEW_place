#pragma once
//
//	AT11B_36_–öàV—D‘¾
//	”wŒi
#define BACKGROUND_X 3
#define BACKGROUND_Y 15
#include"character.h"

void bgPrint();
void bgDelete();
void BackGroundDraw();
void BackGroundUpdate();
void bgStatusUpdata(Character playerStatus);
void bgSquare(int x, int y, int width, int height, char cell[2], int color, int bold);
void bgdistance();