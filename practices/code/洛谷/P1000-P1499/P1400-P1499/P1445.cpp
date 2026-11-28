// https://www.luogu.com.cn/problem/P1445
// 题意：给 n，
// 求正整数有序对 (x,y) 满足 1/x+1/y=1/(n!) 的个数，
// 交换后按不同有序对计数。输出答案对 10^9+7 取模。
// 数据范围：1 ≤ n ≤ 10^6。
// 难度评分：1800（洛谷分级换算）
// 算法标签：线性筛、数论

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;
const int MOD = 1e9+7;

int n;

int prime[MAXN];
int cnt;
int num[MAXN];

int t[MAXN];

void prepare(int n){
    for(int i=2;i<=n;i++){
        if(!num[i]){
            prime[++cnt]=i;
            num[i]=cnt;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            num[i*prime[j]]=j;
            if(i%prime[j]==0){
                break;
            }
        }
    }
}

signed main()
{
    cin>>n;
    prepare(n);
    // for(int i=2;i<=n;i++){
    //     int tmp=i;
    //     while(tmp!=1){
    //         t[num[tmp]]++;
    //         tmp/=prime[num[tmp]];
    //     }
    // }
    // int ans=1;
    // for(int i=1;i<=cnt;i++){
    //     ans=(ans*(2*t[i]+1))%MOD;
    // }
    int ans=1;
    for(int i=1;i<=cnt;i++){
        int count=0;
        int power=prime[i];
        while(power<=n){
            count+=n/power;
            power*=prime[i];
        }
        ans=(ans*(2*count+1))%MOD;
    }
    cout<<ans<<endl;
    return 0;
}