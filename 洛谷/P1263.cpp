#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;
const int MAXV = MAXN*MAXN;
const int MAXE = 10*MAXV;
const int INF = 1e9;

int n,m,s,t;
int val[MAXN][MAXN];
int row[MAXN][MAXN];
int col[MAXN][MAXN];
int rowcnt,colcnt;

int dep[MAXV];
int iter[MAXV];
int cnt=2;
int head[MAXV];
int nxt[MAXE];
int to[MAXE];
int now[MAXE];
int cap[MAXE];

map<pair<int,int>,pair<int,int>>mp;

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
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            val[i][j]=read();
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(val[i][j]!=2){
                if(j==1||val[i][j-1]==2){
                    ++rowcnt;
                }
                row[i][j]=rowcnt;
            }
        }
    }

    for(int j=1;j<=m;j++){
        for(int i=1;i<=n;i++){
            if(val[i][j]!=2){
                if(i==1||val[i-1][j]==2){
                    ++colcnt;
                }
                col[i][j]=colcnt;
            }
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(val[i][j]==0){
                mp[{row[i][j],col[i][j]}]={i,j};
            }
        }
    }

    s=rowcnt+colcnt+1;
    t=s+1;

    for(int i=1;i<=rowcnt;i++){
        addedge(s,i,1);
    }
    for(int i=1;i<=colcnt;i++){
        addedge(i+rowcnt,t,1);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(val[i][j]==0){
                addedge(row[i][j],rowcnt+col[i][j],1);
            }
        }
    }
    cout<<maxflow()<<endl;

    for(int u=1;u<=rowcnt;u++){
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v>rowcnt&&v<s&&now[i]==cap[i]){
                pair<int,int>tmp=mp[{u,v-rowcnt}];
                cout<<tmp.first<<' '<<tmp.second<<endl;
            }
        }
    }
    return 0;
}