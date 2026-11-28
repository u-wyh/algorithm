// https://www.luogu.com.cn/problem/P7965
// 题意：有 n 个箱子与 n 个玩具（初始 i 号玩具在 i 号箱内）
// 有 m 个 1..n 的排列
// p_1..p_m
// （每次应用排列 p 会同时把位于 i 号箱的玩具放到 p_i 号箱）。
// 给定 q 组询问 (a, b)，
// 每次询问能否按任意顺序、任意次数（含 0 次）选择应用这些排列，
// 使 a 号玩具最终进入 b 号箱。
// 第一行输入 n, m, q，接下来 m 行每行一个排列，
// 接下来 q 行每行 a, b。
// 输出 q 行，可行输出 DA，否则输出 NE。
// 数据范围：1 <= n, m <= 1000，1 <= q <= 5*10^5，
// 1 <= a, b <= n。
// 难度评分：1300（洛谷分级换算）
// 算法标签：并查集
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;

int fa[MAXN];
int n,m,q;

void build(){
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
}

int find(int i){
    if (i != fa[i]){
        fa[i] = find(fa[i]);
    }
    return fa[i];
}

void un(int x,int y){
    fa[find(x)] = find(y);
}

int main()
{
    cin>>n>>m>>q;
    build();
    int nums[n+1];
    for(int i=1;i<=m;i++){
        for(int i=1;i<=n;i++){
            cin>>nums[i];
            un(i,nums[i]);
        }
    }
    for(int i=1,u,v;i<=q;i++){
        cin>>u>>v;
        if(find(u)==find(v)){
            cout<<"DA\n";
        }else{
            cout<<"NE\n";
        }
    }
    return 0;
}
