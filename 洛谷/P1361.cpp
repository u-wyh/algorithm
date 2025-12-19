#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3e3+5;
const int MAXM = 5e6+5;
const int INF = 1e10;

int n,m,s,t;

int dep[MAXN];
int iter[MAXN];

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int now[MAXM];
int cap[MAXM];
int cnt=2;

int son[MAXN];

void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    cap[cnt]=w;
    head[u]=cnt++;
}

//BFS构建分层图，并判断是否存在增广路径
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

// DFS寻找增广路径（多路增广）
//多路增广的含义是来到了一个节点 不仅仅是只去一条边增广  而是去多条边一起增广
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

// Dinic算法主函数
int maxflow(){
    int flow=0;
    while(bfs()){
        //当前弧全部初始化为最初值
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

signed main()
{
    int ans=0;
    n=read();
    s=n+2,t=n+1;
    for(int i=1;i<=n;i++){
        int w=read();
        ans+=w;
        addedge(s,i,w);
        addedge(i,s,0);
    }
    for(int i=1;i<=n;i++){
        int w=read();
        ans+=w;
        addedge(i,t,w);
        addedge(t,i,0);
    }
    int tot=n+2;
    m=read();
    for(int i=1;i<=m;i++){
        int k=read();
        for(int j=1;j<=k;j++){
            son[j]=read();
        }
        int val1=read();
        int val2=read();
        ans+=(val1+val2);
        addedge(s,tot+1,val1);
        addedge(tot+1,s,0);
        addedge(tot+2,t,val2);
        addedge(t,tot+2,0);
        for(int j=1;j<=k;j++){
            addedge(tot+1,son[j],INF);
            addedge(son[j],tot+1,0);
            addedge(son[j],tot+2,INF);
            addedge(tot+2,son[j],0);
        }
        tot+=2;
    }
    n=tot;
    cout<<(ans-maxflow())<<endl;
    return 0;
}