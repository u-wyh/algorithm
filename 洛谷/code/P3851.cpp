// https://www.luogu.com.cn/problem/P3851
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2505;
const int MAXM = 30000;
const int INF = 5e4;

int n,m,s,t;

int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int limit[MAXM<<1];
int cntg=2;

int dis[MAXN];
int que[MAXN];
// 当前弧优化数组
int cur[MAXN];

char str[13][13];
int r,c,T;

void addedge(int u,int v,int w){
    nxt[cntg]=head[u];
    to[cntg]=v;
    limit[cntg]=w;
    head[u]=cntg++;
}

void bfs(int s){
    // 重置 距离 和 当前弧 数组
    for(int i=1;i<=n;i++){
        dis[i]=n;
        cur[i]=head[i];
    }
    dis[s]=0;
    int l=1,r=0;
    que[++r]=s;
    while(l<=r){
        int u=que[l++];
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int lim=limit[i];
            if(dis[v]==n && lim>0){
                dis[v]=dis[u]+1;
                que[++r]=v;
            }
        }
    }
}

// 目前来到了u这个点，还有rest的流量，遇到t停止
int dfs(int u,int rest,int t){
    if(u==t){
        return rest;
    }
    int flow=0;
    for(int i=cur[u];i && rest>0;i=nxt[i]){
        cur[u]=i;
        int v=to[i];
        int lim=limit[i];
        if(dis[u]+1==dis[v] && lim>0){
            int k=dfs(v,min(rest,lim),t);
            flow+=k;
            rest-=k;
            limit[i]-=k;
            limit[i^1]+=k;
        }
    }
    return flow;
}

int maxflow(int s,int t){
    int ans=0;
    bfs(s);
    while(dis[t]!=n){
        ans+=dfs(s,INF,t);
        bfs(s);
    }
    return ans;
}

int tim[14][14];
int id[14][14];
int idcnt;
int cnto;

int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
pair<int,int> q[300];

void bfs(int x,int y){
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            tim[i][j]=300;
        }
    }
    tim[x][y]=0;
    int ql=1,qr=0;
    q[++qr]={x,y};
    while(ql<=qr){
        int x=q[ql].first;
        int y=q[ql++].second;
        for(int i=0;i<4;i++){
            int nx=x+walk[i][0];
            int ny=y+walk[i][1];
            if(nx<=r&&nx>=1&&ny<=c&&ny>=1&&tim[nx][ny]==300&&str[nx][ny]!='*'){
                tim[nx][ny]=tim[x][y]+1;
                q[++qr]={nx,ny};
            }
        }
    }
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            if(str[i][j]=='P'&&tim[i][j]<=T){
                int o=(tim[i][j]-1)*cnto+id[x][y];
                addedge(id[i][j],o,1);
                addedge(o,id[i][j],0);
            }
        }
    }
}

void prepare(){
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            if(str[i][j]=='P'){
                id[i][j]=++idcnt;
            }
        }
    }
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            if(str[i][j]=='O'){
                id[i][j]=++idcnt;
                cnto++;
            }
        }
    }
    s=idcnt+(T-1)*cnto+1;
    t=s+1;
    n=t;

    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            if(str[i][j]=='P'){
                addedge(s,id[i][j],1);
                addedge(id[i][j],s,0);
            }
        }
    }
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            if(str[i][j]=='O'){
                bfs(i,j);

                addedge(id[i][j],t,1);
                addedge(t,id[i][j],0);

                for(int k=2;k<=T;k++){
                    int p=(k-1)*cnto+id[i][j];
                    addedge(p-cnto,p,INF);
                    addedge(p,p-cnto,0);

                    addedge(p,t,1);
                    addedge(t,p,0);
                }
            }
        }
    }
}

signed main()
{
    cin>>r>>c>>T;
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            cin>>str[i][j];
        }
    }
    prepare();
    int ans=maxflow(s,t);
    cout<<ans<<endl;
    return 0;
}