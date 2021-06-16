#include "FrameForClient.h"

FrameForClient myWindow;
//��ʱ��
VOID CALLBACK TimerProc(HWND   hwnd, UINT   message, UINT   iTimerID, DWORD   dwTime){
	myWindow.Update();
}

//���
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
//���
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	myWindow.InitInstance();//��ʼ��ʵ��
	myWindow.InitWndClass(WndProc, hInstance);//ע�ᴰ����
	if (!myWindow.CreateWnd(hInstance, nCmdShow)){//��ʼ������
		return 0;
	}
	myWindow.InitGenius();//��ʼ����Ϸ����
	myWindow.MessageLoopGame();//��Ϣѭ����ûɶ�ã�
	
	myWindow.Clear();//���
	return 0;
}

