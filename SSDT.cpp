// SSDT.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <winerror.h>
#include  <iomanip>
using namespace std;
#define FILE_PATH L"D:\\2345改名\\RenameTool.exe"
int main()
{  
	BOOL ElevatePrivileges();
	ElevatePrivileges();
	BYTE *pBuffer;
	HANDLE hFile = CreateFile(FILE_PATH,GENERIC_ALL, FILE_SHARE_READ, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL,0);
	DWORD b;
	if (hFile == INVALID_HANDLE_VALUE)
	{
                     cout << "Open File Fail !" << endl;
	   getchar();
	   return 0;
	}
	b=GetFileSize(hFile, &b);
	pBuffer=new BYTE[b];
	ReadFile(hFile, pBuffer,b, NULL, 0);
	CloseHandle(hFile);
	int i = 0;
	char a = 0x20;
	int r = 0;
	//PIMAGE_DOS_HEADER P = (PIMAGE_DOS_HEADER)pBuffer;
	for (i = 1; i<= b; i++)
	{
	     printf("%02X", pBuffer[i-1]);
		 cout << a;
		if (i % 16== 0&&i>=16) cout << endl;
	}
	
	cout << endl;
	cout << "The File Size is " <<b<<"  "<< "Bytes" << endl;
	getchar();
    return 0;
}

BOOL ElevatePrivileges()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	tkp.PrivilegeCount = 1;
	if (!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))//取得进程令牌句柄.
		return FALSE;//失败返回0.
	LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tkp.Privileges[0].Luid);//获取对其他进程进行调试的特权.
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(TOKEN_PRIVILEGES), NULL, NULL))//设定打开该特权
	{
		return FALSE;
	}
	return TRUE;
}
