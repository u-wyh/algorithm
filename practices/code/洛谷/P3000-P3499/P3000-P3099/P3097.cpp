// https://www.luogu.com.cn/problem/P3097
// 题意：输入挤奶机数量 N、天数 D，每台机器初始日产奶量 M_i，
// 以及每天开始前的一次单点修改 (i, m) 表示将 M_i 改为 m。
// 每天可以选择若干台机器使用，但不能同时使用编号相邻的两台机器。
// 求这 D 天每天最大产奶量之和。
// 输出一个正整数表示 D 天的总最大产奶量（需用 64 位整数存储）。
// 数据范围：1 <= N <= 40000。
// 1 <= D <= 50000，M_i 和 m 为正整数。
// 题面未注明 M_i 和 m 的数值上限。
// 总产奶量可能超过 32 位整数。
// 算法标签：线段树、动态规划
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4e4+5;
const int INF = 1e9;

int n,m;
int arr[MAXN];
struct node{
    int a,b,c,d;//分别表示左右边界都不选 选左边界 选右边界 都选
    // 00 10 01 11
}tree[MAXN<<2];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

inline int max(int a, int b, int c, int d) {
    return max(max(a, b), max(c, d));
}

void up(int i) {
    int l = i << 1, r = i << 1 | 1;
    tree[i].a = max(tree[l].a + tree[r].a, tree[l].c + tree[r].a, tree[l].a + tree[r].b, -INF);
    tree[i].b = max(tree[l].b + tree[r].a, tree[l].d + tree[r].a, tree[l].b + tree[r].b, -INF);
    tree[i].c = max(tree[l].a + tree[r].c, tree[l].c + tree[r].c, tree[l].a + tree[r].d, -INF);
    tree[i].d = max(tree[l].b + tree[r].c, tree[l].d + tree[r].c, tree[l].b + tree[r].d, -INF);
}

void build(int l,int r,int i){
    if(l==r){
        tree[i].a=0;
        tree[i].b=tree[i].c=-INF;
        tree[i].d=arr[l];
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void update(int pos,int val,int l,int r,int i){
    if(l==r){
        tree[i].d=val;
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            update(pos,val,l,mid,i<<1);
        }
        else{
            update(pos,val,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
    build(1,n,1);
    long long ans=0;
    for(int i=1;i<=m;i++){
        int pos=read();
        int val=read();
        update(pos,val,1,n,1);
        ans+=max(max(tree[1].a,tree[1].b),max(tree[1].c,tree[1].d));
    }
    cout<<ans<<endl;
    return 0;
}