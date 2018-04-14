#include <iostream>
#include <cmath>
using namespace std;
void main( )
{ begin:
  unsigned long data, i = 2,t;
unsigned long prime(unsigned long x);
  cin>>data;
  t=data;
  if (prime(data)==1) {cout<<1<<"*"<<data<<"="<<data<<endl; goto begin;}
  while(data>1)
    {
      if(data%i == 0)
        {cout<<i<<"*";data=data/i;}
        else i++;
  }
cout<<"="<<t<<endl;
goto begin;
cout<<endl;
}


unsigned long prime(unsigned long x)
{
 unsigned long m=2;
 for (m=2;m<=sqrt(x);m=m+1)
 if (x%m==0) 
 return 0;
 return 1;
 }