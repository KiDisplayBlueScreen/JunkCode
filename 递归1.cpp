#include <iostream>
using namespace std;
int main ()

{   begin:
	cout<<"你想输出第几个斐波那契数呢?"<<endl;
    unsigned long n;
    cin>>n;
	unsigned long Fib(unsigned long a);
	cout<<Fib(n)<<endl;
goto begin;
system ("pause");
return 0;
}
unsigned long Fib(unsigned long a)
{    unsigned long b;
     if (a==1||a==2) b=1;
	 else b=Fib(a-1)+Fib(a-2);
     return b;
}
