#include <iostream>
#include <string>
using namespace std;
int main()

{  begin:
   unsigned long x;  
   cout<<"����һ�������в���ȫ�ֽ�"<<endl;
   cin>>x;
   unsigned long fun(unsigned long a);
   cout<<"����"<<fun(x)<<"����."<<endl;
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
	 cout<<"������"<<a<<"������"<<endl;
	 for (i=1;i<=a;i++) 
	 if (a%i==0) {p[y]=i;y++;}
		 for(y=0;y<k;y++)
         cout<<p[y]<<endl;
 return k;
 }





