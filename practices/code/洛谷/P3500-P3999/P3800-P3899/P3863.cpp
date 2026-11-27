// https://www.luogu.com.cn/problem/P3863
// 题意：第一行输入序列长度 n 和操作数 q，
// 第二行输入初始序列 a_1..a_n。
// 第 i 个操作发生在第 i 秒（初始为第 0 秒）：
// 1 l r x 将区间 [l, r] 元素加上 x；
// 2 p y 查询 a_p 在过去的 0..i-1 秒中有多少秒满足值不小于 y。
// 对每个操作 2 输出一行一个整数表示答案。
// 数据范围：对于 100% 的数据，2 <= n, q <= 100000，
// 1 <= l <= r <= n，1 <= p <= n
// -10^9 <= x, y, a_i <= 10^9。
// 算法标签：分块、扫描线、二分查找
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXM = 1e3+5;

int n,m;
int arr[MAXN];

struct node{
    int op,pos,t,val,id;
};
node event[MAXN<<2];
int cntq,cnte;

int blen,bnum;
int bl[MAXM];
int br[MAXM];
int bi[MAXN];
int lazy[MAXN];

int nums[MAXN];
int sorted[MAXN];

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

bool cmp(node a,node b){
    return (a.pos!=b.pos)?(a.pos<b.pos):(a.t<b.t);
}

void addchange(int pos,int t,int val){
    event[++cntq]={1,pos,t,val,0};
}

void addquery(int pos,int t,int val){
    event[++cntq]={2,pos,t,val,++cnte};
}

void inneradd(int l,int r,int v){
    for(int i=l;i<=r;i++){
        nums[i]+=v;
    }
    for(int i=bl[bi[l]];i<=br[bi[l]];i++){
        sorted[i]=nums[i];
    }
    sort(sorted+bl[bi[l]],sorted+br[bi[l]]+1);
}

void add(int l,int r,int v){
    int lb=bi[l],rb=bi[r];
    if(lb==rb){
        inneradd(l,r,v);
    }
    else{
        inneradd(l,br[bi[l]],v);
        inneradd(bl[bi[r]],r,v);
        for(int i=lb+1;i<=rb-1;i++){
            lazy[i]+=v;
        }
    }
}

int innerquery(int l,int r,int v){
    v-=lazy[bi[l]];
    int ans=0;
    for(int i=l;i<=r;i++){
        if(nums[i]>=v){
            ans++;
        }
    }
    return ans;
}

int getcnt(int i,int v){
    v-=lazy[i];
    int l=bl[i],r=br[i],ans=br[i]+1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sorted[mid]>=v){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return br[i]-ans+1;
}

int query(int l,int r,int v){
    int lb=bi[l],rb=bi[r],ans=0;
    if(lb==rb){
        ans=innerquery(l,r,v);
    }
    else{
        ans+=innerquery(l,br[bi[l]],v);
        ans+=innerquery(bl[bi[r]],r,v);
        for(int i=lb+1;i<=rb-1;i++){
            ans+=getcnt(i,v);
        }
    }
    return ans;
}

void prepare(){
    blen=sqrt(m);
    bnum=(m+blen-1)/blen;
    for(int i=1;i<=m;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(m,i*blen);
    }
    sort(event+1,event+cntq+1,cmp);
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
    m++;
    for(int t=2;t<=m;t++){
        int op,pos,val,l,r;
        op=read();
        if(op==1){
            l=read(),r=read(),val=read();
            addchange(l,t,val);
            addchange(r+1,t,-val);
        }
        else{
            pos=read(),val=read();
            addquery(pos,t,val);
        }
    }
    prepare();
    for(int i=1;i<=cntq;i++){
        if(event[i].op==1){
            add(event[i].t,m,event[i].val);
        }
        else{
            ans[event[i].id]=query(1,event[i].t-1,event[i].val-arr[event[i].pos]);
        }
    }
    for(int i=1;i<=cnte;i++){
        printf("%lld\n",ans[i]);
    }
    return 0;
}