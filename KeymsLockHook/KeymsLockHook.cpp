//
//		Win7 x64鼠标键盘锁（SDK）  by Thvoifar
//	https://bbs.pediy.com/thread-228522.htm
//
//


#include <tchar.h>
#include <windows.h>

// 全局变量和初始化

HHOOK g_hMouse = NULL;// 鼠标钩子句柄
HHOOK g_hLowlevelMouse = NULL; // 底层鼠标钩子句柄
HHOOK g_hKeyboard = NULL;// 键盘钩子句柄
HHOOK g_hLowlevelKeyboard = NULL;// 底层键盘钩子句柄
#pragma data_seg("SharedSec")// 设置共享节
HWND g_hWnd = NULL;// 传递调用进程的主窗口句柄
#pragma data_seg()


// 钩子过程函数体

LRESULT CALLBACK MouseProc(
	int code,       // hook code
	WPARAM wParam,  // virtual-key code
	LPARAM lParam   // keystroke-message information
	)
{
	return 1;
}

LRESULT CALLBACK LowLevelMouseProc(
	int nCode,
	WPARAM wParam,
	LPARAM lParam
	)
{
	return 1;
}

LRESULT CALLBACK KeyboardProc(
	int code,       // hook code
	WPARAM wParam,  // virtual-key code
	LPARAM lParam   // keystroke-message information
	)
{
	return 1;
}

LRESULT CALLBACK LowLevelKeyboardProc(
	int nCode,     // hook code
	WPARAM wParam, // message identifier
	LPARAM lParam  // pointer to structure with message data
	)
{
	PKBDLLHOOKSTRUCT pKey;
	pKey = (PKBDLLHOOKSTRUCT)lParam;
	// 屏蔽WIN CTRL ESC WIN+Tab Ctrl+ESC Ctrl+Shift+Esc Ctrl+Alt+Tab Ctrl+WIN+Tab WIN+U WIN+P WIN+X WIN+D WIN+E等键
	if (pKey->vkCode == VK_LWIN || pKey->vkCode == VK_RWIN || (GetAsyncKeyState(VK_CONTROL) & 0x8000) || (GetAsyncKeyState(VK_ESCAPE) & 0x8000))// 屏蔽WIN键，Ctrl+ESC组合键
	{
		return 1;
	}
	// 屏蔽Alt相关键 Alt+Tab 
	if (pKey->flags & LLKHF_ALTDOWN) // Alt按下
	{
		if ('Q' == pKey->vkCode) // Alt+Q退出
		{
			UnhookWindowsHookEx(g_hMouse);
			UnhookWindowsHookEx(g_hLowlevelMouse);
			UnhookWindowsHookEx(g_hKeyboard);
			UnhookWindowsHookEx(g_hLowlevelKeyboard);
			SendMessage(g_hWnd, WM_CLOSE, 0, 0);
		}
		return 1;
	}
	return CallNextHookEx(g_hLowlevelKeyboard, nCode, wParam, lParam);
}

// 钩子DLL中导出函数：

extern "C" _declspec(dllexport) BOOL __stdcall SetKeymsHook(HWND hwnd)
{
	g_hWnd = hwnd;
	HMODULE hModule = GetModuleHandle(_T("KeymsLockHook.dll")); //获取动态链接库KeymsLockHook.dll模块句柄
	g_hMouse = SetWindowsHookEx(WH_MOUSE, MouseProc, hModule, 0);
	if (NULL == g_hMouse)
	{
		MessageBox(NULL, _T("安装鼠标钩子出错1！"), _T("error"), 0);
		return FALSE;
	}
	g_hLowlevelMouse = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, hModule, 0);
	if (NULL == g_hLowlevelMouse)
	{
		MessageBox(NULL, _T("安装鼠标钩子出错2！"), _T("error"), 0);
		return FALSE;
	}
	g_hKeyboard = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, hModule, 0);
	if (NULL == g_hKeyboard)
	{
		MessageBox(NULL, _T("安装键盘钩子出错1！"), _T("error"), 0);
		return FALSE;
	}
	g_hLowlevelKeyboard = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hModule, 0);
	if (NULL == g_hLowlevelKeyboard)
	{
		MessageBox(NULL, _T("安装键盘钩子出错2！"), _T("error"), 0);
		return FALSE;
	}
	return TRUE;
}