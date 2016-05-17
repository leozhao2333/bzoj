#include <cstdio>  
#include <algorithm>  
#include <cstring>  
#include <cstdlib>  
#include <iostream>  
using namespace std;  
#define LL long long  
#define INF 1000000000  
#define N 1000  
char a[20], b[20];  
int len;  
int dp[20][10][2];  
int dfs(int id, int s, int pre, bool f){  
    if(id >= len){  
        if(s == 1)return 1;  
        else return 0;  
    }  
    if(!f && dp[id][pre][s] != 0)return dp[id][pre][s];  
    int edge = f ? (a[id] - '0') : 9;  
    int ans = 0;  
    for(int i = 0; i <= edge; i++){  
        if(s == 0){  
            if(i == 0)ans += dfs(id + 1, 0, 0, f && i == edge);  
            else ans += dfs(id + 1, 1, i, f && i == edge);  
        }  
        else if(s == 1){  
            if(abs(i - pre) >= 2)ans += dfs(id + 1, 1, i, f && i == edge);  
        }  
    }  
   
    return f ? ans : (dp[id][pre][s] = ans);  
}  
int main(){  
    while(scanf("%s %s", a, b) !=EOF){  
        memset(dp, 0, sizeof(dp));  
        len = strlen(a);  
        int suma = dfs(0, 0, 0, true);  
   
        int f = 1;  
        for(int i = 0; i < len - 1; i++){  
            if(abs(a[i] - a[i + 1]) < 2){f = 0; break;}  
        }  
        strcpy(a, b);  
        len = strlen(a);  
   
        memset(dp, 0, sizeof(dp));  
        int sumb = dfs(0, 0, 0, true);  
        sumb -= suma;  
        sumb += f;  
        printf("%d\n", sumb);  
    }  
    return 0;  
}  
