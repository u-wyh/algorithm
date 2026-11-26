// https://www.luogu.com.cn/problem/P6003
// 题意：要在 K 天内还给 Bessie 至少 N 加仑牛奶，每天至少给 M 加仑；
// 选定正整数 X 后，每天根据已给总量 G 给出 Y = max(M, floor((N - G) / X)) 加仑，求满足条件的 X 的最大值。
// 数据范围：1 <= N, K, M <= 10^12，K * M < N。
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n,k,m;

bool check(int x){
    int r=n,t=k;
    while(t&&r>0){
        int y=r/x;
        if(y<=m){
            r-=m*t;
            t=0;
        }
        else{
            int a=min(t,r/y-x+1);
            r-=a*y;
            t-=a;
        }
    }
    return r<=0;
}

signed main()
{
    cin>>n>>k>>m;
    int l=1,r=n,ans=1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    cout<<ans<<endl;
    return 0;
}