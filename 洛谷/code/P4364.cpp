// https://www.luogu.com.cn/problem/P4364
// 题意：将给定的 n 个难度值重新排列为 d_1..d_n
// 满足每个 i 都有 d_i >= d_{floor(i/k)}（floor(i/k)=0 时无限制）
// 求字典序最大（依次优先 d_1, d_2, ... 最大）的序列。
// 数据范围：1 <= n <= 500000，1 < k <= 10^9（小数），1 <= d_i <= 10^9（可能有重复值）。
#include<bits/stdc++.h>
// 算法标签：贪心、线段树、二分查找
using namespace std;
const int MAXN = 5e5+5;

int n;
double k;
int val[MAXN];
int cnt[MAXN];
int sz[MAXN];
int fa[MAXN];

int tree[MAXN<<2];
int tag[MAXN<<2];

int ans[MAXN];

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

void up(int i){
    tree[i]=min(tree[i<<1],tree[i<<1|1]);
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]=l;
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void lazy(int i,int v){
    tree[i]+=v;
    tag[i]+=v;
}

void down(int i){
    if(tag[i]){
        lazy(i<<1,tag[i]);
        lazy(i<<1|1,tag[i]);
        tag[i]=0;
    }
}

void update(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,jobv);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            update(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            update(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int find(int jobv,int l,int r,int i){
    if(l==r){
        return l+(tree[i]<jobv);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(tree[i<<1|1]>=jobv){
            return find(jobv,l,mid,i<<1);
        }
        else{
            return find(jobv,mid+1,r,i<<1|1);
        }
    }
}

bool cmp(int a,int b){
    return a>b;
}

int main()
{
    scanf("%d %lf",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%d",&val[i]);
    }
    sort(val+1,val+n+1,cmp);
    for(int i=n-1;i>=1;i--){
        if(val[i]==val[i+1]){
            cnt[i]=cnt[i+1]+1;
        }
        else{
            cnt[i]=0;
        }
    }
    for(int i=1;i<=n;i++){
        sz[i]=1;
        fa[i]=i/k;
    }
    for(int i=n;i>=1;i--){
        sz[fa[i]]+=sz[i];
    }
    build(1,n,1);
    for(int i=1;i<=n;i++){
        if(fa[i]!=fa[i-1]){
            update(ans[fa[i]],n,sz[fa[i]]-1,1,n,1);
        }
        int pos=find(sz[i],1,n,1);
        pos+=cnt[pos];
        ans[i]=pos;
        update(pos,n,-sz[i],1,n,1);
    }

    for(int i=1;i<=n;i++){
        printf("%d ",val[ans[i]]);
    }
    return 0;
}