#include<cstdio>
#include<string>
#include<iostream>
using namespace std;
long long a[101000];
long long dat[101000];
int n,m;
long long lowbit(long x){return x&-x;}
void add(long long x,long long ii){while (x<=n){a[x]+=ii;x+=lowbit(x);}}
long long ask(long long x)
{long long sum=0;while (x){sum+=a[x];x-=lowbit(x);}return sum;}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &dat[i]),add(i, dat[i]);
	for (int i=1;i<=m;i++)
	{
		string s;
	  	cin>>s;
	  	int ii,x;
	  	if (s[0]=='Q')
	  	{
	  		scanf("%d",&x);
	  		long long sum=0;
	  		for (int j=1;j<=x;j++)
	  		 sum+=(long long)ask(j);
	  		cout<<(long long)sum<<endl; 
		}
	  	else {
	  		   scanf("%d%d",&ii,&x);
	  		   add(ii,(long long)x-dat[ii]);
			   dat[ii] = x;
		     }
	} 
}
