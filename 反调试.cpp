// ConsoleApplication4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <Winternl.h>
DWORD Scratch;
EXCEPTION_DISPOSITION __cdecl _except_handler1
(
	struct _EXCEPION_RECORD *ExceptionRecord,
	void* EstablisherFrame,
	struct _CONTEXT* ContextRecord,
	void* DispatcherContext
)
{
	printf("Welcome To Exception Handler. \n");
	ContextRecord->Eax = (DWORD)&Scratch;

	return ExceptionContinueExecution;

}
#define ThreadHideFromDebugger 17
typedef DWORD(WINAPI *ZW_SET_INFOMATION_THREAD)(HANDLE, DWORD, PVOID,ULONG);
//定义一种返回值为DWORD,参数为(HANDLE, DWORD, PVOID,ULONG)的函数类型,命名为ZW_SET_INFOMATION_THREAD.

VOID DisableDebugEvent(VOID)
{
	HINSTANCE hModule;
	ZW_SET_INFOMATION_THREAD ZwSetInformationThread;//声明一个ZW_SET_INFOMATION_THREAD类型的函数,命名为ZwSetInformationThread
	LPCWSTR pModuleName = L"ntdll";
	hModule = GetModuleHandle(pModuleName);
	ZwSetInformationThread = (ZW_SET_INFOMATION_THREAD)GetProcAddress(hModule,"ZwSetInformationThread");
	ZwSetInformationThread(GetCurrentThread(),ThreadHideFromDebugger, 0, 0);
}
char* StrcpyEx(char* Destination, const char* Source)
{
	__try
	{
		strcpy_s(Destination,5,Source);
	}

	__except (EXCEPTION_EXECUTE_HANDLER)
	{

		printf("Input Error.");

     }

	return Destination;
	

}
LPVOID GetHeap(void)
{
	return HeapAlloc(GetProcessHeap(), 0, 0x100);
}
int main()
{
	VOID DisableDebugEvent(VOID);
	DisableDebugEvent();
	LPVOID GetHeap(void);
	DWORD NtGlobalFlags;
	__asm
	{
		mov eax, FS:[0x30];
		mov eax, [eax + 0x68];
		mov NtGlobalFlags,eax
	}
	DWORD Heap[0x100] = { 0 };
	PDWORD pHeapData=(PDWORD)GetHeap();

	for (int i = 0; i <= 0x100; i++)
	{
		Heap[i] = *pHeapData;
		pHeapData++;
		printf("%08X \n", Heap[i]);
	}
	CONTEXT Context;
	printf("%d", NtGlobalFlags);
    printf("%08X \n",Context.Eax);
	printf("%08X \n", Context.Ebx);
	printf("%08X \n", Context.Ebp);
	printf("%08X \n", Context.Esp);
	printf("%08X \n", Context.Esi);



	system("pause");
	printf("Exit From Debugger. \n");
	system("pause");
    return 0;
}

