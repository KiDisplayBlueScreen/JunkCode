#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <Winternl.h>
using namespace std;
typedef DWORD(WINAPI *ZW_SET_INFOMATION_THREAD)(HANDLE, DWORD, PVOID,ULONG);
#define ThreadHideFromDebugger 17
BOOL ElevateDebugPrivileges()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	tkp.PrivilegeCount = 1;
	if (!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,&hToken))//取得进程令牌句柄.
		return FALSE;//失败返回0.
	LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tkp.Privileges[0].Luid);//获取对其他进程进行调试的特权.
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(TOKEN_PRIVILEGES), NULL, NULL))//设定打开该特权
	{
		return FALSE;
	}
	return TRUE;
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

DWORD WINAPI GetSpecifiedProcessID(LPCWSTR PROCESSNAME)
{
	DWORD Id;
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 ProcessInfo;
	ProcessInfo.dwSize = sizeof(ProcessInfo);
	BOOL bMore = Process32First(hSnapShot, &ProcessInfo);
	while (bMore)
	{
		if (wcscmp(PROCESSNAME,ProcessInfo.szExeFile)== 0)
		{
			Id = ProcessInfo.th32ProcessID;
		}
		bMore=Process32Next(hSnapShot, &ProcessInfo);
	}
	CloseHandle(hSnapShot);
	return Id;
}

BYTE* GetModuleAddr(LPCWSTR ModName)
{    
	DWORD Id=GetSpecifiedProcessID(ModName);
	HANDLE Snapshot= CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,Id);
	if (Snapshot == 0 || Id == 0)
	{
		cout << "Invalid Snapshot Handle" << endl;
		return 0;
	}
	MODULEENTRY32 Mod;
	Mod.dwSize=sizeof(Mod);
	BYTE *pbModBase=NULL;
	BOOL bMore=Module32First(Snapshot,&Mod);
	while (bMore)
	{
		if (wcscmp(ModName,Mod.szModule) == 0)
		{
			pbModBase = Mod.modBaseAddr;
			break;
		}
		bMore = Module32Next(Snapshot,&Mod);
	}
	CloseHandle(Snapshot);
	if (pbModBase!=0)
		return pbModBase;
	else return 0;
}
BOOL VMCheck()
{
   DWORD Flag;
   _asm
     {
          mov eax,1
          cpuid
          and ecx,0x80000000
          mov Flag,ecx
       }
 if (Flag==0) return 1;
 else return 0;

}
BOOL ElevatePrivilegesEx(DWORD DesiredAccess,LPCWSTR lpName,DWORD Attributes)
{   
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	tkp.PrivilegeCount = 1;
	if (!OpenProcessToken(GetCurrentProcess(), DesiredAccess,&hToken))//取得进程令牌句柄.
		return FALSE;//失败返回0.
	LookupPrivilegeValue(NULL, lpName, &tkp.Privileges[0].Luid);
	tkp.Privileges[0].Attributes = Attributes;
	if (!AdjustTokenPrivileges(hToken,FALSE,&tkp, sizeof(TOKEN_PRIVILEGES), NULL, NULL))//设定打开该特权
	{
		return FALSE;
	}
	return TRUE;
}
WCHAR* WINAPI GetProcessNameByPID(DWORD ProcessID)
{
	
	WCHAR* pProcessName=NULL;
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 ProcessInfo;
	ProcessInfo.dwSize = sizeof(ProcessInfo);
	BOOL bMore = Process32First(hSnapShot,&ProcessInfo);
	while (bMore)
	{
		if (ProcessInfo.th32ProcessID==ProcessID)
		{
			pProcessName=(ProcessInfo.szExeFile);
			break;
		}
		bMore = Process32Next(hSnapShot, &ProcessInfo);
	}

	if (pProcessName == NULL)
	{
		CloseHandle(hSnapShot);
		return 0;
	}
	else
	{
		CloseHandle(hSnapShot);
		return pProcessName;
	}
}

WCHAR* WINAPI GetParentNameByProcName(LPCWSTR ProcessName)
{
	WCHAR* pProcessName = NULL;
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 ProcessInfo;
	DWORD ParentProcessID=0;
	ProcessInfo.dwSize = sizeof(ProcessInfo);
	BOOL bMore = Process32First(hSnapShot, &ProcessInfo);
	while (bMore)
	{
		if (wcscmp(ProcessName,ProcessInfo.szExeFile) == 0)
		{
			ParentProcessID = (ProcessInfo.th32ParentProcessID);
			break;
		}
		bMore = Process32Next(hSnapShot, &ProcessInfo);
	}

	if (ParentProcessID!= 0)
	{
		pProcessName = GetProcessNameByPID(ParentProcessID);
	}
	
	if (pProcessName != NULL)
	{
		CloseHandle(hSnapShot);
		return pProcessName;
	}
	else
	{
		CloseHandle(hSnapShot);
		return 0;
	}
	
}
typedef struct tagProcessInfo
{
	DWORD PID;
	WCHAR* ProcessName;
	WCHAR* ParentName;
}SimProcessInfo;
typedef SimProcessInfo* PSIMPLE_PROCESS_INFO;

