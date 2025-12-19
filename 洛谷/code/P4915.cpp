#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXM = 4e5+5;

int n,q,m;
int a[MAXN];
int b[MAXN];

int op[MAXN];
int x[MAXN];
int y[MAXN];

int sorted[MAXM];
int val[MAXM];

int tree[MAXM<<2];
int tag[MAXM<<2];
int len[MAXM<<2];

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

int find(int val){
    int l=1,r=m,ans=1;
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

void up(int i){
    tree[i]=tree[i<<1]+tree[i<<1|1];
}

void build(int l,int r,int i){
    if(l==r){
        len[i]=sorted[l+1]-sorted[l];
        tree[i]=val[l]*len[i];
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        len[i]=len[i<<1]+len[i<<1|1];
        up(i);
    }
}

void prepare(){
    int len=0;
    for(int i=1;i<=n;i++){
        sorted[++len]=a[i];
    }
    for(int i=1;i<=q;i++){
        if(op[i]==1){
            sorted[++len]=x[i];
            sorted[++len]=y[i];
            sorted[++len]=y[i]+1;
        }
        else{
            sorted[++len]=x[i];
        }
    }
    sort(sorted+1,sorted+len+1);
    sorted[1+len]=sorted[len]+1;
    len++;
    m=1;
    for(int i=2;i<=len;i++){
        if(sorted[i]!=sorted[i-1]){
            sorted[++m]=sorted[i];
        }
    }
    m--;
    for(int i=1;i<=n;i++){
        a[i]=find(a[i]);
    }
    for(int i=1;i<=q;i++){
        if(op[i]==1){
            x[i]=find(x[i]);
            y[i]=find(y[i]);
        }
        else{
            x[i]=find(x[i]);
        }
        // cout<<' '<<op[i]<<' '<<x[i]<<' '<<y[i]<<endl;
    }
    for(int i=1;i<=n;i++){
        val[a[i]]+=b[i];
    }
    for(int i=1;i<=m;i++){
        val[i]+=val[i-1];
        // cout<<i<<":   "<<sorted[i]<<' '<<val[i]<<endl;
    }
    build(1,m,1);
}

void lazy(int i,int val){
    tag[i]+=val;
    tree[i]+=len[i]*val;
}

void down(int i){
    if(tag[i]){
        lazy(i<<1,tag[i]);
        lazy(i<<1|1,tag[i]);
        tag[i]=0;
    }
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,jobv);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            add(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;
        int ans=0;
        down(i);
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
    n=read(),q=read();
    for(int i=1;i<=n;i++){
        a[i]=read(),b[i]=read();
    }
    for(int i=1;i<=q;i++){
        op[i]=read(),x[i]=read(),y[i]=read();
    }
    prepare();
    for(int i=1;i<=q;i++){
        if(op[i]==1){
            int len=sorted[y[i]]-sorted[x[i]]+1;
            int all=query(x[i],y[i],1,m,1);
            // cout<<i<<":        "<<all<<' '<<len<<endl;
            printf("%.4lf\n",1.0*all/len);
        }
        else{
            add(x[i],m,y[i],1,m,1);
        }
    }
    return 0;
}
/*
2 2
1 3
5 2
1 3 3
1 3 5
*/