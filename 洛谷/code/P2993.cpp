// https://www.luogu.com.cn/problem/P2993
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e4+5;
const int MAXM = 6e4+5;
const int INF = 1e9;

int n,m,k;

int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int weight[MAXM<<1];
int cntg=1;

int headg[MAXN];
int nxtg[MAXN<<1];
int tog[MAXN<<1];
int weightg[MAXN<<1];
int cntt=1;

struct cmp{
    bool operator()(const pair<int,int> a,const pair<int,int> b){
        return a.first>b.first;
    }
};
priority_queue<pair<int,int>,vector<pair<int,int>>,cmp>heap;

int dis[MAXN];
int dep[MAXN];
bool vis[MAXN];

struct Point{
    int dis,id;
};
Point point[MAXN];
bool cpmpare(Point &a,Point &b){
    if(a.dis!=b.dis){
        return a.dis<b.dis;
    }
    return a.id<b.id;
}

inline void addedge(int u,int v,int w){
    nxt[cntg]=head[u];
    to[cntg]=v;
    weight[cntg]=w;
    head[u]=cntg++;
}

inline void addedgeg(int u,int v,int w){
    nxtg[cntt]=headg[u];
    tog[cntt]=v;
    weightg[cntt]=w;
    headg[u]=cntt++;
}

void dijkstra(int s){
    for(int i=1;i<=n;i++){
        dis[i]=INF;
    }
    dis[s]=0;
    heap.push({0,s});
    while(!heap.empty()){
        int u=heap.top().second;
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
                heap.push({dis[v],v});
            }
        }
    }
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        if(v!=fa){
            dfs(v,u);
        }
    }
}

vector<int> edges[MAXN];
void dfsBuild(int u){
    vis[u]=true;

    for(int i:edges[u]){
        int v=to[i];
        int w=weight[i];

        if(!vis[v]&&dis[u]+w==dis[v]){
            addedgeg(u,v,w);
            addedgeg(v,u,w);
            dfsBuild(v);
        }
    }
}
void build(){
    for(int u=1;u<=n;u++){
        vis[u]=false;

        for(int i=head[u];i;i=nxt[i]){
            edges[u].push_back(i);
        }

        sort(edges[u].begin(),edges[u].end(),
            [](int a,int b){
                return to[a]<to[b];
            }
        );
    }

    dfsBuild(1);
    dfs(1,0);
    for(int i=1;i<=n;i++){
        vis[i]=false;
    }
}

// void build(){
//     for(int i=1;i<=n;i++){
//         vis[i]=false;
//     }
//     for(int u=2;u<=n;u++){
//         int pv=n+1,pw=0;
//         for(int i=head[u];i;i=nxt[i]){
//             int v=to[i];
//             int w=weight[i];

//             if((dis[v]+w==dis[u])&&(v<pv)){
//                 pv=v;
//                 pw=w;
//             }
//         }
//         addedgeg(pv,u,pw);
//         addedgeg(u,pv,pw);
//     }
//     dfs(1,0);
// }

int sz[MAXN];

void getSize(int u,int fa){
    sz[u]=1;
    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        if(v!=fa&&!vis[v]){
            getSize(v,u);
            sz[u]+=sz[v];
        }
    }
}

int getCentroid(int u,int fa){
    getSize(u,fa);
    int half=sz[u]>>1;
    bool find=false;
    while(!find){
        find=true;
        for(int i=headg[u];i;i=nxtg[i]){
            int v=tog[i];
            if(v!=fa&&!vis[v]&&sz[v]>half){
                fa=u;
                u=v;
                find=false;
                break;
            }
        }
    }
    return u;
}

int ans,ways;
int best[MAXN];
int cnt1[MAXN];
int tmp[MAXN];
int cnt2[MAXN];
int maxdep;
int maxlen;

void dfs1(int u,int fa,int d,int dist){
    maxlen=max(maxlen,d);
    // tmp[d]=max(tmp[d],dist);
    if(tmp[d]<dist){
        cnt2[d]=1;
        tmp[d]=dist;
    }
    else if(tmp[d]==dist){
        cnt2[d]++;
    }
    // if(tmp[d]==dist&&d<=k-1){
    //     int res=tmp[d]+best[k-d-1];
    //     if(res==ans){
    //         ways+=cnt1[k-d-1];
    //     }
    //     else if(res>ans){
    //         ways=cnt1[k-d-1];
    //         ans=res;
    //     }
    // }
    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        int w=weightg[i];
        if(v!=fa&&!vis[v]){
            dfs1(v,u,d+1,dist+w);
        }
    }
}

void calc(int u){
    maxdep=0;
    cnt1[0]=1;
    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        int w=weightg[i];
        if(!vis[v]){
            maxlen=0;
            dfs1(v,u,1,w);
            for(int l=1;l<=maxlen&&k-l-1>=0;l++){
                int res=tmp[l]+best[k-l-1];
                if(ans==res){
                    ways+=cnt1[k-l-1]*cnt2[l];
                }
                else if(ans<res){
                    ans=res;
                    ways=cnt1[k-l-1]*cnt2[l];
                }
            }
            for(int l=1;l<=maxlen;l++){
                // best[l]=max(best[l],tmp[l]);
                if(best[l]==tmp[l]){
                    cnt1[l]+=cnt2[l];
                }
                else if(best[l]<tmp[l]){
                    best[l]=tmp[l];
                    cnt1[l]=cnt2[l];
                }
                cnt2[l]=0;
                tmp[l]=0;
            }
            maxdep=max(maxdep,maxlen);
        }
    }
    for(int l=1;l<=maxdep;l++){
        best[l]=0;
        cnt1[l]=0;
    }
}

void solve(int u){
    // cout<<u<<endl;
    // if(sz[u]<k){
    //     return ;
    // }
    vis[u]=true;
    calc(u);
    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        if(!vis[v]){
            solve(getCentroid(v,u));
        }
    }
}

int main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
    }

    dijkstra(1);
    // cout<<9888<<endl;

    build();

    // for(int i=1;i<=n;i++){
    //     cout<<i<<":   "<<dep[i]<<' '<<dis[i]<<endl;
    // }

    solve(getCentroid(1,0));

    cout<<ans<<' '<<ways<<endl;
    return 0;
}