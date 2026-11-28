// https://www.luogu.com.cn/problem/P1137
// 题意：有 N 座城市，每条关系 (x,y) 表示两地有路且 x 在 y 西边。
// 只能沿路向东走，可以任选起点。
// 对每个终点 i，输出以 i 结束的路线最多能经过几个城市。
// 数据范围：1 ≤ N ≤ 10^5，1 ≤ M ≤ 2 × 10^5。
// 难度评分：1400（洛谷分级换算）
// 算法标签：拓扑排序、动态规划

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int MAXM = 200005;

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int indegree[MAXN];
int ans[MAXN];
int cnt=1;
int n,m;
queue<int >q;

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;
        indegree[v]++;
    }
    for(int i=1;i<=n;i++){
        if(indegree[i]==0){
            q.push(i);
            //ans[i]=1;
        }
    }
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        for(int i=head[cur];i>0;i=Next[i]){
            indegree[to[i]]--;
            if(indegree[to[i]]==0){
                q.push(to[i]);
            }
            ans[to[i]]=max(ans[to[i]],ans[cur]+1);
        }
    }
    for(int i=1;i<=n;i++){
        printf("%d\n",ans[i]+1);
    }
    return 0;
}
