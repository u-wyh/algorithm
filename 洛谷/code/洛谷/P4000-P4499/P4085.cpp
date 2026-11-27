// https://www.luogu.com.cn/problem/P4085
// 题意：第一行输入干草捆数 N 和最低风味和要求 M；
// 接下来 N 行每行输入第 i 个干草捆的风味 F_i 和辣度 S_i。
// 选择一段连续区间 [l, r]，使区间内 F_i 之和至少为 M，
// 并最小化区间内 S_i 的最大值。
// 输出满足要求的最小辣度（保证有解）。
// 数据范围：1 <= N <= 10^5，
// 1 <= F_i, S_i <= 10^9，1 <= M <= 10^18。
// 算法标签：二分答案
#include<bits/stdc++.h>
using namespace std;
int n;
long long m;
long long f[100005],s[100005];

bool check(long long mid){
    long long sum=0;
    for(int i=1;i<=n;i++){
        if(s[i]>mid){
            sum=0;
        }else{
            sum+=f[i];
            if(sum>=m){
                return true;
            }
        }
    }
    return false;
}

int main()
{
    cin>>n>>m;
    long long l=0,r=0;
    for(int i=1;i<=n;i++){
        cin>>f[i]>>s[i];
        r=max(r,s[i]);
    }
    long long ans=r;
    while(l<=r){
        long long mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    cout<<ans;
    return 0;
}
