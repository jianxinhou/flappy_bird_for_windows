#pragma once

#include "parameter.h"

class GameAudio
{
protected:
	LPDIRECTSOUND pDS;
	vector<LPDIRECTSOUNDBUFFER> pBuffer;
public:
	void Create(HWND hWnd);
	void AddAudio(LPTSTR musicpath);
	void Play(UINT);
	void Close();
	GameAudio();
	~GameAudio();
};

