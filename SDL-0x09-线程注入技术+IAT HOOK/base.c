
/*
* һ��MessageBox��Hookʾ��,����HookImportFunction
*/
#include <stdio.h>
#include <process.h>

#include "HookImportFunction.h"

////���Ӻ���
//int WINAPI MessageBoxCallBackProc(IN HWND hWnd, IN LPCSTR lpText, IN LPCSTR lpCaption, IN UINT uType);
////����MessageBoxA����ԭ��
//typedef int(WINAPI* MessageBoxNextHook_t)(HWND, LPCSTR, LPCSTR, UINT);
////����ԭ����ָ��
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

////��װ����
//void InstallHooks()
//{
//	HookAPI("user32.dll", "MessageBoxA", (PROC)MessageBoxCallBackProc, (PROC*)&MessageBoxNextHook);
//}
////ж�ع���
//void UninstallHooks()
//{
//	if (MessageBoxNextHook)
//		HookAPI("user32.dll", "MessageBoxA", (PROC)MessageBoxNextHook, NULL);
//}
////MessageBox�ص�����
//int WINAPI MessageBoxCallBackProc(IN HWND hWnd, IN LPCSTR lpText, IN LPCSTR lpCaption, IN UINT uType)
//{
//	return (*MessageBoxNextHook)(NULL, "���Ҹ�������", "���ǹ���", MB_OK | MB_ICONINFORMATION);
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