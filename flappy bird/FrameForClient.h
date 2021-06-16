#pragma once
#include "parameter.h"
#include "MyFrame.h"
#include "Game.h"
class FrameForClient :
	public MyFrame
{
	// Add the object on here...
	Game game;

public:
	FrameForClient();
	~FrameForClient();
	void Update(); 
	void InitInstance();
	void InitGenius();
	LRESULT wndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void Clear();
};

