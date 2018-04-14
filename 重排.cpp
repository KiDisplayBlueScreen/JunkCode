#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
  double n;
  int j=1,i=1;
  double t;
  double a[11];
  double m;
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
	
  cout<<"这是已经排好的数组,输入一个数将其插入到里面."<<endl;
  for (i=0;i<=9;i++)
  {cout<<setw(8)<<a[i];}
  cout<<endl;

  cin>>m;
  a[10]=m;
  for (j=0;j<10;j++)
  for (i=0;i<10-j;i++)
    if (a[i]>a[i+1])
	{ t=a[i];
       a[i]=a[i+1];
	   a[i+1]=t;} 

   cout<<"这是重排的数组:"<<endl;
   for (i=0;i<=10;i++)
   {cout<<setw(8)<<a[i];}
   cout<<endl;
   return 0;
}