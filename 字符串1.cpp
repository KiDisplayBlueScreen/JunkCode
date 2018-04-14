#include <iostream>
using namespace std;
void main()
{
	int a[19]={2,2,2,3,4,4,5,6,6,6,6,7,7,8,9,9,10,10,10};
	int t=2,i;
	for (i=1;i<=18;i=i+1)
    { 
	if (t==a[i]) a[i]=0;
	else if (t!=a[i]) t=a[i];}
	for (i=0;i<=18;i++)
	if(a[i]!=0)	
		cout<<a[i]<<endl;

}