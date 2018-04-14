// 333.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <WinBase.h>
using namespace std;
int main()
{
	char szCommandLine[]="cmd";
	STARTUPINFO si={sizeof(si)};
	PROCESS_INFORMATION pi;
	si.dwFlags=START_USERSHOWWINDOW;
	si.wShowWindow=TRUE;
	if (CreateProcess(NULL,szCommandLine,NULL,NULL,FALSE,CREAT_NEW_CONSOLE,NULL,NULL,&si,&pi))
	{CloseHandle(pi.hThread);
	 CloseHandle(pi.hProcess);
	 cout<<"The New Process ID is"<<pi.dwProcessId<<endl;
	 cout<<"The New Thread ID is"<<pi.dwThreadId<<endl;
	}
	return 0;
}









}

