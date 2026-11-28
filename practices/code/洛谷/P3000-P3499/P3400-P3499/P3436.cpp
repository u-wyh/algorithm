// https://www.luogu.com.cn/problem/P3436
// 题意：输入住宅楼数 n（编号 1..n，主楼编号 n+1）和单向道路数 m，
// 以及 m 条单向边 (u_i, v_i)（允许重边和自环）。
// 每栋楼可在一条路径中访问多次，
// 两条从住宅楼到主楼的路线只要经过的边序列不完全相同就算不同路线
// （重边算不同道路）。
// 若存在住宅楼方案数 > 36500，
// 第一行输出 zawsze、第二行输出超过 36500 的住宅楼数、第三行升序
// 输出其编号；
// 否则三行分别输出最大方案数、达到最大值的住宅楼数及升序编号。
// 数据范围：1 <= n, m <= 1000000，
// 1 <= u_i, v_i <= n+1，至少有一栋住宅楼可到达主楼。
// 难度评分：2000（洛谷分级换算）
// 算法标签：强连通分量、拓扑排序、动态规划
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n,m;

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt=1;

int head1[MAXN];
int nxt1[MAXN];
int to1[MAXN];
int cnt1=1;

int dfn[MAXN];
int low[MAXN];
int dfncnt;
int st[MAXN];
bool instack[MAXN];
int top;
int color;
int col[MAXN];
int sz[MAXN];

long long dp[MAXN];

int in[MAXN];

queue<int>q;

int ans[MAXN];

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

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

inline void Addedge(int u,int v){
    nxt1[cnt1]=head1[u];
    to1[cnt1]=v;
    head1[u]=cnt1++;
}

void tarjan(int u){
    low[u]=dfn[u]=++dfncnt;
    st[++top]=u;
    instack[u]=true;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(instack[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(low[u]==dfn[u]){
        color++;
        sz[color]++;
        if(ans[u]>1){
            sz[color]++;
        }
        col[u]=color;
        while(st[top]!=u){
            instack[st[top]]=false;
            col[st[top--]]=color;
            sz[color]++;
        }
        instack[st[top]]=false;
        top--;
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n+1;i++){
        ans[i]=1;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        if(u==v){
            ans[u]=2;
        }
        addedge(u,v);
    }
    for(int i=1;i<=n+1;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=n+1;i++){
        for(int j=head[i];j;j=nxt[j]){
            int v=to[j];
            if(col[v]!=col[i]){
                Addedge(col[v],col[i]);
                in[col[i]]++;
            }
        }
    }
    for(int i=1;i<=color;i++){
        if(in[i]==0&&i!=col[n+1]){
            q.push(i);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head1[u];i;i=nxt1[i]){
            int v=to1[i];
            in[v]--;
            if(in[v]==0&&v!=col[n+1]){
                q.push(v);
            }
        }
    }
    q.push(col[n+1]);
    if(sz[col[n+1]]>1){
        dp[col[n+1]]=40000;
    }
    else{
        dp[col[n+1]]=1;
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head1[u];i;i=nxt1[i]){
            int v=to1[i];
            dp[v]+=dp[u];
            in[v]--;
            if(in[v]==0){
                q.push(v);
                if(sz[v]>1){
                    dp[v]=40000;
                }
            }
        }
    }
    long long maxans=0;
    for(int i=1;i<=n;i++){
        maxans=max(maxans,dp[col[i]]);
    }

    if(maxans>36500){
        cout<<"zawsze"<<endl;
        int res=0;
        for(int i=1;i<=n;i++){
            if(dp[col[i]]>36500){
                res++;
            }
        }
        cout<<res<<endl;
        for(int i=1;i<=n;i++){
            if(dp[col[i]]>36500){
                cout<<i<<' ';
            }
        }
    }
    else{
        cout<<maxans<<endl;
        int res=0;
        for(int i=1;i<=n;i++){
            if(dp[col[i]]==maxans){
                res++;
            }
        }
        cout<<res<<endl;
        for(int i=1;i<=n;i++){
            if(dp[col[i]]==maxans){
                cout<<i<<' ';
            }
        }
    }

    return 0;
}