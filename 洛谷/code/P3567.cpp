// https://www.luogu.com.cn/problem/P3567
// 题意：输入包裹数 n、询问数 m，序列 a_1..a_n，以及 m 个区间询问 [l, r]。
// 对每个询问，判断是否存在一个数在区间 [l, r] 中出现次数严格大于区间长度的一半。
// 输出 m 行，存在则输出该数，否则输出 0。
// 数据范围：1 <= n, m <= 5*10^5，1 <= a_i <= n。
#include<bits/stdc++.h>
// 算法标签：可持久化线段树、权值线段树
using namespace std;
const int MAXN = 5e5+5;
const int MAXT = MAXN*25;

int n,m;
int root[MAXT];
int ls[MAXT];
int rs[MAXT];
int sum[MAXT];
int cnt;

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

int build(int l, int r) {
    int rt = ++cnt;
    if (l < r) {
        int mid = (l + r) / 2;
        ls[rt] = build(l, mid);
        rs[rt] = build(mid + 1, r);
    }
    sum[rt] = 0;
    return rt;
}

int add(int pos,int l,int r,int i){
    int rt=++cnt;
    ls[rt] = ls[i];
	rs[rt] = rs[i];
	sum[rt] = sum[i] + 1;
    if(l==r){
        //cout<<' '<<l<<endl;
        return rt;
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid)
            ls[rt]=add(pos,l,mid,ls[i]);
        else
            rs[rt]=add(pos,mid+1,r,rs[i]);
    }
    return rt;
}

int query(int l,int r,int u,int v,int len){
    if(l==r){
        if(sum[v]-sum[u]>=len){
            return l;
        }
        return 0;
    }
    int lsize=sum[ls[v]]-sum[ls[u]];
    int rsize=sum[rs[v]]-sum[rs[u]];
    int mid=(l+r)/2;
    if(lsize>=len){
        return query(l,mid,ls[u],ls[v],len);
    }
    else if(rsize>=len){
        return query(mid+1,r,rs[u],rs[v],len);
    }
    else{
        return 0;
    }
}

int main()
{
    n=read(),m=read();
    root[0]=build(1,n);
    for(int i=1;i<=n;i++){
        int u=read();
        root[i]=add(u,1,n,root[i-1]);
    }
    for(int i=1,l,r;i<=m;i++){
        l=read(),r=read();
        cout<<query(1,n,root[l-1],root[r],(r-l+1)/2+1)<<endl;
    }
    return 0;
}
