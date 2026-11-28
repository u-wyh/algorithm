// https://www.luogu.com.cn/problem/P6594
// 题意：n 个点点权 h_i 的树，
// 关闭若干条边使 m 个老师路径 (x_i, y_i)
// 上经过的关闭边数之和 <= k
// 最小化各连通块内 h_i 极差的最大值。
// 数据范围：n <= 800，m <= 10^5，
// 0 <= k <= 8*10^7，
// 1 <= h_i <= 10^9，u_i != v_i。
// 难度评分：1800（洛谷分级换算）
// 算法标签：二分答案、树形动态规划、树上差分
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 805;
const int LIMIT = 11;
const int INF = 1e9;

int n,m,k,p;

int val[MAXN];//每个节点的点权

int diff[MAXN];//用于树上边差分

//用于求lca
int dep[MAXN];
int st[MAXN][LIMIT];

int dp[MAXN][MAXN];//dp[i][j]表示i为首的子树 他自己被包含在val[j]~val[j]+k的集合中  最小代价

//链式前向星  双向边
int cnt=1;
int head[MAXN];
int to[MAXN<<1];
int weight[MAXN<<1];//不用初始化 反正都是0
int nxt[MAXN<<1];

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

inline int lca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int i=p;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b){
        return a;
    }
    for(int i=p;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

//建立dep和st表信息
void dfs(int u,int f){
    dep[u]=dep[f]+1;
    st[u][0]=f;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==f){
            continue;
        }
        dfs(v,u);
    }
}

//完成树上差分  确立边权
void dfs1(int u,int fa){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs1(v,u);
        weight[i]+=diff[v];
        diff[u]+=diff[v];
        // cout<<u<<' '<<v<<' '<<weight[i]<<endl;
    }
}

void dfs2(int u,int fa,int k){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs2(v,u,k);
    }
    for(int i=1;i<=n;i++){
        if(val[u]<val[i]||val[u]>val[i]+k){
            continue;
        }
        dp[u][i]=0;
        for(int j=head[u];j;j=nxt[j]){
            int v=to[j];
            if(v==fa){
                continue;
            }
            dp[u][i]+=min(dp[v][i],dp[v][0]+weight[j]);
        }
        dp[u][0]=min(dp[u][i],dp[u][0]);
    }
}

bool check(int limit){
    for(int i=1;i<=n;i++){
        for(int j=0;j<=n;j++){
            dp[i][j]=INF;
        }
    }
    dfs2(1,0,limit);
    if(dp[1][0]<=k){
        return true;
    }
    else{
        return false;
    }
}

int main()
{
    n=read(),m=read(),k=read();
    p=log2(n);
    int l=INT_MAX,r=0;
    for(int i=1;i<=n;i++){
        val[i]=read();
        r=max(r,val[i]);
        l=min(l,val[i]);
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1,0);
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        diff[u]+=1;
        diff[v]+=1;
        diff[lca(u,v)]-=2;
    }
    dfs1(1,0);
    r-=l;
    l=0;
    int ans=r;
    while(l<=r){
        int mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    printf("%d\n",ans);
    return 0;
}