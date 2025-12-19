#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;
const int MAXM = 1e5+5;
const int MOD = 10000;
#define int long long

int n,m,st,en,t0;
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cunt=1;

int dis[MAXN];
int cnt[MAXN];
int in[MAXN];

void addedge(int u,int v,int w){
    Next[cunt]=head[u];
    to[cunt]=v;
    weight[cunt]=w;
    head[u]=cunt++;
}

signed main()
{
    cin>>n>>m>>st>>en>>t0;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        in[v]++;
    }
    queue<int>q;
    q.push(st);
    cnt[st]=1;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i>0;i=Next[i]){
            int v=to[i];
            int w=weight[i];
            if(!--in[v]){
                q.push(v);
            }
            (dis[v]+=dis[u]+cnt[u]*w)%=MOD;
            (cnt[v]+=cnt[u])%=MOD;
        }
    }
    int ans=(dis[en]+(cnt[en]-1)*t0)%MOD;
    cout<<ans;
    return 0;
}
