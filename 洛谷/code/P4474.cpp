#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXV = MAXN*MAXN;
const int MAXE = 10*MAXV;
const int INF = 1e9;

int n,m,s,t;
int val[MAXN][MAXN];
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

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

int id(int x,int y){
    return (x-1)*m+y;
}

int main()
{
    n=read(),m=read();
    s=n*m+1,t=s+1;
    int all=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            val[i][j]=read();
            all+=val[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if((i+j)%2){
                addedge(s,id(i,j),val[i][j]);
                for(int k=0;k<4;k++){
                    int ni=i+walk[k][0];
                    int nj=j+walk[k][1];
                    if(ni>=1&&ni<=n&&nj>=1&&nj<=m){
                        addedge(id(i,j),id(ni,nj),INF);
                    }
                }
            }
            else{
                addedge(id(i,j),t,val[i][j]);
            }
        }
    }
    int flow=maxflow();
    cout<<(all-flow)<<endl;
    return 0;
}