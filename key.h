#pragma once
/*
*	AT11B_36_yuta_yanagisawa
*		�L�[����
*/

struct KeyStatus
{
	int code;
	bool push;
	bool press;
	bool release;
	int pressCount;
};

//	1/60�b���ƂɂP��Ă�
//	�o�^�����L�[���X�L�������Ċe�ϐ��ɓ����

void keyScan();
bool keyPush(int keyCode);
bool keyPress(int keyCode);
int keyPressCount(int keyCode);
void keyCountReset(int keyCode);
bool keyRelease(int keyCode);
int getIndexOfKeyCode(int keyCode);

