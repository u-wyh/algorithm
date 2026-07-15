#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXT = MAXN*50;
const int LIMIT = 20;

int n,m,len,p;
int st[MAXN][LIMIT];
int dep[MAXN];
int nums[MAXN];
int help[MAXN];
int val[MAXN];//表示从头顶点到这个节点的异或值

int cnt=0;
int root[MAXN];
int ls[MAXT];
int rs[MAXT];
int tree[MAXT];

//链式前向星建图
int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int tot=1;

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
    nxt[tot]=head[u];
    to[tot]=v;
    head[u]=tot++;
}

inline int find(int val){
    int l=1,r=len,ans=len;
    while(l<=r){
        int mid=(l+r)/2;
        if(help[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    if(help[ans]!=val){
        ans=-1;
    }
    return ans;
}

int lca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int i=p;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b){
        return a;
    }
    for(int i=p;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

int build(int l,int r){
    int rt=++cnt;
    if(l==r){
        return rt;
    }
    int mid=(l+r)/2;
    ls[rt]=build(l,mid);
    rs[rt]=build(mid+1,r);
    return rt;
}

int add(int pos,int l,int r,int i){
    int rt=cnt++;
    tree[rt]=tree[i]+1;
    ls[rt]=ls[i],rs[rt]=rs[i];
    if(l==r){
        return rt;
    }
    int mid=(l+r)/2;
    if(pos<=mid){
        ls[rt]=add(pos,l,mid,ls[rt]);
    }
    else{
        rs[rt]=add(pos,mid+1,r,rs[rt]);
    }
    return rt;
}

void dfs(int u,int f){
    val[u]=val[f]^nums[u];
    root[u]=add(find(nums[u]),1,len,root[f]);
    dep[u]=dep[f]+1;
    st[u][0]=f;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=f){
            dfs(v,u);
        }
    }
}

inline bool query(int pos,int l,int r,int u,int v){
    if(tree[u]==tree[v]){
        return false;
    }
    if(l==r){
        return tree[u]>tree[v];
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            return query(pos,l,mid,ls[u],ls[v]);
        }
        else{
            return query(pos,mid+1,r,rs[u],rs[v]);
        }
    }
}

int main()
{
    n=read(),m=read();
    p=log2(n);
    for(int i=1;i<=n;i++){
        nums[i]=read();
        help[i]=nums[i];
    }
    sort(help+1,help+n+1);
    help[0]=help[1]-1;
    for(int i=1;i<=n;i++){
        if(help[i]!=help[i-1]){
            help[++len]=help[i];
        }
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    root[0]=build(1,len);
    dfs(1,0);
    for(int i=1;i<=m;i++){
        int u,v,k;
        u=read(),v=read(),k=read();
        int fa=lca(u,v);
        int w=find(k^val[u]^val[v]^nums[fa]);
        fa=st[fa][0];
        if(w==-1){
            printf("no\n");
            continue;
        }
        if(query(w,1,len,root[u],root[fa])){
            printf("yes\n");
            continue;
        }
        else if(query(w,1,len,root[v],root[fa])){
            printf("yes\n");
            continue;
        }
        else{
            printf("no\n");
            continue;
        }
    }
    return 0;
}