#pragma once
#include <windows.h>
typedef BOOL(__stdcall *HookFun)(HWND hwnd);//定义函数指针

class CKeymsLock
{
public:
	CKeymsLock();
	~CKeymsLock();
	bool StartHook(HWND hWnd);
private:
	HookFun m_hookfun;
};

