#pragma once
//-------------------------------
//	�Q�[���S�̂̋��ʂ̐ݒ�
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

extern GameScene Scene;//�O���[�o���ϐ����O�ł��Q�Ƃł���悤��

extern int stageNo;