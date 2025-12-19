#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;
const int INF = 1e18;

int n,m,k,d;

bool vis[MAXN];
int dis1[MAXN];//n到该节点的最短距离
int dis2[MAXN];//k到该节点的最短距离
int dis3[MAXN];//从起点1到这个节点的所有花费最小值
int ans=INF;

int head[MAXN];
int nxt[MAXM << 1];
int to[MAXM << 1];
int cnt = 1;

struct Compare {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    }
};
priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> heap;

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

int get(int l,int r){
	if(l>r){
		return 0;
	}
	return (l+r)*(r-l+1)/2; 
}

int getsum(int x){
	return x/d*get(1,d)+get(d+1-x%d,d);
}

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void bfs(int st,int *dis,bool op){
    deque<int>dq;
    for(int i=1;i<=n;i++){
        dis[i]=INF;
    }
    dis[st]=0;
    dq.push_back(st);
    while(!dq.empty()){
        int u=dq.front();
        dq.pop_front();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(!op){
                if(dis[u]+1<dis[v]){
                    dis[v]=dis[u]+1;
                    dq.push_back(v);
                }
            }
            else{
                if(dis2[v]>=d){
                    ans=min(ans,dis[u]+getsum(dis1[v]+1));
                }
                else if((dis[u]+d-dis2[v])<dis[v]){
                    dis[v]=dis[u]+d-dis2[v];
                    dq.push_back(v);
                }
            }
        }
    }
}

void dijkstra(int st,int *dis,bool op) {
    for (int i = 1; i <= n ; i++) {
        dis[i] = INF;
        vis[i] = false;
    }
    dis[st] = 0;
    heap.push({st, 0});
    while (!heap.empty()) {
        int u = heap.top().first;
        heap.pop();
        if (vis[u]) {
            continue;
        }
        vis[u] = true;
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            int w = 1;
            if(op==false){
                if (dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    heap.push({v, dis[v]});
                }
            }
            else{
                if(dis2[v]>=d){
                    //表示如果这个节点超出了他的范围 那么这两个人就会来到同一个起点
                    //那么这个节点直接跑最短路即可
                    ans=min(ans,dis[u]+getsum(dis1[v]+1));
                }
                else if((dis[u]+d-dis2[v])<dis[v]){
                    dis[v]=dis[u]+d-dis2[v];
                    heap.push({v,dis[v]});
                }
            }
        }
    }
}

signed main()
{
    n=read(),m=read(),k=read(),d=read();
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    // dijkstra(n,dis1,false);
    // dijkstra(k,dis2,false);
    // dijkstra(1,dis3,true);
    bfs(n,dis1,false);
    bfs(k,dis2,false);
    bfs(1,dis3,true);
    ans=min(ans,dis3[n]);
    cout<<ans<<endl;
    return 0;
}