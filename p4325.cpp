#include<cstdio>
#include<cstring>
using namespace std;
int t,n;
int ans;
int card[20];
//从1到11表示3到K,12表示A,13表示2。14表示小王，15表示大王
void shunzi(int l,int r,int cut)
{
	for (int i=l;i<=r;i++)
	 card[i]=card[i]-cut;
}
void dfs(int temp,int nn)
{
	if (temp>ans)
	 return;
    if (nn==0)
	{ if (temp<ans)
	  ans=temp;
      return;}	  
	for (int i = 1; i <= 13; i++)//顺子左边界
	{
		if (card[i] == 0)
			continue;
		for (int j = i + 1; j <= 12; j++)//单顺子右边界 
		{
			if (!card[j])
				break;
			if (j - i < 4)
				continue;
			else shunzi(i, j, 1), dfs(temp + 1, nn - (j - i + 1)), shunzi(i, j, -1);
		}
		for (int j = i; j <= 12; j++)//双顺子右边界
		{
			if (card[j] < 2)
				break;
			if (j - i < 2)
				continue;
			else shunzi(i, j, 2), dfs(temp + 1, (nn - (j - i + 1)) * 2), shunzi(i, j, -2);
		}
		for (int j = i; j <= 12; j++)//三顺子右边界
		{
			if (card[j] < 3)
				break;
			if (j - i < 1)
				continue;
			else shunzi(i, j, 3), dfs(temp + 1, (nn - (j - i + 1)) * 3), shunzi(i, j, -3);
		}
	 }
	bool flag=false;
	for (int i = 1; i <= 13; i++)//炸弹左边界
	{
		if (card[i] == 4)
		{
			for (int j = 1; j <= 14; j++)//炸弹带双牌
				if (j == i)
					continue;
				else if (card[j] >= 2)
				{
					card[i] -= 4;
					flag = true;
					card[j] -= 2;
					for (int k = 1; k <= 14; k++)
						if (k == i || k == j)
							continue;
						else if (card[k]>=2)
						     {
								 card[k] -= 2;
								 dfs(temp + 1, nn - 8);
								 card[k] += 2;
						      }
					card[i] += 4;
					card[j] += 2;
				}
			for (int j = 1; j <= 14; j++)//炸弹带两只单牌
				if (j == i)
					continue;
				else if (card[j] >= 1)
				{
					card[i] -= 4;
					card[j] -= 1;
					for (int k = 1; k <= 14; k++)
						if (k == i || k == j)
							continue;
						else if (card[k] >= 1)
						{
							card[k] -= 1;
							flag = true;
							dfs(temp + 1, nn - 6);
							card[k] += 1;
						}
					card[j] += 1;
					card[i] += 4;
				}
			card[i] -= 4;//炸弹不带
			dfs(temp + 1, nn - 4);
			card[i] += 4;
		}
	}
	for (int i = 1; i <= 13; i++)//三只左边界
	{
		if (card[i] >= 3)//3带几
		{
			for (int j = 1; j <= 13; j++)//3带1对 
				if (j == i)
					continue;
				else if (card[j] >= 2)
					card[i] -= 3, card[j] -= 2,flag=true, dfs(temp + 1, nn - 5), card[i] += 3, card[j] += 2;
			for (int j = 1; j <= 14; j++)//3带1
				if (j == i)
					continue;
				else if (card[j] >= 1)
					card[i] -= 3, card[j] -= 1, flag=true,dfs(temp + 1, nn - 4), card[i] += 3, card[j] += 1;
			card[i] -= 3;//3不带
			dfs(temp + 1, nn - 3);
			card[i] += 3;
		}
	}
	int tt=0;
	if (!flag)
	{
		for (int i = 1; i <= 14; i++)
			if (card[i] != 0)
				tt++;
		if (temp + tt < ans)
		{
			ans = temp + tt; return;
		}
		else return;
	}
	/*for (int i = 1; i <= 13; i++)//双排左边界
	{
		if (card[i] >= 2)
		{
			card[i] -= 2;
			dfs(temp + 1, nn - 2);
			card[i] += 2;
		}
	}
	for (int i = 1; i <= 13; i++)//单牌右边界
	{
		if (card[i] >= 1)
		{
			card[i] -= 1;
			dfs(temp + 1, nn - 1);
			card[i] += 1;
		}
	}*/
    	
}
int main()
{
	scanf("%d%d",&t,&n);
	for (int I=1;I<=t;I++)
	{
	 memset(card,0,sizeof(card));
	 int xx1,xx2;	
	 for (int i=1;i<=n;i++)
	 {
	  scanf("%d%d",&xx1,&xx2);
	  if (xx1==0)
	  {
			card[14]++;
	  }
	  else {
		  if (xx1 >= 3)card[xx1 - 2]++;
		  if (xx1 <3 )card[xx1 + 11]++;
	  }
     }
	 ans=2147483;
     dfs(0,n);
	 printf("%d\n",ans);
	}
}
