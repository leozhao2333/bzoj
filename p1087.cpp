#include <stdio.h>  
#define MAXN 100  
long long int f[MAXN][MAXN][600],ans; //f[i][j][k]=�����ӵ���i�У����Ѿ�����j�����ӣ���ʱ��i��״̬Ϊk�ķ�����,ans=���շ�����  
int stay[MAXN]; //stay[i]=��i�ֿ���״̬  
int map[MAXN][MAXN],cnt[MAXN]; //cnt[i]=��i��״̬��Ӧ������  
int n,k,m=0;  
void pre_dfs(int x,int pos,int now) //dfsԤ����ö�ٳ�ͬһ���ڻ�����ͻ��״̬,x���Ѿ����˵�������,n�ǵ�ǰ�����ӵ�λ��,now=��ǰ��״̬  
{  
    int i;  
    stay[++m]=now; //����һ�ֿ���״̬  
    cnt[m]=x;  
    if(x>=(n+1)/2||x>=k) return; //����Ѿ��ŵ��������������Ӱ���,���Բ����ٷ��ˣ��˳�  
    for(i=pos+2;i<=n;i++)  
        pre_dfs(x+1,i,now+(1<<(i-1))); //ö����һ�����ӷŵ�λ��  
}  
void pre_map()  
{  
    int i,j;  
    for(i=1;i<=m;i++) //��һ��״̬  
        for(j=1;j<=m;j++) //�ڶ���״̬  
        {  
            map[i][j]=map[j][i]=((stay[i]&stay[j])||((stay[i]>>1)&stay[j])||((stay[i]<<1)&stay[j]))?0:1; //����һ��ĳ����͵ڶ���ĳ�����ڶԽ��߻�ͬһ��ʱ�����г�ͻ��  
        }  
    for(i=1;i<=m;i++) //dpԤ����  
        f[1][cnt[i]][i]=1;   
}  
int main()  
{  
    int i,j,now,h;  
    scanf("%d%d",&n,&k);  
    pre_dfs(0,-1,0); //Ԥ����ö�ٳ�ͬһ�����п��з���������DPѭ������  
    pre_map(); //Ԥ�����������ҳ�ͻ������Լ�dp��ʼ��  
    for(i=2;i<=n;i++) //i��  
        for(j=0;j<=k;j++) //j������  
            for(now=1;now<=m;now++)  
            {  
                if(cnt[now]>j) continue; //��ǰ�ѷŵ�����������һ��״̬��Ӧ�������٣���Ȼ���������⣬����  
                for(h=1;h<=m;h++) //ö����һ��״̬  
                    if(map[h][now]&&cnt[h]+cnt[now]<=j) f[i][j][now]+=f[i-1][j-cnt[now]][h]; //����������������һ�еĿ��з�����  
            }  
    for(i=1;i<=m;i++)  
        ans+=f[n][k][i]; //ͳ�ƴ�  
    printf("%lld\n",ans);  
    return 0;  
} 
