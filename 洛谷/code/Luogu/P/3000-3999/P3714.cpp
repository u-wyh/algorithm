#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int INF = 2e9+1;

int n,m,limitl,limitr;
int val[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int col[MAXN<<1];
int cnt=1;

bool vis[MAXN];
int sz[MAXN];

int pretree[MAXN<<2];
int curtree[MAXN<<2];

struct Edge{
    int node,color;
};
Edge edge[MAXN];
int cnte;

bool cmp(Edge a,Edge b){
    return a.color<b.color;
}

int edgecnt[MAXN];
int pathsum[MAXN];

int colornode[MAXN];
int cntc;

int subtree[MAXN];
int cnts;

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

inline void addedge(int u,int v,int c){
    nxt[cnt]=head[u];
    to[cnt]=v;
    col[cnt]=c;
    head[u]=cnt++;
}

void build(int *tree,int l,int r,int i){
    tree[i]=-INF;
    if(l==r){
        return;
    }
    else{
        int mid=(l+r)>>1;
        build(tree,l,mid,i<<1);
        build(tree,mid+1,r,i<<1|1);
    }
}

void clear(int *tree,int l,int r,int i){
    if(tree[i]==-INF){
        return ;
    }
    tree[i]=-INF;
    if(l<r){
        int mid=(l+r)>>1;
        clear(tree,l,mid,i<<1);
        clear(tree,mid+1,r,i<<1|1);
    }
}

void update(int *tree,int pos,int jobv,int l,int r,int i){
    if(l==r){
        tree[i]=max(tree[i],jobv);
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            update(tree,pos,jobv,l,mid,i<<1);
        }
        else{
            update(tree,pos,jobv,mid+1,r,i<<1|1);
        }
        tree[i]=max(tree[i<<1],tree[i<<1|1]);
    }
}

int query(int *tree,int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;
        int ans=-INF;
        if(jobl<=mid){
            ans=max(ans,query(tree,jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=max(ans,query(tree,jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

void getsize(int u,int fa){
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]&&v!=fa){
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
            if(!vis[v]&&v!=fa&&sz[v]>half){
                fa=u;
                u=v;
                find=false;
                break;
            }
        }
    }
    return u;
}

void dfs(int u,int fa,int precolor,int edge,int sum){
    if(edge>limitr){
        return ;
    }
    edgecnt[u]=edge;
    pathsum[u]=sum;
    subtree[++cnts]=u;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int c=col[i];
        if(v!=fa&&!vis[v]){
            dfs(v,u,c,edge+1,sum+(precolor==c?0:val[c]));
        }
    }
}

int calc(int u){
    cnte=0;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int c=col[i];
        if(!vis[v]){
            edge[++cnte]={v,c};
        }
    }
    sort(edge+1,edge+cnte+1,cmp);
    update(pretree,0,0,0,n,1);
    int ans=-INF;
    cntc=0;
    for(int k=1;k<=cnte;k++){
        int v=edge[k].node;
        int c=edge[k].color;
        if(k>1&&edge[k-1].color!=c){
            clear(curtree,0,n,1);
            for(int i=1;i<=cntc;i++){
                int node=colornode[i];
                update(pretree,edgecnt[node],pathsum[node],0,n,1);
            }
            cntc=0;
        }
        cnts=0;
        dfs(v,u,c,1,val[c]);
        for(int i=1;i<=cnts;i++){
            int node=subtree[i];
            int l=max(0,limitl-edgecnt[node]);
            int r=limitr-edgecnt[node];
            ans=max(ans,query(pretree,l,r,0,n,1)+pathsum[node]);
            ans=max(ans,query(curtree,l,r,0,n,1)-val[c]+pathsum[node]);
        }
        for(int i=1;i<=cnts;i++){
            int node=subtree[i];
            colornode[++cntc]=node;
            update(curtree,edgecnt[node],pathsum[node],0,n,1);
        }
    }
    clear(pretree,0,n,1);
    clear(curtree,0,n,1);
    return ans;
}

int solve(int u){
    vis[u]=true;
    int ans=calc(u);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]){
            ans=max(ans,solve(getcentroid(v,u)));
        }
    }
    return ans;
}

int main()
{
    n=read(),m=read(),limitl=read(),limitr=read();
    for(int i=1;i<=m;i++){
        val[i]=read();
    }
    for(int i=1;i<n;i++){
        int u,v,c;
        u=read(),v=read(),c=read();
        addedge(u,v,c);
        addedge(v,u,c);
    }
    build(curtree,0,n,1);
    build(pretree,0,n,1);
    cout<<solve(getcentroid(1,0))<<endl;
    return 0;
}