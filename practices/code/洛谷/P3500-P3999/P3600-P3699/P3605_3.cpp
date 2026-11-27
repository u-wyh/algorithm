// https://www.luogu.com.cn/problem/P3605
// 题意：输入奶牛数量 n，每头奶牛互不相同的能力指数 p_1..p_n，
// 以及 2..n 号奶牛在公司树（1 号为根）中的父节点编号。
// 若奶牛 i 是奶牛 j 的祖先，则 j 是 i 的下属；
// 对每头奶牛 i 统计其下属中满足 p_j > p_i 的人数。
// 输出 n 行，第 i 行表示第 i 头奶牛满足条件的下属数量。
// 数据范围：1 <= n <= 10^5，1 <= p_i <= 10^9，
// 且所有 p_i 互不相同。
// 算法标签：线段树合并、离散化
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXT = MAXN*40;

int n,len;
int val[MAXN];
int sorted[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;

int ans[MAXN];

int root[MAXN];
int ls[MAXT];
int rs[MAXT];
int sz[MAXT];
int cnt;

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

int find(int val){
    int l=1,r=len,ans=1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sorted[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int add(int val,int l,int r,int i){
    if(i==0){
        i=++cnt;
    }
    if(l==r){
        sz[i]++;
    }
    else{
        int mid=(l+r)>>1;
        if(val<=mid){
            ls[i]=add(val,l,mid,ls[i]);
        }
        else{
            rs[i]=add(val,mid+1,r,rs[i]);
        }
        sz[i]=sz[ls[i]]+sz[rs[i]];
    }
    return i;
}

int merge(int l,int r,int v,int u){
    if(u==0||v==0){
        return u+v;
    }
    if(l==r){
        sz[u]+=sz[v];
    }
    else{
        int mid=(l+r)>>1;
        ls[u]=merge(l,mid,ls[v],ls[u]);
        rs[u]=merge(mid+1,r,rs[v],rs[u]);
        sz[u]=sz[ls[u]]+sz[rs[u]];
    }
    return u;
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl>jobr||i==0){
        return 0;
    }
    if(jobl<=l&&r<=jobr){
        return sz[i];
    }
    else{
        int ans=0;
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

void calc(int u){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        calc(v);
        root[u]=merge(1,len,root[v],root[u]);
    }
    ans[u]=query(val[u]+1,len,1,len,root[u]);
}

void prepare(){
    for(int i=1;i<=n;i++){
        sorted[i]=val[i];
    }
    sort(sorted+1,sorted+n+1);
    len=1;
    for(int i=2;i<=n;i++){
        if(sorted[i]!=sorted[i-1]){
            sorted[++len]=sorted[i];
        }
    }

    for(int i=1;i<=n;i++){
        val[i]=find(val[i]);
        root[i]=add(val[i],1,len,root[i]);
    }

    calc(1);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    for(int i=2;i<=n;i++){
        int fa;
        cin>>fa;
        addedge(fa,i);
    }

    prepare();

    for(int i=1;i<=n;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}