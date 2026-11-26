// https://www.luogu.com.cn/problem/P10582
// 题意：在 n×n 的全 0 矩阵上，两人各操作 n 次。
// 小蓝先手，每次把两格设为 1。
// 小乔第 i 次可把一个 i×i 的方块清零。
// 小蓝想让全程出现过的 1 的最大个数尽量大，小乔想让它尽量小。
// 输出双方最优时的这个峰值。
// 数据范围：1 ≤ T ≤ 10^5，1 ≤ n ≤ 10^9。

#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;

bool check(int x){
    if(((n+x)/(1+x)*(n+x)/(1+x)>=x)){
        return true;
    }
    return false;
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        if(n==1){
            cout<<1<<endl;
            continue;
        }
        if(n==2){
            cout<<3<<endl;
            continue;
        }
        int l=3,r=n*n,ans=3;
        while(l<=r){
            int mid=(l+r)/2;
            if(check(mid-2)){
                ans=mid;
                l=mid+1;
            }
            else{
                r=mid-1;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}