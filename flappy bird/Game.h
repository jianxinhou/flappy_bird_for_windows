#pragma once
#include "parameter.h"
#include "Genius.h"
#include "GamePhysics.h"
#include "GameAudio.h"

class Game
{
protected:
	Genius num[10];//分数数字
	Genius Medal[4];//
	Genius gamelogo;//logo
	Genius title;//标题
	Genius begin;//开始
	UINT logotime;
protected:
	Pipe pipes;//管道
	GamePhysics ppipes[2];//管道物理部分
	bool IsPass[2];
protected:
	Genius bird[3];//三个不同颜色的鸟
	float birdangle;//鸟的角度
	UINT BirdState;//哪个颜色的鸟
protected:
	Genius bkground[2];//两个背景一个白天，一个晚上
	Genius ground;//第
	Genius ready;//
	Genius explain;
	Genius over;//结束
	Genius score;//分数
	GamePhysics pscore;
	GamePhysics pover;
	GamePhysics pground;//地面物理
	HDC bufferDC;//缓冲区
	HBITMAP bufferBtMap;
	UINT GameScore;//分数
	char ScoreTemp[10];
	char RecordTemp[10];
	string Score;//分数
	UINT DayState;
	UINT isScore[2];
	
public:
	GamePhysics pbird;
	UINT GameState;
	bool afterflag;
	HFONT font;
	vector<UINT> Record;
	UINT medal;
	GameAudio audio;
public:
	void BeforeDataInit();
	void DuringDataInit();
	void AfterDataInit();
	void LogoDataInit();
	void InitDC(HDC goalDC,HWND hwnd);
	void GameLogo();
	void BeforeGame();
	void DuringGame();
	void AfterGame();
	void GameProcess(HDC goalDC);
	Game();
	~Game();
};

