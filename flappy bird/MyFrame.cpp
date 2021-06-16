#include "MyFrame.h"

extern LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

MyFrame::MyFrame(){   
	Time = 10;
	MyWnd = NULL;
	MyInst = NULL;
	Title = L"MyGame";
	nWidth = 1000;
	nHeight = 1000;
	nIcon = IDI_ICON;
	nSmIcon = IDI_SMAICON;
}

MyFrame::~MyFrame()
{
	ReleaseDC(MyWnd, BKGDC);
}

BOOL MyFrame::SetWndText(LPWSTR title){
	if (MyInst == NULL){
		if (title != DEFAULT ){
			Title = title;
		}
		return true;
	}
	else{
		return false;
	}
}

BOOL MyFrame::SetWndSize(UINT width, UINT height){
	if (MyInst == NULL){
		if (width != DEFAULT ){
			nWidth = width;
		}
		if (height != DEFAULT){
			nHeight = height;
		}
		return true;
	}
	else{
		return false;
	}
}

BOOL MyFrame::SetSleepTime(UINT time){
	if (MyInst == NULL){
		if (time != DEFAULT){
			Time = time;
		}
		return true;
	}
	else{
		return false;
	}
}

BOOL MyFrame::SetAppIcon(UINT icon, UINT smlicon){
	if (MyInst == NULL){
		if (icon != DEFAULT){
			nIcon = icon;
		}
		if (smlicon != DEFAULT){
			nSmIcon = smlicon;
		}
		return true;
	}
	else{
		return false;
	}
}

ATOM MyFrame::InitWndClass(WNDPROC WindProc, HINSTANCE hInstance){
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(nIcon));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_BTNSHADOW - 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = _T("MyApp");
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(nSmIcon));

	return RegisterClassEx(&wcex);
}

BOOL MyFrame::CreateWnd(HINSTANCE hInstance, int nCmdShow){
	MyInst = hInstance;

	int screenW = GetSystemMetrics(SM_CXSCREEN);
	int screenH = GetSystemMetrics(SM_CYSCREEN);

	MyWnd = CreateWindowW(_T(L"MyApp"),
		Title,
		WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
		(screenW - nWidth) / 2, (screenH - nHeight) / 2,
		nWidth, nHeight,
		NULL,
		NULL,
		hInstance,
		NULL);
	if (!MyWnd){
		return FALSE;
	}

	ShowWindow(MyWnd, nCmdShow);
	UpdateWindow(MyWnd);
	BKGDC = GetDC(MyWnd);
	return TRUE;
}

int MyFrame::MessageLoopGame(){
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
