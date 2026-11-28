// https://www.luogu.com.cn/problem/P1164
// 题意：有 N 种菜，每种只有一份，价格是 a[i]，手上正好有 M 元。
// 统计选择若干菜使总价等于 M 的不同选法。即使价格相同，菜品不同也分别计数。
// 数据范围：1 ≤ N ≤ 100，1 ≤ M ≤ 10000，
// 1 ≤ a[i] ≤ 1000，答案在 [0,2^31-1]。
// 难度评分：1100（洛谷分级换算）
// 算法标签：动态规划

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;
const int MAXM = 1e4+5;

int n,m;
int a[MAXN];
int c[MAXN+MAXM];
int d[MAXN+MAXM];

void compute(){
    c[0]=1;
    c[a[1]]=1;
    for(int i=2;i<=n;i++){
        for(int j=0;j<=m;j++){
            d[j]=c[j];
        }
        for(int j=0;j<=m;j++){
            d[j+a[i]]+=c[j];
        }
        for(int j=0;j<=m;j++){
            c[j]=d[j];
            d[j]=0;
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    compute();
    cout<<c[m]<<endl;
    return 0;
}