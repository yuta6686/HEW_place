//�[�[�[�[�[�[�[�[�[�[�[�[�[
//�L�[���͊Ǘ�
//	AT11B_36_���V�D��
#include<stdio.h>
#define CONIOEX
#include"conioex.h"
#include"key.h"

static KeyStatus keyDic[] =
{
	{PK_ESC,false,false,false,0},
	{PM_LEFT,false,false,false,0},
	{PK_SP,false,false,false,0},
	{PK_ENTER,false,false,false,0},
	{PK_Q,false,false,false,0},
	{PM_CURX,false,false,false,0},
	{PM_CURY,false,false,false,0},
	{PK_W,false,false,false,0},
	{PK_S,false,false,false,0},
	{PK_A,false,false,false,0},
	{PK_D,false,false,false,0},
	{PK_1,false,false,false,0},
	{PK_R,false,false,false,0},
	{PK_O,false,false,false,0},
	{PK_C,false,false,false,0}
};
static int keyDicCount = sizeof(keyDic) / sizeof(KeyStatus);

void keyScan() {
	//�o�^�S�L�[�ɕt����
	for (int i = 0; i < keyDicCount; i++)
	{
		if (inport(keyDic[i].code))//������Ă���
		{
			keyDic[i].release = false;

			//�P��O�ɉ�����Ă����H
			if (keyDic[i].press){
				keyDic[i].push = false;
				keyDic[i].pressCount++;
			}
			else {
				//�O�񉟂���Ȃ������������ꂽ�u��
				keyDic[i].push = true;
				keyDic[i].press = true;
				keyDic[i].release = false;
			}
		}
		else {//�L�[��������Ă��Ȃ�
			keyDic[i].push = false;
			if (keyDic[i].press){//�P��O�ɉ�����Ă����H
				keyDic[i].release = true;
				keyDic[i].press = false;
			}
			else {
				keyDic[i].release = false;
				keyDic[i].pressCount = 0;
			}
		}
	}
}

bool keyPush(int keyCode)
{
	int index = getIndexOfKeyCode(keyCode);
	if (index >= 0)
	{
		return keyDic[index].push;
	}
	return false;
}

bool keyPress(int keyCode)
{
	int index = getIndexOfKeyCode(keyCode);
	if (index >= 0)
	{
		return keyDic[index].press;
	}
	return false;
}

int keyPressCount(int keyCode)
{
	int index = getIndexOfKeyCode(keyCode);
	if (index >= 0)
	{
		return keyDic[index].pressCount;
	}
	return 0;
}

void keyCountReset(int keyCode)
{
	int index = getIndexOfKeyCode(keyCode);

	if (index >= 0) {

		keyDic[index].pressCount=0;
	}

}

bool keyRelease(int keyCode)
{
	int index = getIndexOfKeyCode(keyCode);
	if (index >= 0)
	{
		return keyDic[index].release;
	}
	return false;
}

int getIndexOfKeyCode(int keyCode)
{
	//��̕ϐ�keyDic�ɃL�[���o�^����Ă���O��
	//�P���ɑS���T���B�x�^�ȕ��@
	for (int i = 0; i < keyDicCount; i++)
	{
		if (keyDic[i].code == keyCode)
		{
			return i;
		}
	}
	
	//printf("�L�[�R�[�h�w��~�X=%d\n",keyCode);
	return -1;	//������Ȃ�������
	//-1�Ƃ��G���[�I�Ȑ��l��Ԃ�
}