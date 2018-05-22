#include "stdafx.h"
#include <Windows.h>

int main()
{
	LPCSTR WndClass = "Shell_TrayWnd";
	LPCSTR Program = "Progman";
	HWND TaskBar = FindWindowA(WndClass, 0);
	HWND DesktopIcon = FindWindowA(Program, 0);


	ShowWindow(TaskBar, SW_HIDE);
	ShowWindow(DesktopIcon, SW_HIDE);

	ShowWindow(TaskBar, SW_NORMAL);
	ShowWindow(DesktopIcon, SW_NORMAL);



	PAUSE;
    return 0;
}

