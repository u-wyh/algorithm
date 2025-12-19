#include<stdio.h>
#include<cstring>
#include<queue>
#define min(a,b) a<b?a:b
#define max(a,b) a>b?a:b
using namespace std;
int n,m;
struct edge{
	int to,nxt;
}e[50005];//使用链式前向星存图
int hed[50005],cnt;//注意每组数据开始前要把hed和cnt数组清零

inline void add(int u,int v){
	e[++cnt].to = v;
	e[cnt].nxt = hed[u];
	hed[u] = cnt;
}

bool vis[1005];//记得清零

struct node{
	int tp,dis;//tp:当前点的编号;dis:从起点到这个点的距离
};

int ans = -1;//最终的答案
inline void bfs(int s){
	queue<node> q;
	q.push((node){s,0});//初始状态
	vis[s] = true;
	while(!q.empty()){
		node fr = q.front();
		q.pop();
		int u = fr.tp,dis = fr.dis;
		ans = max(ans,dis);//在遍历每个点的时候更新答案
		for(int i = hed[u];i;i = e[i].nxt){
			int v = e[i].to;
			if(vis[v]) continue;
			q.push((node){v,dis+1});
			vis[v] = true;
		}
	}
}
int main(){
	while(true){
		scanf("%d%d",&n,&m);
		if(n==0 && m==0) break;
		ans = -1;//清零
		memset(hed,0,sizeof(hed));
		cnt = 0;
		int u,v;
		for(register int i = 1;i<=m;++i){
			scanf("%d%d",&u,&v);
			add(u,v),add(v,u);//加双向边
		}
		for(register int i = 1;i<=n;++i){//以i为起点进行bfs
			memset(vis,false,sizeof(vis));//每次bfs开始前进行清零
			bfs(i);
		}
		printf("%d\n",ans*100);
	}
	return 0;
}
