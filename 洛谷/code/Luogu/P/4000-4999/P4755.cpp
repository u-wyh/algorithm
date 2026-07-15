#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m,root;
int val[MAXN];
int arr[MAXN];

int tree[MAXN];

int ls[MAXN];
int rs[MAXN];
int sta[MAXN];
int fa[MAXN];
int sz[MAXN];
int son[MAXN];

long long ans=0;

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

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int v){
    while(x<=m){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

int sum(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

int find(int val){
    int l=1,r=m,ans=m;
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

void build(){
    int top=0;
    for (int i = 1; i <= n; i++) {
        int pos = top;

        while (pos > 0 && val[sta[pos]] < val[i]) {
            pos--;
        }
        if (pos > 0) {
            rs[sta[pos]] = i;
        }
        if (pos < top) {
            ls[i] = sta[pos + 1];
        }

        sta[++pos] = i;
        top = pos;
    }
    root=sta[1];
}

void dfs1(int u,int f){
    fa[u]=f;
    sz[u]=1;
    if(ls[u]){
        dfs1(ls[u],u);
    }
    if(rs[u]){
        dfs1(rs[u],u);
    }
    sz[u]+=sz[ls[u]];
    sz[u]+=sz[rs[u]];
    if(sz[ls[u]]>sz[rs[u]]){
        son[u]=ls[u];
    }
    else{
        son[u]=rs[u];
    }
    // cout<<u<<":  "<<son[u]<<endl;
}

int findpos(int val){
    int l=1,r=m,ans=m+1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(arr[mid]>val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

void dfs(int u,int rt){
    int v=arr[val[rt]]/arr[val[u]];
    int pos=findpos(v)-1;
    ans+=sum(pos);
    if(ls[u]){
        dfs(ls[u],rt);
    }
    if(rs[u]){
        dfs(rs[u],rt);
    }
}

void dfs3(int u,int v){
    add(val[u],v);
    if(ls[u]){
        dfs3(ls[u],v);
    }
    if(rs[u]){
        dfs3(rs[u],v);
    }
}

void dfs2(int u,int keep){
    int v=ls[u]+rs[u]-son[u];
    if(v){
        dfs2(v,0);
    }
    if(son[u]){
        dfs2(son[u],1);
    }
    add(val[u],1);
    if(arr[1]==1){
        ans+=sum(1);
    }
    if(v){
        dfs(v,u);
    }

    if(keep==1){
        if(v){
            dfs3(v,1);
        }
    }
    else{
        add(val[u],-1);
        if(son[u]){
            dfs3(son[u],-1);
        }
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
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
    build();
    // cout<<root<<endl;
    // for(int i=1;i<=n;i++){
    //     cout<<i<<":   "<<ls[i]<<' '<<rs[i]<<' '<<val[i]<<endl;
    // }
    dfs1(root,0);
    dfs2(root,1);
    cout<<ans<<endl;
    return 0;
}
/*
4
1 3 9 3

5
1 1 2 1 1

*/