// https://www.luogu.com.cn/problem/P10480
// 题意：给 N 个点、M 条边的有向无环图。
// 按点的编号逐个输出，从该点出发能到达的不同点数，起点也计入。
// 数据范围：1 ≤ N,M ≤ 30000，1 ≤ x,y ≤ N。
// 算法标签：邻接表、模拟

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 30005;
const int MAXM = 30005;

int n,m;
int u,v;
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt=1;
bool vis[MAXN];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>u>>v;
        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;
    }
    for(int i=1;i<=n;i++){
        int ans=0;
        vis[i]=true;
        for(int j=head[i];j>0;j=Next[j]){
            vis[to[j]]=true;
        }
        for(int j=1;j<=n;j++){
            printf("%3d",vis[j]);
            if(vis[j]){
                ans++;
                vis[j]=false;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}

