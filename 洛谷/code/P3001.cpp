#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2005;
const int MAXM = 25005;

int n,m;
double val;
int st,en;

int cnt=1;
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
long double weight[MAXM];

long double dis[MAXN];
int updatecnt[MAXN];
bool enter[MAXN];
queue<int>q;

void addedge(int u,int v,long double w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

bool spfa(){
    dis[st]=val;
    updatecnt[st]=1;
    enter[st]=1;
    q.push(st);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        enter[u]=false;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            long double w=weight[i];
            if(dis[v]>dis[u]*w){
                dis[v]=dis[u]*w;
                if(!enter[v]){
                    enter[v]=1;
                    updatecnt[v]++;
                    q.push(v);
                    if(updatecnt[v]>=n){
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

signed main()
{
    cin>>n>>m>>val>>st>>en;
    for(int i=1;i<=m;i++){
        int u,v;
        long double w;
        cin>>u>>v>>w;
        addedge(u,v,w);
    }
    for(int i=1;i<=n;i++){
        dis[i]=1e18;
    }
    if(spfa()){
        printf("%.6Lf",dis[en]);
    }
    else{
        cout<<0<<endl;
    }
    return 0;
}