// https://www.luogu.com.cn/problem/P2391
// 题意：n 个位置初始为 0，进行 m 次区间染色。
// 第 i 次将 ((i*p+q) mod n)+1 到 ((i*q+p) mod n)+1（含端点）染成颜色 i。
// 输出最终每个位置的颜色（未染色为 0）。
// 数据范围：1 <= n <= 10^6，1 <= m <= 10^7，1 <= m*p+q, m*q+p <= 2*10^9。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n,m,p,q;
int fa[MAXN];
int col[MAXN];

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

int main()
{
    cin>>n>>m>>p>>q;
    for(int i=1;i<=n+1;i++){
        fa[i]=i;
    }
    for(int i=m;i>=1;i--){
        int l=(i*p+q)%n+1;
        int r=(i*q+p)%n+1;
        if(l>r){
            swap(l,r);
        }
        for(int j=find(l);j<=r;j=find(j+1)){
            //表示这个节点可以染色
            col[j]=i;
            fa[j]=j+1;
        }
    }
    for(int i=1;i<=n;i++){
        cout<<col[i]<<endl;
    }
    return 0;
}
