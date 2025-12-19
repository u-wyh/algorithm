#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXT = MAXN*40;
const int INF = 1e9;

int n,m;

int cnt;
int root[MAXN];
int ls[MAXT];
int rs[MAXT];
int tree[MAXT];

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

int insert(int val,int l,int r,int i){
    int rt=++cnt;
    ls[rt]=ls[i];
    rs[rt]=rs[i];
    tree[rt]=tree[i]+val;
    if(l<r){
        int mid=(l+r)>>1;
        if(val<=mid){
            ls[rt]=insert(val,l,mid,ls[rt]);
        }
        else{
            rs[rt]=insert(val,mid+1,r,rs[rt]);
        }
    }
    return rt;
}

int query(int jobl,int jobr,int l,int r,int u,int v){
    if(jobl<=l&&r<=jobr){
        return tree[u]-tree[v];
    }
    else{
        int mid=(l+r)>>1;
        int ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,ls[u],ls[v]);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,rs[u],rs[v]);
        }
        return ans;
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        int val=read();
        root[i]=insert(val,1,INF,root[i-1]);
    }
    m=read();
    while(m--){
        int l,r;
        l=read(),r=read();
        int ans=1;
        while(true){
            int res=query(1,ans,1,INF,root[r],root[l-1]);
            if(res>=ans){
                ans=res+1;
            }
            else{
                break;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}