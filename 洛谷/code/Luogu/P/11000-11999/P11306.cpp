#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXH = 20;

int n,q,ans;
int p;

int ls[MAXN];
int rs[MAXN];
int val[MAXN];
int lt[MAXN];
int rt[MAXN];
int dfn[MAXN];
int seg[MAXN];
int dfncnt;

int tree[MAXN];

int fa[MAXN][MAXH];

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

void dfs(int u){
    if(!u){
        return ;
    }
    lt[u]=dfncnt+1;
    dfs(ls[u]);
    dfn[u]=++dfncnt;
    seg[dfncnt]=u;
    dfs(rs[u]);
    rt[u]=dfncnt;
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

bool check(int i){
    return (query(rt[i]-1)-query(lt[i]-1))==0;
}

void update(int x,int v){
    if(dfn[x]<n){
        if(val[x]>val[seg[dfn[x]+1]]){
            add(dfn[x],-1);
        }
        if(v>val[seg[dfn[x]+1]]){
            add(dfn[x],1);
        }
    }
    if(dfn[x]>1){
        if(val[x]<val[seg[dfn[x]-1]]){
            add(dfn[x]-1,-1);
        }
        if(v<val[seg[dfn[x]-1]]){
            add(dfn[x]-1,1);
        }
    }
    val[x]=v;
}

int solve(int x){
    if(!check(x)){
        return 0;
    }
    int ans=1;
    for(int i=p;i>=0;i--){
        if(fa[x][i]&&check(fa[x][i])){
            x=fa[x][i];
            ans+=(1<<i);
        }
    }
    return ans;
}

int main()
{
    n=read(),q=read();
    p=log2(n)+1;
    for(int i=1;i<=n;i++){
        ls[i]=read(),rs[i]=read();
        if(ls[i]){
            fa[ls[i]][0]=i;
        }
        if(rs[i]){
            fa[rs[i]][0]=i;
        }
    }
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=p;i++){
        for(int j=1;j<=n;j++){
            fa[j][i]=fa[fa[j][i-1]][i-1];
        }
    }
    dfs(1);
    for(int i=1;i<n;i++){
        if(val[seg[i]]>val[seg[i+1]]){
            add(i,1);
        }
    }
    for(int i=1;i<=n;i++){
        if(check(i)){
            ans++;
        }
    }

    while(q--){
        int k,x;
        k=read(),x=read();
        ans-=solve(k);
        update(k,x);
        ans+=solve(k);
        printf("%d\n",ans);
    }
    return 0;
}