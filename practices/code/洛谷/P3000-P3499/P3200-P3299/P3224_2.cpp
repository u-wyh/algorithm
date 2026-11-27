// https://www.luogu.com.cn/problem/P3224
// 题意：输入岛屿数 n、初始桥数 m、各岛屿互异的重要度排名 p_1..p_n，
// 以及 q 次操作。
// 操作 'B x y' 表示在岛 x 与 y 之间修桥合并连通块；
// 操作 'Q x k'
// 表示查询当前与 x 连通的所有岛屿中重要度第 k
// 小的岛屿编号（不存在输出 -1）。
// 对每个 'Q' 操作输出一行答案岛屿编号。
// 数据范围：1 <= m <= n <= 10^5，
// 1 <= q <= 3*10^5，p 为 1..n 的排列。
// 算法标签：线段树合并、并查集
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXT = MAXN*40;

int n,m,q;
int pos[MAXN];
int fa[MAXN];

int root[MAXN];
int ls[MAXT];
int rs[MAXT];
int sz[MAXT];
int cntv;

void up(int x){
    sz[x]=sz[ls[x]]+sz[rs[x]];
}

int add(int val,int l,int r,int i){
    int rt=i;
    if(rt==0){
        rt=++cntv;
    }
    if(l==r){
        sz[rt]=1;
    }
    else{
        int mid=(l+r)>>1;
        if(val<=mid){
            ls[rt]=add(val,l,mid,ls[rt]);
        }
        else{
            rs[rt]=add(val,mid+1,r,rs[rt]);
        }
        up(rt);
    }
    return rt;
}

int merge(int l, int r, int t1, int t2) {
    if (t1 == 0 || t2 == 0) {
        return t1 + t2;
    }
    if (l == r) {
        // 遇到叶子结点
        sz[t1] += sz[t2];
    } else {
        int mid = (l + r) >> 1;
        ls[t1] = merge(l, mid, ls[t1], ls[t2]);
        rs[t1] = merge(mid + 1, r, rs[t1], rs[t2]);
        up(t1);
    }
    return t1;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
        root[fy]=merge(1,n,root[fy],root[fx]);
    }
}

int query(int jobv,int l,int r,int i){
    if(i==0||jobv>sz[i]){
        return -1;
    }
    if(l==r){
        return pos[l];
    }
    else{
        int mid=(l+r)>>1;
        if(sz[ls[i]]>=jobv){
            return query(jobv,l,mid,ls[i]);
        }
        else{
            return query(jobv-sz[ls[i]],mid+1,r,rs[i]);
        }
    }
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=n;i++){
        int val;
        scanf("%d",&val);
        pos[val]=i;
        root[i]=add(val,1,n,root[i]);
    }
    for(int i=1;i<=m;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        un(x,y);
    }
    scanf("%d",&q);
    for(int i=1;i<=q;i++){
        char op;
        int x,y;
        scanf(" %c %d %d",&op,&x,&y);
        if(op=='B'){
            un(x,y);
        }
        else{
            printf("%d\n",query(y,1,n,root[find(x)]));
        }
    }
    return 0;
}