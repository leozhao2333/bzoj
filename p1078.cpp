#include<cstdio>
#include<algorithm>
using namespace std;
struct node
{
    int left,right,father;
}tree[200];
int ans[200],n,root;
void get(int x,int now)
{
    if ((!tree[x].right&&!tree[x].left)||(!tree[x].right&&tree[x].left&&(tree[tree[x].left].left)))
    {
        tree[tree[x].father].left=tree[x].left;
        if (tree[x].left)
            tree[tree[x].left].father=tree[x].father;
        ans[now]=x;
        if (!tree[x].father) root=tree[x].left;
        return;
    }
    get(tree[x].left,now);
    swap(tree[x].left,tree[x].right);
}
int main()
{
    root=1;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        x++;
        if (x<100)
        tree[x].left=i+1,tree[i+1].father=x;
        else x-=100,tree[x].right=i+1,tree[i+1].father=x;
    }
    tree[1].father=0;
    for (int i=n+1;i;i--)
     get(root,i);
    for (int i=1;i<=n;i++)
     printf("%d ",ans[i]-1);
    printf("%d",ans[n+1]-1);
}
