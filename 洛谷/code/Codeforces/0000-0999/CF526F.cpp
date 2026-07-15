#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

int n;
int val[MAXN];

int tree[MAXN<<2];
int cnt[MAXN<<2];
int tag[MAXN<<2];

int st1[MAXN],top1;
int st2[MAXN],top2;

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
    cnt[i]=0;
    if(tree[i]==tree[i<<1]){
        cnt[i]+=cnt[i<<1];
    }
    if(tree[i]==tree[i<<1|1]){
        cnt[i]+=cnt[i<<1|1];
    }
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]=l;
        cnt[i]=1;
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void lazy(int i,int v){
    tag[i]+=v;
    tree[i]+=v;
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

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        if(tree[i]==0){
            return cnt[i];
        }
        else{
            return 0;
        }
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

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        int x,y;
        x=read(),y=read();
        val[y]=x;
    }
    build(1,n,1);
    long long ans=0;
    for(int i=1;i<=n;i++){
        update(1,n,-1,1,n,1);

        while(top1&&val[st1[top1]]<val[i]){
            int pos=st1[top1];
            top1--;
            int lt=st1[top1]+1;
            update(lt,pos,val[i]-val[pos],1,n,1);
        }
        st1[++top1]=i;

        while(top2&&val[st2[top2]]>val[i]){
            int pos=st2[top2];
            top2--;
            int lt=st2[top2]+1;
            update(lt,pos,val[pos]-val[i],1,n,1);
        }
        st2[++top2]=i;

        ans+=query(1,i,1,n,1);
    }
    cout<<ans<<endl;
    return 0;
}