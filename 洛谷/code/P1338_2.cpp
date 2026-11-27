// https://www.luogu.com.cn/problem/P1338
// 题意：把 1 到 n 的排列按字典序从小到大考察。逆序对指左边数大于右边数的一对下标。输出第一个恰好有 m 个逆序对的排列。
// 数据范围：n ≤ 50000，输入保证有解。
// 算法标签：构造、数学

#include<bits/stdc++.h>
using namespace std;

long long n,m;

int main()
{
    cin>>n>>m;
    int k;
    for(int i=1;i<=n;i++){
        if(i*i-i>=2*m){
            k=i;
            break;
        }
    }
    for(int i=1;i<=n-k;i++){
        cout<<i<<' ';
    }
    if(m==(k*k-k)/2){
        for(int i=n;i>n-k;i--){
            cout<<i<<' ';
        }
    }else{
        int h=m-((k-1)*(k-1)-(k-1))/2;
        cout<<n-k+1+h<<' ';
        for(int i=n;i>n-k;i--){
            if(i==n-k+1+h)
                continue;
            else
                cout<<i<<' ';
        }
    }
    return 0;
}
