//ーーーーーーーーーーーーー
//キー入力管理
//	AT11B_36_柳澤優太
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
	//登録全キーに付いて
	for (int i = 0; i < keyDicCount; i++)
	{
		if (inport(keyDic[i].code))//押されている
		{
			keyDic[i].release = false;

			//１回前に押されていた？
			if (keyDic[i].press){
				keyDic[i].push = false;
				keyDic[i].pressCount++;
			}
			else {
				//前回押されなかったが押された瞬間
				keyDic[i].push = true;
				keyDic[i].press = true;
				keyDic[i].release = false;
			}
		}
		else {//キーが押されていない
			keyDic[i].push = false;
			if (keyDic[i].press){//１回前に押されていた？
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
	//上の変数keyDicにキーが登録されている前提
	//単純に全部探す。ベタな方法
	for (int i = 0; i < keyDicCount; i++)
	{
		if (keyDic[i].code == keyCode)
		{
			return i;
		}
	}
	
	//printf("キーコード指定ミス=%d\n",keyCode);
	return -1;	//見つからなかったら
	//-1とかエラー的な数値を返す
}