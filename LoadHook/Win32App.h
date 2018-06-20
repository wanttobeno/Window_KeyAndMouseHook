#pragma once
#include <Windows.h>

#include "KeymsLock.h"

class CWin32App
{
public:
	CWin32App(void);
	~CWin32App(void);
public:
	BOOL Create(HINSTANCE hinst);
	BOOL Run();
	BOOL InitializeObjects();
	void Shutdown();
	LRESULT OnPaint(HWND hWnd);
	LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
protected:
	CKeymsLock		m_KeyLock;
private:
	HWND		m_hWnd;
};

#ifdef ZY_TEST
#include <windows.h>
#include <gdiplus.h>
#include "Win32App.h"
using namespace Gdiplus;
#pragma comment(lib,"gdiplus.lib")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	int nRet = -1;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	CWin32App winApp;
	if (winApp.Create(hInstance))
		nRet = winApp.Run();
	GdiplusShutdown(gdiplusToken);
	return nRet;
}
#endif // ZY_TEST