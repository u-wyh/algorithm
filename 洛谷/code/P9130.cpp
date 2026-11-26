// https://www.luogu.com.cn/problem/P9130
// 题意：Bessie 每天晚餐若谷仓有干草就吃 1 捆，第 d_i 天早晨会收到 b_i 捆干草。
// 初始无干草，处理 U 次更新：将第 d 天早晨到达的干草数设为 b。
// 每次更新后输出 Bessie 有干草吃的「所有天数编号之和」，对 10^9+7 取模。
// 数据范围：1 <= U <= 10^5，1 <= d_i <= 10^14，0 <= b_i <= 10^9。
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MAXN = 1e5+5;
const int MOD = 1e9+7;
const int INV2 = (MOD+1)/2;

int n,m;
int x[MAXN];
int y[MAXN];
int t[MAXN];

int out[MAXN<<2];
int tree[MAXN<<2];
int ans[MAXN<<2];
int lson[MAXN<<2];

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

int find(int x){
    int l=1,r=m,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(t[mid]>=x){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

inline int fun(int l,int r){
    return ((((r-l+1)%MOD)*((l+r)%MOD))%MOD*INV2)%MOD;
}

pair<int,int>query(int l,int r,int v,int i){
    if(l==r){
        return {t[l]+tree[i]+v-1,ans[i]};
    }
    else{
        int mid=(l+r)>>1;
        if(v<=(t[mid+1]-t[l]-tree[i<<1])){
            return query(l,mid,v,i<<1);
        }
        else{
            pair<int,int>tmp=query(mid+1,r,v-(t[mid+1]-t[l]-tree[i<<1])+out[i<<1],i<<1|1);
            tmp.second+=ans[i<<1]+lson[i];
            return tmp;
        }
    }
}

void up(int i,int l,int r){
    int mid=(l+r)>>1;
    int lt=out[i<<1];
    int rt=t[r+1]-t[mid+1]-tree[i<<1|1];
    if(rt<lt){
        out[i]=out[i<<1|1]+lt-rt;
        ans[i]=ans[i<<1]+fun(t[mid+1],t[r+1]-1);
        tree[i]=tree[i<<1]+t[r+1]-t[mid+1];
        lson[i]=0;
    }
    else{
        out[i]=out[i<<1|1];
        tree[i]=tree[i<<1]+tree[i<<1|1]+lt;
        lson[i]=0;
        if(lt){
            pair<int,int>tmp=query(mid+1,r,lt,i<<1|1);
            lson[i]=((fun(t[mid+1],tmp.first)-tmp.second)%MOD+MOD)%MOD;
        }
        ans[i]=ans[i<<1]+ans[i<<1|1]+lson[i];
    }
}

void update(int pos,int jobv,int l,int r,int i){
    if(l==r){
        tree[i]=min(jobv,t[l+1]-t[l]);
        ans[i]=fun(t[l],t[l]+tree[i]-1);
        out[i]=jobv-tree[i];
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            update(pos,jobv,l,mid,i<<1);
        }
        else{
            update(pos,jobv,mid+1,r,i<<1|1);
        }
        up(i,l,r);
    }
}

signed main()
{
    n=read();
    for(int i=1;i<=n;i++){
        x[i]=read(),y[i]=read();
        t[i]=x[i];
    }
    sort(t+1,t+n+1);
    m=1;
    for(int i=2;i<=n;i++){
        if(t[i]!=t[i-1]){
            t[++m]=t[i];
        }
    }
    t[m+1]=1e18;
    for(int i=1;i<=n;i++){
        int pos=find(x[i]);
        update(pos,y[i],1,m,1);
        printf("%lld\n",(ans[1]%MOD+MOD)%MOD);
    }
    return 0;
}