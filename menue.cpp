/*
*	���j���[�쐬
*		B_36_���V�D��
* 
*/
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�w�b�_�[�C���N���[�h
#include<stdio.h>
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[����w�b�_�[�t�@�C���C���N���[�h
#define CONIOEX 
#include"conioex.h"
#include"key.h"
#include"main.h"
#include"title.h"
#include"dot.h"
#include"character.h"
#include"background.h"
//�[�[�[�[�[�[�[�[�[�[�[�[�u�[��
bool clear_once = false;	//clearDraw�֐����P�x�g�p���邽��
bool over_once=false;		//overDraw�֐����P�x�g�p���邽��
extern bool hantei;			//TitleUpdate�֐��������邽�߂̂�i�P��ڂ̑���j
extern bool chousei;		//TitleUpdate�֐��������邽�߂̂�i�Q��ڂ̑���j
//�[�[�[�[�[�[�[�[�[�[�[�[�[�\����
extern Character dot;		

//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�ȉ��֐�
void MenueUpdate()
{
	if (keyPush(PK_SP) || keyPush(PK_ENTER))
	{
		clrscr();//��ʏ���
		Scene = MENUE;//���j���[��
		return;
	}
}

void GameClearUpdate()
{
	if (keyPush(PK_ENTER) || keyPush(PK_SP))
	{
		Scene = TITLE;
		clrscr();
		stopsound(music[SHOURI]);
		//bool����
		dot.updated = true;
		hantei = false;
		chousei = false;
		return;
	}
}
void GameClearDraw() 
{
	if (clear_once == true)
	{//�P�񂾂��ʂ��悤�ɂ���
		return;
	}
	else {
		gotoxy(15, 1);
		dotDraw(GAMECLEAR, DISPLAY, 0, 0, 0, 0);
		gotoxy(15, 15);
		dotDraw(COMPRETE, DISPLAY, 0, 0, 0, 0);
		clear_once = true;
	}
}

void GameOverUpdate()
{
	if (keyPush(PK_ENTER) || keyPush(PK_SP))
	{
		Scene = TITLE;			//�V�[�����^�C�g����
		clrscr();
		stopsound(music[MGAMEOVER]);
		//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[bool����
		dot.updated = true;
		hantei = false;
		chousei = false;
		return;
	}
}

void GameOverDraw()
{//�P�񂾂��ʂ��悤�ɂ���
	if (over_once == true) {
		return;
	}
	else {
		char cell[2] = "/";	//���̊֐��Ŏg���p�̕ϐ�
		//bgSquare(int x, int y, int width, int height, char cell[2], int color, int bold);
		bgSquare(10, 4, 138, 40, cell, RED, 1);

		gotoxy(15, 5);
		//dotDraw(int int_value, int DOE_value, int _top, int _down, int _right, int _left);
		dotDraw(DOTGAMEOVER, DISPLAY, 5, 0, 0, 0);
		over_once = true;
	}
}