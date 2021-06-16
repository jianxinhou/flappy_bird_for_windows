#include "FrameForClient.h"

FrameForClient myWindow;
//定时器
VOID CALLBACK TimerProc(HWND   hwnd, UINT   message, UINT   iTimerID, DWORD   dwTime){
	myWindow.Update();
}

//入口
LRESULT CALLBACK WndProc(HWND hWnd,UINT message, WPARAM wParam, LPARAM lParam){
	if (myWindow.wndProc(message, wParam, lParam)){
		return 0;
	}
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message){
	case WM_CREATE:
		SetTimer(NULL, 1, myWindow.GetTime(), TimerProc);
		break;
	case WM_DESTROY:
		KillTimer(NULL, 1);
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
//入口
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	myWindow.InitInstance();//初始化实例
	myWindow.InitWndClass(WndProc, hInstance);//注册窗口类
	if (!myWindow.CreateWnd(hInstance, nCmdShow)){//初始化窗口
		return 0;
	}
	myWindow.InitGenius();//初始化游戏精灵
	myWindow.MessageLoopGame();//消息循环（没啥用）
	
	myWindow.Clear();//清除
	return 0;
}

