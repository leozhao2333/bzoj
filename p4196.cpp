#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110000
#define lson l,mid,root<<1
#define rson mid+1,r,root<<1|1
using namespace std;
int to[N],next[N],head[N],cnt;
int size[N],deep[N],top[N],fa[N];
int son[N],l[N],r[N],rank[N],tot,n;
int sum[N<<2];
bool cov[N<<2],flag[N<<2];
char str[100];
void add(int x,int y){to[++cnt]=y,next[cnt]=head[x],head[x]=cnt;}
void dfs1(int x,int p,int d)
{
	fa[x]=p,deep[x]=d,size[x]=1;
	int i,y,ma;
	for (i=head[x],ma=0;i;i=next[i])
	{
		if ((y=to[i])!=p)
		{
			dfs1(y,x,d+1);
			size[x]+=size[y];
			if (ma<size[y])son[x]=y,ma=size[y];
		}
	}
}
void dfs2(int x,int t)
{
	top[x]=t,l[x]=++tot,rank[tot]=x;
	if (son[x])dfs2(son[x],t);
	int i,y;
	for (i=head[x];i;i=next[i])
	 if ((y=to[i])!=fa[x]&&y!=son[x])dfs2(y,y);
	r[x]=tot;
}
void pushup(int root){sum[root]=sum[root<<1]+sum[root<<1|1];}
void pushdown(int root,int len)
{
	if (cov[root])
	{
		cov[root<<1]=cov[root<<1|1]=1;
		flag[root<<1]=flag[root<<1|1]=flag[root];
		sum[root<<1]=flag[root]?len-(len>>1):0;
		sum[root<<1|1]=flag[root]?len>>1:0;
		cov[root]=0;
	}
}
void update(int l,int r,int root,int st,int en,bool val)
{
	if (st<=l&&r<=en)
	{
		cov[root]=1;
		flag[root]=val;
		sum[root]=(r-l+1)*val;
	}
	else
	{
		int mid=(l+r)>>1;
		pushdown(root,r-l+1);
		if (en<=mid)update(lson,st,en,val);
		else if (st>mid)update(rson,st,en,val);
		     else update(lson,st,en,val),update(rson,st,en,val);
		pushup(root);
	}
}
int query(int l,int r,int root,int st,int en)
{
	if (st<=l&&r<=en)return sum[root];
	else 
	{
		int mid=(l+r)>>1;
		pushdown(root,r-l+1);
		if (en<=mid)return query(lson,st,en);
		else if (st>mid)return query(rson,st,en);
		     else return query(lson,st,en)+query(rson,st,en);
	}
}
int solve1(int x)
{
	int y=0,ret=0;
	while(top[x]!=top[y])
	{
		if (deep[top[x]]<deep[top[y]])swap(x,y);
		ret+=l[x]-l[top[x]]+1-query(1,n,1,l[top[x]],l[x]);
		update(1,n,1,l[top[x]],l[x],1);
		x=fa[top[x]];
	}
	if (deep[x]<deep[y])swap(x,y);
	ret+=l[x]-l[y]+1-query(1,n,1,l[y],l[x]);
	update(1,n,1,l[y],l[x],1);
	return ret;
}
int solve2(int x)
{
	int ret=query(1,n,1,l[x],r[x]);
	update(1,n,1,l[x],r[x],0);
	return ret;
}
int main()
{
	int m,i,j,k,x,y;
	scanf("%d",&n);
	for (i=1;i<n;i++)
	{
		scanf("%d",&x);
		add(x,i);
	}
	dfs1(0,-1,0);
	dfs2(0,-1);
	scanf("%d",&m);
	for (i=1;i<=m;i++)
	{
		scanf("%s%d",str,&x);
		if (str[0]=='i')printf("%d\n",solve1(x));
		else printf("%d\n",solve2(x));
	}
}
