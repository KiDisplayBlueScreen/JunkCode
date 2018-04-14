#include <iostream>
#include <iomanip>
#define n 5
using namespace std;
int main()
{    unsigned long a[n][n];
     unsigned long i,j;
	 long m=0;
     for (i=0;i<n;i++) 
	 {a[i][0]=1;a[i][i]=1;}

         for (i=2;i<n;i++) 
		 for (j=1;j<=i-1;j++)
		 {a[i][j]=a[i-1][j-1]+a[i-1][j];}

         for (i=0;i<n;i++)
         for (j=0,m=i;j<=i;j++)
		 { cout<<setw(10)<<a[i][j];
		 if (m==j) cout<<endl;
		 }			
	cout<<endl;
return 0;
}