/*
	20170613 修复消息循环中到值CPU一直占用25%的


*/

#include "Win32App.h"
#include <tchar.h>

#define WINDOW_CLASS    _T("Win32")
#define WINDOW_NAME     _T("Win32App")
#define WINDOW_WIDTH    640
#define WINDOW_HEIGHT   480


CWin32App	*g_pApp=NULL;

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return g_pApp->WinProc(hWnd,msg,wParam,lParam);
}

CWin32App::CWin32App(void)
{
	m_hWnd = NULL;
	g_pApp= this;
}

CWin32App::~CWin32App(void)
{
}

BOOL CWin32App::Run()
{
	// Show the window
	ShowWindow(m_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(m_hWnd);

	// Enter the message loop
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	Shutdown();
	return 0;
}

void CWin32App::Shutdown()
{

}

BOOL CWin32App::Create(HINSTANCE hinst)
{
	// Register the window class
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		WINDOW_CLASS, NULL };
	RegisterClassEx(&wc);

	// Create the application's window
	m_hWnd = CreateWindow(WINDOW_CLASS, WINDOW_NAME, WS_OVERLAPPEDWINDOW,
		100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, GetDesktopWindow(),
		NULL, wc.hInstance, NULL);

	BOOL bRet = IsWindow(m_hWnd);
	return bRet;
}

LRESULT CWin32App::OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	RECT rtClient = { 0 };
	GetClientRect(hWnd, &rtClient);
	HBRUSH br = CreateSolidBrush(RGB(192, 192, 192));
	FillRect(hdc, &rtClient, br);
	TCHAR *pBuf = _T("LeftClick Start Hook\n  Alt+Q to Exit Hook!");
	TextOut(hdc, 150, 150, pBuf, _tcslen(pBuf));
	DeleteObject(br);
	EndPaint(hWnd, &ps);
	return 0;
}


typedef BOOL(__stdcall *HookFun)(HWND hwnd);//定义函数指针

LRESULT WINAPI CWin32App::WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
	{
	  m_KeyLock.StartHook(hWnd);
	}
		break;
	case WM_PAINT:
		OnPaint(hWnd);
		break;
	case WM_KEYUP:
		if(wParam == VK_ESCAPE) PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}