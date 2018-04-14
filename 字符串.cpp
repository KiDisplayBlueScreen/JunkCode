#include <iostream>
#include <string>
using namespace std;
int main()

{  begin:
   unsigned long x;  
   cout<<"输入一个数进行不完全分解"<<endl;
   cin>>x;
   unsigned long fun(unsigned long a);
   cout<<"共有"<<fun(x)<<"个数."<<endl;
   cout<<endl;
   goto begin;
 }


 unsigned long fun( unsigned long a)
 {
 unsigned long i;
 int k=0;
 int y=0;
 for (i=1;i<=a;i++)
 {if(a%i==0) {k++;}}
     unsigned long *p;
	 p=new unsigned long[k];
	 cout<<"能整除"<<a<<"的数有"<<endl;
	 for (i=1;i<=a;i++) 
	 if (a%i==0) {p[y]=i;y++;}
		 for(y=0;y<k;y++)
         cout<<p[y]<<endl;
 return k;
 }





