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