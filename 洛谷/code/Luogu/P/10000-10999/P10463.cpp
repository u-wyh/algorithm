#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;

int n,m;
int tree[MAXN<<2];
int sum[MAXN<<2];
int arr[MAXN];

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

int gcd(int a, int b) {
    return b == 0 ? abs(a) : gcd(b, a % b);
}

void up(int i){
    tree[i]=gcd(tree[i<<1],tree[i<<1|1]);
    sum[i]=sum[i<<1]+sum[i<<1|1];
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]=sum[i]=arr[l]-arr[l-1];
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void add(int pos,int val,int l,int r,int i){
    if(l==r){
        tree[i]+=val;
        sum[i]+=val;
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            add(pos,val,l,mid,i<<1);
        }
        else{
            add(pos,val,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int querysum(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return sum[i];
    }
    else{
        int ans=0;
        int mid=(l+r)/2;
        if(jobl<=mid){
            ans+=querysum(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=querysum(jobl,jobr,mid+1,r,i<<1|1);
        }
        return ans;
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)/2;
        if(jobl<=mid&&jobr>mid){
            return gcd(query(jobl,jobr,l,mid,i<<1),query(jobl,jobr,mid+1,r,i<<1|1));
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
    build(1,n,1);
    for(int i=1;i<=m;i++){
        char op;
        int u,v,w;
        cin>>op;
        u=read(),v=read();
        if(op=='C'){
            w=read();
            add(u,w,1,n,1);
            if(v!=n){
                add(v+1,-w,1,n,1);
            }
        }
        else{
            if(u+1<=v)
                cout<<gcd(querysum(1,u,1,n,1),query(u+1,v,1,n,1))<<endl;
            else {
                cout<<querysum(1,u,1,n,1)<<endl;
            }
        }
    }
    return 0;
}
