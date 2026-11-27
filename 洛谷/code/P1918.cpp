// https://www.luogu.com.cn/problem/P1918
// 题意：给定 n 个位置各自的球瓶数，所有数量互异。每次询问给出目标数量 m，输出球瓶恰好有 m 个的位置编号，找不到输出 0。
// 数据范围：1 ≤ n,Q ≤ 10^5，1 ≤ a_i,m ≤ 10^9。
// 算法标签：map

#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,m;
    map<int ,int >ds;
    cin>>n;
    int a,b;
    for(int i=1;i<=n;i++){
        cin>>a;
        ds[a]=i;
    }
    cin>>m;
    while(m--){
        cin>>b;
        if(ds.find(b)!=ds.end())
            cout<<ds[b]<<endl;
        else
            cout<<0<<endl;
    }
    return 0;
}
