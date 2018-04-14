#include <iostream>
#include <string>
using namespace std;
int main()
{
	int a[5]={75,97,70,88,10};
	string str[5]={"ÌøÎè½©Ê¬","Ù¤¸ÕÌØ¶û","°ôÇò½©Ê¬","±ùÄ¢¹½","Ì«Ñô»¨"};
    int i,j,t;
	for (j=0;j<4;j++)
		for(i=0;i<4-j;i++)
        { if (a[i]<a[i+1])
		{t=a[i];
		a[i]=a[i+1];
		a[i+1]=t;}
}
for(i=0;i<5;i++)
cout<<str[i]<<"="<<a[i]<<endl;
return 0;
}