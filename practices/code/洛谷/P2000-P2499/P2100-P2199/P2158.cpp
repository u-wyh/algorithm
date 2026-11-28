// https://www.luogu.com.cn/problem/P2158
// 题意：N*N 方阵，站在左下角 (0,0) 向方阵内看，求能看到的学生人数。
// 输出能看到的学生人数。
// 数据范围：1 <= N <= 40000。
// 难度评分：1800（洛谷分级换算）
// 算法标签：欧拉函数、线性筛
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 40005;

int n;

int phi[MAXN];
int prime[MAXN];
int cnt=0;
bool vis[MAXN];

void euler(int n){
    phi[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cnt]=i;
            phi[i]=i-1;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=1;
            if(i%prime[j]==0){
                phi[i*prime[j]]=prime[j]*phi[i];
            }
            else{
                phi[i*prime[j]]=(prime[j]-1)*phi[i];
            }
        }
    }
}

int main()
{
    int n;
    cin>>n;
    if(n==1){
        cout<<0;
        return 0;
    }
    n--;
    euler(n);
    int ans=0;
    for(int i=2;i<=n;i++){
        // cout<<phi[i]<<' ';
        ans+=phi[i];
    }
    // cout<<endl;
    ans*=2;
    ans+=3;
    cout<<ans<<endl;
    return 0;
}