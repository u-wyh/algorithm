#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;
const int MAXV = MAXN*2;
const int MAXE = 30*MAXV;
const int INF = 1e9;

int n,s,t;
int val[MAXN];
int dp[MAXN];

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
    return dep[t]>=0;// 如果汇点未被访问到，说明无增广路径
}

int dfs(int u,int f){
    //表示当前来到了u节点 有f的流量可供使用  f就是目前这条路最多可以消耗掉的流量
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
    n=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    int len=0;
    for(int i=1;i<=n;i++){
        dp[i]=1;
        for(int j=1;j<i;j++){
            if(val[j]<=val[i]){
                dp[i]=max(dp[i],dp[j]+1);
            }
        }
        len=max(len,dp[i]);
    }
    cout<<len<<endl;

    if(len==1){
        cout<<n<<endl<<n<<endl;
        return 0;
    }

    s=2*n+1,t=s+1;
    for(int i=1;i<=n;i++){
        addedge(i,i+n,1);
    }
    for(int i=1;i<=n;i++){
        if(dp[i]==1){
            addedge(s,i,1);
        }
        if(dp[i]==len){
            addedge(i+n,t,1);
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(val[i]<=val[j]&&dp[j]==dp[i]+1){
                addedge(i+n,j,1);
            }
        }
    }

    int flow=maxflow();
    cout<<flow<<endl;

    
    s=2*n+1,t=s+1;
    cnt=2;
    for(int i=1;i<=t;i++){
        head[i]=0;
    }
    for(int i=2;i<n;i++){
        addedge(i,i+n,1);
    }
    addedge(1,1+n,INF);
    addedge(n,2*n,INF);
    for(int i=2;i<n;i++){
        if(dp[i]==1){
            addedge(s,i,1);
        }
        if(dp[i]==len){
            addedge(i+n,t,1);
        }
    }
    addedge(s,1,INF);
    if(dp[n]==len){
        addedge(2*n,t,INF);
    }

    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(val[i]<=val[j]&&dp[j]==dp[i]+1){
                addedge(i+n,j,1);
            }
        }
    }

    flow=maxflow();
    cout<<flow<<endl;

    return 0;
}