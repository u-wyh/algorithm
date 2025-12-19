#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,m;

int red[MAXN];
int blue[MAXN];

int sorted[MAXN];

int dfncnt;
int dfn[MAXN];
int sz[MAXN];

int ans[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int tree[MAXN];

struct node{
    int i,lt,rt,r,b;
};
node nums[MAXN];

bool cmp1(node a,node b){
    if(a.r!=b.r){
        return a.r<b.r;
    }
    if(a.b!=b.b){
        return a.b<b.b;
    }
    return a.lt>b.lt;
}

bool cmp2(node a,node b){
    if(a.b!=b.b){
        return a.b<b.b;
    }
    return a.lt>b.lt;
}

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int v){
    while(x<=n){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

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

void dfs(int u,int fa){
    dfn[u]=++dfncnt;
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs(v,u);
            sz[u]+=sz[v];
        }
    }
}

void prepare(){
    for(int i=1;i<=n;i++){
        sorted[i]=red[i];
    }
    sort(sorted+1,sorted+n+1);
    m=1;
    for(int i=2;i<=n;i++){
        if(sorted[i]!=sorted[i-1]){
            sorted[++m]=sorted[i];
        }
    }
    for(int i=1;i<=n;i++){
        red[i]=find(red[i]);
    }

    for(int i=1;i<=n;i++){
        sorted[i]=blue[i];
    }
    sort(sorted+1,sorted+n+1);
    m=1;
    for(int i=2;i<=n;i++){
        if(sorted[i]!=sorted[i-1]){
            sorted[++m]=sorted[i];
        }
    }
    for(int i=1;i<=n;i++){
        blue[i]=find(blue[i]);
    }

    dfs(1,0);

    for(int i=1;i<=n;i++){
        nums[i]={i,dfn[i],dfn[i]+sz[i]-1,red[i],blue[i]};
    }
    sort(nums+1,nums+n+1,cmp1);
}

void merge(int l,int m,int r){
    int p1,p2;
    for(p1=l-1,p2=m+1;p2<=r;p2++){
        while(p1+1<=m&&nums[p1+1].b<=nums[p2].b){
            p1++;
            add(nums[p1].lt,1);
        }
        ans[nums[p2].i]+=query(nums[p2].rt)-query(nums[p2].lt-1);
    }
    for(int i=l;i<=p1;i++){
        add(nums[i].lt,-1);
    }
    sort(nums+l,nums+r+1,cmp2);
}

void cdq(int l,int r){
    if(l==r){
        return ;
    }
    int mid=(l+r)>>1;
    cdq(l,mid);
    cdq(mid+1,r);
    merge(l,mid,r);
}

int main()
{
    n=read();
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=1;i<=n;i++){
        red[i]=read(),blue[i]=read();
    }
    prepare();
    cdq(1,n);
    for(int i=1;i<=n;i++){
        if(ans[i]){
            // cout<<i<<":  ";
            printf("%d\n",ans[i]);
        }
    }
    return 0;
}