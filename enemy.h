#pragma once
#include"common.h"

//---------------------------
//öāVDū
//GĖ

struct rangeData {
	int x;
	int y;
};

enum Status {
	STATUS_ENEMY,	//0
	STATUS_WALL,	//1
	STATUS_GOAL,		//2
	STATUS_ENEMY_SIDE	//3	
};

void EnemyInit();
void EnemyUpdate();
void EnemyDraw();
bool EnemyHitCheck(floatPosition pos);
void EnemyProt(int n);
void EnemyErase(int n);
//void EnemyKill();