#include <iostream>
#include <math.h>
using namespace std;
int main()
{  begin:
   unsigned long n;
   unsigned long i;
   int m;
   cout<<"请输入大于1的n以判断其是否为素数. \n";
   cin>>n;
   if (n==2||n==3||n==5||n==7) cout<<"n是素数. \n";
   else if (n<=0||n==1) {cout<<"输入的n范围不对. \n";goto begin;}
   else if (n%2==0) cout<<"n不是素数 \n";
   else if (n%5==0) cout<<"n不是素数 \n";
   else if (n%2==1) 
   for(i=2;i<=sqrt(n);i=i)
   { i=i+1;
   if (n%i==0) {cout<<"n不是素数. \n";m=0;}
   else continue;
   }  
   cout<<m<<endl;
if (m!=0) cout<<"n是素数."<<endl;
goto begin;
return 0;
}
