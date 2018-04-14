#include <iostream>
using namespace std;
void main()
{
unsigned long a[10],n,i,j,t,u;
int x;
for (x=0;x<=9;x++)
{cout<<"Please Input No." <<x+1<<"  Numbers"<<endl;
cin>>n;
a[x]=n;}
cout<<endl;
i=a[0];j=a[0];

for (x=0;x<9;x++)
{ 
if(i<=a[x+1]) i=a[x+1]; 
 else continue; }

 

for (x=0;x<9;x++)
{ 
if(j>=a[x+1]) j=a[x+1]; 
 else continue; }


for (x=0;x<9;x++)
{if(i==a[x]) i=x;
else continue; }


for (x=0;x<9;x++)
{if(j==a[x]) j=x;
else continue; }


t=a[i];
a[i]=a[0];
a[0]=t;

u=a[j];
a[j]=a[9];
a[9]=u;

for (x=0;x<=9;x++)
cout<<a[x]<<endl;

}