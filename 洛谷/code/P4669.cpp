// https://www.luogu.com.cn/problem/P4669
// 题意：N 个人开会，k 人一轮需 k*P+V 分钟（1 人耗时为 0），可并行分小组开会再由各组代表继续递归/开会选出最终方案，求最少总时间。
// 数据范围：1 <= N <= 10^15，1 <= P, V <= 1000。
#include<bits/stdc++.h>
// 算法标签：动态规划
using namespace std;
#define int long long
const int MAXN = 1e7+5;

int n,p,v;
int f[MAXN];

signed main()
{
    cin>>n>>p>>v;
    f[0]=1;
    for(int i=1;i<=10000000;i++){
        for(int j=2;j<=(i-v)/p;j++){
            f[i]=max(f[i],f[i-v-p*j]*j);
        }
        if(f[i]>=n){
            cout<<i<<endl;
            return 0;
        }
    }
    return 0;
}