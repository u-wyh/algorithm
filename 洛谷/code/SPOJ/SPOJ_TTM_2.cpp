// https://www.spoj.com/problems/TTM/
// 题意：给长度为 n 的数组 A 和 m 次操作。
// C l r d 将区间 [l, r] 加 d，时间加 1。
// Q l r 查当前区间和，H l r t 查时刻 t 的和。
// B t 回到时刻 t，之后无法访问被丢弃的版本。
// 输出：逐行输出 Q 和 H 查询的答案。
// 数据范围：1 <= n, m <= 10^5，
// 绝对值满足 abs(A_i) <= 10^9，abs(d) <= 10^4。
// 1 <= l <= r <= n，初始时刻为 0。
// 查询和回退的时刻 t 合法，且 t >= 0。
// 算法标签：可持久化线段树、懒标记
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXT = MAXN*100;

int n,m,t;
int val[MAXN];

int cnt;
int root[MAXN];

int sum[MAXT];
int tag[MAXT];
int len[MAXT];
int ls[MAXT];
int rs[MAXT];

void up(int i){
    sum[i]=sum[ls[i]]+sum[rs[i]];
}

int build(int l,int r){
    int rt=++cnt;
    len[rt]=r-l+1;
    if(l==r){
        sum[rt]=val[l];
    }
    else{
        int mid=(l+r)>>1;
        ls[rt]=build(l,mid);
        rs[rt]=build(mid+1,r);
        up(rt);
    }
    return rt;
}

int clone(int i){
    ++cnt;
    ls[cnt]=ls[i];
    rs[cnt]=rs[i];
    tag[cnt]=tag[i];
    sum[cnt]=sum[i];
    len[cnt]=len[i];
    return cnt;
}

void lazy(int i,int v){
    sum[i]+=len[i]*v;
    tag[i]+=v;
}

void down(int i){
    if(tag[i]){
        ls[i]=clone(ls[i]);
        rs[i]=clone(rs[i]);
        lazy(ls[i],tag[i]);
        lazy(rs[i],tag[i]);
        tag[i]=0;
    }
}

int addrange(int jobl,int jobr,int jobv,int l,int r,int i){
    int rt=clone(i);
    if(jobl<=l&&r<=jobr){
        lazy(rt,jobv);
    }
    else{
        int mid=(l+r)>>1;
        down(rt);
        if(jobl<=mid){
            ls[rt]=addrange(jobl,jobr,jobv,l,mid,ls[rt]);
        }
        if(jobr>mid){
            rs[rt]=addrange(jobl,jobr,jobv,mid+1,r,rs[rt]);
        }
        up(rt);
    }
    return rt;
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return sum[i];
    }
    else{
        int ans=0;
        down(i);
        int mid=(l+r)>>1;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,ls[i]);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,rs[i]);
        }
        return ans;
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }

    root[0]=build(1,n);
    t=0;

    for(int i=1;i<=m;i++){
        string op;
        int l,r,d;
        cin>>op;
        if(op=="C"){
            cin>>l>>r>>d;
            root[t+1]=addrange(l,r,d,1,n,root[t]);
            t++;
        }
        else if(op=="Q"){
            cin>>l>>r;
            cout<<query(l,r,1,n,root[t])<<endl;
        }
        else if(op=="H"){
            cin>>l>>r>>d;
            cout<<query(l,r,1,n,root[d])<<endl;
        }
        else{
            cin>>d;
            t=d;
        }
    }
    return 0;
}