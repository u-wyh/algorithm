#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXT = MAXN*100;

int n,m;
long long ans;
int arr[MAXN];
struct node{
    int id,t,v;
};
node nums[MAXN];

bool vis[MAXN];

int fa[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int root[MAXN];
int ls[MAXT];
int rs[MAXT];
int sz[MAXT];
int cntv;

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
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

int find(int val){
    int l=1,r=m,ans=0;
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

bool cmp(node a,node b){
    return a.t>b.t;
}

void up(int x){
    sz[x]=sz[ls[x]]+sz[rs[x]];
}

int add(int val,int l,int r,int i){
    int rt=i;
    if(rt==0){
        rt=++cntv;
    }
    if(l==r){
        sz[rt]++;
    }
    else{
        int mid=(l+r)>>1;
        if(val<=mid){
            ls[rt]=add(val,l,mid,ls[rt]);
        }
        else{
            rs[rt]=add(val,mid+1,r,rs[rt]);
        }
        up(rt);
    }
    return rt;
}

int findfa(int x){
    return x==fa[x]?x:fa[x]=findfa(fa[x]);
}

int query(int jobl,int jobr,int l,int r,int i){
    if(i==0){
        return 0;
    }
    if(jobl<=l&&r<=jobr){
        return sz[i];
    }
    else{
        int mid=(l+r)>>1;
        int ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,ls[i]);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,rs[i]);
        }
        return ans;
    }
}

int merge(int l,int r,int t1,int t2){
    if(t1==0||t2==0){
        return t1+t2;
    }
    if(l==r){
        sz[t1]+=sz[t2];
    }
    else{
        int mid=(l+r)>>1;
        ls[t1]=merge(l,mid,ls[t1],ls[t2]);
        rs[t1]=merge(mid+1,r,rs[t1],rs[t2]);
        up(t1);
    }
    return t1;
}

void compute(){
    sort(arr+1,arr+n+1);
    m=1;
    for(int i=2;i<=n;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    for(int i=1;i<=n;i++){
        nums[i].v=find(nums[i].v);
        root[i]=add(nums[i].v,1,m,root[i]);
    }

    sort(nums+1,nums+n+1,cmp);

    for(int i=1;i<=n;i++){
        int u=nums[i].id;
        int val=nums[i].v;
        vis[u]=true;
        for(int ei=head[u];ei;ei=nxt[ei]){
            int v=to[ei];
            if(vis[v]){
                int fv=findfa(v);
                int fu=findfa(u);
                // int fu=u;
                if(fv!=fu){
                    fa[fv]=fu;
                    
                    int sz1=query(1,val,1,m,root[fu]);
                    int sz2=query(val,m,1,m,root[fu]);
                    int sz3=query(1,val,1,m,root[fv]);
                    int sz4=query(val,m,1,m,root[fv]);

                    ans+=1ll*sz1*sz4*u+1ll*sz2*sz3*u;
                    root[fu]=merge(1,m,root[fu],root[fv]);
                }
            }
        }
        ans+=u;
    }
}

signed main()
{
    n=read();
    for(int i=1;i<=n;i++){
        fa[i]=i;
        nums[i].id=i;
    }
    for(int i=1;i<=n;i++){
        nums[i].t=read();
    }
    for(int i=1;i<=n;i++){
        nums[i].v=read();
        arr[i]=nums[i].v;
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    compute();
    cout<<ans<<endl;
    return 0;
}