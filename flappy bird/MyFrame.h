#include <windows.h>
#include "resource.h"
#include <tchar.h>
#pragma once


#define DEFAULT 0

class MyFrame  
{
private:
	LPWSTR Title;
	UINT Time;
	UINT nWidth;    //something used in create the windows
	UINT nHeight;
	UINT nIcon;
	UINT nSmIcon;
protected:
	HINSTANCE MyInst;
	HWND MyWnd;
	HDC BKGDC;
public:
	UINT GetTime(){
		return Time;
	}
	BOOL SetWndText(LPWSTR title);
	BOOL SetSleepTime(UINT time);             //only use in In InitInstance();
	BOOL SetWndSize(UINT width, UINT hight);
	BOOL SetAppIcon(UINT icon, UINT smicon);
public:
	ATOM InitWndClass(WNDPROC WindProc,HINSTANCE hInstance);
	BOOL CreateWnd(HINSTANCE hInstance, int nCmdShow);
	int MessageLoopGame();
	virtual void Update() = 0;
	MyFrame();
	~MyFrame();
};