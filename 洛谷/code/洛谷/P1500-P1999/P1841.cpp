// https://www.luogu.com.cn/problem/P1841
// 题意：给定 n 座城市和 m 条带长度的双向道路。
// 如果删除某座城市后，另外两座城市之间的最短路变长或不再连通，就称它为重要城市。
// 按编号升序输出所有重要城市，
// 没有则输出 No important cities.。
// 数据范围：N ≤ 200，M ≤ N(N−1)/2，
// 道路长度在 [1,10000]，无重边和自环。
// 算法标签：Floyd、最短路

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;
const int MAXM = 20005;

int n,m;
int dis[MAXN][MAXN];
int kind[MAXN][MAXN];
bool ans[MAXN];

void floyd(){
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i!=j&&j!=k&&k!=i)
                if(dis[i][k]!=INT_MAX&&dis[k][j]!=INT_MAX){
                    if(dis[i][j]>dis[i][k]+dis[k][j]){
                        dis[i][j]=dis[i][k]+dis[k][j];
                        kind[i][j]=1;
                    }
                    else if(dis[i][j]==dis[i][k]+dis[k][j]){
                        kind[i][j]++;
                    }
                }
            }
        }
    }
}

void compute(){
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(kind[i][j]==1&&i!=j&&k!=j&&i!=k){
                    if(dis[i][k]!=INT_MAX&&dis[k][j]!=INT_MAX&&dis[i][j]==dis[i][k]+dis[k][j]){
                        ans[k]=true;
                    }
                }
            }
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            dis[i][j]=INT_MAX;
        }
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        dis[u][v]=w;
        dis[v][u]=w;
    }
    floyd();
    compute();
    bool flag=false;
    for(int i=1;i<=n;i++){
        if(ans[i]){
            cout<<i<<' ';
            flag=true;
        }
    }
    if(!flag){
        cout<<"No important cities."<<endl;
    }
    return 0;
}
