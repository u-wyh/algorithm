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
