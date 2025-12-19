#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e4+5;
const int MAXH = 29;
const int MAXK = MAXN*40;

int n;
int p,q,all;
int val[MAXN];
map<int,int>mp;

int in[MAXN];
int out[MAXN];

bool tag[MAXN][2];
int ok[MAXN][2];

int cnt=1;
int trie[MAXK][2];

int fa[MAXN];
int sz[MAXN];
int son[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cntg=1;

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

void dfs1(int u,int f){
    fa[u]=f;
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=f){
            val[v]=val[u]^w;
            dfs1(v,u);
            sz[u]+=sz[v];
            if(sz[son[u]]<sz[v]){
                son[u]=v;
            }
        }
    }
}

int find(int val){
    int cur=1;
    int ans=0;
    for(int i=MAXH;i>=0;i--){
        int best=1-((val>>i)&1);
        if(trie[cur][best]){
            ans+=(1<<i);
            cur=trie[cur][best];
        }
        else{
            cur=trie[cur][1-best];
        }
    }
    return ans;
}

void insert(int val){
    int cur=1;
    for(int i=MAXH;i>=0;i--){
        int path=(val>>i)&1;
        if(trie[cur][path]==0){
            trie[cur][path]=++cnt;
        }
        cur=trie[cur][path];
    }
}

void clear(){
    for(int i=1;i<=cnt;i++){
        trie[i][0]=trie[i][1]=0;
    }
    all=0;
    cnt=1;
}

void dfs(int u){
    insert(val[u]);
    all=max(all,find(val[u]));
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa[u]){
            dfs(v);
        }
    }
}

void dfs2(int u,int keep){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa[u]&&v!=son[u]){
            dfs2(v,0);
        }
    }
    if(son[u]){
        dfs2(son[u],1);
    }
    insert(val[u]);
    all=max(find(val[u]),all);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa[u]&&v!=son[u]){
            dfs(v);
        }
    }
    in[u]=all;
    if(keep==0){
        clear();
    }
}

int main()
{
    n=read();
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dfs1(1,0);
    for(int i=n;i>=1;i--){
        mp[val[i]]=i;
    }
    for(int i=1;i<=n;i++){
        insert(val[i]);
        int ans=find(val[i]);
        if(all<=ans){
            all=ans;
            p=i,q=mp[all^val[i]];
        }
    }

    // cout<<p<<' '<<q<<' '<<all<<endl;

    while(p!=0){
        tag[p][0]=true;
        ok[fa[p]][0]=p;
        p=fa[p];
    }
    while(q!=0){
        tag[q][1]=true;
        ok[fa[q]][1]=q;
        q=fa[q];
    }
    for(int i=1;i<=n;i++){
        if(!tag[i][0]&&!tag[i][1]){
            // cout<<i<<endl;
            out[i]=all;
        }
    }

    clear();
    int u=1;
    while(tag[u][0]){
        out[u]=all;
        insert(val[u]);
        all=max(all,find(val[u]));
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v!=ok[u][0]&&v!=fa[u]){
                dfs(v);
            }
        }
        u=ok[u][0];
    }

    clear();
    u=1;
    while(tag[u][1]){
        out[u]=all;
        insert(val[u]);
        all=max(all,find(val[u]));
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v!=ok[u][1]&&v!=fa[u]){
                dfs(v);
            }
        }
        u=ok[u][1];
    }
    out[1]=INT_MIN;

    clear();
    dfs2(1,1);
    int ans=0;
    for(int i=1;i<=n;i++){
        // cout<<i<<":  "<<in[i]<<' '<<out[i]<<endl;
        ans=max(ans,in[i]+out[i]);
    }
    printf("%d\n",ans);
    return 0;
}