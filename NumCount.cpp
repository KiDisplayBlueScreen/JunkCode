#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	begin:
	int i = 0;
	int x = 0;
	cout << "请输入期数:  ";
	cin >> i;
	int* NumCount = new int[i];
	for (x = 0; x < i; x++)
	{
		cout << "请输入第" << x + 1 << "期的号码,不超过12:   ";
		cin >> NumCount[x];
		cout << endl;
	}
	int a1 = 0;
	int a2 = 0;
	int a3 = 0;
	int a4 = 0;
	int a5 = 0; 
	int a6 = 0;
	int a7 = 0;
	int a8 = 0;
	int a9 = 0;
	int a10 = 0;
	int a11= 0;
	int a12 = 0;
	for (x = 0; x < i && NumCount[x] != 0;x++)
	{
		switch (NumCount[x])
		{
		  case 1:
			a1=a1+1;
			break;
		  case 2:
			  a2++;
			  break;
		  case 3:
			  a3++;
			  break;
		  case 4:
			  a4++;
			  break;
		  case 5:
			  a5++;
			  break;
		  case 6:
			  a6++;
			  break;
		  case 7:
			  a7++;
			  break;
		  case 8:
			  a8++;
			  break;
		  case 9:
			  a9++;
			  break;
		  case 10:
			  a10++;
			  break;
		  case 11:
			  a11++;
			  break;
		  case 12:
			  a12++;
			  break;
		}


	}
	cout << "在所有" << i << "期号码中,1号出现了" << a1 << "次." << endl;
	cout << endl;
	cout<<"2号出现了"<<a2 << "次." << endl;
	cout << endl;
	cout << "3号出现了" << a3 << "次." << endl;
	cout << endl;
	cout << "4号出现了" << a4 << "次." << endl;
	cout << endl;
	cout << "5号出现了" << a5 << "次." << endl;
	cout << endl;
	cout << "6号出现了" << a6<< "次." << endl;
	cout << endl;
	cout << "7号出现了" << a7 << "次." << endl;
	cout << endl;
	cout << "8号出现了" << a8 << "次." << endl;
	cout << endl;
	cout << "9号出现了" << a9 << "次." << endl;
	cout << endl;
	cout << "10号出现了" << a10 << "次." << endl;
	cout << endl;
	cout << "11号出现了" << a11<< "次." << endl;
	cout << endl;
	cout << "12号出现了" << a12 << "次." << endl;
	cout << endl;

	goto begin;






	system("pause");




    return 0;
}

