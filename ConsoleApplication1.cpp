#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
using namespace std;
int main()
{
	int i = 0;
	STARTUPINFO StartInfo = { 0 };
	StartInfo.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION ProcessInformation = { 0 };
	BYTE Data[0xFFF] = { 0 };
	WCHAR Kanal[] = L"C:\\Users\\hasee\\source\\repos\\ConsoleApplication1\\Release\\Kanal.exe";
	DWORD NumberOfBytesRead;
	SIZE_T  *lpNumberOfBytesRead=&NumberOfBytesRead;
	if (CreateProcess(0, Kanal, 0, 0, 0, CREATE_SUSPENDED, 0, 0, &StartInfo,&ProcessInformation) == 0)
	{
		cout << "CreateProcess Fail." << endl;
		system("pause");
		return 0;
	}
	HANDLE hProcess = ProcessInformation.hProcess;

	ReadProcessMemory(hProcess, (PVOID)0x004010C0, Data, 0xF50,lpNumberOfBytesRead);


	TerminateProcess(hProcess, 0);
	PBYTE pB=(PBYTE)VirtualAlloc(0, 0x5000, MEM_COMMIT, PAGE_READWRITE);
	PBYTE Orgin = pB;
	while (i <= 0xF60)
	{
		wsprintfA((LPSTR)pB, "0x%02X,", Data[i]);
		pB += 5;
		i++;
	}
	VirtualFree(Orgin, 0, MEM_RELEASE);
	HANDLE hFile=CreateFile(L"Signature.txt", GENERIC_ALL, FILE_SHARE_DELETE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	WriteFile(hFile, Orgin, 0x5000, &NumberOfBytesRead, 0);

	CloseHandle(hFile);

	system("pause");
	return 0;
}