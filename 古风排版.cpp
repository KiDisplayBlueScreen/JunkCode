// ConsoleApplication5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
using namespace std;
char map[105][105];
int main()
{
	int n;
	char a[5000];
	scanf_s("%d", &n);
	getchar();
	cin.getline(a, 1000);
	for (int i = 0; i <= 100; i++)
		for (int j = 0; j <= 100; j++)
			map[i][j] = ' ';
	int len = strlen(a);
	int x = len / n; //ÐÐ 
	int y = len%n; //Î´ÂúÁÐ
	int t = 0;
	if (y)
	{
		for (int i = x; i >= 1; i--)
		{
			for (int j = 0; j<n; j++)
			{
				map[j][i] = a[t++];
			}
		}
		for (int i = 0; i<y; i++)
			map[i][0] = a[t++];
	}
	else
	{
		x--;
		for (int i = x; i >= 0; i--)
		{
			for (int j = 0; j<n; j++)
				map[j][i] = a[t++];
		}
	}
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j <= x; j++)
			printf("%c", map[i][j]);
		printf("\n");
	}
	system("pause");
}