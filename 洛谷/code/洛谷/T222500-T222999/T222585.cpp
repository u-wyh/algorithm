// https://www.luogu.com.cn/problem/T222585
// 题意：给 n 个点、m 条有向边组成的无环图。
// 输出：字典序最小的拓扑序，点号用空格分隔。
// 数据范围：1 <= n, m <= 10^5，允许重边。
// 算法标签：拓扑排序、优先队列
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int MAXM = 100001;

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int edge[MAXM][2];
int indegree[MAXN];
int cnt=1;
int n,m;
priority_queue<int, vector<int>, greater<int>> pq;

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>edge[i][0]>>edge[i][1];
    }
    for(int i=1;i<=m;i++){
        Next[cnt]=head[edge[i][0]];
        to[cnt]=edge[i][1];
        head[edge[i][0]]=cnt++;
        indegree[edge[i][1]]++;
    }
    for(int i=1;i<=n;i++){
        if(indegree[i]==0){
            pq.push(i);
        }
    }
    while(!pq.empty()){
        int cur=pq.top();
        pq.pop();
        printf("%d ",cur);
        for(int i=head[cur];i!=0;i=Next[i]){
            indegree[to[i]]--;
            if(indegree[to[i]]==0){
                pq.push(to[i]);
            }
        }
    }
    return 0;
}
