#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;

struct node{
    int l,r,all,sum;
}tree[MAXN<<2];
int n,m;
int arr[MAXN];
int val[MAXN];
int pre[MAXN];
int last[MAXN];

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

node up(node l,node r){
    node u;
    u.all=max(max(l.all,r.all),l.r+r.l);
    u.sum=l.sum+r.sum;
    u.l=max(l.l,l.sum+r.l);
    u.r=max(r.r,r.sum+l.r);
    return u;
}

void build(int l,int r,int i){
    if(l==r){
        tree[i].l=tree[i].r=tree[i].all=tree[i].sum=0;
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        tree[i]=up(tree[i<<1],tree[i<<1|1]);
    }
}

void update(int pos,int jobv,int l,int r,int i){
    if(l==r){
        tree[i].l=tree[i].r=tree[i].all=tree[i].sum=jobv;
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            update(pos,jobv,l,mid,i<<1);
        }
        else{
            update(pos,jobv,mid+1,r,i<<1|1);
        }
        tree[i]=up(tree[i<<1],tree[i<<1|1]);
    }
}

node query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)/2;
        if(jobl<=mid&&jobr>mid){
            return up(query(jobl,jobr,l,mid,i<<1),query(jobl,jobr,mid+1,r,i<<1|1));
        }
        else if(jobl<=mid){
            return query(jobl,jobr,l,mid,i<<1);
        }
        else{
            return query(jobl,jobr,mid+1,r,i<<1|1);
        }
    }
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
    for(int i=1;i<=m;i++){
        val[i]=read();
    }
    //build(1,n,1);
    int ans=0;
    for(int i=1;i<=n;i++){
        if(last[arr[i]]==0){
            //说明第一次出现  不用变化
            update(i,val[arr[i]],1,n,1);
            last[arr[i]]=i;
        }
        else if(pre[arr[i]]==0){
            //第二次出现
            update(last[arr[i]],-val[arr[i]],1,n,1);
            update(i,val[arr[i]],1,n,1);
            pre[arr[i]]=last[arr[i]];
            last[arr[i]]=i;
        }
        else{
            update(pre[arr[i]],0,1,n,1);
            update(last[arr[i]],-val[arr[i]],1,n,1);
            update(i,val[arr[i]],1,n,1);
            pre[arr[i]]=last[arr[i]];
            last[arr[i]]=i;
        }
        ans=max(ans,query(1,i,1,n,1).all);
    }
    cout<<ans<<endl;
    return 0;
}

