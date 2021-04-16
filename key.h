#pragma once
/*
*	AT11B_36_yuta_yanagisawa
*		キー入力
*/

struct KeyStatus
{
	int code;
	bool push;
	bool press;
	bool release;
	int pressCount;
};

//	1/60秒ごとに１回呼ぶ
//	登録したキーをスキャンして各変数に入れる

void keyScan();
bool keyPush(int keyCode);
bool keyPress(int keyCode);
int keyPressCount(int keyCode);
void keyCountReset(int keyCode);
bool keyRelease(int keyCode);
int getIndexOfKeyCode(int keyCode);

