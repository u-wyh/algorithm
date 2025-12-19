#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n;
int val[MAXN];
int pre[MAXN];
int pos[MAXN];

// 到目前扫描到的r为止  这个位置上的数字是否是唯一的（从该位置到r）
int one[MAXN<<2];
// 表示到目前扫描到的r为止  如果这个位置作为左边界  那么有多少个位置可以充当右边界
int middle[MAXN<<2];
int tree[MAXN<<2];
int tag[MAXN<<2];

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

void lazy(int i,int v){
    tag[i]+=v;
    middle[i]+=v;
    tree[i]+=one[i]*v;
}

void down(int i){
    if(tag[i]){
        lazy(i<<1,tag[i]);
        lazy(i<<1|1,tag[i]);
        tag[i]=0;
    }
}

void up(int i){
    tree[i]=tree[i<<1]+tree[i<<1|1];
    one[i]=one[i<<1]+one[i<<1|1];
}

void change(int pos,int jobv,int l,int r,int i){
    if(l==r){
        one[i]+=jobv;
        tree[i]=one[i]*middle[i];
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(pos<=mid){
            change(pos,jobv,l,mid,i<<1);
        }
        else{
            change(pos,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl>jobr){
        return ;
    }
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
    if(jobl>jobr){
        return 0;
    }
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        int ans=0;
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
    n=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
        pre[i]=pos[val[i]];
        pos[val[i]]=i;
    }

    int ans=0;
    for(int i=1;i<=n;i++){
        if(pre[i]){
            change(pre[i],-1,1,n,1);
            add(pre[pre[i]]+1,pre[i]-1,-1,1,n,1);
        }
        ans+=query(pre[i]+1,i-2,1,n,1);
        change(i,1,1,n,1);
        add(pre[i]+1,i-1,1,1,n,1);
    }
    cout<<ans<<endl;
    return 0;
}