#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <Synchapi.h>
using namespace std;
CONDITION_VARIABLE IsReg;
PBYTE GetDWORDBit(DWORD Dest);
int main()
{
	char str1[30] = { "I love China" };
	char str2[] = { "I love you" };
	printf("%ls \n", strcat_s(str1, 30, str2));





	SYSTEMTIME System = { 0 };
	LPCSTR Year = "%d Year \n";
	LPCSTR Month = "%d Month \n";
	LPCSTR Day = "%d Day \n";
	LPCSTR Str = "123456";
	LPCSTR Format = "%c";
	int Loop = 6;
	__asm
	{
		LEA EAX,System
		PUSH EAX
		CALL GetLocalTime

		LEA EAX,System
		MOV ECX,EAX
		PUSH ECX
		MOVZX AX,WORD PTR[EAX]
		PUSH EAX
		MOV EBX,Year
		PUSH EBX
		CALL printf

		POP EBX
		POP EAX
		POP ECX
		MOVZX AX,WORD PTR[ECX+2]
		PUSH EAX
		MOV EBX,Month
		PUSH EBX
		CALL printf


		
		MOV EDI,6
		MOV ECX,Loop

		Label:
		MOV EAX, Str
		MOVZX EAX,BYTE PTR[EAX+ECX]
		PUSH EAX
		MOV EDX,Format
		PUSH EDX
		CALL printf

		MOV ECX,Loop
		DEC ECX
		CMP ECX,-1
		MOV Loop,ECX
		JNZ Label



	}




	





	system("pause");
	return 0;
}
PBYTE GetDWORDBit(DWORD Dest)
{
	BYTE Return[8] = { 0 };
	__asm
	{
		mov eax, Dest
		and eax, 0xF0000000
		shr eax, 0x1C
		mov Return[0], al

		mov eax, Dest
		and eax, 0xF000000
		sar eax, 0x18
		mov Return[1], al

		mov eax, Dest
		and eax, 0xF00000
		sar  eax, 0x14
		mov Return[2], al


		mov eax, Dest
		and eax, 0xF0000
		sar  eax, 0x10
		mov Return[3], al

		mov eax, Dest
		and eax, 0xF000
		sar  eax, 0xC
		mov Return[4], al

		mov eax, Dest
		and eax, 0xF00
		sar  eax, 0x8
		mov Return[5], al

		mov eax, Dest
		and eax, 0xF0
		sar  eax, 0x4
		mov Return[6], al


		mov eax, Dest
		and eax, 0xF
		mov Return[7], al
	}
	return Return;
}