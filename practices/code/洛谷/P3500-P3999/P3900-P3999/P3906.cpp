// https://www.luogu.com.cn/problem/P3906
// 题意：给定一个 n 个点 m 条边的无向连通简单图（边权均为 1）
// 以及 k 个点对 (v, u)。
// 对每对 (v, u)，
// 按编号升序输出所有位于 v 到 u 的
// 至少一条最短路径上的顶点集合 I(v, u)。
// 数据范围：1 <= n <= 40，1 <= m, k <= n(n-1)/2。
// 难度评分：1300（洛谷分级换算）
// 算法标签：广度优先搜索、最短路
#include<bits/stdc++.h>
using namespace std;

queue<int>q;
bool ans[41];
int a[41][41],pre[41][41],num[41],dis[41],n;

void bfs(int s,int t){
	memset(num,0,sizeof num),memset(dis,63,sizeof dis);  //  忘了清数组会爆0
	dis[s]=0,q.push(s);
	while(!q.empty()){
		s=q.front(),q.pop();
		for(int i=1;i<=n;i++) if(a[s][i])
			if(dis[i]>dis[s]+1)
				dis[i]=dis[s]+1,pre[i][++num[i]]=s,q.push(i);
			else if(dis[i]==dis[s]+1) pre[i][++num[i]]=s;  //  分情况记录前驱
	}
	memset(ans,0,sizeof ans),q.push(t),ans[t]=1;
	while(!q.empty()){
		s=q.front(),q.pop();
		for(int i=num[s];i;i--) if(!ans[pre[s][i]])
			ans[pre[s][i]]=1,q.push(pre[s][i]);  //  倒着搜回去
	}
	for(int i=1;i<=n;i++) if(ans[i]) printf("%d ",i);
}
int main(){
	int m,q,x,y;
	scanf("%d%d",&n,&m);
	while(m--) scanf("%d%d",&x,&y),a[x][y]=1,a[y][x]=1;
	scanf("%d",&q);
	while(q--) scanf("%d%d",&x,&y),bfs(x,y),putchar('\n');
	return 0;
}
