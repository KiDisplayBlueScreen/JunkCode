#include "stdafx.h"
#include <Windows.h>
#include <iostream>
using namespace std;
DWORD p(LONG x);
DWORD p1(LONG x);
LONGLONG TimeCount(LONG x);
LONGLONG  TimeCount1(LONG x);
int main()
{
	DWORD x;
	cin >> x;
	LONGLONG time = TimeCount1(x);
	
	char buffer[50];
	sprintf_s(buffer, "Average ExeuteTime: %d Millisecond ", time);
	cout << buffer << endl;

	Sleep(10000);

	time = TimeCount1(x);
	sprintf_s(buffer, "Average ExeuteTime: %d Millisecond ", time);
	cout << buffer << endl;
	
	system("pause");
    return 0;
}
LONGLONG  TimeCount(LONG x)
{
	LONGLONG Time[10];
	LONGLONG Aver=0;
	for (int t = 0; t <= 9; t++)
	{
		LARGE_INTEGER m_Freq = { 0 };
		QueryPerformanceFrequency(&m_Freq);
		LARGE_INTEGER m_liPerfStart = { 0 };
		QueryPerformanceCounter(&m_liPerfStart);

		for (int i = 0; i <= 1000; i++)

		{
			cout << p(x) << endl;

		}
		LARGE_INTEGER liPerfNow = { 0 };
		QueryPerformanceCounter(&liPerfNow);
		Time[t]=(((liPerfNow.QuadPart - m_liPerfStart.QuadPart) * 1000) / m_Freq.QuadPart);
	}
	
	for (int t = 0; t <= 9; t++)
	{
		Aver = Aver + Time[t];
	}

	return (Aver / 10);

}
LONGLONG  TimeCount1(LONG x)
{
	LONGLONG Time[10];
	LONGLONG Aver = 0;
	for (int t = 0; t <= 9; t++)
	{
		LARGE_INTEGER m_Freq = { 0 };
		QueryPerformanceFrequency(&m_Freq);
		LARGE_INTEGER m_liPerfStart = { 0 };
		QueryPerformanceCounter(&m_liPerfStart);

		for (int i = 0; i <= 1000; i++)
		{
			cout << p1(x) << endl;

		}
		LARGE_INTEGER liPerfNow = { 0 };

		QueryPerformanceCounter(&liPerfNow);

		Time[t] = (((liPerfNow.QuadPart - m_liPerfStart.QuadPart) * 1000) / m_Freq.QuadPart);
	}

	for (int t = 0; t <= 9; t++)
	{
		Aver = Aver + Time[t];
	}
	return (Aver / 10);
}
DWORD p(LONG x)
{
	return (2 * x*x*x - 3 * x*x + 5 * x - 4);
}

DWORD p1(LONG x)
{
	return  ((2 * x - 3)*x + 5)*x - 4;
}