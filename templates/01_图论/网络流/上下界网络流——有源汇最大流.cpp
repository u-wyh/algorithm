// https://www.luogu.com.cn/problem/P5192
// https://loj.ac/p/116(这个更适合做模板)
// 有源汇的最大流的步骤是首先建立出增量网络流图  要加上一条从t到s容量为INF的边
// 根据每个节点的in 添加附加源汇点的边  求出可行流
// 如果可行流存在  那么删除从t到s的那条边 在残余网络上跑最大流
// 此时的最大流加上可行流就是答案
// 最小流就是在残余网络上计算退流 从t到s  用可行流减去退流即可
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;
const int MAXM = 1e4+5;
const int MAXV = MAXN;
const int MAXE = 3*MAXM;
const int INF = 1e9;

int n,m,s,t;
int ss,tt;// 附加源点、汇点

int dep[MAXV];
int iter[MAXV];

int cnt=2;
int head[MAXV];
int nxt[MAXE];
int to[MAXE];
int now[MAXE];
int cap[MAXE];
int ts_id; // 记录t->s边的编号

// 每个节点的下界净流量
int in[MAXV];

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

bool bfs(int s,int t){
    for(int i=1;i<=tt;i++){
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

int dfs(int u,int t,int f){
    if(u==t){
        return f;
    }
    int flow=0;
    for(int &i=iter[u];i;i=nxt[i]){
        int v=to[i];
        int w=cap[i];
        int k=now[i];
        if(dep[u]+1==dep[v]&&k<w){
            int d=dfs(v,t,min(f,w-k));
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

int maxflow(int s,int t){
    int flow=0;
    while(bfs(s,t)){
        for(int i=1;i<=tt;i++){
            iter[i]=head[i];
        }
        int maxflow;
        while((maxflow=dfs(s,t,INF))>0){
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

int main()
{
    n=read(),m=read(),s=read(),t=read();
    ss=n+1,tt=ss+1;
    for(int i=1;i<=m;i++){
        int u,v,l,r;
        u=read(),v=read(),l=read(),r=read();
        addedge(u,v,r-l);
        in[u]-=l;
        in[v]+=l;
    }

    // 记录添加t->s边前的cnt  添加t->s边，容量INF
    ts_id=cnt;
    addedge(t,s,INF);

    // 建立所有的附加边
    int all=0;
    for(int i=1;i<=n;i++){
        if(in[i]>0){
            addedge(ss,i,in[i]);
            all+=in[i];
        }
        else if(in[i]<0){
            addedge(i,tt,-in[i]);
        }
    }

    int flow1=maxflow(ss,tt);
    if(flow1!=all){
        printf("please go home to sleep");
    }
    else{
        // 记录可行流值
        int f0=now[ts_id];

        // 删除t->s边：将容量和当前流量设为0
        // 附加边不需要改变 因为他们的剩余流量一定是0
        cap[ts_id] = 0;
        cap[ts_id ^ 1] = 0;
        now[ts_id] = 0;
        now[ts_id ^ 1] = 0;

        // 在残余网络上从s到t跑最大流
        int flow2 = maxflow(s, t);

        // 如果求的是最小流 那么就是跑一下退流  用可行流减去退流即可
        // // 在残余网络上从t到s跑最大流（退流）
        // int flow_back = maxflow(t, s);
            
        // // 最小流 = 可行流 - 退流
        // printf("%lld\n\n", f0 - flow_back);
         
        printf("%d\n", f0 + flow2);
    }
    return 0;
}