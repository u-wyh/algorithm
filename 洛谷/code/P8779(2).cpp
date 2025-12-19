#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

long long sum[MAXN];
bool vis[MAXN];
int n,m,t;
queue<int>q;
int fa[MAXN];

int head[MAXN];
int to[MAXN<<1];
long long weight[MAXN<<1];
int Next[MAXN<<1];
int cnt=1;

void addedge(int u,int v,long long w){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

int find(int i){
    if (i != fa[i]){
        fa[i] = find(fa[i]);
    }
    return fa[i];
}

void un(int x,int y){

    fa[max(find(x),find(y))] = min(find(y),find(x));
}

int main()
{
    cin>>n>>m>>t;
    for(int i=0;i<=n;i++){
        sum[i]=LLONG_MAX;
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        long w;
        cin>>u>>v>>w;
        u--;
        un(u,v);
        addedge(u,v,w);
        addedge(v,u,-w);
    }
    for(int i=0;i<=n;i++){
        if(fa[i]==i){
            q.push(i);
            vis[i]=true;
            sum[i]=0;
            while(!q.empty()){
                int u=q.front();
                q.pop();
                for(int i=head[u];i>0;i=Next[i]){
                    int v=to[i];
                    if(!vis[v]){
                        vis[v]=true;
                        q.push(v);
                        long long w=weight[i];
                        sum[v]=sum[u]+w;
                    }
                }
            }
        }
    }
    for(int i=1,u,v;i<=t;i++){
        cin>>u>>v;
        u--;
        if(find(u)==find(v)){
            long long ans=sum[v]-sum[u];
            cout<<ans<<endl;
        }
        else
            cout<<"UNKNOWN"<<endl;
    }
    return 0;
}