PSIMPLE_PROCESS_INFO GetAllProcessEx()
{   

	SimProcessInfo ProcInfo[200] = { 0 };
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapShot == INVALID_HANDLE_VALUE)
	{
		cout << "Get Process Snap Shot Fail ." << endl;
		return 0;
	}
	BOOL bMore = Process32First(hSnapShot, &pe32);
	for (int i = 0; bMore != FALSE; i++)
	{
		ProcInfo[i].PID = pe32.th32ProcessID;
		ProcInfo[i].ProcessName = pe32.szExeFile;
		ProcInfo[i].ParentName = GetProcessNameByPID(pe32.th32ParentProcessID);
		bMore = Process32Next(hSnapShot, &pe32);
	}
	CloseHandle(hSnapShot);
	return ProcInfo;
}

BOOL DebuggerCheck()
{
	PROCESSINFOCLASS ProcessInfo1 = ProcessBasicInformation;
	PROCESS_BASIC_INFORMATION ProcessInfo2;
	ZeroMemory(&ProcessInfo2, sizeof(ProcessInfo2));
	ULONG ProcessInformationLength = sizeof(ProcessInfo2);
	PULONG   ReturnLength = 0;
	HMODULE hFile = LoadLibrary(L"C:\\WINDOWS\\System32\\ntdll.dll");
	LPCSTR p = "ZwQueryInformationProcess";
	GetProcAddress(hFile, p);
	__asm
	{
		    push ReturnLength;
		    push ProcessInformationLength;
		    lea ebx, ProcessInfo2
			push ebx
			push ProcessInfo1
			push - 1
			call eax
	}

	BOOL DebugFlag = ProcessInfo2.PebBaseAddress->BeingDebugged;
	if (DebugFlag == 1) return 1;
	if (DebugFlag == 0) return 0;

}


PIMAGE_OPTIONAL_HEADER GetOptionalHeader(LPCWSTR lpModuleName)
{
	HMODULE hFile = GetModuleHandle(lpModuleName);
	PIMAGE_DOS_HEADER pDOSHeader = (PIMAGE_DOS_HEADER)(hFile);
	PIMAGE_FILE_HEADER pFileHeader = (PIMAGE_FILE_HEADER)((BYTE*)hFile + pDOSHeader->e_lfanew + 4);
	PIMAGE_OPTIONAL_HEADER pOptionalHeader = (PIMAGE_OPTIONAL_HEADER)((BYTE*)hFile + pDOSHeader->e_lfanew + 24);
	return pOptionalHeader;
}

PIMAGE_SECTION_HEADER GetSectionHeader(LPCWSTR lpModuleName)
{

	HMODULE hFile = GetModuleHandle(lpModuleName);
	PIMAGE_DOS_HEADER pDOSHeader = (PIMAGE_DOS_HEADER)(hFile);
	PIMAGE_FILE_HEADER pFileHeader = (PIMAGE_FILE_HEADER)((BYTE*)hFile + pDOSHeader->e_lfanew + 4);
	PIMAGE_OPTIONAL_HEADER pOptionalHeader = (PIMAGE_OPTIONAL_HEADER)((BYTE*)hFile + pDOSHeader->e_lfanew + 24);
	PIMAGE_SECTION_HEADER pSectionHeader = (PIMAGE_SECTION_HEADER)((BYTE*)hFile + pDOSHeader->e_lfanew + 24 + pFileHeader->SizeOfOptionalHeader);
	return pSectionHeader;

}
VOID DisableDebugEvent(VOID)
{
	HINSTANCE hModule;
	ZW_SET_INFOMATION_THREAD ZwSetInformationThread;//声明一个ZW_SET_INFOMATION_THREAD类型的函数,命名为ZwSetInformationThread
	LPCWSTR pModuleName = L"ntdll";
	hModule = GetModuleHandle(pModuleName);
	ZwSetInformationThread = (ZW_SET_INFOMATION_THREAD)GetProcAddress(hModule,"ZwSetInformationThread");
	ZwSetInformationThread(GetCurrentThread(),ThreadHideFromDebugger, 0, 0);
}


NTSTATUS WINAPI NtQuerySystemInformation
(
	SYSTEM_INFORMATION_CLASS SystemInformationClass,
	PVOID SystemInformation,
	ULONG SystemInformationLength,
	PULONG ReturnLength
);

