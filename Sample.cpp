#include<stdio.h>
#include "stdafx.h"
#include <Windows.h>
#include <iostream>
using namespace std;
PBYTE GetDWORDBit(DWORD Dest);
int main()
{
	LPCWSTR User32 = L"user32.dll";
	PBYTE pBaseOfCode = NULL;
	DWORD SizeOfCode;
	LPCSTR Format = "Opcode Find At 0x%08X \n";
	LPCSTR Message = "BaseOfCode: 0x%08X \n";
	LPCSTR Pause = "pause";
	
	__asm
	{
		MOV ECX,1
		CMP ECX,0
		PUSHFD
		MOV EAX,[ESP]
		POPFD
		AND EAX,0x40
		MOV EAX,User32
		PUSH EAX
		CALL LoadLibrary
		MOV EBX,EAX
		ADD EAX,[EAX+0x3C]
		ADD EAX,0x18
		ADD EAX,0x4
	    MOV EDX,[EAX]
		MOV SizeOfCode,EDX
		ADD EAX,0x10
		MOV EAX,[EAX]
		ADD EBX,EAX
		MOV pBaseOfCode,EBX
		MOV EAX,Message
		PUSH pBaseOfCode
		PUSH EAX
		CALL printf
		

		XOR EAX, EAX
		MOV EDI, pBaseOfCode

		label0:
		
		MOV DL,BYTE PTR[EDI]
		CMP DL,0xFF
		JE label1

		CMP EAX, SizeOfCode
		JAE label4

		label3:
		INC EAX
		INC EDI
		JMP label0

		label1:
		CMP BYTE PTR [EDI+1],0xE4
        JNE label3


		label2:
		PUSH EAX
		MOV pBaseOfCode,EDI
	    MOV EAX,Format
		PUSH pBaseOfCode
	    PUSH EAX
		CALL printf
		POP EBX
		POP ECX
		POP EAX
		JMP label3

	    label4:
		MOV EAX,Pause
		PUSH EAX
		CALL system
		

	}
	return 0;
}










PBYTE GetDWORDBit(DWORD Dest)
{
	BYTE Return[8] = { 0 };
	__asm
	{
		mov eax,Dest
		and eax, 0xF0000000
		shr eax,0x1C
		mov Return[0],al

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
BYTE GetDWORDBitEx(DWORD Dest,int Pos)
{
	if (Pos > 7 || Pos < 0) return -1;

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

	return Return[Pos];
}