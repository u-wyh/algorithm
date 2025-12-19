#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const int MAXM = 120000;

int n,m,k;

int ans[MAXN];
int dis[MAXN];
bool vis[MAXN];

int cnt = 1;
int head[MAXN];
int nxt[MAXM << 1];
int to[MAXM << 1];
int weight[MAXM << 1];

struct Compare {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    }
};
priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> heap;

inline void addedge(int u, int v, int w) {
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

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


void dijkstra(int st,int *dis) {
    for (int i = 1; i <= n+1 ; i++) {
        dis[i] = INT_MAX;
        vis[i]=false;
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
            int w = weight[i];
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                heap.push({v, dis[v]});
            }
        }
    }
}

int main() 
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dijkstra(n,dis);
    for(int i=1;i<=k;i++){
        int v,w;
        v=read(),w=read();
        addedge(n+1,v,dis[v]-w+1e9);//为了防止出现负边权
    }
    dijkstra(n+1,ans);
    for(int i=1;i<n;i++){
        if(ans[i]-1e9<=dis[i]){
            cout<<1<<endl;
        }
        else{
            cout<<0<<endl;
        }
    }
    return 0;
}