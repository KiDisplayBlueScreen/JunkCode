// Instance 2.5.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
using namespace std;

int main()
{
	OSVERSIONINFO vi = { sizeof(vi) };
	GetVersionEx(&vi);
	cout << vi.dwMajorVersion << endl;
	cout << vi.dwMinorVersion << endl;
	cout << vi.dwPlatformId << endl;
	unsigned long  a=9;
	DWORD* b = &a;
	system("pause");
	 
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
}

