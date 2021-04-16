#pragma once
//-------------------------------
//	ゲーム全体の共通の設定
/*
*	AT11B_36_yuta_yanagisawa
*
*/

#define FINAL_STAGE 3


enum GameScene {
	TITLE,
	MENUE,
	GAME,
	GAME_CLEAR,
	GAME_OVER,
	RESULT,
	FREE
};

extern GameScene Scene;//グローバル変数を外でも参照できるように

extern int stageNo;