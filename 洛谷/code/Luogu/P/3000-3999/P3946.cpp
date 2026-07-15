#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 1e6+5;

int n,m,k,t;
int st,en;

int limit[MAXN];
int dis[MAXN];
bool vis[MAXN];

int cnt = 1;
int head[MAXM];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];

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

inline void addedge(int u, int v, int w) {
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void dijkstra(int st) {
    for (int i = 1; i <= n ; i++) {
        dis[i] = INT_MAX;
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
        if(dis[u]>=limit[u]&&u!=t){
            continue;
        }
        if(u==en){
            break;
        }
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
    n=read(),m=read(),st=read(),en=read();
    t=read(),k=read();
    for(int i=1;i<=n;i++){
        int u,v;
        u=read(),v=read();
        if(k)
            limit[i]=(v-u+k-1)/k;
        else
            limit[i]=INT_MAX;
    }
    // for(int i=1;i<=n;i++){
    //     cout<<limit[i]<<' ';
    // }
    // cout<<endl;
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dijkstra(st);
    if(dis[en]>t){
        cout<<"wtnap wa kotori no oyatsu desu!";
    }
    else{
        cout<<dis[en]<<endl;
    }
    return 0;
}