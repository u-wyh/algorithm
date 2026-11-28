// https://www.luogu.com.cn/problem/P2015
// 题意：给定以 1 为根的二叉树，每条边有若干苹果。
// 剪枝后恰留 Q 条仍和根相连的边，求能留下的最大苹果数。
// 数据范围：1 ≤ Q < N ≤ 100，每条边的苹果数 ≤ 3×10^4。
// 难度评分：1500（洛谷分级换算）
// 算法标签：树形动态规划、背包动态规划、深度优先搜索

#include<bits/stdc++.h>
#define ll long long
#define gc getchar
#define maxn 105
using namespace std;

inline ll read(){
	ll a=0;int f=0;char p=gc();
	while(!isdigit(p)){f|=p=='-';p=gc();}
	while(isdigit(p)){a=(a<<3)+(a<<1)+(p^48);p=gc();}
	return f?-a:a;
}int n,m,f[maxn][maxn];

struct ahaha{
	int w,to,next;
}e[maxn<<1];int tot,head[maxn];
inline void add(int u,int v,int w){
	e[tot]={w,v,head[u]};head[u]=tot++;
}

int sz[maxn];
void dfs(int u,int fa){
	for(int i=head[u];~i;i=e[i].next){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);sz[u]+=sz[v]+1;
		for(int j=min(sz[u],m);j;--j)
			for(int k=min(sz[v],j-1);k>=0;--k)
				f[u][j]=max(f[u][j],f[u][j-k-1]+f[v][k]+e[i].w);
	}
}

int main(){memset(head,-1,sizeof head);
	n=read();m=read();
	for(int i=1;i<n;++i){
		int u=read(),v=read(),w=read();
		add(u,v,w);add(v,u,w);
	}
	dfs(1,-1);
	printf("%d\n",f[1][m]);
	return 0;
}
