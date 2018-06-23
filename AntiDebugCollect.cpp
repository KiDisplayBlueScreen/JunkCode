#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <excpt.h>
#include <string.h>
#include "FuncDef.h";
#pragma comment(linker,"/INCLUDE:__tls_used")
using namespace std;
#pragma data_seg(".CRT$XLB")
PIMAGE_TLS_CALLBACK P_Thread_CallBack=TLS_CALLBACK;
#pragma data_seg()

int main()
{

	//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)AntiDebugThread, 0, 0, 0);

	if (ZwQueryInformationProcessDetect()!=0||NtGlobalFlagsDetect()!=0)
	{  
		DebuggerFound();
	}
	
	 if (HeapDetect()!=0)
	 { 
		 DebuggerFound();
	 }
	 CloseHandleDetect();
	 APIBreakPointDetect(L"kernel32","VirtualAlloc");

	 if (NtQueryObjectDetect() != 0)
	 {
		 MessageBoxA(0, "NtQueryObject Detect!", "Tips", MB_OK);
	  }
	 if (CSRSSDetect() != 0)
	 {
		 MessageBoxA(0, "CSRSSDetect Detect!", "Tips", MB_OK);
	 }

		PAUSE;
    return 0;
}
VOID DebuggerFound()
{
	MessageBoxA(0, "Debugger Found!", "Tips", MB_OK);
}


VOID NTAPI TLS_CALLBACK(PVOID Handle, DWORD Reason, PVOID Reserve)
{

	DWORD DebuggerFound;
	MessageBoxA(0, "TLS_CALLBACK!", "Tips", MB_OK);
	__asm
	{
		MOV EAX, FS:[0x30];
		MOVZX EAX, [EAX + 2];
	    MOV DebuggerFound,EAX
	}
	if (DebuggerFound == 1)
		exit(0);
}

DWORD GetProcAddressByName(LPCTSTR lpModuleName, LPCSTR ProcName)
{
	HMODULE hModule = GetModuleHandle(lpModuleName);
	if (hModule == 0)
	{
		hModule = LoadLibrary(lpModuleName);
		if (hModule == 0) return 0;
	}
	DWORD ProcAddress = (DWORD)GetProcAddress(hModule, ProcName);
	return  ProcAddress;

}



