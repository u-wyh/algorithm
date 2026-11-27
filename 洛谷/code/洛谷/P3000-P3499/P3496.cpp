// https://www.luogu.com.cn/problem/P3496
// 题意：输入城镇数 n（1..n）和双向道路数 m，以及 m 条道路连接关系。
// 要求给每个城镇标记为 K（裁缝行会）、S（缝纫行会）或 N（无行会），
// 使得任意城镇要么自身是 K，要么与至少一个 K 相邻；对 S 同理。
// 若无合法方案输出 NIE；
// 否则第一行输出 TAK，随后 n 行输出每个城镇的字母 K、S 或 N。
// 数据范围：1 <= n <= 200000，0 <= m <= 500000。
// 算法标签：贪心、图论
#include<cstdio>
using namespace std;
const int MAXN=200010,MAXM=1000010;//注意边数要乘2

int h[MAXN],color[MAXN],tot=0;//h为邻接表中的head，tot为总边数
bool vis[MAXN];//记录是否有连接
struct Edge{//边的结构体
	int v;
	int next;//next记录这条边在邻接表中指向同端点的另一条边
}e[MAXM];

void addEdge(int u,int v){//建边
	tot++;
	e[tot].v=v;
	e[tot].next=h[u],h[u]=tot;
}

void dfs(int u){//深搜，u为原节点，保证已染色
	for(int k=h[u];k;k=e[k].next){//邻接表查找
		int v=e[k].v;
		color[v]=color[u]%2+1;//公式
	}
}

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	while(m--){
		int uu,vv;
		scanf("%d%d",&uu,&vv);
		vis[uu]=1,vis[vv]=1;//记录
		addEdge(uu,vv);addEdge(vv,uu);//建边
	}
	for(int i=1;i<=n;i++)//判断是否不行
	    if(!vis[i]){
	    	printf("NIE\n");//输出
	    	return 0;//返回
		}
	printf("TAK\n");//直接输出
	for(int i=1;i<=n;i++)//每个点都搜一遍
		if(!color[i]){//没搜过
			color[i]=1;//先设为白点
			dfs(i);//开搜
		}
	for(int i=1;i<=n;i++){//输出
		if(color[i]==1) printf("K\n");
		else printf("S\n");
	}
	return 0;//华丽结束
}
