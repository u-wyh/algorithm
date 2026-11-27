// https://www.luogu.com.cn/problem/P9984
// 题意：给定 N 个节点、M
// 条边的连通无向简单图（节点 1..N，边按输入顺序编号 1..M）。
// 对每个起始节点 v ∈ [1, N] 执行以下过程：初始集合 S = {v}，
// 变量 h = 0；
// 当 |S| < N 时重复选择当前“恰有一个端点在 S
// 中”的所有边里编号最小的边 e，将 e 不在 S 中的端点加入 S，
// 并令 h = 10h + e。
// 输出每个 v 最终得到的 h 对 10^9 + 7 取模的结果。
// 题意：第一行输入 N, M，
// 后 M 行输入第 e 条边的端点 (a_e, b_e)；
// 输出 N 行，第 i 行为从节点 i 出发的结果。
// 数据范围：
// 2 <= N <= 2 * 10^5，
// N - 1 <= M <= 4 * 10^5，保证图连通且无重边。
// 算法标签：带权并查集
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 4e5+5;

int n,m;

int fa[MAXN];
int cnt;
struct node{
    int p,val;
};
node nums[MAXN];

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

node add(node a,node b){
    return {a.p*b.p%MOD,(a.val*b.p+b.val)%MOD};
}

int find(int x){
    if(x==fa[x]){
        return x;
    }
    int f=find(fa[x]);
    nums[x]=add(nums[x],nums[fa[x]]);
    fa[x]=f;
    return f;
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        fa[i]=i;
        nums[i]={1,0};
    }
    cnt=n;
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        int fx=find(u);
        int fy=find(v);
        if(fx!=fy){
            node xval=nums[u];
            node yval=nums[v];
            node tmp={10,i};

            nums[fa[u]]=add(tmp,yval);
            nums[fa[v]]=add(tmp,xval);

            fa[fa[u]]=fa[fa[v]]=++cnt;
            fa[cnt]=cnt;
            nums[cnt]={1,0};
        }
    }

    for(int i=1;i<=n;i++){
        find(i);
        cout<<nums[i].val<<endl;
    }
    return 0;
}