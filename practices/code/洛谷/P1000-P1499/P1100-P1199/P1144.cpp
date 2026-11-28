// https://www.luogu.com.cn/problem/P1144
// 题意：给 n 个点、m 条边的无向无权图。
// 对每个点求从 1 号点出发的最短路条数，重边分开计数。
// 答案对 100003 取模，走不到就输出 0。
// 数据范围：1 ≤ n ≤ 10^6，1 ≤ m ≤ 2 × 10^6。
// 难度评分：1500（洛谷分级换算）
// 算法标签：广度优先搜索、最短路

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int MAXM = 4e6+5;
const int MOD = 100003;

int cnt=1;
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int dis[MAXN];
int Cnt[MAXN];
int n,m;
queue<pair<int,int>>q;

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        dis[i]=INT_MAX;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;
    }
    dis[1]=0;
    Cnt[1]=1;
    q.push({1,0});
    while(q.empty()){
        int u=q.front().first;
        int f=q.front().second;
        q.pop();
        for(int i=head[u];i>0;i=Next[i]){
            if(to[i]!=u){
                if(dis[to[i]]==dis[u]+1)
                    Cnt[to[i]]+=Cnt[u];
                else if(dis[to[i]]>dis[u]+1){
                    Cnt[to[i]]=Cnt[u];
                    dis[to[i]]=dis[u]+1;
                }
                q.push({to[i],u});
            }
        }
    }
    for(int i=1;i<=n;i++){
        cout<<Cnt[i]<<endl;
    }
    return  0;
}
