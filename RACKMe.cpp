#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#pragma comment(lib,"user32.lib")
using namespace std;
typedef struct B
{
	char a;
	int b;
	long v;
} A;
int main()
{
	A a = { 0 };
	printf("Size Of A: %d \n", sizeof(A));

	cin >> a.a;
	cin >> a.b;
	cin >> a.v;
	cout << (1 > 2) ? 2 : 6;

	cout << a.a<<endl;
	cout << a.b;
	cout << a.v;
	
	system("pause");



}
LRESULT WINAPI CallWindowProc
(
	_In_ WNDPROC lpPrevWndFunc,
	_In_ HWND    hWnd,
	_In_ UINT    Msg,
	_In_ WPARAM  wParam,
	_In_ LPARAM  lParam
)
{
	switch (Msg)
	{
	     case WM_DESTROY:
			 PostQuitMessage(0);
			 break;
		 case WM_RBUTTONDOWN:
		 case WM_SIZE:
		 case WM_CREATE:
		 case	 WM_LBUTTONDOWN:
		 case WM_GETMINMAXINFO:
			 return 0;

		 case WM_COMMAND:




	default:
		break;
	}



}
