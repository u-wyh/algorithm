//https://www.luogu.com.cn/problem/P10193
// 这道题目很创新 考察对DJ算法的理解程度
// 他的源点不再仅仅只是一个了  而是有很多个
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const int MAXM = 2e5+5;

int n,m,c,r,k;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt = 1;

struct node{
	int id,dis,pre;
	//表示当前来到的节点编号  pre表示的是目前这个最短路径是由那个源点出发得来的  dis表示从pre源点出发的到id这个点的最短距离
};
struct Compare {
    bool operator()(const node& a, const node& b) {
        return a.dis > b.dis;
    }
};
priority_queue<node, vector<node>, Compare> heap;
map<int,bool>vis[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dijkstra(){
	for(int i=1;i<=c;i++){
		heap.push({i,0,i});
	}
	while(!heap.empty()){
		node now=heap.top();
		heap.pop();
		int u=now.id;
		int dis=now.dis;
		int pre=now.pre;

		if (vis[u].size() >= k || vis[u].count(pre)) {
            //表示这个节点已经是符合要求的了  或者  以前就已经完成了从pre这个源点出发的最短路
            continue;
        }
		vis[u][pre] = true;
        for(int i=head[u];i;i=nxt[i]){
			int v=to[i];
			int w=weight[i];
			int d=w+dis;
			if(d>r||vis[v].size()>=k||vis[v].count(pre)){
				continue;
			}
			heap.push({v,d,pre});
		}
	}
}

int main()
{
	n=read(),m=read(),c=read(),r=read(),k=read();
	for(int i=1;i<=m;i++){
		int u,v,w;
		u=read(),v=read(),w=read();
		addedge(u,v,w);
		addedge(v,u,w);
	}
	dijkstra();
	vector<int> vec;
    for (int i = c + 1; i <= n; i++) {
        if (vis[i].size() >= k) {
            vec.push_back(i);
        }
    }
    
    cout << vec.size() << '\n';
    for (int to : vec) {
        cout << to << '\n';
    }
	return 0;
}