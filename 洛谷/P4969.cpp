#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n,m,talent;
int arr[MAXN];
int tree[MAXN<<2];

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

inline void up(int i){
    tree[i]=tree[i<<1]+tree[i<<1|1];
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]=arr[l]<=talent?1:0;
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
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

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int ans=0;
        int mid=(l+r)/2;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,i<<1);
        }
        else{
            ans+=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        return ans;
    }
}

signed main()
{
    n=read(),talent=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
    build(1,n,1);
    m=read();
    for(int i=1;i<=m;i++){
        string op;
        int u,v;
        cin>>op;
        u=read(),v=read();
        if(op=="BookCity"){
            if(arr[u]-v<=0){
                if(arr[u]>talent){
                    update(u,1,1,n,1);
                }
                arr[u]=1;
            }
            else if(arr[u]>talent&&arr[u]-v<=talent){
                update(u,1,1,n,1);
                arr[u]-=v;
            }
            else if(arr[u]>talent&&arr[u]-v>talent){
                arr[u]-=v;
            }
            else{
                arr[u]-=v;
            }
        }
        else if(op=="Guy"){
            if(arr[u]<=talent){
                if(arr[u]*v>talent){
                    update(u,0,1,n,1);
                }
                arr[u]*=v;
            }
            else{
                arr[u]*=v;
            }
        }
        else if(op=="tingtime"){
            if(arr[u]>talent){
                if(v<=talent){
                    update(u,1,1,n,1);
                }
                arr[u]=v;
            }
            else{
                if(v>talent){
                    update(u,0,1,n,1);
                }
                arr[u]=v;
            }
        }
        else{
            if(u>v)
                swap(u,v);
            cout<<query(u,v,1,n,1)*600<<endl;
        }
    }
    return 0;
}
