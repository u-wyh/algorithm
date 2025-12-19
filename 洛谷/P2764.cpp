// 这道题的大思路是转换成二分图匹配的知识  求最大匹配
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 155;
const int MAXM = 6005;
const int MAXV = MAXN*2;
const int MAXE = 2*(MAXV+MAXM);
const int INF = 1e9;

int n,m,s,t;
int nxtval[MAXN];
bool vis[MAXN];

int dep[MAXV];
int iter[MAXV];

int cnt=2;
int head[MAXV];
int nxt[MAXE];
int to[MAXE];
int now[MAXE];
int cap[MAXE];

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
    cap[cnt]=w;
    now[cnt]=0;
    head[u]=cnt++;

    nxt[cnt]=head[v];
    to[cnt]=u;
    cap[cnt]=0;
    now[cnt]=0;
    head[v]=cnt++;
}

bool bfs(){
    for(int i=1;i<=t;i++){
        dep[i]=-1;
    }
    queue<int>q;
    dep[s]=0;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=cap[i];
            int k=now[i];
            if(dep[v]<0&&(k<w)){
                dep[v]=dep[u]+1;
                q.push(v);
            }
        }
    }
    return dep[t]>=0;
}

int dfs(int u,int f){
    if(u==t){
        return f;
    }
    int flow=0;
    for(int &i=iter[u];i;i=nxt[i]){
        int v=to[i];
        int w=cap[i];
        int k=now[i];
        if(dep[u]+1==dep[v]&&k<w){
            int d=dfs(v,min(f,w-k));
            if(d>0){
                now[i]+=d;
                now[i^1]-=d;
                flow+=d;
                f-=d;
                if(f==0){
                    break;
                }
            }
        }
    }
    return flow;
}

int maxflow(){
    int flow=0;
    while(bfs()){
        for(int i=1;i<=t;i++){
            iter[i]=head[i];
        }
        int maxflow;
        while((maxflow=dfs(s,INF))>0){
            flow+=maxflow;
        }
    }
    return flow;
}

int main()
{
    n=read(),m=read();
    s=2*n+1,t=s+1;
    for(int i=1;i<=n;i++){
        addedge(s,i,1);
        addedge(i+n,t,1);
    }
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v+n,1);
    }
    int flow=maxflow();
    for(int u=1;u<=n;u++){
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v>n&&v<=2*n&&now[i]==1){
                v=v-n;
                nxtval[u]=v;
                vis[v]=true;
                break;
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            vector<int>path;
            int cur=i;
            while(cur){
                path.push_back(cur);
                cur=nxtval[cur];
            }
            for(int j=0;j<(int)path.size();j++){
                cout<<path[j]<<' ';
            }
            cout<<endl;
        }
    }
    cout<<(n-flow)<<endl;
    return 0;
}