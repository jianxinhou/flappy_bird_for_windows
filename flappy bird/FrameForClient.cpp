#include "FrameForClient.h"
FrameForClient::FrameForClient(){
}

FrameForClient::~FrameForClient(){
}

void FrameForClient::InitInstance(){//Initialize Window
	/*
	//only use in In InitInstance();
	BOOL SetWndText(LPWSTR title);  if title = DEFAULT ,the title of window is default title
	BOOL SetSleepTime(UINT time);   if time = DEFAULT , the sleep time is 10 ms      
	BOOL SetWndSize(UINT width, UINT height); //if width(height) = DEFAULT , the width(height) will be default size
	BOOL SetAppIcon(UINT icon, UINT smicon); //if icon(smlicon) = DEFAULT , the icon(smlicon) will be default icon
	*/
	//To do something...
	SetAppIcon(IDI_ICON_BIRD,IDI_ICON_BIRD);
	SetWndText(_T(L"flappy bird"));
	SetWndSize(304, /*551*/510);
	SetSleepTime(20);//设置定时器时间
}

void FrameForClient::InitGenius(){//Initialize Genius
	game.InitDC(BKGDC,MyWnd);//调用游戏进程类中的初始化函数
}

void FrameForClient::Update(){//update the game 
	//To do something
	game.GameProcess(BKGDC);
	//int x = 0;
}



LRESULT FrameForClient::wndProc( UINT uMsg, WPARAM wParam, LPARAM lParam){//deal with message
	int x;
	int y;
	switch (uMsg){
		//Add message
	case WM_LBUTTONDOWN:
		switch (game.GameState){	//判定游戏状态
		case 0:						//游戏加载
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			if (x > LOGO_BUTTON_X&&x<LOGO_BUTTON_X + LOGO_BUTTON_WIDTH &&y>LOGO_BUTTON_Y&&y < LOGO_BUTTON_Y + LOGO_BUTTON_HEIGHT){
				game.GameState = 1;
				game.BeforeDataInit();
			}
			break;
		case 1:						//游戏说明
			game.DuringDataInit();
			game.GameState = 2;
			game.audio.Play(ID_FLY);
			break;
		case 2:						//游戏进程中
			game.pbird.SetV(0, BIRD_FLY_V);
			game.audio.Play(ID_FLY);
			break;
		case 3:						//游戏结算界面
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			if (game.afterflag){
				if (x > 86&&x<86 + LOGO_BUTTON_WIDTH &&y>290&&y < 290 + LOGO_BUTTON_HEIGHT){
					game.BeforeDataInit();
					game.GameState = 1;
				}
			}
			break;
		}
		break;
	default:
		return 0;
	}
	return 1;
}

void FrameForClient::Clear(){//delete the Genius

	//To do something

}