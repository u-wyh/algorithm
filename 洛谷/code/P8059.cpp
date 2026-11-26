// https://www.luogu.com.cn/problem/P8059
// 题意：1..n 号共 n 只猴子，1 号猴子挂在树枝上不会掉落，每只猴子左右两只手分别最多抓着一只猴子（形成无向连接，不与 1 号连通即掉落）。
// 从时刻 0 开始共有 m 秒，第 i 秒（时刻 i-1）有一只猴子放开它的左手（1）或右手（2）。
// 求每只猴子掉落到地上的时刻，未掉落输出 -1。
// 第一行输入 n, m，接下来 n 行每行两个整数表示猴子 k 左右手抓住的猴子（-1 为空），接下来 m 行每行两个整数表示松手猴子编号与手编号（1/2）。
// 输出 n 行每行一个整数。
// 数据范围：1 <= n <= 2*10^5，1 <= m <= 4*10^5。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXM = 4e5+5;

int n,m;
int fa[MAXN];
int ls[MAXN],rs[MAXN];
struct node{
    int u,op;
}nums[MAXM];
int ans[MAXN];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=n;i++){
        cin>>ls[i]>>rs[i];
    }
    for(int i=1;i<=m;i++){
        cin>>nums[i].u>>nums[i].op;
    }
    return 0;
}
