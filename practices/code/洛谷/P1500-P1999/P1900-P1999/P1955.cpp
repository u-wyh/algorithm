// https://www.luogu.com.cn/problem/P1955
// 题意：每组给定 n 条变量约束。
// e=1 表示两个变量必须相等，e=0 表示必须不同。
// 判断能否同时满足全部约束，能输出 YES，否则输出 NO。
// 数据范围：1 ≤ t ≤ 10，1 ≤ n ≤ 10^5，
// 1 ≤ i,j ≤ 10^9，e 为 0 或 1。
// 难度评分：1300（洛谷分级换算）
// 算法标签：并查集

#include<bits/stdc++.h>
using namespace std;

int t,n,x,y,opt,fa[200010],a[100005],b[100005];

void build(int n){
    for(int i=0;i<=n;i++){
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
    cin>>t;
    while(t--){
        cin>>n;
        build(2*n);
        for(int i=1;i<=n;i++){
            cin>>x>>y>>opt;
            if(opt==1){
                un(x,y);
            }else{
                int fx=fa[x];
                int fy=fa[y];
                if(fx==fy){
                    cout<<"NO"<<endl;
                    goto next;
                }else{
                    un(x+n,y);
                    un(y+n,x);
                }
            }
        }
        cout<<"YES"<<endl;
        next:
            continue;
    }
    return 0;
}
