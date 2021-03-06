#include "stdafx.h"
#include <iostream>
#include <Windows.h>
using namespace std;
typedef struct _CPUid
{
	DWORD EAX;
	DWORD EBX;
	DWORD ECX;
	DWORD EDX;
} CPUIDINFO,*PCPUIDINFO;
PCPUIDINFO GetCPUInfo(PCPUIDINFO CPUInfo, int FuncNumber);
PBYTE GetEAXBit(PBYTE EAXbBit, PDWORD EAX);
PBYTE GetEDXBit(PBYTE EDXbBit, PDWORD EDX);
int main()
{
	CPUIDINFO Cpu;
	GetCPUInfo(&Cpu, 1);
	DWORD Eax = Cpu.EAX;
	DWORD Edx = Cpu.EDX;
	BYTE EAXBIT[6] = { 0 };
	BYTE EDXBit[2] = { 0 };
	GetEAXBit(EAXBIT, &Eax);
	GetEDXBit(EDXBit, &Edx);
	BYTE MachineID[8] = { 0 };
	MachineID[0] = EDXBit[1];
	MachineID[1] = EDXBit[0];
	for (int i = 2; i <= 7; i++)
	{
		MachineID[i] = EAXBIT[7 - i];
	}

	for (int i = 0; i <= 7; i++)
	{
		printf("%01X", MachineID[i]);
	}
	cout << endl;

	for (int i = 0; i <= 7; i++)
	{
		if (MachineID[i]>=0xA&& MachineID[i]<=0xF)
		{
			MachineID[i] += 0x37;
		}
		else
		{
			MachineID[i] += 0x30;
		}
	}
	WORD RegCode[8] = { 0 };

	RegCode[0] = MachineID[7] + 0x46;
	RegCode[1] = MachineID[6] + 0x55;
	RegCode[2] = MachineID[5] + 0x43;
	RegCode[3] = MachineID[4] + 0x4B;
	RegCode[4] = MachineID[3] * 4 + 0x80;
	RegCode[5] = MachineID[2] + 0x59;
	RegCode[6] = MachineID[1] + 0x4F;
	RegCode[7] = MachineID[0] + 0x55;
	PDWORD NumberOfBytesWritten =&Edx;
	HANDLE hFile=CreateFile(L"OverSpeed.key", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_DELETE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	WriteFile(hFile, RegCode, 16, NumberOfBytesWritten, 0);

	if (GetLastError() != ERROR_SUCCESS)
	{
		cout << "生成注册文件失败 !" << endl;
	}
	else cout << "生成注册文件成功 !" << endl;
	cout << endl;
	system("pause");
    return 0;
}
PCPUIDINFO GetCPUInfo(PCPUIDINFO CPUInfo,int FuncNumber)
{
	DWORD a;
	DWORD b;
	DWORD c;
	DWORD d;
	__asm
	{
		mov eax,FuncNumber
		cpuid
		mov a,eax
		mov b,edx
		mov c, ecx
		mov d, ebx
	}
	CPUInfo->EAX = a;
	CPUInfo->EBX = d;
	CPUInfo->ECX = c;
	CPUInfo->EDX = b;
	return CPUInfo;
}
PBYTE GetEAXBit(PBYTE EAXbBit,PDWORD EAX)
{
	
	BYTE a = EAXbBit[0];
	BYTE b = EAXbBit[1];
	BYTE c = EAXbBit[2];
	BYTE d= EAXbBit[3];
	BYTE e = EAXbBit[4];
	BYTE f = EAXbBit[5];
	DWORD EAX2 = *EAX;
	__asm
	{
		mov eax, EAX2
		and eax, 0xF
		mov a, al

		mov eax, EAX2
		and eax, 0xF0
		sar eax, 0x4
		mov b, al

		mov eax, EAX2
		and eax, 0xF00
		sar eax, 0x8
		mov c, al

		mov eax, EAX2
		and eax, 0xF000
		sar eax, 0xC
		mov d, al

		mov eax, EAX2
		and eax, 0xF0000
		sar eax, 0x10
		mov e, al

		mov eax, EAX2
		and eax, 0xF00000
		sar eax, 0x14
		mov f, al

	}
	EAXbBit[0] = a;
	EAXbBit[1] = b;
	EAXbBit[2] = c;
	EAXbBit[3] = d;
	EAXbBit[4] = e;
	EAXbBit[5] = f;
	return EAXbBit;
}
PBYTE GetEDXBit(PBYTE EDXbBit, PDWORD EDX)
{
	BYTE a = EDXbBit[0];
	BYTE b = EDXbBit[1];
	DWORD EDX1 = *EDX;
	__asm
	{
		mov eax, EDX1
		and eax, 0xF000000
		sar eax, 0x18
		mov a, al

		mov eax, EDX1
		and eax, 0xF0000000
		shr eax, 0x1C
		mov b, al
	}
	EDXbBit[0] = a;
	EDXbBit[1] = b;
	return EDXbBit;
}