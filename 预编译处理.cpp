#include <iostream>
#include <cmath>
using namespace std;
int main()
{begin:
float e(float x,long n);
unsigned long f(long n);
float x;
long n;
cout<<"����ָ��x"<<endl;
cin>>x;
cout<<"��������n"<<endl;
cin>>n;
cout<<"e��"<<x<<"���ݵļ��㵽��"<<n<<"��Ľ���ֵ��:"<<e(x,n-1)<<endl;
cout<<endl;
goto begin;
return 0;
}

float e(float x,long n)
{
unsigned long f(long n);
long i=0;float s=0;
for (i=0;i<=n;i++)
s=s+pow(x,i)/f(i);
return s;
}

unsigned long f(long n)
{
long j=1;
long t;
for (j=1,t=1;j<=n;j++)
t=t*j;
return t;
}