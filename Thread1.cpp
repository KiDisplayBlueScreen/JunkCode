#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>
#include <iostream>

using namespace std;
int i = 0;
int j = 0;
int b = 1;
DWORD WINAPI ThreadProc(LPVOID lpParam)
{       
	while (b)
	{
		i++;
		j++;
	}
	return 0;
}
int main()
{   
	HANDLE h[2];
	DWORD dwThreadId;
	h[0] = CreateThread(0, 0, ThreadProc, 0, 0, &dwThreadId);
	h[1] = CreateThread(0, 0, ThreadProc, 0, 0, &dwThreadId);
	Sleep(1000);
	b = 0;
	WaitForMultipleObjects(2, h, 1, 1000);
	printf("%d", i); cout << endl;
	printf("%d", j); cout << endl;
	CloseHandle(h[1]);
	CloseHandle(h[0]);
	system("pause");
	return 0;
}
