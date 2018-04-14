// Win32Project1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project1.h"
#include "Resource.h"
#include <string>
#include <string.h>
#include <stdlib.h>
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM   MyRegisterClass(HINSTANCE hInstance);
BOOL    InitInstance(HINSTANCE, int);
LRESULT CALLBACK  WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK  About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int  nCmdShow)
{

	
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	wchar_t sz[] = L"Fuck you";
	HDC hdc;
	HWND hWnd = FindWindow(L"Notepad", 0);
	if (IsWindow(hWnd))
	{
		hdc = GetDC(hWnd);
		TextOut(hdc, 10, 10, sz, lstrlenW(sz));
		ReleaseDC(hWnd, 0);
		
	 }




	if (FindWindow(L"TXGuiFoundation", 0) != 0)
		SendMessage(FindWindow(L"TXGuiFoundation", 0), WM_CLOSE, 0, 0); // Initialize global strings

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);//Register The Window Class

    if (!InitInstance (hInstance, nCmdShow))//Create The Window,Perform application initialization:
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;//Define The Pointer To Default Message Handle Function.
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = (LPCWSTR)IDR_MENU1;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
long CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)//LRESULT=long
{   
	//If you Add a New Menu Item,you should change here to decide what the new item will do
#define Segments 9000
#define Pi 3.1415926535
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt;
	int cxClient, cyClient;
	POINT pt[Segments];
	int i;
	static std::string str;
	WCHAR szText[] = L"The easiest Windows Program";
    switch (message)
    {
    case WM_COMMAND://When you hit one of any menu item,a WM_COMMAND message will be sent and handle here
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:  //If you hit About box
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
			case ID__LOADACCELERATORS:
					MessageBox(0, L"Fuck You", L"ID__LOADACCELERATORS", 0);
					break;
			case WM_CHAR:
			{

			}
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			RECT rt;
			int x, y;
			GetClientRect(hWnd, &rt);
			cxClient = rt.right - rt.left;//Pixel Lenth Of The Window.
			cyClient = rt.bottom - rt.top;//Pixel Width Of The Window.
			char s[] = "";
			HPEN hPen= CreatePen(PS_SOLID, 3, RGB(255, 8, 230));
			HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
			//The Following Two Statements Draw A Line That Start From Left-Middle Of The Window To Right-Middle Of The Window.
			MoveToEx(hdc, 0, cyClient / 2, 0);//Set the startpoint to left-middle of the window.
			LineTo(hdc, cxClient, cyClient / 2);//Set the endpoint to right-middle of the window.
			for (i = 0; i < Segments; i++)
			{   

				//itoa(pt[i].x, s, 10);
				//MessageBoxA(hWnd, s, s, MB_OK);
				//itoa(pt[i].y, s, 10);
				//if (MessageBoxA(hWnd, s, s, MB_OK) == 0)
					//goto here;
			   // here:
				pt[i].x = cxClient*i / Segments;//Divide The X-axis To i Segments.
				//pt[i].y = (int)((cyClient / 2)*(log((double)pt[i].x)));
				pt[i].y = (int)((cyClient / 2)*(1-sin(2 * Pi*i / Segments)));
				
				
			}

			Polyline(hdc, pt, Segments);
			SelectObject(hdc, hOldPen);
			DeleteObject(hPen);
            EndPaint(hWnd, &ps);
        }
        break;


	case WM_CREATE:
		SetWindowText(hWnd, L"The Lowest Program");//Set The Window Title;
		break;


    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
