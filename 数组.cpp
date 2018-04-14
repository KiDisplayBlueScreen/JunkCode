#include <iostream>
using namespace std;
int main()
{
  unsigned long i,n;
  int j=1;
  unsigned long t;
  unsigned long a[10];
  for (i=0;i<=9;i++)
  {   cout<<"Pleaes Input No."<<i+1<<"  "<<"Number"<<endl;
	  cin>>n;
      a[i]=n;
  }
cout<<endl;
  for (j=0;j<9;j++)
  for (i=0;i<9-j;i++)
    if (a[i]>a[i+1])
	{ t=a[i];
       a[i]=a[i+1];
	   a[i+1]=t;} 
for (i=0;i<=9;i++)
cout<<a[i]<<endl;
return 0;
}