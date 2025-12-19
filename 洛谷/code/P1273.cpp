#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int n,m;
int head[3010],k;
int val[3010];//用户为观看比赛而准备支付的钱数
int dp[3010][3010];//dp[i][j]表示i节点，选j个用户，能得到的钱的最大值
struct node{
	int to,next,w;
}edge[6010];

void adde(int u,int v,int w)
{
	edge[++k].to=v; edge[k].next=head[u];
	edge[k].w=w; head[u]=k;
}
int dfs(int u)
{
	if(u>n-m)//u为用户终端
	{
		dp[u][1]=val[u];
		return 1;
	}
	int sum=0,t;
	for(int k=head[u];k;k=edge[k].next)//该点连接了几个节点意为有几组，遍历每一组
	{
		int v=edge[k].to;
		t=dfs(v);
		sum+=t; //t为该组的元素个数，或是说这个儿子为根的子树大小（这里的大小指子树中用户的个数），sum为该节点最多可以选多少个用户，即背包容量
		for(int j=sum;j>0;j--)
		{
			for(int i=1;i<=t;i++)//遍历组中的元素，选多少个用户相当于一个元素
			{
				if(j-i>=0) dp[u][j]=max(dp[u][j],dp[u][j-i]+dp[v][i]-edge[k].w);
			}
		}
	}
	return sum;
}
int main()
{
	memset(dp,~0x3f,sizeof(dp));//初始化一个极大负值，因为dp可能为负
	scanf("%d%d",&n,&m);
	for(int u=1;u<=n-m;u++)
	{
		int size,v,w;
		scanf("%d",&size);
		for(int j=1;j<=size;j++)
		{
			scanf("%d%d",&v,&w);
			adde(u,v,w);
		}
	}
	for(int i=n-m+1;i<=n;i++) scanf("%d",&val[i]);
	for (int i=1;i<=n;i++) dp[i][0]=0;//选0个用户的花费肯定是0啦
	dfs(1);
	for (int i=m;i>=1;i--)
        if (dp[1][i]>=0)
		{
            printf("%d",i);
            break;
        }
	return 0;
}
