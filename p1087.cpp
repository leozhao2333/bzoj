#include <stdio.h>  
#define MAXN 100  
long long int f[MAXN][MAXN][600],ans; //f[i][j][k]=放棋子到第i行，且已经放了j个棋子，此时第i行状态为k的方案数,ans=最终方案数  
int stay[MAXN]; //stay[i]=第i种可行状态  
int map[MAXN][MAXN],cnt[MAXN]; //cnt[i]=第i种状态对应棋子数  
int n,k,m=0;  
void pre_dfs(int x,int pos,int now) //dfs预处理枚举出同一行内互不冲突的状态,x是已经放了的棋子数,n是当前放棋子的位置,now=当前行状态  
{  
    int i;  
    stay[++m]=now; //新增一种可行状态  
    cnt[m]=x;  
    if(x>=(n+1)/2||x>=k) return; //如果已经放的棋子数超过格子半数,明显不能再放了，退出  
    for(i=pos+2;i<=n;i++)  
        pre_dfs(x+1,i,now+(1<<(i-1))); //枚举下一颗棋子放的位置  
}  
void pre_map()  
{  
    int i,j;  
    for(i=1;i<=m;i++) //第一行状态  
        for(j=1;j<=m;j++) //第二行状态  
        {  
            map[i][j]=map[j][i]=((stay[i]&stay[j])||((stay[i]>>1)&stay[j])||((stay[i]<<1)&stay[j]))?0:1; //当第一行某个点和第二行某个点在对角线或同一列时，两行冲突了  
        }  
    for(i=1;i<=m;i++) //dp预处理  
        f[1][cnt[i]][i]=1;   
}  
int main()  
{  
    int i,j,now,h;  
    scanf("%d%d",&n,&k);  
    pre_dfs(0,-1,0); //预处理枚举出同一行所有可行方案，减少DP循环次数  
    pre_map(); //预处理上下左右冲突的情况以及dp初始化  
    for(i=2;i<=n;i++) //i行  
        for(j=0;j<=k;j++) //j个棋子  
            for(now=1;now<=m;now++)  
            {  
                if(cnt[now]>j) continue; //当前已放的棋子数比这一行状态对应棋子数少，显然不符合题意，跳过  
                for(h=1;h<=m;h++) //枚举上一行状态  
                    if(map[h][now]&&cnt[h]+cnt[now]<=j) f[i][j][now]+=f[i-1][j-cnt[now]][h]; //符合条件，加上上一行的可行方案数  
            }  
    for(i=1;i<=m;i++)  
        ans+=f[n][k][i]; //统计答案  
    printf("%lld\n",ans);  
    return 0;  
} 
