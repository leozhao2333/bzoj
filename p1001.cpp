#include<cstdio>
#include<cstring>
using namespace std;
struct data
{
	int to,next,v;
}e[8000004];
int n,m,nm;
int dis[2000001],q[2000001],head[2000001];
bool flag[2000001];
int ne;
void insert(int u,int v,int w)
{
	ne++;
	e[ne].to=v;
	e[ne].v=w;
	e[ne].next=head[u];
	head[u]=ne;
	ne++;
	e[ne].to=u;
	e[ne].v=w;
	e[ne].next=head[v];
	head[v]=ne;
}
void spfa()
{
	memset(dis,0x3f,sizeof(dis));
	int i,t=0,w=1;
	dis[0]=q[w]=0;flag[0]=1;
	while (t!=w)
	{
		int u=q[t++];
		flag[u]=0;
		if (t==M)t=0;
		for (int i=head[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if (dis[v]>dis[u]+e[i].v)
			{
				dis[v]=dis[u]+e[i].v;
				if (flag[v]==0)
				{
					flag[v]=1;
					q[w++]=v;
					if (w==M)w=0;
				}
			}
		}
	}
}
int main()
{
	scnaf("%d%d",&n,&m);
    nm=n*m;
	int x,y,z;
	for (int j=1;j<=n;j++)
	{
		scanf("%d",&x);
		insert(j,nm+1,x);
	}
	for (int i=1;i<n-1;i++)
	 for (int j=1;j<m;j++)
		 scanf("%d",&x),insert((i<<1)*(m-1)+j,((i<<1)-1)*(m-1)+j,x);
	for (int j=1;j<m;j++)
     scanf("%d",&x),insert(0,((n<<1)-3)*(m-1)+j,x);
    for (int i=0;i<=n-1;i++)
     for (int j=1;j<=m;j++)
	 {
		 scanf("%d",&x);
		 if (j==1)insert(0,(i<<1)*(m-1)+m,x);
		 else if (j==m)insert((i<<1|1)*(m-1),nm+1,x);
		 else insert((i<<1)*(m-1)+j-1,(i<<1)*(m-1)+j+m-1,x);
	 }		 
	for (int i=0;i<n-1;i++)
	 for (int j=1;j<n;j++)
		 scanf("%d",&x),insert((i<<1|1)*(m-1)+j,(i<<1)*(m-1)+j,x);
	spfa();
	printf("%d",dis[nm+1]);
}