typedef struct _RTL_PROCESS_MODULE_INFORMATION
{
	HANDLE Section;
	PVOID MappedBase;
	PVOID ImageBase;
	ULONG ImageSize;
	ULONG Flags;
	USHORT LoadOrderIndex;
	USHORT InitOrderIndex;
	USHORT LoadCount;
	USHORT OffsetToFileName;
	UCHAR FullPathName[256];
} RTL_PROCESS_MODULE_INFORMATION, *PRTL_PROCESS_MODULE_INFORMATION;

typedef struct _RTL_PROCESS_MODULES
{
	ULONG NumberOfModules;
	RTL_PROCESS_MODULE_INFORMATION Modules[1];
} RTL_PROCESS_MODULES, *PRTL_PROCESS_MODULES;

typedef struct _VM_COUNTERS
{
	SIZE_T PeakVirtualSize;
	SIZE_T VirtualSize;
	ULONG PageFaultCount;
	SIZE_T PeakWorkingSetSize;
	SIZE_T WorkingSetSize;
	SIZE_T QuotaPeakPagedPoolUsage;
	SIZE_T QuotaPagedPoolUsage;
	SIZE_T QuotaPeakNonPagedPoolUsage;
	SIZE_T QuotaNonPagedPoolUsage;
	SIZE_T PagefileUsage;
	SIZE_T PeakPagefileUsage;
} VM_COUNTERS,*PVM_COUNTERS;

typedef struct _CLIENT_ID
{
	HANDLE UniqueProcess;
	HANDLE UniqueThread;
} CLIENT_ID;
typedef CLIENT_ID *PCLIENT_ID;

typedef struct _SYSTEM_THREADS
{
	LARGE_INTEGER  KernelTime;
	LARGE_INTEGER  UserTime;
	LARGE_INTEGER  CreateTime;
	ULONG    WaitTime;
	PVOID    StartAddress;
	CLIENT_ID   ClientID;
	KPRIORITY   Priority;
	KPRIORITY   BasePriority;
	ULONG    ContextSwitchCount;
	ULONG    ThreadState;
	KWAIT_REASON  WaitReason;
	ULONG    Reserved; 
}SYSTEM_THREADS, *PSYSTEM_THREADS;


typedef struct _SYSTEM_PROCESSES
{
	ULONG          NextEntryDelta;              
	ULONG          ThreadCount;             
	ULONG          Reserved1[6];
	LARGE_INTEGER  CreateTime;             
	LARGE_INTEGER  UserTime;                  
	LARGE_INTEGER  KernelTime;             
	UNICODE_STRING ProcessName;               
	KPRIORITY      BasePriority;            
	HANDLE         ProcessId;                  
	HANDLE         InheritedFromProcessId;   
	ULONG          HandleCount;                 
	ULONG          Reserved2[2];
	VM_COUNTERS    VmCounters;                  
	IO_COUNTERS    IoCounters;             
	SYSTEM_THREADS Threads[1];                
}SYSTEM_PROCESSES, *PSYSTEM_PROCESSES;

typedef struct _SYSTEM_THREAD_INFORMATION 
{
	ULONGLONG KernelTime;
	ULONGLONG UserTime;
	ULONGLONG CreateTime;
	ULONG WaitTime;
	ULONG Reserved1;
	PVOID StartAddress;
	CLIENT_ID ClientId;
	KPRIORITY Priority;
	LONG BasePriority;
	ULONG ContextSwitchCount;
	ULONG State;
	KWAIT_REASON WaitReason;
} SYSTEM_THREAD_INFORMATION, *PSYSTEM_THREAD_INFORMATION;



typedef enum _KWAIT_REASON
{
	Executive,
	FreePage,
	PageIn,
	PoolAllocation,
	DelayExecution,
	Suspended,
	UserRequest,
	WrExecutive,
	WrFreePage,
	WrPageIn,
	WrPoolAllocation,
	WrDelayExecution,
	WrSuspended,
	WrUserRequest,
	WrEventPair,
	WrQueue,
	WrLpcReceive,
	WrLpcReply,
	WrVirtualMemory,
	WrPageOut,
	WrRendezvous,
	WrKeyedEvent,
	WrTerminated,
	WrProcessInSwap,
	WrCpuRateControl,
	WrCalloutStack,
	WrKernel,
	WrResource,
	WrPushLock,
	WrMutex,
	WrQuantumEnd,
	WrDispatchInt,
	WrPreempted,
	WrYieldExecution,
	WrFastMutex,
	WrGuardedMutex,
	WrRundown,
	MaximumWaitReason
} KWAIT_REASON;


