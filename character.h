#pragma once
/*
*	AT11B_36_yuta_yanagisawa
*	�L�����N�^�[�̂��
*/

#include"common.h"

enum CharacterStatus
{
	Live,//�����Ă�
	Coll,//��Q���ɏՓ˂��Ă���
	Dead,//����ł���
};

struct Character
{
	floatPosition realPos;//���W
	floatPosition lastPos;//�O����W
	float width;
	float height;
	int color;//�F

	float angle;	//�p�x
	float lastAngle;
	float speedx;//�X�s�[�h
	float speedy;
	CharacterStatus status;//���
	bool updated;//�X�V�t���O
	bool hit;//�q�b�g�t���O

	int HP;
	int kind;
	char mess[64];
	char mess2[64];
};

