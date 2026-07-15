#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXT = MAXN*20;

int n,m;
int val[MAXN];
int arr[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;

int root[MAXN];
int ls[MAXT];
int rs[MAXT];
int maxv[MAXT];
int tag[MAXT];
int cnt;

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

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

int find(int val){
    int l=1,r=m,ans=1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(arr[mid]>=val){
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
    maxv[i]=max(maxv[ls[i]],maxv[rs[i]]);
}

void lazy(int i,int v){
    if(i!=0){
        maxv[i]+=v;
        tag[i]+=v;
    }
}

void down(int i){
    if(tag[i]){
        lazy(ls[i],tag[i]);
        lazy(rs[i],tag[i]);
        tag[i]=0;
    }
}

int update(int pos,int jobv,int l,int r,int i){
    int rt=i;
    if(rt==0){
        rt=++cnt;
    }
    if(l==r){
        maxv[rt]=max(maxv[rt],jobv);
    }
    else{
        int mid=(l+r)>>1;
        down(rt);
        if(pos<=mid){
            ls[rt]=update(pos,jobv,l,mid,ls[rt]);
        }
        else{
            rs[rt]=update(pos,jobv,mid+1,r,rs[rt]);
        }
        up(rt);
    }
    return rt;
}

int query(int jobl,int jobr,int l,int r,int i){
    if(i==0){
        return 0;
    }
    if(jobl<=l&&r<=jobr){
        return maxv[i];
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        int ans=0;
        if(jobl<=mid){
            ans=max(ans,query(jobl,jobr,l,mid,ls[i]));
        }
        if(jobr>mid){
            ans=max(ans,query(jobl,jobr,mid+1,r,rs[i]));
        }
        return ans;
    }
}

int merge(int l,int r,int t1,int t2,int max1,int max2){
    if(t1==0||t2==0){
        if(t1!=0){
            lazy(t1,max2);
        }
        if(t2!=0){
            lazy(t2,max1);
        }
        return t1+t2;
    }
    if(l==r){
        maxv[t1]+=max(max2,maxv[t2]);
    }
    else{
        down(t1);
        down(t2);
        int mid=(l+r)>>1;
        ls[t1]=merge(l,mid,ls[t1],ls[t2],max(max1,maxv[rs[t1]]),max(max2,maxv[rs[t2]]));
        rs[t1]=merge(mid+1,r,rs[t1],rs[t2],max1,max2);
        up(t1);
    }
    return t1;
}

void dfs(int u){
    int sum=0;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v);
        sum+=query(val[u],m,1,m,root[v]);
        root[u]=merge(1,m,root[u],root[v],0,0);
    }
    root[u]=update(val[u],sum+1,1,m,root[u]);
}

void prepare(){
    for(int i=1;i<=n;i++){
        arr[i]=val[i];
    }
    sort(arr+1,arr+n+1);
    m=1;
    for(int i=2;i<=n;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    for(int i=1;i<=n;i++){
        val[i]=find(val[i]);
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=2;i<=n;i++){
        int fa=read();
        addedge(fa,i);
    }
    prepare();
    dfs(1);
    cout<<query(1,m,1,m,root[1]);
    return 0;
}