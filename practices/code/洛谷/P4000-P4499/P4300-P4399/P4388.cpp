// https://www.luogu.com.cn/problem/P4388
// 题意：用稻草人摆出 R * C 矩形网格，
// 从左上角向右下角射箭穿透毁坏对角线经过格子的稻草人，给定每次毁坏数 N
// 求有多少种本质不同的矩形摆放方案（R * C 与 C * R 等价）。
// 数据范围：1 <= N <= 10^6。
// 难度评分：1800（洛谷分级换算）
// 算法标签：欧拉函数、线性筛、数论
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

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
                break;
            }
            else{
                phi[i*prime[j]]=(prime[j]-1)*phi[i];
            }
        }
    }
}

int main()
{
    cin>>n;
    euler(n+1);
    long long ans=0;
    for(int i=1;i*i<=n;i++){
        if(n%i==0){
            ans+=phi[i+1];
            if(n/i!=i){
                ans+=phi[n/i+1];
            }
        }
    }
    ans++;
    ans/=2;
    cout<<ans<<endl;
    return 0;
}