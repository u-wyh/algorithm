#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 3e6+5;

int n,m,c;
int st,en;

int dis[MAXM];
bool vis[MAXM];

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
    for (int i = 0; i <= n ; i++) {
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
    n=read(),m=read(),c=read();
    for(int i=0;i<=n;i++){
        for(int j=1;j<=n;j<<=1){
            if((i^j)>n){
                continue;
            }
            addedge(i,j^i,j*c);
        }
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
    }
    st=read(),en=read();
    dijkstra(st);
    cout<<dis[en]<<endl;
    return 0;
}