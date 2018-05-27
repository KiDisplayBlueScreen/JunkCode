#include "stdafx.h"
#include <Windows.h>
#include <iostream>
using namespace std;
#pragma warning(disable:4996)
LPSTR GetSubString(LPSTR OriginString, LONG StartPos, LONG EndPos);
LPSTR InsertString(LPSTR OriginString, LONG Pos, LPSTR SubString);
int main()
{
	CHAR OriginString[20] = { 0 };
	CHAR SubString[20] = { 0 };
	LONG Pos;
	LONG End;

	cout << "Please Input The OriginString: " << endl;
	cin >> OriginString;
	ENDL

	cout << "Please Input The SubString: " << endl;
	cin >> SubString;
	ENDL

	cout << "Please Input The Position: " << endl;
	cin >> Pos;




	LPSTR NEW=InsertString(OriginString, Pos, SubString);

	printf("New String: %s \n \n", NEW);


	cout << "Please Input The OriginString: " << endl;
	cin >> OriginString;
	ENDL

    cout << "Please Input The SubString Start Pos: " << endl;
	cin >> Pos;
	ENDL

	cout << "Please Input The SubString End Pos: " << endl;
	cin >> End;
	ENDL

	LPSTR Sub = GetSubString(OriginString, Pos, End);

	printf("New String: %s \n", Sub);
	PAUSE;
    return 0;
}
LPSTR GetSubString(LPSTR OriginString, LONG StartPos, LONG EndPos)
{
	ULONG OriginLength = strlen(OriginString);
	if (OriginLength == 0 || StartPos<0 || StartPos>OriginLength || EndPos > OriginLength || StartPos >EndPos)
		return 0;

	LPSTR SubString = (LPSTR)malloc(EndPos-StartPos+ 1);
	ZeroMemory(SubString, EndPos - StartPos + 1);
	memcpy(SubString, &OriginString[StartPos - 1], EndPos - StartPos);

	return SubString;
}
LPSTR InsertString(LPSTR OriginString, LONG Pos, LPSTR SubString)
{
	if (OriginString == NULL || SubString == NULL) return 0;

	ULONG OriginLength = strlen(OriginString);
	ULONG SubLength = strlen(SubString);
	ULONG TotalLength = OriginLength + SubLength;
	LPSTR NewString = NULL;
	int i = 0;

	if (Pos<0 || Pos>OriginLength  || OriginLength == 0) return 0;

	if (Pos == 0)
	{
		NewString = (LPSTR)malloc(TotalLength + 1);
		ZeroMemory(NewString, TotalLength + 1);
		strcat_s(NewString, TotalLength + 1, (LPCSTR)SubString);
		strcat_s(NewString, TotalLength + 1, (LPCSTR)OriginString);
		return NewString;
	}

	if (Pos == OriginLength)
	{
		NewString = (LPSTR)malloc(TotalLength + 1);
		ZeroMemory(NewString, TotalLength + 1);
		strcat_s(NewString, TotalLength, (LPCSTR)OriginString);
		strcat_s(NewString, TotalLength, (LPCSTR)SubString);
		return NewString;

	}

	NewString = (LPSTR)malloc(TotalLength + 1);
	ZeroMemory(NewString, TotalLength + 1);

	memcpy(NewString, OriginString, Pos);
	strcat_s(NewString, TotalLength, (LPCSTR)SubString);
	memcpy(&NewString[Pos + SubLength], &OriginString[Pos], OriginLength - Pos);

	return NewString;
}
