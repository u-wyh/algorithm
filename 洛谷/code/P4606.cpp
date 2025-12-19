#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;
const int MAXH = 22;

int n,m,p,q;

int headg[MAXN];
int nxtg[MAXM<<1];
int tog[MAXM<<1];
int cntg=1;

int head[MAXN<<1];
int nxt[MAXM*4];
int to[MAXN*4];
int cntt=1;

int low[MAXN];
int dfn[MAXN];
int dfncnt;
int sta[MAXN],top;

int cnt;

int sum[MAXN<<1];
int dep[MAXN<<1];
int st[MAXN<<1][MAXH];

int keycnt;
int key[MAXN];

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

inline void addedgeg(int u,int v){
    nxtg[cntg]=headg[u];
    tog[cntg]=v;
    headg[u]=cntg++;
}

inline void addedge(int u,int v){
    nxt[cntt]=head[u];
    to[cntt]=v;
    head[u]=cntt++;
}

void tarjan(int u,int fa){
    dfn[u]=low[u]=++dfncnt;
    sta[++top]=u;

    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        if(v==fa){
            continue;
        }

        if(!dfn[v]){
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>=dfn[u]){
                cnt++;
                while(sta[top]!=v){
                    int x=sta[top--];
                    addedge(cnt,x);
                    addedge(x,cnt);
                }
                top--;
                addedge(cnt,v);
                addedge(v,cnt);

                addedge(u,cnt);
                addedge(cnt,u);
            }
        }
        else{
            low[u]=min(low[u],dfn[v]);
        }
    }
}

void dfs(int u,int fa){
    dfn[u]=++dfncnt;
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    sum[u]=sum[fa]+(u<=n?1:0);
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs(v,u);
        }
    }
}

inline int lca(int u,int v){
    if(dep[u]<dep[v]){
        swap(u,v);
    }
    for(int i=p;i>=0;i--){
        if(dep[st[u][i]]>=dep[v]){
            u=st[u][i];
        }
    }
    if(u==v){
        return u;
    }

    for(int i=p;i>=0;i--){
        if(st[u][i]!=st[v][i]){
            u=st[u][i];
            v=st[v][i];
        }
    }
    return st[u][0];
}

void init(){
    cntg=1,cntt=1;
    for(int i=1;i<=n;i++){
        headg[i]=0;
        dfn[i]=low[i]=0;
    }
    for(int i=1;i<=cnt;i++){
        head[i]=0;
    }
    cnt=n;
    dfncnt=0;
    top=0;
}

int dis(int x,int y){
    int fa=lca(x,y);
    return sum[x]+sum[y]-2*sum[fa];
}

bool cmp(int a,int b){
    return dfn[a]<dfn[b];
}

int compute(){
    sort(key+1,key+keycnt+1,cmp);
    int total=0;
    for(int i=1;i<=keycnt;i++){
        total+=dis(key[i],key[(i%keycnt)+1]);
    }
    int root=lca(key[1],key[keycnt]);
    return total/2-keycnt+(root<=n?1:0);
}

int main()
{
    int T=read();
    while(T--){
        n=read(),m=read();
        init();
        for(int i=1;i<=m;i++){
            int u,v;
            u=read(),v=read();
            addedgeg(u,v);
            addedgeg(v,u);
        }
        tarjan(1,0);
        p=log2(cnt)+1;
        
        dfncnt=0;
        dfs(1,0);

        q=read();
        while(q--){
            keycnt=read();
            for(int i=1;i<=keycnt;i++){
                key[i]=read();
            }
            cout<<compute()<<endl;
        }
    }
    return 0;
}