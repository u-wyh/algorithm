// https://www.luogu.com.cn/problem/P6436
// 题意：
// 给定 n 点树与参数 t, d, l, q，
// 每条双向航线 (u,v) 小 E 耗时 p_i、PF 耗时 e_i。
// 两人均从 1 号点出发，小 E 早 t 时刻出发，岛上可无限免费补给，
// 背包容量 k 需买 k 万元。
// PF 可在满足单程耗时 <= d 且路径中间
// 至少 q 个岛的 (u,v) 间建一条耗时
// floor(time(u->v)/2) 的双向航线。
// 路上食物不能耗尽，且不能在途中或早于小 E 到达岛上被抓（同时到达岛不算抓）。
// 输出最小 k 以及该 k 下能安全逃达的岛屿数
// r（含点 1，要求 r >= l）；无解输出 no solution。
// 数据范围：
// 1 <= n <= 7500
// 1 <= l <= n
// 0 <= t <= 10^8
// 0 <= u_i < v_i <= n（输入边端点）
// 1 <= p_i, e_i, d <= 10^8
// 0 <= q <= 20
// 保证可能新建的双向航线方案数不超过 5 * 10^6
// 难度评分：2300（洛谷分级换算）
// 算法标签：深度优先搜索、Dijkstra、排序
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 7505;
const int MAXM = 15005;
const long long INF = (1LL<<62);

int n,l,q;
long long t,d;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int wp[MAXM];
int we[MAXM];
int cntg=1;

long long disE[MAXN];
long long disP[MAXN];
long long need[MAXN];

long long best[MAXN];
long long dis[MAXN];

bool safe[MAXN];

long long ans[MAXN];
int cntans;

inline void addedge(int u,int v,int p,int e)
{
    nxt[cntg]=head[u];
    to[cntg]=v;
    wp[cntg]=p;
    we[cntg]=e;
    head[u]=cntg++;
}

// 预处理两人的根路径距离和背包需求
void dfs1(int u,int fa)
{
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];

        if(v==fa){
            continue;
        }

        disE[v]=disE[u]+wp[i];
        disP[v]=disP[u]+we[i];
        need[v]=max(need[u],(long long)wp[i]);

        dfs1(v,u);
    }
}

// 枚举以s为一个端点的所有合法新增航线
void dfs2(int s,int u,int fa,int len,long long dist)
{
    if(u>s&&len>=q+1){
        long long w=dist/2;

        best[u]=min(best[u],disP[s]+w);
        best[s]=min(best[s],disP[u]+w);
    }

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];

        if(v==fa){
            continue;
        }

        long long nd=dist+we[i];

        if(nd>d){
            continue;
        }

        dfs2(s,v,u,len+1,nd);
    }
}

// 判断根路径上的所有点是否安全
void dfs3(int u,int fa)
{
    if(safe[u]){
        ans[++cntans]=need[u];
    }

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];

        if(v==fa){
            continue;
        }

        safe[v]=safe[u]&&disE[v]<=t+dis[v];
        dfs3(v,u);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>t>>d>>l>>q;

    for(int i=1;i<n;i++){
        int u,v,p,e;
        cin>>u>>v>>p>>e;

        addedge(u,v,p,e);
        addedge(v,u,p,e);
    }

    dfs1(1,0);

    for(int i=1;i<=n;i++){
        best[i]=INF;
    }

    best[1]=0;

    for(int s=1;s<=n;s++){
        dfs2(s,s,0,0,0);
    }

    priority_queue<
        pair<long long,int>,
        vector<pair<long long,int>>,
        greater<pair<long long,int>>
    > heap;

    for(int i=1;i<=n;i++){
        dis[i]=best[i];

        if(dis[i]<INF){
            heap.push({dis[i],i});
        }
    }

    while(!heap.empty()){
        long long du=heap.top().first;
        int u=heap.top().second;
        heap.pop();

        if(du!=dis[u]){
            continue;
        }

        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            long long nd=du+we[i];

            if(nd<dis[v]){
                dis[v]=nd;
                heap.push({nd,v});
            }
        }
    }

    safe[1]=true;
    dfs3(1,0);

    if(cntans<l){
        cout<<"no solution\n";
        return 0;
    }

    sort(ans+1,ans+cntans+1);

    long long k=ans[l];
    int r=upper_bound(ans+1,ans+cntans+1,k)-ans-1;

    cout<<k<<'\n';
    cout<<r<<'\n';

    return 0;
}