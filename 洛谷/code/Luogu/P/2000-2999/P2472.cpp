#include<bits/stdc++.h>
using namespace std;
const int MAXN = 25;
const int MAXV = MAXN*MAXN*2;
const int MAXE = 40005;
const int INF = 1e9;

int n,m,d,s,t;

char h[MAXN][MAXN];
char p[MAXN][MAXN];

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

bool ok(int x1,int y1,int x2,int y2){
    return ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))<=d*d;
}

int main()
{
    scanf("%d %d %d",&n,&m,&d);
    for(int i=1;i<=n;i++){
        scanf("%s",h[i]+1);
    }
    for(int i=1;i<=n;i++){
        scanf("%s",p[i]+1);
    }

    s=n*m+1;
    t=s+1;

    int need=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(h[i][j]!='0'){
                int height=h[i][j]-'0';
                int in=(i-1)*n+j;
                int out=in+n*m;
                addedge(in,out,height);

                if(p[i][j]=='L'){
                    addedge(s,in,1);
                    need++;
                }

                if(i<=d||i>=n-d-1||j<=d||j>=m-d-1){
                    addedge(out,t,INF);
                }
            }
        }
    }

    for(int x1=1;x1<=n;x1++){
        for(int y1=1;y1<=m;y1++){
            if(h[x1][y1]=='0'){
                continue;
            }
            int out=(x1-1)*n+y1+n*m;
            for(int x2=1;x2<=n;x2++){
                for(int y2=1;y2<=m;y2++){
                    if(h[x2][y2]=='0'){
                        continue;
                    }
                    if(x1==x2&&y1==y2){
                        continue;
                    }

                    if(ok(x1,y1,x2,y2)){
                        int in=(x2-1)*n+y2;
                        addedge(out,in,INF);
                    }
                }
            }
        }
    }

    int flow=maxflow();
    cout<<(need-flow)<<endl;
    return 0;
}