#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <Psapi.h>
#include <Winternl.h>
using namespace std;
BOOL ElevateDebugPrivileges();
LPCTSTR UUAccelerator =L"uu.exe";
HANDLE GetProcessHandleByName(TCHAR* Name);
LPSTR GetUUFullPath(HANDLE hUU);

int main()
{

	ElevateDebugPrivileges();
	HANDLE hUUAccelerator = GetProcessHandleByName((LPWSTR)UUAccelerator);
	DWORD LastError = GetLastError();
	DWORD OldProtect;
	DWORD ReturnLength = 0;
	DWORD ZwQueryInformationProcess = 0;
	PROCESS_BASIC_INFORMATION UUInfo = { 0 };
	PEB UUPEB = { 0 };
	ULONG  ProcessInformationLength = sizeof(PROCESS_BASIC_INFORMATION);
	ZwQueryInformationProcess = (DWORD)GetProcAddress(GetModuleHandleA("ntdll.dll"), "ZwQueryInformationProcess");
	BYTE Patch[2] = { 0xF0,0x78 };
	PVOID UUPEBBasicAddress = NULL;
	PBYTE UUBaseAddress = NULL;
	__asm
	{
		    LEA EAX, ReturnLength;
		    PUSH EAX
			PUSH ProcessInformationLength
			LEA EAX, UUInfo
			PUSH EAX
			PUSH 0
			PUSH hUUAccelerator
			CALL ZwQueryInformationProcess
			LEA EAX, UUInfo
			MOV EAX, DWORD PTR [EAX + 4]
			MOV UUPEBBasicAddress,EAX
	}

	ReadProcessMemory(hUUAccelerator, UUPEBBasicAddress, &UUPEB, sizeof(PEB), 0);
	UUBaseAddress = (PBYTE)UUPEB.Reserved3[1];

	printf("UUBaseAddress: 0x%08X \n", UUBaseAddress);

	if (hUUAccelerator == 0)
	{
		printf("Get UUAccelerator Handle Fail! Please Check If you have ran UUAccelerator or Run This Program As Administrator. \n");
		printf("Error Code:   0x%08X  \n", LastError);
		PAUSE;
		return 0;
	}


	if  (VirtualProtectEx(hUUAccelerator, (UUBaseAddress+0x1000), 0x331000, PAGE_EXECUTE_READWRITE, &OldProtect)==0)
	{
		LastError = GetLastError();
		printf("Page Protect Change Fail! Please Check If you have ran  UUAccelerator or Run This Program As Administrator. \n");
		printf("Error Code:   0x%08X  \n", LastError);
		PAUSE;
	}

	if (WriteProcessMemory(hUUAccelerator,(UUBaseAddress+0x47E80+8),(LPVOID)Patch,2,0)==0)
	{
		LastError = GetLastError();
		printf("Patch Fail! Please Check If you have ran  UUAccelerator or Run This Program As Administrator. \n");
		printf("Error Code:   0x%08X  \n", LastError);
		PAUSE;
	}
	printf("Patch  UUAccelerator Success!  \n");
	VirtualProtectEx(hUUAccelerator, (LPVOID)UUBaseAddress, 0x331000, OldProtect, &OldProtect);

	CloseHandle(hUUAccelerator);
	PAUSE;
    return 0;
}
HANDLE GetProcessHandleByName(TCHAR* Name)
{
	ElevateDebugPrivileges();
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
LPSTR GetUUFullPath(HANDLE hUU)
{
	BYTE UUFullPath[0x100] = { 0 };
	return  (GetModuleFileNameExA(hUU, 0, (LPSTR)UUFullPath, 0x100) > 0 ? (LPSTR)UUFullPath : 0);
}
HANDLE CreateFileSimple(LPCTSTR lpFileName, DWORD DesireAccess, DWORD ShareMode, DWORD CreationDisposition)
{
	return CreateFile(lpFileName, DesireAccess, ShareMode, 0, CreationDisposition, FILE_ATTRIBUTE_NORMAL, 0);
}
