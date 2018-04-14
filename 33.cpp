#include <windows.h>

#include <tchar.h>

 

int WINAPI _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd )

{

int sum = 0;

for( int i = 1; i<=10; i++ )

sum += i;

 

TCHAR strSum[256] = { 0 };

wsprintf( strSum, _T("%d"), sum );

MessageBox( NULL, strSum, _T("Title"), MB_OK );

return 0;

}
//调用GetMoudleHandleA获取当前实例的句柄作为参数传给WinMain
   //HINSTANCE hPrevInstance在32位程序中总是0
   //调用GetCommandLineA获取程序的参数然后传给WinMain
   //指明窗口的显示方式