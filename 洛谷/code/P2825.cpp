#include<bits/stdc++.h>
using namespace std;
const int MAXN = 55;
const int MAXV = 5005;
const int MAXE = MAXV*10;
const int INF = 1e9;

int n,m,s,t;
int rowcnt,colcnt;
char str[MAXN][MAXN];
int rowid[MAXN][MAXN];
int colid[MAXN][MAXN];

int dep[MAXV];
int iter[MAXV];

int cnt=2;
int head[MAXV];
int nxt[MAXE];
int to[MAXE];
int now[MAXE];
int cap[MAXE];

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
        //注意这里是引用  iter会随着i发生变化
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
        //当前弧全部初始化为最初值
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
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%s",str[i]+1);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(str[i][j]=='#'){
                continue;
            }
            if(j==1||str[i][j-1]=='#'){
                rowcnt++;
            }
            rowid[i][j]=rowcnt;
        }
    }
    for(int j=1;j<=m;j++){
        for(int i=1;i<=n;i++){
            if(str[i][j]=='#'){
                continue;
            }
            if(i==1||str[i-1][j]=='#'){
                colcnt++;
            }
            colid[i][j]=colcnt;
        }
    }
    s=rowcnt+colcnt+1;
    t=s+1;
    for(int i=1;i<=rowcnt;i++){
        addedge(s,i,1);
    }
    for(int i=1;i<=colcnt;i++){
        addedge(rowcnt+i,t,1);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(str[i][j]=='*'){
                addedge(rowid[i][j],rowcnt+colid[i][j],1);
            }
        }
    }

    int flow=maxflow();
    cout<<flow<<endl;
    return 0;
}