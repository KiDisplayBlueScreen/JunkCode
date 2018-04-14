#include <iostream>
using namespace std;
int main()
{

int i=1,j=1,s;
for (i=1;i<=50;i++)
for (j=1;j<=50;j++)
{   s=i*j;
cout<<i<<"*"<<j<<"="<<s<<"\t";
}
system("pause");
return 0;
}