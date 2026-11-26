// https://www.luogu.com.cn/problem/P10535
// 题意：有 n 类、共 2n 种接口，只有 i 和 n+i 能相扣。
// 给 m 种可重复购买的双向线，每种给两端接口和价格。
// 求把接口 S 和 T 的电器连通的最低费用，无解输出 I have no idea how to solve it.。
// 数据范围：1 ≤ n,m ≤ 10^5，接口编号在 [1,2n]，1 ≤ w[i] ≤ 10^9。

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int M=1e6+10;
int n,m;

struct EDGE{
	int v,w;
};
vector<EDGE>G[M];
void add(int u,int v,int w){
	G[u].push_back(EDGE{v,w});
}

int dis[M];
struct NODE{
	int v,id;
	bool operator <(NODE A)const{
		return v>A.v;
	}
};

int cnt=0;
bool pd[M];
void dij(int s){
	for(int i=0;i<M;i++)dis[i]=1e15;
	dis[s]=0;
	priority_queue<NODE>q;
	q.push(NODE{0,s});
	while(!q.empty()){
		NODE zc=q.top();
		q.pop();
		int u=zc.id;
		if(pd[u])continue;
		pd[u]=true;
		for(EDGE it:G[u]){
			int v=it.v,w=it.w;
			if(dis[u]+w<dis[v]){
				dis[v]=dis[u]+w;
				q.push(NODE{dis[v],v});
			}
		}
	}
}
int getf(int x){
	if(x<=4*m+n)return x+n;
	return x-n;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v,w;scanf("%lld%lld%lld",&u,&v,&w);
		add(4*m+v,++cnt,w);
		add(cnt,getf(4*m+u),0);
		add(4*m+u,++cnt,w);
		add(cnt,getf(4*m+v),0);
	}
	int s,t;cin>>s>>t;
	s=getf(4*m+s),t+=4*m;
	dij(s);
	if(dis[t]==1e15)puts("I have no idea how to solve it.");
	else cout<<dis[t]<<endl;
	return 0;
}
