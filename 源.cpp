#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
void main()
{
begin:
	unsigned long a[500] = { 0 };
	unsigned long b[500] = { 0 };
	double f;
	int i; int j; int n;
	cout << "Please Input n" << endl;
	cin >> n; 
	cout << endl;
	a[0] = 1; b[1] = 1;
	for (j=0;j<=n;j++)
		for (i=1;(i*(i+1))/2+j<=n;i++)
		       {  
		         if (a[i*(i + 1) / 2 + j]==0)
				 {
					 a[i*(i + 1) / 2 + j] = pow(2, j);
				 }
				 else continue;
		}
	for (j = 1; j <= n; j++)
	{
		b[j] = b[j - 1] + a[j - 1];
		f = log(b[j]) / log(2);
		cout << "前"<<j<<"项和为"<<b[j]<<"它是2的"<<fixed<< setprecision(10) << f<<"次幂" << endl;
		if ((int)f == f&&j > 100)
			cout << "这是符合要求的第" << j << "项"<<endl;
	}
	goto begin;
}