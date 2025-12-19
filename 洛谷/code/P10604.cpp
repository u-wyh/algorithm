#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e4+5;
const int MAXT = MAXN*50;
const int MAXH = 18;

int n,k,sumw;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cntg=1;

int dep[MAXN];
int dist[MAXN];
int st[MAXN][MAXH];

bool vis[MAXN];
int sz[MAXN];
int centfa[MAXN];

int addroot[MAXN];
int minusroot[MAXN];
int ls[MAXT];
int rs[MAXT];
int tree[MAXT];
int cntt;

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

inline void addedge(int u,int v,int w){
    nxt[cntg]=head[u];
    to[cntg]=v;
    weight[cntg]=w;
    head[u]=cntg++;
}

void dfs(int u,int fa,int dis){
    dep[u]=dep[fa]+1;
    dist[u]=dis;
    st[u][0]=fa;
    for(int p=1;p<MAXH;p++){
        st[u][p]=st[st[u][p-1]][p-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=fa){
            dfs(v,u,dis+w);
        }
    }
}

int getlca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int p=MAXH-1;p>=0;p--){
        if(dep[st[a][p]]>=dep[b]){
            a=st[a][p];
        }
    }
    if(a==b){
        return a;
    }
    for(int p=MAXH-1;p>=0;p--){
        if(st[a][p]!=st[b][p]){
            a=st[a][p];
            b=st[b][p];
        }
    }
    return st[a][0];
}

int getdist(int a,int b){
    return dist[a]+dist[b]-(dist[getlca(a,b)]<<1);
}

void getsize(int u,int fa){
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa&&!vis[v]){
            getsize(v,u);
            sz[u]+=sz[v];
        }
    }
}

int getcentroid(int u,int fa){
    getsize(u,fa);
    int half=sz[u]>>1;
    bool find=false;
    while(!find){
        find=true;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v!=fa&&!vis[v]&&sz[v]>half){
                find=false;
                fa=u;
                u=v;
                break;
            }
        }
    }
    return u;
}

void centroidtree(int u,int fa){
    centfa[u]=fa;
    vis[u]=true;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]){
            centroidtree(getcentroid(v,u),u);
        }
    }
}

int add(int pos,int jobv,int l,int r,int i){
    if(i==0){
        i=++cntt;
    }
    if(l==r){
        tree[i]+=jobv;
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            ls[i]=add(pos,jobv,l,mid,ls[i]);
        }
        else{
            rs[i]=add(pos,jobv,mid+1,r,rs[i]);
        }
        tree[i]=tree[ls[i]]+tree[rs[i]];
    }
    return i;
}

int query(int jobl,int jobr,int l,int r,int i){
    if(i==0){
        return 0;
    }
    if(jobl<=l&&r<=jobr){
        return tree[i];
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

void add(int x,int v){
    addroot[x]=add(0,v,0,sumw,addroot[x]);
    for(int cur=x,fa=centfa[cur];fa;cur=fa,fa=centfa[cur]){
        int dist=getdist(x,fa);
        addroot[fa]=add(dist,v,0,sumw,addroot[fa]);
        minusroot[cur]=add(dist,v,0,sumw,minusroot[cur]);
    }
}

int query(int x,int k){
    int ans=query(0,k,0,sumw,addroot[x]);
    for(int cur=x,fa=centfa[cur];fa;cur=fa,fa=centfa[cur]){
        int dist=getdist(x,fa);
        if(k>=dist){
            ans+=query(0,k-dist,0,sumw,addroot[fa]);
            ans-=query(0,k-dist,0,sumw,minusroot[cur]);
        }
    }
    return ans;
}

int compute(int x){
    int ans=0;
    int l=0,r=sumw;
    while(l<=r){
        int mid=(l+r)>>1;
        if(query(x,mid)>=k){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int main()
{
    n=read(),k=read()+1;
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
        sumw+=w;
    }
    dfs(1,0,0);
    centroidtree(getcentroid(1,0),0);
    for(int i=1;i<=n;i++){
        add(i,1);
    }
    for(int i=1;i<=n;i++){
        cout<<compute(i)<<endl;
    }
    return 0;
}