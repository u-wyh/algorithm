// https://www.luogu.com.cn/problem/P1840
// 题意：数轴上 1 到 n 的点起初都是黑色。每次把闭区间 [l_i,r_i] 内的点染白，输出操作后剩余的黑点数。
// 数据范围：1 ≤ n,m ≤ 2×10^5，1 ≤ l_i ≤ r_i ≤ n。
// 算法标签：并查集

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int fa[MAXN];
int n,m;

int found(int x){
    return x==fa[x]?x:fa[x]=found(fa[x]);//父节点一定在自己右边
}

void un(int x,int y){
    fa[found(y)]=found(x);
}

int main()
{
    cin>>n>>m;
    int black=n;
    for(int i=1;i<=n+1;i++){
        fa[i]=i;
    }
    while(m--){
        int l,r;
        cin>>l>>r;
        int t=found(l);
        while(t<=r){
            un(t+1,t);//如果右边变为白色  需要合并  那么答案--
            black--;
            t=found(t);
        }
        cout<<black<<endl;
    }
    return 0;
}
