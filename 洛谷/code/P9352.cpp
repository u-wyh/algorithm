#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int LIMIT = 18;

int n,power;
int arr[MAXN];//记录高度
long long dp[MAXN];//表示如果i作为起点  不断跳跃  只能去往比自己小的点 最远距离
int fa[MAXN];
//表示这个联通块中的代表节点  也就是最高的节点
//因为要去选择这个节点的方向  所以这个点要么走 要么不走（堵住）
//反正这个节点要么堵住  要么去了之后再堵住  那么不如选择后者
int st[MAXN][LIMIT];
int deep[MAXN];

int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

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

void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u, int f) {
    deep[u] = deep[f] + 1;
    st[u][0] = f;
    for (int p = 1; p <= power; p++) {
        st[u][p] = st[st[u][p - 1]][p - 1];
    }
    //完成u的deep  stjump
    for (int e = head[u]; e != 0; e = Next[e]) {
        if (to[e] != f) {
            dfs(to[e], u);
        }
        //向下递归
    }
}


int lca(int a, int b) {
    if (deep[a] < deep[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    //确定大小关系
    for (int p = power; p >= 0; p--) {
        if (deep[st[a][p]] >= deep[b]) {
            a = st[a][p];
        }
    }
    //首先将两者变为同一高度
    if (a == b) {
        return a;
    }
    //如果相同说明就是祖先关系
    for (int p = power; p >= 0; p--) {
        if (st[a][p] != st[b][p]) {
            a = st[a][p];
            b = st[b][p];
        }
        //判断跳完后是否符合规则
    }
    return st[a][0];
    //我们将头结点的祖先设置为0  实际上没有0
}

int dis(int u,int v){
    return deep[u]+deep[v]-2*deep[lca(u,v)];
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

int main()
{
    n=read();
    power=log2(n);
    for(int i=1;i<=n;i++){
        fa[i]=i;
        arr[i]=read();
    }
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        u=arr[u],v=arr[v];//根据各个点的高度建图
        addedge(u,v),addedge(v,u);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++){
        //此时只有i以及小于i的点是可以到达的
        for(int j=head[i];j;j=Next[j]){
            int v=find(to[j]);
            if(v<i){
                //其实这个节点只要开放了  就一定可以到达
                //表示这个节点可以到达
                fa[v]=i;
                dp[i]=max(dp[i],dp[v]+dis(i,v));
                //这个公式的意思是  如果要去v这个方向  那么一定会去这个联通块的最大的地方
            }
        }
    }
    cout<<dp[n]<<endl;
    return 0;
}
