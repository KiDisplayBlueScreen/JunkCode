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
//����GetMoudleHandleA��ȡ��ǰʵ���ľ����Ϊ��������WinMain
   //HINSTANCE hPrevInstance��32λ����������0
   //����GetCommandLineA��ȡ����Ĳ���Ȼ�󴫸�WinMain
   //ָ�����ڵ���ʾ��ʽ