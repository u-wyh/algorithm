// https://www.luogu.com.cn/problem/P1287
// 题意：将 n 个互不相同的球放入 r 个互不相同的盒子中，要求每个盒子都不为空，求方案数。
// 输入：一行输入两个整数 n 和 r。
// 输出：一行输出一个整数表示方案数。
// 数据范围：0 <= r <= n <= 10，答案小于 2^31。
#include<bits/stdc++.h>
using namespace std;

int comb(int a,int b){
    int ans=1;
    for(int i=1;i<=b;i++){
        ans*=(a-i+1);
        ans/=i;
    }
    return ans;
}

int main()
{
    int n,r;
    cin>>n>>r;
    int ans=0;
    for(int k=0;k<=r;k++){
        int tmp=1;
        if((r-k)&1){
            tmp=-1;
        }
        tmp*=comb(r,k);
        for(int i=1;i<=n;i++){
            tmp*=k;
        }
        // cout<<k<<":  "<<tmp<<endl;
        ans+=tmp;
    }
    cout<<ans<<endl;
    return 0;
}