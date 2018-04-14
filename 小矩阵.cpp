#include <iostream>
using namespace std;
int main()
{    int i,j;
     unsigned long a[3][4];
	 unsigned long n;
	 unsigned long max;
     for (i=1;i<=3;i++)
     for (j=1;j<=4;j++)
     {  cout<<"请输入第"<<i<<"行第"<<j<<"列的元素的值"<<endl;
	    cin>>n;
		a[i-1][j-1]=n;
	 }
cout<<endl;
      max=a[0][0];
     for (i=1;i<=3;i++)
     for (j=1;j<=4;j++)
	 {
	 if (a[i-1][j-1]>=max)
		 max=a[i-1][j-1];
	 }
  cout<<"Max="<<max<<endl;
return 0;
}