VOID IsDebuggerPresentAsm()
{
	__asm
	{
		MOV EAX, FS:[0x30];
		MOVZX EAX, [EAX + 2];
		RETN
	}
}
BOOL CheckRemoteDebug()
{
	PBOOL pDebuggerPresent;
	CheckRemoteDebuggerPresent((HANDLE)-1, pDebuggerPresent);
	return *pDebuggerPresent;
}
BOOL ZwQueryInformationProcessDetect()
{
	DWORD ZwQueryInformationProcess = GetProcAddressByName(L"ntdll.dll", "ZwQueryInformationProcess");
	DWORD ProcessDebugPort=0;
	DWORD ProcessDebugObjectHandle=0;
	DWORD ProcessDebugFlags=0;
	DWORD DReturnLength;
	PULONG ReturnLength = &DReturnLength;
	__asm
	{
		PUSH ReturnLength
		PUSH 4
		LEA EAX,ProcessDebugPort
		PUSH EAX
		PUSH 7
		PUSH -1
		CALL ZwQueryInformationProcess
		PUSH ReturnLength
		PUSH 4
		LEA EAX, ProcessDebugObjectHandle
		PUSH EAX
		PUSH 0x1E
		PUSH - 1
		CALL ZwQueryInformationProcess
		PUSH ReturnLength
		PUSH 4
		LEA EAX, ProcessDebugFlags
		PUSH EAX
		PUSH 0x1F
		PUSH - 1
		CALL ZwQueryInformationProcess
	}
	printf("ProcessDebugPort=0x%08X \n", ProcessDebugPort);
	printf("ProcessDebugObjectHandle=0x%08X \n", ProcessDebugObjectHandle);
	printf("ProcessDebugFlags=0x%08X \n", ProcessDebugFlags);

	if (ProcessDebugPort != 0 || ProcessDebugObjectHandle != 0 || ProcessDebugFlags != 1)
		return 1;
	else return 0;

}
VOID DisableDebugEvent()
{
	DWORD ZwSetInformationThread= GetProcAddressByName(L"ntdll.dll", "ZwSetInformationThread");
	HANDLE CurrentThread = GetCurrentThread();
	__asm
	{
		PUSH 0
		PUSH 0
		PUSH 17
		PUSH CurrentThread
		CALL ZwSetInformationThread;
	}
}
BOOL NtGlobalFlagsDetect()
{
	DWORD NtGlobalFlags;
	__asm
	{
		mov eax, FS:[0x30];
		mov eax, [eax + 0x68];
		mov NtGlobalFlags, eax
	}
	printf("NtGlobalFlags=0x%08X \n", NtGlobalFlags);
	//当调试器不存在时NtGlobalFlags=0,否则=0x70.
	return (NtGlobalFlags==0)?0:1;

}
BOOL HeapDetect()
{
	DWORD Heap[0x200] = { 0 };
	PDWORD pHeapData = (PDWORD)HeapAlloc(GetProcessHeap(), 0, 0x100);
	int Count = 0;
	for (int i = 0; i <= 0x150; i++)
	{
		Heap[i] = *pHeapData;
		pHeapData++;
		if (Heap[i] == 0xBAADF00D || Heap[i] == 0xFEEEFEEE)
		{
			Count++;
		}
	}
	//当调试器不存在时Heap[i]中不会出现0xBAADF00D或者0xFEEEFEEE.
	return (Count > 10 ? 1 : 0);
	
}
BOOL CloseHandleDetect()
{
	CloseHandle((HANDLE)0x12345678);
	if (GetLastError() == 0)
	{
		DebuggerFound();
	}
	return 1;
}
BOOL APIBreakPointDetect(LPCWSTR lpModuleName, LPCSTR lpProcName)
{
	PBYTE APIAddress = (PBYTE)GetProcAddressByName(lpModuleName, lpProcName);

	if (*APIAddress == 0xCC)
	{
		MessageBoxA(0, "BreakPoint Detect! ", "Tips", MB_OK);
		return 1;
	}
}
BOOL NtQueryObjectDetect()
{
	BOOL DebuggerPresent=0;
	DWORD NtQueryObject = GetProcAddressByName(L"ntdll.dll", "NtQueryObject");
	PVOID   ObjectInformation=VirtualAlloc(0,0x6000,MEM_COMMIT,PAGE_READWRITE);
	ULONG ObjectInformationLength=0x6000;
	DWORD ReturnLength;
	__asm
	{
		LEA EAX,ReturnLength
		PUSH EAX
		PUSH ObjectInformationLength
		PUSH ObjectInformation
		PUSH 3
		PUSH 0
		CALL NtQueryObject
	}
	printf("0x%08X Bytes Need \n", ReturnLength);
	POBJECT_ALL_INFORMATION AllObjectInfo = (POBJECT_ALL_INFORMATION)ObjectInformation;
	POBJECT_TYPE_INFORMATION pObjectTypeInfo = (POBJECT_TYPE_INFORMATION)AllObjectInfo->ObjectTypeInfo;
	for (int i = 0; i <= AllObjectInfo->NumberOfObjectsTypes; i++)
	{
		if (pObjectTypeInfo->TypeName.Buffer == NULL)
		{
			break;
		}
		printf("   ObjectName: %ls  \n", pObjectTypeInfo->TypeName.Buffer);
		printf("   TotalNumberOfHandles: %d  \n", pObjectTypeInfo->TotalNumberOfHanders);
		printf("   TotalNumberOfObjects: %d  \n", pObjectTypeInfo->TotalNumberOfObjects);
		printf("\n");
		if (wcscmp(L"DebugObject", pObjectTypeInfo->TypeName.Buffer) == 0)
		{
			DebuggerPresent=(pObjectTypeInfo->TotalNumberOfObjects > 0)?1:0;
		}

		ULONG uNameLength = pObjectTypeInfo->TypeName.Length;
		ULONG uDataLength = uNameLength - uNameLength % sizeof(ULONG) + sizeof(ULONG);//TypeName字符串的长度+4.


		// 3.3 指向下一个对象信息
		pObjectTypeInfo = (POBJECT_TYPE_INFORMATION)pObjectTypeInfo->TypeName.Buffer;//取得字符串地址.
		pObjectTypeInfo = (POBJECT_TYPE_INFORMATION)((PBYTE)pObjectTypeInfo + uDataLength);

		
	}
	VirtualFree(ObjectInformation,0, MEM_RELEASE);
	return DebuggerPresent;
}
HANDLE GetProcessHandleByName(LPCWSTR Name)
{
	
	DWORD Pid = 0;
	HANDLE Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 Process;
	ZeroMemory(&Process, sizeof(Process));
	Process.dwSize = sizeof(Process);
	if (Process32First(Snapshot, &Process))
	{
		do
		{
			if (wcscmp(Process.szExeFile, Name) == 0)
			{
				Pid = Process.th32ProcessID;
				break;
			}
		} while (Process32Next(Snapshot, &Process));
	}
	CloseHandle(Snapshot);

	if (Pid != 0)
	{
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Pid);
		return hProcess;
	}
	return NULL;
}
BOOL CSRSSDetect()
{
	return (GetProcessHandleByName(L"csrss.exe") > 0 ? 1 : 0);
}
VOID AntiDebugThread()
{
	HWND DebuggerWindow=0;
	CHAR WindowTitle[100] = { 0 };
	while (TRUE)
	{
		DebuggerWindow = GetForegroundWindow();
		if (DebuggerWindow != 0)
		{
			GetWindowTextA(DebuggerWindow, WindowTitle, 100);
			if (strstr(WindowTitle, "[LCG" )!=NULL)
			{
				MessageBoxA(0, "OllyDebug Window Found!", "Tips", MB_OK);
				ExitThread(0);
			}

		}
		DebuggerWindow = FindWindow(0, L"x32dbg");
		if (DebuggerWindow != 0)
		{
			ExitProcess(0);
		}
		Sleep(2000);
	}

}
VOID AntiAttach()
{
    DWORD Self;
    DWORD OldProtect;
    __asm
   {
	PUSH 0
	CALL GetModuleHandleA
	MOV Self,EAX
	LEA EAX,OldProtect
	PUSH EAX
	PUSH 0x40
	PUSH 0x1000
	PUSH Self
	CALL VirtualProtect
	MOV EAX,Self
	MOV BYTE PTR[EAX], 0
	MOV BYTE PTR[EAX + 1], 0
   }
}
