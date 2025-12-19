#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n,m,k;
int nums[MAXN];

int head;
int cnt;
int key[MAXN];
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
int sum[MAXN];
double priority[MAXN];

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

int newnode(int val){
    ++cnt;
    key[cnt]=val;
    sz[cnt]=1;
    priority[cnt]=(double)rand()/RAND_MAX;
    sum[cnt]=val;
    return cnt;
}

void up(int i){
    sz[i]=sz[ls[i]]+sz[rs[i]]+1;
    sum[i]=sum[ls[i]]+sum[rs[i]]+key[i];
}

int findrank(int val){
    int ans=0;
    int u=head;
    while(u){
        if(key[u]<=val){
            ans+=sz[ls[u]]+1;
            u=rs[u];
        }
        else{
            u=ls[u];
        }
    }
    return ans;
}

int merge(int l, int r) {
    if (l == 0 || r == 0) {
        return l + r;
    }
    if (priority[l] >= priority[r]) {
        rs[l] = merge(rs[l], r);
        up(l);
        return l;
    } else {
        ls[r] = merge(l, ls[r]);
        up(r);
        return r;
    }
}

void split(int l, int r, int i, int rank) {
    if (i == 0) {
        rs[l] = ls[r] = 0;
    } else {
        if (sz[ls[i]] + 1 <= rank) {
            rs[l] = i;
            split(i, r, rs[i], rank - sz[ls[i]] - 1);
        } else {
            ls[r] = i;
            split(l, i, ls[i], rank);
        }
        up(i);
    }
}

signed main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    for(int i=1;i<=m;i++){
        int rk=findrank(nums[i]-1);
        split(0,0,head,rk);
        int lm=rs[0];
        int r=ls[0];
        head=merge(merge(lm,newnode(nums[i])),r);
    }
    split(0,0,head,k);
    int lm=rs[0];
    int r=ls[0];
    cout<<sum[lm]<<' ';
    head=merge(lm,r);
    for(int i=m+1;i<=n;i++){
        int rk=findrank(nums[i-m]-1)+1;
        split(0,0,head,rk);
        int lm=rs[0];
        int r=ls[0];
        split(0,0,lm,rk-1);
        head=merge(rs[0],r);

        rk=findrank(nums[i]-1);
        split(0,0,head,rk);
        lm=rs[0];
        r=ls[0];
        head=merge(merge(lm,newnode(nums[i])),r);

        split(0,0,head,k);
        cout<<sum[rs[0]]<<' ';
        head=merge(rs[0],ls[0]);
    }
    return 0;
}