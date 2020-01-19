
/*
* 一个MessageBox的Hook示例,基于HookImportFunction
*/
#include <stdio.h>
#include <process.h>

#include "HookImportFunction.h"

////钩子函数
//int WINAPI MessageBoxCallBackProc(IN HWND hWnd, IN LPCSTR lpText, IN LPCSTR lpCaption, IN UINT uType);
////定义MessageBoxA函数原型
//typedef int(WINAPI* MessageBoxNextHook_t)(HWND, LPCSTR, LPCSTR, UINT);
////保存原函数指针
//MessageBoxNextHook_t MessageBoxNextHook = NULL;

int WINAPI WriteFileCallBackProc(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);
typedef int(WINAPI* WriteFileNextHook_t)(HANDLE, LPCVOID, DWORD, LPDWORD, LPOVERLAPPED);
WriteFileNextHook_t WriteFileNextHook = NULL;

void InstallHooks(void);
void UninstallHooks(void);

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		InstallHooks();
		break;

	case DLL_PROCESS_DETACH:
		UninstallHooks();
		break;

	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;
	}

	return TRUE;
}

////安装钩子
//void InstallHooks()
//{
//	HookAPI("user32.dll", "MessageBoxA", (PROC)MessageBoxCallBackProc, (PROC*)&MessageBoxNextHook);
//}
////卸载钩子
//void UninstallHooks()
//{
//	if (MessageBoxNextHook)
//		HookAPI("user32.dll", "MessageBoxA", (PROC)MessageBoxNextHook, NULL);
//}
////MessageBox回调函数
//int WINAPI MessageBoxCallBackProc(IN HWND hWnd, IN LPCSTR lpText, IN LPCSTR lpCaption, IN UINT uType)
//{
//	return (*MessageBoxNextHook)(NULL, "被我给逮到了", "我是钩子", MB_OK | MB_ICONINFORMATION);
//}


void InstallHooks()
{
	HookAPI("KERNELBASE.dll", "WriteFile", (PROC)WriteFileCallBackProc, (PROC*)&WriteFileNextHook);
}
void UninstallHooks()
{
	if (WriteFileNextHook)
		HookAPI("KERNELBASE.dll", "WriteFile", (PROC)WriteFileNextHook, NULL);
}
int WINAPI WriteFileCallBackProc(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped)
{
	return (*WriteFileNextHook)(hFile, "hehehe", nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
}