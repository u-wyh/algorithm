// https://codeforces.com/problemset/problem/981/E
// 题意：给长为 n 的全 0 数组，以及 q 条区间加法。
// 操作 (l_i, r_i, x_i) 把区间每项加 x_i。
// 每条操作可任选执行一次，或跳过。
// 输出：输出数组最大值在 [1, n] 内的可能取值个数，
// 再按升序输出所有这些取值。
// 数据范围：1 <= n, q <= 10^4，
// 1 <= l_i <= r_i <= n，1 <= x_i <= n。
// 算法标签：线段树分治、位集背包
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;
const int MAXT = 5e5+5;
const int BIT = 1e4;
const int MAXH = 20;

int n,q;

int head[MAXN<<2];
int nxt[MAXT];
int to[MAXT];
int cnt=1;

bitset<BIT+1>dp;
bitset<BIT+1>backup[MAXH];
bitset<BIT+1>ans;

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

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        addedge(i,jobv);
    }
    else{
        int mid=(l+r)>>1;
        if(jobl<=mid){
            add(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
    }
}

void dfs(int l,int r,int i,int d){
    backup[d]=dp;
    for(int ei=head[i];ei;ei=nxt[ei]){
        int v=to[ei];
        dp|=(dp<<v);
    }
    if(l==r){
        ans|=dp;
    }
    else{
        int mid=(l+r)>>1;
        dfs(l,mid,i<<1,d+1);
        dfs(mid+1,r,i<<1|1,d+1);
    }
    dp=backup[d];
}

int main()
{
    n=read(),q=read();
    for(int i=1;i<=q;i++){
        int l,r,k;
        l=read(),r=read(),k=read();
        add(l,r,k,1,n,1);
    }
    dp.set(0);
    dfs(1,n,1,1);
    int ansCnt = 0;
    for (int i = 1; i <= n; i++) {
        if (ans[i] == 1) {
            ansCnt++;
        }
    }
    cout << ansCnt << '\n';
    for (int i = 1; i <= n; i++) {
        if (ans[i] == 1) {
            cout << i << ' ';
        }
    }
    cout << '\n';
    return 0;
}