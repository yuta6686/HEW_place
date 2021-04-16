#pragma once
/*
*	AT11B_36_yuta_yanagisawa
*	キャラクターのやつ
*/

#include"common.h"

enum CharacterStatus
{
	Live,//生きてる
	Coll,//障害物に衝突している
	Dead,//死んでいる
};

struct Character
{
	floatPosition realPos;//座標
	floatPosition lastPos;//前回座標
	float width;
	float height;
	int color;//色

	float angle;	//角度
	float lastAngle;
	float speedx;//スピード
	float speedy;
	CharacterStatus status;//状態
	bool updated;//更新フラグ
	bool hit;//ヒットフラグ

	int HP;
	int kind;
	char mess[64];
	char mess2[64];
};

