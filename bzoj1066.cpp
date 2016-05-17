#include<iostream>
#include<cstdio>
#include<cstring>
#define inf 0x7fffffff
using namespace std;
struct data{int to,next,v;}e[500001];
int r,c,d,cnt=1,ans,mp[21][21],mark[21][21],q[802],h[802],head[802];
void ins(int u,int v,int w)
{cnt++;e[cnt].to=v;e[cnt].next=head[u];head[u]=cnt;e[cnt].v=w;}
void insert(int u,int v,int w)
{ins(u,v,w);ins(v,u,0);}
bool judge(int x1,int y1,int x2,int y2)
{
	if (((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))<=(d*d)&&mp[x1][y1]&&mp[x2][y2])return 1;
	return 0;
}
void build()
{
	for (int x1=1;x1<=r;x1++)
	 for (int y1=1;y1<=c;y1++)
	  for (int x2=x1-d;x2<=x1+d;x2++)
	   for (int y2=y1-d;y2<=y1+d;y2++)
	if (judge(x1,y1,x2,y2)&&(x1!=x2||y1!=y2))insert(mark[x1][y1]+400,mark[x2][y2],inf);
    for (int i=1;i<=r;i++)
     for (int j=1;j<=c;j++)
		 if (mp[i][j])insert(mark[i][j],mark[i][j]+400,mp[i][j]);	 
}
bool bfs()
{
	memset(h,-1,sizeof(h));
	int t=0,w=1,i,now,q[0]={0},h[0]={0};
	while(t<w)
	{
		now=q[t];t++;i=head[now];
		while (i)
		{
			if (e[i].v&&h[e[i].to]==-1)
			{
				h[e[i].to]=h[now]+1;
				q[w++]=e[i].to;
			}
			i=e[i].next;
		}
	}
	if (h[801]==-1) return 0;return 1;
}
int dfs(int x,int f)
{
	if (x==801) return f;
	int i=head[x],used=0,w;
	while (i)
	{
		if (e[i].v&&h[e[i].to]==h[x]+1)
		{
			w=f-used;w=dfs(e[i].to,min(w,e[i].v));
			e[i].v-=w;e[i^1].v+=w;
			used+=w;if (used==f)return f;
		}
		i=e[i].next;
		}
	if (!used)h[x]=-1;
     return used;	
	}
}
void dinic(){while (bfs())ans-=dfs(0,inf);}
int main()
{
	scanf("%d%d%d",&r,&c,&d);
	char ch[21];
	for (int i=1;i<=r;i++)
	{
		scanf("%s",ch);
		for (int j=1;j<=c;j++)
		 mp[i][j]=ch[j-1]-'0';
	}
	int tot=0;
	for (int i=1;i<=r;i++)
	 for (int j=1;j<=c;j++)
	 {tot++;mark[i][j]=tot;}
    for (int i=1;i<=r;i++)
	{
		scanf("%s,ch");
		for (int j=1;j<=c;j++)
		 if (ch[j-1]=='L')
		 {insert(0,mark[i][j],1);ans++;}
	}
	for (int i=1;i<=d;i++)
	 for (int j=d+1;j<=r-d;j++)
	 {
		 insert(mark[j][i]+400,801,inf);
		 insert(mark[j][c-i+1]+400,801,inf);
	 }
	for (int i=1;i<=d;i++)
     for (int j=d+1;j<=r-d;j++)
	 {
		 insert(mark[i][j]+400,801,inf);
		 insert(marj[r-i+1][j]+400,801,inf);
	 }		 
	 build();
	 dinic();
	 printf("%d",ans);
	 return 0;
}
