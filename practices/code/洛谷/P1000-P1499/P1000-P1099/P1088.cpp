// https://www.luogu.com.cn/problem/P1088
// 题意：把 1 到 N 的所有排列按字典序排列。
// 给当前排列和 M，求在它之后第 M 个排列，输出其中的 N 个数。
// 数据范围：1 ≤ N ≤ 10000，1 ≤ M ≤ 100，
// 保证答案仍在排列范围内。
// 难度评分：900（洛谷分级换算）
// 算法标签：模拟

#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;

int a[10110],n,m;
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(;m--;)
        next_permutation(a+1,a+n+1);
    for(int i=1;i<=n;i++)
        cout<<a[i]<<' ';
    return 0;
}

