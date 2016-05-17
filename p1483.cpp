#include<cstdio>
#include<algorithm>
using namespace std;
const int nn=1000001;
int n,m,i,j,k,x,y,ans,a[nn],h[nn],l[nn],t[nn],g[nn],f[nn];
void change(int x,int y){
     for (int i=t[x];i;i=l[i]) ans=ans-(a[i+1]==y)-(a[i-1]==y);
     for (int i=t[x];i;i=l[i]) a[i]=y;
     l[h[x]]=t[y];t[y]=t[x];g[y]+=g[x];
     h[x]=t[x]=g[x]=0;
}
int main(){ 
    scanf("%d%d",&n,&m);
    for (i=1;i<=n;i++){
        scanf("%d",&a[i]);f[a[i]]=a[i];
        if (a[i]!=a[i-1]) ans++;
        if (!t[a[i]]) h[a[i]]=i;
        l[i]=t[a[i]];t[a[i]]=i;g[a[i]]++;
        }
    for (i=1;i<=m;i++){
        scanf("%d",&k);
        if (k==2) printf("%d\n",ans);
             else {scanf("%d%d",&x,&y);
                   if (x==y) continue; 
                   if (g[f[x]]>g[f[y]]) swap(f[x],f[y]);
                   x=f[x];y=f[y];
                   if (g[x]) change(x,y);
                  }
    }
}
