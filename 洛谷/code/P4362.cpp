// https://www.luogu.com.cn/problem/P4362
// 题意：把一棵 N 个节点（最大果子为 1 号）的带权树分成 M 个非空组给 M 个头吃，大头必须吃恰好 K 个且包含 1 号节点
// 同一头吃下树枝两端则产生该边权值 c 的难受值，求最小总难受值（无解输出 -1）。
// 数据范围：1 <= N <= 300，2 <= M <= N，1 <= K <= N，1 <= a, b <= N，0 <= c <= 10^5。
#include<iostream>
#include<cstdio>
#include<cstring>
// 算法标签：树形动态规划、树上背包
using namespace std;
const int N=1000+4;
struct Edge{int v,w,nxt;}e[N<<1];
int h[N],f[N][N][2],tmp[N][2];
int tot,m,n,k;
inline void add(int u,int v,int w){
	e[++tot]=(Edge){v,w,h[u]};
	h[u]=tot;
}
void dfs(int u,int fa){
	f[u][0][0]=f[u][1][1]=0;
	for(int i=h[u];i;i=e[i].nxt){
		int v=e[i].v,w=e[i].w;
		if(v==fa) continue;
		dfs(v,u);
		memcpy(tmp,f[u],sizeof(f[u]));
		memset(f[u],0x3f,sizeof(f[u]));
		for(int j=0;j<=k;++j){
			for(int t=0;t<=j;++t){
				f[u][j][0]=min(f[u][j][0],min(f[v][t][0]+tmp[j-t][0]+(m==2)*w,f[v][t][1]+tmp[j-t][0]));
				f[u][j][1]=min(f[u][j][1],min(f[v][t][1]+tmp[j-t][1]+w,f[v][t][0]+tmp[j-t][1]));
			}
		}
	}
}
int main(){
	memset(f,0x3f,sizeof(f));
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1,u,v,w;i<n;++i){
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w),add(v,u,w);
	}
	if(n-k<m-1){printf("-1\n");return 0;}
	dfs(1,0);
	printf("%d\n",f[1][k][1]);
	return 0;
}
