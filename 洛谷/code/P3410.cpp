// https://www.luogu.com.cn/problem/P3410
// 题意：输入愿意付钱拍照的人数 M 和下属人数 N；随后 M 行每行给出第 i 个人愿付费用、所需下属编号列表（以 0 结尾），最后一行给出带每个下属的费用。
// 带齐某人所需的全部下属即可获得他的拍照费用，带去的每个下属都必须支付对应配合费用，也可一个人都不带。
// 输出一个整数，表示能获得的最大净收益（收入减支出）。
// 数据范围：1 <= N, M <= 100，各项费用均为 [1, 5*10^8] 内的整数。
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 105;
const int MAXV = MAXN*2;
const int MAXE = 2*MAXN*MAXN;
const int INF = 1e15;

int n,m,s,t;

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

signed main()
{
    m=read(),n=read();
    s=n+m+1,t=s+1;
    int all=0;
    for(int i=1;i<=m;i++){
        int val=read();
        all+=val;
        addedge(s,i,val);
        int x=read();
        while(x!=0){
            addedge(i,m+x,INF);
            x=read();
        }
    }
    for(int i=1;i<=n;i++){
        int val=read();
        addedge(m+i,t,val);
    }
    int flow=maxflow();
    cout<<(all-flow)<<endl;
    return 0;
}