#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXM = 1e5+5;
const int LIMIT = 20;

int n,q;
int arr[MAXN];

vector<int>vec;

int tree[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];

int dfncnt;
int dfn[MAXN];
int top[MAXN];
int st[MAXN][LIMIT];
int dep[MAXN];
int sz[MAXN];
int son[MAXN];

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

inline int lowbit(int x){
    return x&(-x);
}

inline void update(int u,int v){
    while(u<=n){
        tree[u]^=v;
        u+=lowbit(u);
    }
}

inline int query(int x){
    int ans=0;
    while(x){
        ans^=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

void dfs1(int u,int fa){
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    sz[u]=1;
    for(int i=1;i<LIMIT;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs1(v,u);
        if(son[u]==0||sz[son[u]]<sz[v]){
            son[u]=v;
        }
        sz[u]+=sz[v];
    }
}

void dfs2(int u,int t){
    dfn[u]=++dfncnt;
    top[u]=t;
    if(son[u]){
        dfs2(son[u],t);
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==st[u][0]||v==son[u]){
            continue;
        }
        dfs2(v,v);
    }
}

int lca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int i=LIMIT-1;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b){
        return a;
    }
    for(int i=LIMIT-1;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

void pathupdate(int x,int y,int val){
    while(top[x]!=top[y]){
        if(dep[top[x]]<=dep[top[y]]){
            swap(x,y);
        }
        update(dfn[top[x]],val);
        update(dfn[x]+1,val);
        x=st[top[x]][0];
    }
    if(dep[x]<=dep[y]){
        swap(x,y);
    }
    update(dfn[y],val);
    update(dfn[x]+1,val);
}

signed main()
{
    n=read(),q=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,0);
    dfs2(1,1);
    for(int i=1;i<=n;i++){
        update(dfn[i],arr[i]);
        update(dfn[i]+1,arr[i]);
    }
    for(int i=1;i<=q;i++){
        int op,u,v,w;
        op=read(),u=read(),v=read();
        if(op==1){
            w=read();
            pathupdate(u,v,w);
        }
        else{
            int fa=lca(u,v);
            if(dep[u]+dep[v]-2*dep[fa]>=50){
                printf("1");
                continue;
            }
            vec.clear();
            vec.push_back(query(dfn[fa]));
            for(int i=u;i!=fa;i=st[i][0]){
                vec.push_back(query(dfn[i]));
            }
            for(int i=v;i!=fa;i=st[i][0]){
                vec.push_back(query(dfn[i]));
            }
            if((int)vec.size()<=2){
                printf("0");
                continue;
            }
            sort(vec.begin(),vec.end());
            bool flag=true;
            for(int j=2;j<(int)vec.size();j++){
                if((vec[j-1]+vec[j-2])>vec[j]){
                    printf("1");
                    flag=false;
                    break;
                }
            }
            if(flag)
                printf("0");
        }
    }
    return 0;
}