#include<cstdio>
#include<cstring>
using namespace std;
int treeleft[500008],tree[500008],treeright[500008],treefather[500008];
int totson[500008];
int n,opt,x,t,tt,root,sum_node;
int abs(int a){return (a>=0)?a:-a;}
int min(int a,int b){return (a<b)?a:b;}
int max(int a,int b){return (a>b)?a:b;}
void countagain(int node)
{
    totson[node]=1;
    if (treeleft[node]>0)
        totson[node]=totson[node]+totson[treeleft[node]];
    if (treeright[node]>0)
        totson[node]=totson[node]+totson[treeright[node]];
}
void leftrotate(int node1,int node2)
{
    if (treeleft[treefather[node2]]==node2)
        treeleft[treefather[node2]]=node1;
    else treeright[treefather[node2]]=node1;
    treefather[node1]=treefather[node2];
    treeleft[node2]=treeright[node1];
    treefather[treeright[node1]]=node2;
    treefather[node2]=node1;
    treeright[node1]=node2;
    countagain(node2);
    countagain(node1);
}
void rightrotate(int node1,int node2)
{
     if (treeleft[treefather[node2]]==node2)
         treeleft[treefather[node2]]=node1;
     else treeright[treefather[node2]]=node1;
     treefather[node1]=treefather[node2];
     treeright[node2]=treeleft[node1];
     treefather[treeleft[node1]]=node2;
     treefather[node2]=node1;
     treeleft[node1]=node2;
     countagain(node2);
     countagain(node1);
}
void splay(int node)
{
    if (treefather[node]==0)
    {
        root=node;
        return;
    }
    int father=treefather[node];
    if (treefather[father]==0)
    {
        if (treeleft[father]==node)
            leftrotate(node,father);
        else rightrotate(node,father);
    }
    else
    {
        if (treeleft[treefather[father]]==father)
        {
            if (treeleft[father]==node)
                leftrotate(father,treefather[father]),leftrotate(node,father);
            else rightrotate(node,father),leftrotate(node,treefather[node]);
        }
        else
        {
            if (treeleft[father]==node)
                leftrotate(node,father),rightrotate(node,treefather[node]);
            else rightrotate(father,treefather[father]),rightrotate(node,father);
        }
    }
    splay(node);
    return;
}
void norootsplay(int node)
{
    if (treefather[node]==0)
        return;
    int father=treefather[node];
    if (treefather[father]==0)
    {
        if (treeleft[father]==node)
            leftrotate(node,father);
        else rightrotate(node,father);
    }
    else
    {
        if (treeleft[treefather[father]]==father)
        {
            if (treeleft[father]==node)
                leftrotate(father,treefather[father]),leftrotate(node,father);
            else rightrotate(node,father),leftrotate(node,treefather[node]);
        }
        else
        {
            if (treeleft[father]==node)
                leftrotate(node,father),rightrotate(node,treefather[node]);
            else rightrotate(father,treefather[father]),rightrotate(node,father);
        }
    }
    norootsplay(node);
}
void newnode(int node,int x,int father)
{
    totson[node]++;
    if (tree[node]<-200000000)
    {
        tree[node]=x;
        treefather[node]=father;
        return;
    }
    if (tree[node]>x)
    {
        if (treeleft[node]>0)
            newnode(treeleft[node],x,node);
        else
        {
            treeleft[node]=sum_node;
            newnode(treeleft[node],x,node);
        }
    }
    else
    {
        if (treeright[node]>0)
            newnode(treeright[node],x,node);
        else
        {
            treeright[node]=sum_node;
            newnode(treeright[node],x,node);
        }
    }
    return;
}
void addnode(int x)
{
    sum_node++;
    if (root==0)
        root=sum_node;
    newnode(root,x,0);
    splay(sum_node);
}
int lookforclearing(int node,int x)
{
    totson[node]--;
    if (tree[node]==x)
      return node;
    if (tree[node]>x)
      return lookforclearing(treeleft[node],x);
    else return lookforclearing(treeright[node],x);  
}
int getmax(int node)
{
    if (treeright[node]>0)
     return getmax(treeright[node]);
    else return node; 
}
int join(int root1,int root2)
{
    int t=getmax(root1);
    norootsplay(t);
    treefather[root2]=t;
    treeright[t]=root2;
    countagain(t);
    return t;
}
void deletenode(int x)
{
    int t=lookforclearing(root,x);
    int s1=treeleft[t],s2=treeright[t];
    if ((s1>0)&&(s2>0))
    {
        treefather[s1]=0,treefather[s2]=0;
        int r=join(s1,s2);
        treefather[r]=treefather[t];
        if (treefather[t]>0)
        {
            if (t==treeleft[treefather[t]])
                treeleft[treefather[t]]=r;
            else treeright[treefather[t]]=r;
        }
        splay(r);
        return;
    }
    if (s1>0)
    {
        treefather[s1]=treefather[t];
        if (treefather[t]>0)
        {
            if (t==treeleft[treefather[t]])
                treeleft[treefather[t]]=s1;
            else treeright[treefather[t]]=s1;
        }
        splay(s1);
        return;
    }
    if (s2>0)
    {
        treefather[s2]=treefather[t];
        if (treefather[t]>0)
        {
            if (t==treeleft[treefather[t]])
                treeleft[treefather[t]]=s2;
            else treeright[treefather[t]]=s2;
        }
        splay(s2);
        return;
    }
    if (treefather[t]>0)
    {
        if (t==treeleft[treefather[t]])
            treeleft[treefather[t]]=0;
        else treeright[treefather[t]]=0;
        countagain(treefather[t]);
        splay(treefather[t]);
        return;
    }
    root=0;
    return;
}
void asknum(int node,int x)
{
    if (tree[node]>=x)
    {
        if (treeleft[node]>0)
            asknum(treeleft[node],x);
    }
    else
    {
        if (treeleft[node]>0)
            tt=tt+totson[treeleft[node]]+1;
        else tt++;
        if (treeright[node]>0)
            asknum(treeright[node],x);
    }
    return;
}
int askrank(int node,int x)
{
    if (totson[treeleft[node]]>=x)
        return askrank(treeleft[node],x);
    if (totson[treeleft[node]]<x-1)
        return askrank(treeright[node],x-totson[treeleft[node]]-1);
    return tree[node];
}
void pred(int node,int x)
{
    if (tree[node]>=x)
    {
        if (treeleft[node]>0)
            pred(treeleft[node],x);
    }
    else
    {
        tt=max(tt,tree[node]);
        if (treeright[node]>0)
            pred(treeright[node],x);
    }
}
void next(int node,int x)
{
    if (tree[node]<=x)
    {
        if (treeright[node]>0)
            next(treeright[node],x);
    }
    else
    {
        tt=min(tt,tree[node]);
        if (treeleft[node]>0)
            next(treeleft[node],x);
    }
}
int main()
{
    scanf("%d",&n);
    memset(tree,240,sizeof(tree));
    for (int i=1;i<=n;i++)
    {
        scanf("%d%d",&opt,&x);
        switch(opt)
        {
            case 1:addnode(x);break;
            case 2:deletenode(x);break;
            case 3:tt=0,asknum(root,x),printf("%d\n",tt+1);break;
            case 4:printf("%d\n",askrank(root,x));break;
            case 5:tt=-200000000,pred(root,x),printf("%d\n",tt);break;
            case 6:tt=200000000,next(root,x),printf("%d\n",tt);break;
        }
    }
}
