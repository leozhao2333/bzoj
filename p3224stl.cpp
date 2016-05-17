#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n;
vector<int> a;
void insert(int x){a.insert(upper_bound(a.begin(),a.end(),x),x);}
void del(int x){a.erase(lower_bound(a.begin(),a.end(),x));}
int find(int x){return lower_bound(a.begin(),a.end(),x)-a.begin()+1;}
int main()
{
    n=read();
    a.reserve(200000);
    int f,x;
    for (int i=1;i<=n;i++)
    {
        f=read();x=read();
        switch(f)
        {
            case 1:insert(x);break;
            case 2:del(x);break;
            case 3:printf("%d\n",find(x));break;
            case 4:printf("%d\n",a[x-1]);break;
            case 5:printf("%d\n",*--lower_bound(a.begin(),a.end(),x));break;
            case 6:printf("%d\n",*upper_bound(a.begin(),a.end(),x));break;
        }
    }
}
