#include "KeymsLock.h"
#include <tchar.h>

CKeymsLock::CKeymsLock()
{
	m_hookfun = NULL;
	HMODULE hDll = LoadLibrary(_T("KeymsLockHook.dll"));
	if (hDll)
	{
		m_hookfun = (HookFun)GetProcAddress(hDll, "SetKeymsHook");
	}
}

CKeymsLock::~CKeymsLock()
{
}

bool CKeymsLock::StartHook(HWND hWnd)
{
	if (m_hookfun == NULL)
		return false;
	if (!m_hookfun(hWnd))
		return FALSE; // - 安装鼠标键盘钩子
	return true;
}
