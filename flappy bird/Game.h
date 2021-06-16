#pragma once
#include "parameter.h"
#include "Genius.h"
#include "GamePhysics.h"
#include "GameAudio.h"

class Game
{
protected:
	Genius num[10];//��������
	Genius Medal[4];//
	Genius gamelogo;//logo
	Genius title;//����
	Genius begin;//��ʼ
	UINT logotime;
protected:
	Pipe pipes;//�ܵ�
	GamePhysics ppipes[2];//�ܵ�������
	bool IsPass[2];
protected:
	Genius bird[3];//������ͬ��ɫ����
	float birdangle;//��ĽǶ�
	UINT BirdState;//�ĸ���ɫ����
protected:
	Genius bkground[2];//��������һ�����죬һ������
	Genius ground;//��
	Genius ready;//
	Genius explain;
	Genius over;//����
	Genius score;//����
	GamePhysics pscore;
	GamePhysics pover;
	GamePhysics pground;//��������
	HDC bufferDC;//������
	HBITMAP bufferBtMap;
	UINT GameScore;//����
	char ScoreTemp[10];
	char RecordTemp[10];
	string Score;//����
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

