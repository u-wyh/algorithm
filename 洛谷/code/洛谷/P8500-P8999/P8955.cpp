// https://www.luogu.com.cn/problem/P8955
// 题意：给定长为 N 的序列 a 和常数 P（初始 P >= max{a_i}），
// 进行 Q 次操作，每次给定 l_i, r_i, v_i
// 将区间 [l_i, r_i] 内每个 a_j 赋值为 a_j | v_i。
// 对每个位置 i 输出在哪次操作后 a_i 首次严格大于 P，
// 若始终 <= P 则输出 -1。
// 数据范围：1 <= N, Q <= 10^6，
// 1 <= l_i <= r_i <= N，
// 1 <= a_i, v_i, P <= 10^9
// 初始 P >= max{a_i}。
// 算法标签：线段树、线段树上二分、扫描线
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n,q,p;
int nums[MAXN];

int tree[MAXN<<2];

int head[MAXN];
int nxt[MAXN<<2];
int to[MAXN<<2];
int val[MAXN<<2];
int cnt=1;

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

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    val[cnt]=w;
    head[u]=cnt++;
}

void up(int i){
    tree[i]=(tree[i<<1]|tree[i<<1|1]);
}

void update(int pos,int jobv,int l,int r,int i){
    if(l==r){
        tree[i]=jobv;
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            update(pos,jobv,l,mid,i<<1);
        }
        else{
            update(pos,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int val,int l,int r,int i){
    if(l==r){
        return l;
    }
    else{
        int mid=(l+r)/2;
        if((val|tree[i<<1])>p){
            return query(val,l,mid,i<<1);
        }
        else{
            return query(val|tree[i<<1],mid+1,r,i<<1|1);
        }
    }
}

int main()
{
    n=read(),q=read(),p=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    for(int i=1;i<=q;i++){
        int l,r,v;
        l=read(),r=read(),v=read();
        addedge(l,i,v);
        addedge(r+1,i,0);
    }
    for(int i=1;i<=n;i++){
        for(int j=head[i];j;j=nxt[j]){
            update(to[j],val[j],1,q,1);
        }
        if((nums[i]|tree[1])<=p){
            printf("-1 ");
            continue;
        }
        printf("%d ",query(nums[i],1,q,1));
    }
    return 0;
}