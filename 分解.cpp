#include <iostream>
#include <math.h>
using namespace std;
unsigned long prime(unsigned long x)
 {
 unsigned long m=2;
 for (m=2;m<=sqrt(x);m=m+1)
 if (x%m==0) 
 return 0;
 return 1;
 }
int main()
{ begin:
	unsigned long n,i;
cout<<"���������1���������Խ����������ֽ�."<<endl;
cin>>n;
for (i=1;i<=n;i++)
{if (prime(i)==1&&(n%i)==0) cout<<n<<"="<<i<<"*"<<n/i<<endl;
}
//if (prime(n)==0) cout<<"n��������"<<endl;
//if (prime(n)==1) cout<<"n������"<<endl;
goto begin;
return 0;
}
