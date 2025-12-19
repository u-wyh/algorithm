#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;
const int MAXV = 4*MAXN;
const int MAXE = 20*MAXN;
const int INF = 1e9;

int n1,n2,n3,m1,m2;
int s,t;

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
    n1=read(),n2=read(),n3=read();
    s=2*n1+n2+n3+1;
    t=s+1;

    for(int i=1;i<=n2;i++){
        addedge(s,i+n1,1);
    }
    for(int i=1;i<=n3;i++){
        addedge(i+n1+n2,t,1);
    }

    m1=read();
    for(int i=1;i<=m1;i++){
        int x,y;
        x=read(),y=read();
        addedge(y+n1,x,1);
    }
    m2=read();
    for(int i=1;i<=m2;i++){
        int x,y;
        x=read(),y=read();
        addedge(n1+n2+n3+x,y+n2+n1,1);
    }
    
    for(int i=1;i<=n1;i++){
        addedge(i,i+n1+n2+n3,1);
    }

    int flow=maxflow();
    cout<<flow<<endl;
    return 0;
}