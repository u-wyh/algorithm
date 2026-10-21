// https://www.luogu.com.cn/problem/P12491
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int INF = 1e16;

int n,k;
int a[MAXN];
int b[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int sz[MAXN];
bool vis[MAXN];

int ans;

struct node{
    int a,b,col;
};
node nums[MAXN];
int cntn;

bool cmp(node &a,node &b){
    return a.a>b.a;
}

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void getSize(int u,int fa){
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa&&!vis[v]){
            getSize(v,u);
            sz[u]+=sz[v];
        }
    }
}

int getCentroid(int u,int fa){
    getSize(u,fa);
    int half=sz[u]>>1;
    bool find=false;
    while(!find){
        find=true;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v!=fa&&!vis[v]){
                if(sz[v]>half){
                    fa=u;
                    u=v;
                    find=false;
                    break;
                }
            }
        }
    }
    return u;
}

void dfs(int u,int fa,int c,int aa,int bb){
    nums[++cntn]={min(aa,a[u]),bb+b[u],c};
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa&&!vis[v]){
            dfs(v,u,c,min(aa,a[u]),bb+b[u]);
        }
    }
}

int sorted[MAXN];
int len;

int find(int x){
    int l=1,r=len,ans=len+1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sorted[mid]>=x){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int col[MAXN<<2];

void build(int l,int r,int i){
    col[i]=0;
    if(l<r){
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
    }
}

int query(int jobl,int jobr,int jobc,int l,int r,int i){
    if(col[i]==0||col[i]==jobc){
        return 0;
    }
    if(l==r){
        return l;
    }
    int mid=(l+r)>>1;
    int res=0;
    if(jobl<=mid){
        res=query(jobl,jobr,jobc,l,mid,i<<1);
    }
    if(res){
        return res;
    }
    if(jobr>mid){
        return query(jobl,jobr,jobc,mid+1,r,i<<1|1);
    }
    return 0;
}

void update(int pos,int jobc,int l,int r,int i){
    if(col[i]==0){
        col[i]=jobc;
    }
    else if(col[i]!=jobc){
        col[i]=-1;
    }
    if(l==r){
        return ;
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            update(pos,jobc,l,mid,i<<1);
        }
        else{
            update(pos,jobc,mid+1,r,i<<1|1);
        }
    }
}

void calc(int u){
    cntn=0;
    nums[++cntn]={a[u],0,u};
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]){
            dfs(v,u,v,a[u],0);
        }
    }

    for(int i=1;i<=cntn;i++){
        sorted[i]=nums[i].b;
    }
    sort(sorted+1,sorted+cntn+1);
    len=1;
    for(int i=2;i<=cntn;i++){
        if(sorted[i]!=sorted[i-1]){
            sorted[++len]=sorted[i];
        }
    }

    sort(nums+1,nums+cntn+1,cmp);

    build(1,len,1);
    for(int i=1;i<=cntn;i++){
        int x=(k + nums[i].a-1)/nums[i].a - b[u]-nums[i].b;
        x=find(x);
        if(x==len+1){
            update(find(nums[i].b),nums[i].col,1,len,1);
            continue;
        }
        int res=query(x,len,nums[i].col,1,len,1);
        if(res){
            ans=min(ans,sorted[res]+b[u]+nums[i].b);
        }
        update(find(nums[i].b),nums[i].col,1,len,1);
    }
}

void solve(int u){
    calc(u);
    vis[u]=true;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]){
            solve(getCentroid(v,u));
        }
    }
}

signed main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }

    ans=INF;
    solve(getCentroid(1,0));

    for(int i=1;i<=n;i++){
        if((k+a[i]-1)/a[i]<=b[i]){
            ans=min(ans,b[i]);
        }
    }
    cout<<ans<<endl;
    return 0;
}