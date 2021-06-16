#pragma once
#include "CxImage/xImage.h"
#include <Windows.h>
#include"resource1.h"
#include <cstdlib>
#include <vector>
#include <string>
#include <string.h>
#include <fstream>
#include <algorithm>  
#include <mmsystem.h>
#include <dsound.h>
#include <mmreg.h>
using namespace std;
#pragma comment(lib,"Dsound.lib")
#pragma comment(lib,"Dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"cximaged.lib")

const int BIRD_WIDTH = 48;
const int BIRD_HIGHT = 48;
const int LOGO_BIRD_INIT_POSX = 120;
const int LOGO_BIRD_INIT_POSY = 176;
const float LOGO_BIRD_VY = 1.5;
const int LOGO_BIRD_UP_EDGE = 150;
const int LOGO_BIRD_DOWN_EDGE = 200;
const int LOGO_BUTTON_X = 86; 
const int LOGO_BUTTON_Y = 260;
const int LOGO_BUTTON_WIDTH = 116;
const int LOGO_BUTTON_HEIGHT = 70;
const int BEFORE_BIRD_UP_EDGE = 180;
const int BEFORE_BIRD_DOWN_EDGE = 200;
const int BEFORE_BIRD_INIT_POSX = 60;
const int BEFORE_BIRD_INIT_POSY = 190;
const float BEFORE_BIRD_VY = 0.5;
const int GROUND_HIGHT = 112;
const int GROUND_WIDTH = 336;
const int GROUND_POS_Y = 400;
const int BKGROUND_WIDTH = 288;
const int BKGROUND_HEIGHT = 512;
const int PIPE_INITPOS = 1000;
const int PIPE_WIDTH = 52;
const int PIPE_HIGHT = 320;
const int PIPE_V = 5;
const int PIPE_SPACE = 100;
const int PIPE_DIST = 160;
const int PIPE_CREATEPOS = 2 * PIPE_DIST + PIPE_WIDTH;
const int PIPE_HEAD_HIGHT = 30;
const float BIRD_FLY_V = -9;
const float GRAVITY = 0.9;
const int DESTORY_PIPE_X = -52;
const int EXPLAIN_WIDTH = 98;
const int EXPLAIN_HEIGHT = 114;
const int READY_WIDTH = 96;
const int READY_HEIGHT = 62;
const int FONT_WIDTH = 24;
const int FONT_HEIGHT = 44;
const int ID_FLY = 0;
const int ID_POINT = 2;
const int ID_DIE= 3;
const int ID_HIT = 1;
const int ID_WOO = 4;

class POINTF
{
public:
	float x;
	float y;

	//定义赋值运算符＝
	const	POINTF  & operator   =(const  POINTF &pt)
	{
		x = pt.x;
		y = pt.y;
		return *this;
	}

	//定义加法运算符＋
	const	POINTF  operator	+(const POINTF &pt)
	{
		POINTF ptTmp;
		ptTmp.x = x + pt.x;
		ptTmp.y = y + pt.y;
		return ptTmp;
	}

	//定义减法运算符-
	const 	POINTF  operator	-(const POINTF &pt)
	{
		POINTF ptTmp;
		ptTmp.x = x - pt.x;
		ptTmp.y = y - pt.y;
		return ptTmp;
	}
};