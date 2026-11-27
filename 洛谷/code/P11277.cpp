// https://www.luogu.com.cn/problem/P11277
// 题意：构造 n 个正整数，让恰好 k 个下标对 (i,j) 满足 i<j，且两数中较大者能被较小者整除。
// 满分要求每个输出数都不超过 2n-1，任意一个方案都可以。
// 数据范围：1 ≤ n ≤ 250000，0 ≤ k ≤ n(n-1)/2，保证有解。
// 算法标签：贪心、构造

#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MAXN = 250005;

int n,k,m,num;

signed main()
{
    cin>>n>>k;
    //这道题最大的问题就是加入1不是加入到 k<n-m为止   而是尽可能的多加1   
    // 这样可以尽量减轻后面的压力
    while(m<n){
        if(k<(n-m-1)){
            break;
        }
        k-=(n-m-1);
        m++;
        cout<<1<<' ';
    }

    num=n-m+1;

    while(k!=0){
        while((num*(num-1)/2)>k){
            num--;
        }
        k-=(num*(num-1))/2;
        m+=num;
        // while(m>n){
        //     cout<<888<<endl;
        // }
        for(int i=1;i<=num;i++){
            cout<<(n+m-1)<<' ';
        }
    }

    for(int i=m+1;i<=n;i++){
        cout<<(i+n-1)<<' ';
    }

    return 0;
}