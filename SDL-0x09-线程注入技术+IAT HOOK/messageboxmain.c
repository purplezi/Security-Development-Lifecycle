#include <Windows.h>

LONG IATHook
(
	__in void* pImageBase ,
	__in_opt char* pszImportDllName ,
	__in char* pszRoutineName ,
	__in void* pFakeRoutine ,
	__out HANDLE* Param_phHook
);

LONG UnIATHook( __in HANDLE hHook );

void* GetIATHookOrign( __in HANDLE hHook );

typedef int (__stdcall *LPFN_MessageBoxA)( __in_opt HWND hWnd , __in_opt char* lpText , __in_opt char* lpCaption , __in UINT uType);

HANDLE g_hHook_MessageBoxA = NULL;
//////////////////////////////////////////////////////////////////////////

// ����fake messagebox
int __stdcall Fake_MessageBoxA( __in_opt HWND hWnd , __in_opt char* lpText , __in_opt char* lpCaption , __in UINT uType)
{
	LPFN_MessageBoxA fnOrigin = (LPFN_MessageBoxA)GetIATHookOrign(g_hHook_MessageBoxA);
	// ����Ϣtest��Ϊhook
	return fnOrigin(hWnd , "hook" , lpCaption , uType);
}

int __cdecl wmain(int nArgc, WCHAR** Argv)
{
	do 
	{
		UNREFERENCED_PARAMETER(nArgc);
		UNREFERENCED_PARAMETER(Argv);
		// ����IATHook
		IATHook(
			GetModuleHandleW(NULL) ,
			"user32.dll" , 
			"MessageBoxA" ,
			Fake_MessageBoxA ,
			&g_hHook_MessageBoxA
		);
		// ���ñ�Hook���MessageBoxA����
		MessageBoxA(NULL , "test" , "caption" , 0);
		// ȡ��Hook
		UnIATHook( g_hHook_MessageBoxA);
		// ����������MessageBoxA����
		MessageBoxA(NULL , "test" , "caption" , 0);
	
	} while (FALSE);
	
	return 0;
}

