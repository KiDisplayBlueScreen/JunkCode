#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <SpecialAPI.h>
using namespace std;
#define FILE_PATH L"C:\\Users\\hasee\\source\\repos\\SSDT\\Release\\SSDT.exe"
int main()
{
	 BOOL CheckSum();
	 BOOL PatchCheck();
     ULONG S = CheckSum();
	 PatchCheck();
	 printf("%X\n", S);
	 //cout << S << endl;

	TCHAR FileName[100] = { 0 };
	GetModuleFileName(0,FileName,100 * sizeof(TCHAR));
	BYTE* p = NULL;
	CopyFile(FileName, L"C:\\360安全浏览器下载\\ConsoleApplication2.exe", 0);
	HANDLE hFile= CreateFile(L"C:\\360安全浏览器下载\\ConsoleApplication2.exe", GENERIC_ALL, FILE_SHARE_READ, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	DWORD hSize=GetFileSize(hFile, 0);
	HANDLE hFileMapping=CreateFileMapping(hFile, 0, PAGE_EXECUTE_READWRITE, 0, hSize, 0);
    p=(BYTE*)MapViewOfFile(hFileMapping,FILE_MAP_ALL_ACCESS,0,0,0);
	if (p == NULL)
	{
		cout << "Map Fail" << endl;
		getchar();
		return 0;
	}
	int i = 0;
	char a = 0x20;
	for (i = 1; i<=hSize; i++)
	{
		printf("%02X", *p);
		p = p++;
		cout << a;
		if (i % 16 == 0 && i >= 16) cout << endl;
	}
	getchar();
    return 0;
}


BOOL CheckSum()
{    

	TCHAR FileName[100] = { 0 };
	GetModuleFileName(0, FileName, 100 * sizeof(TCHAR));
	BYTE *pBuffer;
    HANDLE hFile=CreateFile(FileName,GENERIC_ALL, FILE_SHARE_READ, 0,OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	DWORD b;
	if (hFile == INVALID_HANDLE_VALUE)
	{
		cout << "Open File Fail !" << endl;
		getchar();
		return 0;
	}
	b = GetFileSize(hFile, &b);
	pBuffer = new BYTE[b];
	ReadFile(hFile, pBuffer, b, NULL, 0);
	CloseHandle(hFile);
	int i = 0;
	ULONG S = 0;
	for (i = 1; i <= b; i++)
	{
		S = S + pBuffer[i-1];
	}
	hFile = CreateFile(L"Memory.txt", GENERIC_ALL, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	LONG Buffer[1] = { 0 };
	Buffer[0] = S;
	WriteFile(hFile,Buffer, 4, 0, 0);
	CloseHandle(hFile);
	return S;
}
BOOL PatchCheck()
{
	HANDLE hFile = CreateFile(L"Memory.txt", GENERIC_ALL, FILE_SHARE_READ, 0, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);
	ULONG S = 0;
	if (GetLastError() != ERROR_FILE_EXISTS) S = CheckSum();
	LONG Buffer[1] = { 0 };
	LPDWORD lpNumberOfBytesRead=NULL;
	ReadFile(hFile, Buffer,4, lpNumberOfBytesRead, 0);
	if (S != Buffer[0])
		cout << "This File Have Been Patch" << endl;
	else cout << "This File Haven't Been Patch" << endl;
	return 0;
	
}