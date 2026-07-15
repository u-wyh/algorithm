#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int n,m;

int val[MAXN];
long long tree[MAXN<<2];
bool tag[MAXN<<2];

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
    tree[i]=tree[i<<1]+tree[i<<1|1];
    tag[i]=(tag[i<<1]&tag[i<<1|1]);
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]=val[l];
        tag[i]=(val[l]==1)?true:false;
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void update(int jobl,int jobr,int l,int r,int i){
    if(tag[i]){
        return ;
    }
    if(l==r){
        tree[i]=sqrt(tree[i]);
        tag[i]=(tree[i]==1)?true:false;
    }
    else{
        int mid=(l+r)/2;
        if(jobl<=mid){
            update(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            update(jobl,jobr,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

long long query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)/2;
        long long ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        return ans;
    }
}

signed main()
{
    int now=0;
    while(scanf("%d",&n)==1){
        now++;
        printf("Case #%d:",now);
        for(int i=1;i<=n;i++){
            val[i]=read();
        }
        m=read();
        build(1,n,1);
        for(int i=1;i<=m;i++){
            int op,l,r;
            op=read(),l=read(),r=read();
            if(op==0){
                update(l,r,1,n,1);
            }
            else{
                printf("%lld\n",query(l,r,1,n,1));
            }
        }
        printf("\n");
    }
    return 0;
}