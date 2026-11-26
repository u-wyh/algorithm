// https://www.luogu.com.cn/problem/P6145
// 题意：在 M 天内进行 N 次挤奶，第 i 次不早于第 S_i 天，且有 C 条约束 (a, b, x) 要求第 b 次比第 a 次至少晚 x 天；
// 保证有解且均不超过第 M 天，求每次挤奶的最早日期。
// 数据范围：1 <= N, C <= 10^5，2 <= M <= 10^9，1 <= S_i, x <= M。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int MAXM = 100005;

int n,M,m;
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;
int indegree[MAXN];
int Time[MAXN];
int ans[MAXN];
queue<int >q;

int main()
{
    cin>>n>>M>>m;
    for(int i=1;i<=n;i++){
        cin>>Time[i];
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=w;
        head[u]=cnt++;
        indegree[v]++;
    }
    for(int i=1;i<=n;i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int cur=q.front();
        ans[cur]=max(ans[cur],Time[cur]);
        q.pop();
        for(int i=head[cur];i>0;i=Next[i]){
            indegree[to[i]]--;
            if(indegree[to[i]]==0){
                q.push(to[i]);
            }
            ans[to[i]]=max(ans[cur]+weight[i],ans[to[i]]);
        }
    }
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
