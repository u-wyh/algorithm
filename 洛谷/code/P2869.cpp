// https://www.luogu.com.cn/problem/P2869
// 题意：N 头牛，第 i 头要求草价格 >= A_i 且绿色度 >= B_i；商店有 M 种草（价格 C_j，绿色度 D_j）。
// 每头牛必须选不同的草，求满足所有牛的最小总花费，无解输出 -1。
// 数据范围：1 <= N, M <= 10^5，1 <= A_i, B_i, C_j, D_j <= 10^9。
#include<bits/stdc++.h>
// 算法标签：基环树、拓扑排序、深度优先搜索
using namespace std;
#define inf 1e18+10
#define int long long
const int maxn=100010;
int n,a[maxn],v[maxn],rd[maxn],ans,minn=inf;
bool vis[maxn];
queue<int>q;
void topo(){
    for(int i=1;i<=n;i++){
        if(!rd[i])
            q.push(i);
    }
    while(!q.empty()){
        int x=q.front();
        q.pop();
        ans+=v[x];
        rd[a[x]]--;
        vis[x]=1;//表示不在环上
        if(!rd[a[x]])
            q.push(a[x]);
    }
    return;
}
void dfs(int x){
    vis[x]=1;
    minn=min(minn,v[x]);
    if(vis[a[x]])return;
    dfs(a[x]);
    return;
}
signed main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld%lld",&a[i],&v[i]);
        rd[a[i]]++;
    }
    topo();
    for(int i=1;i<=n;i++){
        if(!vis[i])
            ans+=v[i];
    }
    for(int i=1;i<=n;i++){
        if(vis[i])
            continue;
        minn=inf;
        dfs(i);
        ans-=minn;
    }
    printf("%lld",ans);
    return 0;
}
