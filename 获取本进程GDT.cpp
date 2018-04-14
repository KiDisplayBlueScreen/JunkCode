#include "stdafx.h"
#include <Windows.h>
#include <iostream>
using namespace std;
int main()
{
	
	char GDT[6];
	unsigned long GDT_ADDR;
	unsigned short GDT_LIMIT;
	_asm sgdt GDT;
	GDT_ADDR = *(unsigned long *)(&GDT[2]);
	GDT_LIMIT = *(unsigned short *)(&GDT[0]);
	printf("GDT Base: %08X\n", GDT_ADDR);
	printf("GDT Limit: %04X\n", GDT_LIMIT);
	cout << GetCurrentProcessorNumber() << endl;
	system("pause");
    return 0;
}
int* a(void)
{

	int a[] = { 2 };
	return a;
}
