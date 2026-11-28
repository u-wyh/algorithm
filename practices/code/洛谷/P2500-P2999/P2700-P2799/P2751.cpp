// https://www.luogu.com.cn/problem/P2751
// 题意：N 个工件依次经过 A、B 两道工序，
// 各有 M_1、M_2 台平行机器独立工作。
// 已知每台机器单次耗时，求完成所有 A 工序的最早时间，
// 以及完成所有 A、B 工序的最早时间。
// 一行输出两个整数。
// 数据范围：1 <= N <= 1000，1 <= M_1, M_2 <= 30，
// 单台耗时 in [1, 20]。
// 难度评分：1600（洛谷分级换算）
// 算法标签：贪心、优先队列
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int MAXM = 35;

int n,m1,m2;
int f[MAXN];
int g[MAXN];

struct node{
    int t,v;
};

struct compare{
    bool operator()(node a,node b){
        return a.t>b.t;
    }
};
priority_queue<node,vector<node>,compare>heap;

int main()
{
    cin>>n>>m1>>m2;

    for(int i=1;i<=m1;i++){
        node tmp;
        cin>>tmp.v;
        heap.push({tmp.v,tmp.v});
    }
    for(int i=1;i<=n;i++){
        node u=heap.top();
        heap.pop();
        f[i]=u.t;
        heap.push({u.t+u.v,u.v});
    }

    while(!heap.empty()){
        heap.pop();
    }

    for(int i=1;i<=m2;i++){
        node tmp;
        cin>>tmp.v;
        heap.push({tmp.v,tmp.v});
    }
    for(int i=n;i>=1;i--){
        node u=heap.top();
        heap.pop();
        g[i]=u.t;
        heap.push({u.t+u.v,u.v});
    }

    int ans=0;
    for(int i=1;i<=n;i++){
        ans=max(ans,f[i]+g[i]);
    }
    cout<<f[n]<<' '<<ans<<endl;
    return 0;
}