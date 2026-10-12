// 用途：用前缀和差值约束回答区间和，未确定时输出 UNKNOWN。
// 时间：O((n+q)α(n))。
// 空间：O(n)。
// 例题：https://www.luogu.com.cn/problem/P8779
// 题意：已知若干区间和，询问另一区间和；不能确定则输出 UNKNOWN。
// 思路：把区间和化为两个前缀和的差，用带权并查集维护差值。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+2;

int n,m,q;
int fa[MAXN];
long long dist[MAXN];

//初始化带权并查集
void prepare() {
    for (int i = 0; i <= n; i++) {
        fa[i] = i;
        dist[i] = 0;
    }
}

//寻找i节点的父亲 扁平化处理  并在该过程中更新距离
int find(int i) {
    if (i != fa[i]) {
        int tmp = fa[i];
        fa[i] = find(tmp);
        dist[i] += dist[tmp];//将距离更新正确
    }
    return fa[i];
}

void un(int l, int r, long long v) {
    int lf = find(l), rf = find(r);
    if (lf != rf) {
        fa[lf] = rf;//强制要求后面的节点作为父亲
        dist[lf] = v + dist[r] - dist[l];
    }
}

long long query(int l, int r) {
    if (find(l) != find(r)) {
        //不在一个集合中
        return LLONG_MAX;
    }
    return dist[l] - dist[r];
}

int main()
{
    cin>>n>>m>>q;
    prepare();
    int l,r;//我们将这些看成区间  每次r++
    long long v;
    for(int i=1;i<=m;i++){
        cin>>l>>r>>v;
        r++;
        un(l,r,v);
    }
    for (int i = 1; i <= q; i++) {
        cin>>l>>r;
        r++;
        v = query(l, r);
        if (v == LLONG_MAX) {
            cout<<"UNKNOWN"<<endl;
        } else {
            cout<<v<<endl;
        }
    }
    return 0;
}
