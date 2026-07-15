#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 4e3+5;
const int MAXM = 6e4+5;
const int INF = 1e18;

int n,m,s,t;

struct node{
    int u,v,w;
};
node nums[MAXM];
int id[MAXM];

int dep[MAXN];
int iter[MAXN];

int cnt=2;
int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int now[MAXM<<1];
int cap[MAXM<<1];

int dfn[MAXN];
int low[MAXN];
int st[MAXN],top;
int color,dfncnt;
int col[MAXN];
bool instack[MAXN];

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
    for(int i=1;i<=n;i++){
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
    return dep[t]>=0;// 如果汇点未被访问到，说明无增广路径
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
                now[i^1]-=d;//更新反向边
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
        for(int i=1;i<=n;i++){
            iter[i]=head[i];
        }
        int maxflow;
        while((maxflow=dfs(s,INF))>0){
            flow+=maxflow;
        }
    }
    return flow;
}

void tarjan(int x){
    dfn[x]=++dfncnt;
    low[x]=dfncnt;
    st[++top]=x;
    instack[x]=true;
    for(int i=head[x];i;i=nxt[i]){
        int v=to[i];
        if(now[i]==cap[i]){
            continue;
        }
        if(!dfn[v]){
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
        else if(instack[v]){
            low[x]=min(low[x],dfn[v]);
        }
    }
    if(dfn[x]==low[x]){
        col[x]=++color;
        while(st[top]!=x){
            col[st[top]]=color;
            instack[st[top]]=false;
            top--;
        }
        instack[x]=false;
        top--;
    }
}

signed main()
{
    n=read(),m=read(),s=read(),t=read();
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        id[i]=cnt;
        addedge(u,v,w);
        nums[i]={u,v,w};
    }
    maxflow();

    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }

    for(int i=1;i<=m;i++){
        int u=nums[i].u;
        int v=nums[i].v;
        int d=id[i];

        bool full=(cap[d]==now[d])?1:0;
        if(full){
            bool flag1=(col[u]!=col[v]);
            bool flag2=(col[u]==col[s])&&(col[v]==col[t]);
            cout<<(flag1?1:0)<<' '<<(flag2?1:0)<<endl;
        }
        else{
            cout<<"0 0"<<endl;
        }
    }
    return 0;
}