// https://www.luogu.com.cn/problem/P2853
// 题意：K 头牛分别在 N 个牧场之一，牧场间有 M 条单向边。
// 求有多少个牧场是所有 K 头牛都能到达的。
// 输出满足条件的牧场数。
// 数据范围：1 <= K <= 100，1 <= N <= 1000，1 <= M <= 10000。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int MAXM = 10005;
const int MAXK = 105;

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt=1;
int sum[MAXN];
bool vis[MAXN];

int nums[MAXK];
int n,m,k;

void dfs(int u){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(!vis[v]){
            vis[v]=true;
            dfs(v);
        }
    }
}

void fun(){
    for(int i=1;i<=n;i++){
        if(vis[i]){
            sum[i]++;
            vis[i]=false;
        }
    }
}

int main()
{
    cin>>k>>n>>m;
    for(int i=1;i<=k;i++){
        cin>>nums[i];
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;
    }

//    for(int i=1;i<=cnt;i++){
//        cout<<Next[i]<<' '<<to[i]<<endl;
//    }

    for(int i=1;i<=k;i++){
        vis[nums[i]]=true;
        dfs(nums[i]);
        fun();
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        //cout<<sum[i]<<" ";
        if(sum[i]==k){
            ans++;
        }
    }
    cout<<ans;
    return 0;
}
