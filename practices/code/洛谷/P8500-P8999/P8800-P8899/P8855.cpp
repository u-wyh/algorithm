// https://www.luogu.com.cn/problem/P8855
// 题意：输入城镇数 N 及 N-1 条树边 (a, b)（边权均为 1），
// 再输入 M 和依次需要访问的 M 个城镇编号（从 1 号城镇出发顺次经过各点）
// 输出最短总旅行时间。
// 数据范围：
// 1 <= N <= 30000
// （注：题面未给出 M 及城镇编号序列的额外上界说明）。
// 难度评分：1500（洛谷分级换算）
// 算法标签：最近公共祖先、倍增、深度优先搜索
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 30005;
const int MAXM = 60005;
const int LIMIT = 16;

int n,m,power;
int stk[MAXN];
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt=1;
int deep[MAXN],stjump[MAXN][LIMIT];

void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int root){
    int top=0;
    stk[top++]=root;
    while(top>0){
        int u=stk[--top];
        int f=stjump[u][0];
        deep[u]=deep[f]+1;
        for(int p=1;p<=power;p++){
            stjump[u][p]=stjump[stjump[u][p-1]][p-1];
        }
        for(int e=head[u];e!=0;e=Next[e]){
            int v=to[e];
            if(v!=f){
                stjump[v][0]=u;
                stk[top++]=v;
            }
        }
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
        if (deep[stjump[a][p]] >= deep[b]) {
            a = stjump[a][p];
        }
    }
    //首先将两者变为同一高度
    if (a == b) {
        return a;
    }
    //如果相同说明就是祖先关系
    for (int p = power; p >= 0; p--) {
        if (stjump[a][p] != stjump[b][p]) {
            a = stjump[a][p];
            b = stjump[b][p];
        }
        //判断跳完后是否符合规则
    }
    return stjump[a][0];
    //我们将头结点的祖先设置为0  实际上没有0
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;
    power=log2(n);
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1);
    cin>>m;
    int pre=1;
    long long ans=0;
    for(int i=0;i<m;i++){
        int v,w;
        cin>>v;
        w=lca(pre,v);
        ans+=deep[pre]+deep[v]-2*deep[w];
        pre=v;
    }
    cout<<ans<<endl;
    return 0;
}
