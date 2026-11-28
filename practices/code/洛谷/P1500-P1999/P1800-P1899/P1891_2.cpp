// https://www.luogu.com.cn/problem/P1891
// 题意：每组给定正整数 n，求 i 从 1 到 n 时，
// i 与 n 的最小公倍数之和。
// 数据范围：1 ≤ T ≤ 3×10^5，1 ≤ n ≤ 10^6。
// 难度评分：1900（洛谷分级换算）
// 算法标签：线性筛、欧拉函数、数论

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;

int phi[MAXN];
int pri[MAXN];
int len;
bool vis[MAXN];
int f[MAXN];

void prepare(int n){
    phi[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            phi[i]=i-1;
            pri[++len]=i;
        }
        for(int j=1;j<=len&&(i*pri[j]<=n);j++){
            vis[i*pri[j]]=true;
            if(i%pri[j]==0){
                phi[i*pri[j]]=phi[i]*pri[j];
                break;
            }
            else{
                phi[i*pri[j]]=phi[i]*(pri[j]-1);
            }
        }
    }

    for(int d=1;d<=n;d++){
        for(int v=d;v<=n;v+=d){
            f[v]+=d*phi[d];
        }
    }
}

signed main()
{
    prepare(1000000);
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        int ans=n*(f[n]+1)/2;
        cout<<ans<<endl;
    }
    return 0;
}