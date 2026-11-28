// https://www.luogu.com.cn/problem/P1690
// 题意：给出 n 个区域之间的有向距离和 P 个宝藏的位置。
// 从区域 1 出发，经过所有宝藏后到区域 n，求最短总路程。
// 数据范围：1 ≤ n ≤ 100，0 ≤ P ≤ 10，
// 宝藏区域编号在 [1,n]，每对区域的有向距离 ≤ 1000，
// 答案 ≤ 2^31−1。
// 难度评分：1300（洛谷分级换算）
// 算法标签：Floyd、深度优先搜索、最短路

#include<bits/stdc++.h>
using namespace std;
long long n,t[1001][1001],m,k[1001];
bool flag[1001];
long long ans=1e18;//答案初始化为无穷大。
void dfs(int now,int m1,long long sum){//深搜。
    if(!m1){
        ans=min(ans,sum+t[now][n]);
        return;
	}
    for(int i=1;i<=m;i++){
        if(!flag[i]){
            flag[i]=1;//更新标记数组。
            dfs(k[i],m1-1,sum+t[now][k[i]]);
            flag[i]=0;//回溯。
        }
    }
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	cin>>t[i][j];//建单向边。
	cin>>m;
	for(int i=1;i<=m;i++)
	cin>>k[i];
    //Floyd最短路。
	for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    if(i!=j!=k)
    t[i][j]=min(t[i][j],t[i][k]+t[k][j]);
    dfs(1,m,0);
	cout<<ans;
}
