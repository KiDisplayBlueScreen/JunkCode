// GetProcessID.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <Powerbase.h>
using namespace std;


typedef struct _PROCESSOR_POWER_INFORMATION {
	ULONG Number;
	ULONG MaxMhz;
	ULONG CurrentMhz;
	ULONG MhzLimit;
	ULONG MaxIdleState;
	ULONG CurrentIdleState;
} PROCESSOR_POWER_INFORMATION, *PPROCESSOR_POWER_INFORMATION;




inline __int64 GetCPUCount()
{
	__asm
	{
		rdtsc;
	}
}
#define GetCPUCount() __rdtsc();


DWORD WINAPI GetSpecifiedProcessID(LPCWSTR PROCESSNAME)
{
	DWORD Id;
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 ProcessInfo;
	ProcessInfo.dwSize = sizeof(ProcessInfo);
	BOOL bMore=Process32First(hSnapShot, &ProcessInfo);
	while (bMore)
	{
		if (wcscmp(PROCESSNAME,ProcessInfo.szExeFile)==0)
		{
			Id = ProcessInfo.th32ProcessID;
			cout << Id << endl;
		}
		 bMore = Process32Next(hSnapShot, &ProcessInfo);//这句前面如果加了else，那么检测到QQ的时候就不会执行这一句，bMore的值就不会更新，造成上面if的判断恒成立.
	}
	return Id;
}

int main()
{   
	PROCESSOR_POWER_INFORMATION info;
	CallNtPowerInformation(ProcessorInformation, 0, 0, &info, sizeof(info));
	__int64 t_begin = GetCPUCount();

		int a = 6 + 9 * 9;



		__int64 t_end = GetCPUCount();
		double millisec = ((double)t_end - (double)t_begin / (double)info.CurrentMhz);
		cout << millisec << endl;

    return 0;
}

