#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e3+5;
const int MAXM = 7e4+5;
const int INF = 1e9;

int n,m;

int cnt=1;
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];

int degree[MAXN];
vector<int>vec[MAXN];

int dis[MAXN];
bool vis[MAXN];

struct compare{
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
         return a.second > b.second; // Ð¡¸ù¶Ñ
    }
};
priority_queue<pair<int,int>,vector<pair<int,int>>,compare>heap;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {
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

void dijstra(){
    for(int i=1;i<=n;i++){
        dis[i]=INF;
    }
    dis[1]=0;
    heap.push({1,0});
    while(!heap.empty()){
        int u=heap.top().first;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                if(degree[v]==0){
                    heap.push({v,dis[v]});
                }
            }
        }
        for(int i=0;i<(int)vec[u].size();i++){
            degree[vec[u][i]]--;
            dis[vec[u][i]]=max(dis[vec[u][i]],dis[u]);
            if(degree[vec[u][i]]==0){
                heap.push({vec[u][i],dis[vec[u][i]]});
            }
        }
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        if(u==v){
            continue;
        }
        addedge(u,v,w);
    }
    for(int i=1;i<=n;i++){
        int t;
        cin>>t;
        if(t){
            degree[i]=t;
            for(int j=1;j<=t;j++){
                int u=read();
                vec[u].push_back(i);
            }
        }
    }
    dijstra();
    cout<<dis[n]<<endl;
    return 0;
}