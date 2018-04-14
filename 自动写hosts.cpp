// Pixiv.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <SpecialAPI.h>

//char DNS[1000] = { "210.129.120.43 www.pixiv.net ","210.140.131.146 source.pixiv.net ", };
char* DNS = "210.129.120.43  www.pixiv.net \n  210.140.131.146 source.pixiv.net \n 210.129.120.44  accounts.pixiv.net \n 210.140.131.147 imgaz.pixiv.net \n 210.140.131.145 comic.pixiv.net \n 210.140.131.145 novel.pixiv.net \n 210.129.120.41 factory.pixiv.net \n 210.129.120.41 oauth.secure.pixiv.net \n  210.129.120.44  en - dic.pixiv.net \n 203.210.8.42 sketch.pixiv.net \n 210.129.120.40 sensei.pixiv.net \n 210.129.120.40 recruit.pixiv.net \n     0.0.0.0	im.ov.yahoo.co.jp";
WCHAR SystemPath[60] = {0};
WCHAR* HostPath = L"\\drivers\\etc\\hosts";
int main()
{   
	ElevateDebugPrivileges();
	DWORD Error;
	LPCTSTR Host = L"C:\\WINDOWS\\System32\\drivers\\etc\\hosts";
	GetSystemDirectory(SystemPath, 60);
	lstrcatW(SystemPath, HostPath);
	HANDLE hHost=CreateFile(SystemPath, FILE_ALL_ACCESS, FILE_SHARE_WRITE, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	Error=GetLastError();
	if (hHost == INVALID_HANDLE_VALUE)
	{
		MessageBox(0, L"打开Host文件失败,请确认是否具有管理员权限", L"Fail", MB_OK);
		printf("Error Code : %d \n", Error);
		system("pause");
		return 0;
	};
	DWORD Size = GetFileSize(hHost, 0);
	DWORD Begin = Size / sizeof(char);
	DWORD NumberOfBytesToWrite =sizeof(char)*strlen(DNS);
	DWORD NumberOfBytesWritten;

	SetFilePointer(hHost, Begin, 0, 0);
	BOOL IsWriteOk=WriteFile(hHost,DNS,NumberOfBytesToWrite,&NumberOfBytesWritten,0);
	Error = GetLastError();
	if (IsWriteOk != 0)
	{
		MessageBox(0, L"写入成功", L"Success", MB_OK);
		printf("Error Code : %d \n", Error);
		printf("Writen By 緋色月下 、墨染の桜 \n");
		system("pause");
		return 0;
	}
	else
	{
		MessageBox(0, L"写入失败", L"Success", MB_OK);
		printf("Error Code : %d \n", Error);
		printf("Writen By 緋色月下 、墨染の桜 \n");
		system("pause");
	}
    return 0;
}

