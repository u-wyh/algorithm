// https://www.luogu.com.cn/problem/P7846
// 题意：给定一棵 n 个点的树，
// 每条边 (u_j, v_j, t_j) 的边权 t_j ∈ {0, 1, 2}。
// 为每个点分配正整数点权 w_i ∈ [1, R]，要求：
// t_j = 0 时 w_{u_j} != w_{v_j}；
// t_j = 1 时无限制；
// t_j = 2 时 w_{u_j} = w_{v_j}。
// 第一行输入 n, R，接下来 n-1 行每行 u_j, v_j, t_j。
// 输出一行两个整数，
// 分别表示满足要求的本质不同序列 w 的个数（对 10^9 + 7 取模）
// 以及所有合法序列中 ∑w_i 的最小值；
// 若无合法序列，两个数均输出 0。
// 数据范围：1 <= n <= 10^5，
// 1 <= R <= 100，t_j ∈ {0, 1, 2}。
// 算法标签：树形动态规划、深度优先搜索
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MOD = 1e9+7;

int n,m;

int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;
int ans;

int f[MAXN][105];

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
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dfs1(int u,int f){
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=f){
            if(w==0){
                ans*=(m-1);
            }
            else if(w==1){
                ans*=m;
            }
            ans%=MOD;
            dfs1(v,u);
        }
    }
}

void dfs(int u, int fa) {
    for (int i=head[u];i;i=Next[i]) {
        int v=to[i];
        int t=weight[i];
        if (v == fa) continue;
        dfs(v, u); // 先递归处理子节点
        for (int c = 1; c <= m; c++) {
            int min_sum = LLONG_MAX;
            if (t == 0) {
                for (int d = 1; d <= m; d++) {
                    if (d == c) continue;
                    min_sum = min(min_sum, f[v][d]);
                }
            } else if (t == 1) {
                // 无限制
                for (int d = 1; d <= m; d++) {
                    min_sum = min(min_sum, f[v][d]);
                }
            } else if (t == 2) {
                // w_u == w_v
                min_sum = f[v][c];
            }
            f[u][c] += min_sum;
        }
    }
    // 加上当前节点的点权
    for (int c = 1; c <= m; c++) {
        f[u][c] += c;
    }
}
signed main()
{
    n=read(),m=read();
    bool flag=false;
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
        if(w==0){
            flag=true;
        }
    }
    if(flag&&m==1){
        cout<<"0 0"<<endl;
        return 0;
    }
    ans=m;
    dfs1(1,0);
    cout<<ans<<' ';
    ans=LLONG_MAX;
    dfs(1,0);
    for(int i=1;i<=m;i++){
        ans=min(ans,f[1][i]);
    }
    cout<<ans<<endl;
    return 0;
}
