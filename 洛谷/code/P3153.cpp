#include<bits/stdc++.h>
using namespace std;
const int MAXN = 55;
const int MAXT = 4*MAXN;
const int MAXE = 2*MAXN*MAXN;
const int INF = 1e9;

int n,k,s,t;
char like[MAXN][MAXN];

int dep[MAXT];
int iter[MAXT];

int cnt=2;
int head[MAXT];
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
    for(int i=0;i<=t;i++){
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
        for(int i=0;i<=t;i++){
            iter[i]=head[i];
        }
        int maxflow;
        while((maxflow=dfs(s,INF))>0){
            flow+=maxflow;
        }
    }
    return flow;
}

void init(){
    cnt=2;
    for(int i=0;i<=t;i++){
        head[i]=0;
    }
}

bool check(int limit){
    init();

    for(int i=1;i<=n;i++){
        addedge(s,i,limit);
    }
    for(int i=1;i<=n;i++){
        addedge(i,n+i,k);
    }
    for(int i=1;i<=n;i++){
        addedge(2*n+i,t,limit);
    }
    for(int i=1;i<=n;i++){
        addedge(3*n+i,2*n+i,k);
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(like[i][j]=='Y'){
                addedge(i,2*n+j,1);
            }
            else{
                addedge(n+i,3*n+j,1);
            }
        }
    }

    int flow=maxflow();
    return flow==limit*n;
}

int main()
{
    scanf("%d %d",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%s",like[i]+1);
    }
    s=0,t=4*n+1;

    int l=0,r=n,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    cout<<ans<<endl;
    return 0;
}