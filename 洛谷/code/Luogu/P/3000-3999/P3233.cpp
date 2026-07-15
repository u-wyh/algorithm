#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;
const int MAXH = 22;

int n,p,q,k;

int headg[MAXN];
int nxtg[MAXN<<1];
int tog[MAXN<<1];
int cntg=1;

int headv[MAXN];
int nxtv[MAXN];
int tov[MAXN];
int cntv=1;

int dep[MAXN];
int sz[MAXN];
int dfn[MAXN];
int st[MAXN][MAXH];
int dfncnt;

int order[MAXN];
int arr[MAXN];
bool iskey[MAXN];
int tmp[MAXN<<1];

int manager[MAXN];
int dist[MAXN];
int ans[MAXN];

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

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    sz[u]=1;
    dfn[u]=++dfncnt;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        if(v!=fa){
            dfs(v,u);
            sz[u]+=sz[v];
        }
    }
}

bool cmp(int a,int b){
    return dfn[a]<dfn[b];
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

inline void addedgev(int u,int v){
    nxtv[cntv]=headv[u];
    tov[cntv]=v;
    headv[u]=cntv++;
}

int buildvirtualtree(){
    sort(arr+1,arr+k+1,cmp);
    int len=0;
    tmp[++len]=1;
    for(int i=1;i<k;i++){
        tmp[++len]=arr[i];
        tmp[++len]=lca(arr[i],arr[i+1]);
    }
    tmp[++len]=arr[k];
    sort(tmp+1,tmp+len+1,cmp);

    int m=1;
    for(int i=2;i<=len;i++){
        if(tmp[i]!=tmp[i-1]){
            tmp[++m]=tmp[i];
        }
    }

    cntv=1;
    for(int i=1;i<=m;i++){
        headv[tmp[i]]=0;
    }
    for(int i=1;i<m;i++){
        addedgev(lca(tmp[i],tmp[i+1]),tmp[i+1]);
    }
    return tmp[1];
}

void dp1(int u){
    dist[u]=1e9+1;
    for(int i=headv[u];i;i=nxtv[i]){
        int v=tov[i];
        dp1(v);
        int w=dep[v]-dep[u];
        if(dist[v]+w<dist[u]||((dist[v]+w==dist[u])&&manager[v]<manager[u])){
            dist[u]=dist[v]+w;
            manager[u]=manager[v];
        }
    }
    if(iskey[u]){
        dist[u]=0;
        manager[u]=u;
    }
}

void dp2(int u){
    for(int i=headv[u];i;i=nxtv[i]){
        int v=tov[i];
        int w=dep[v]-dep[u];
        if(dist[u]+w<dist[v]||((dist[u]+w==dist[v])&&manager[u]<manager[v])){
            dist[v]=dist[u]+w;
            manager[v]=manager[u];
        }
        dp2(v);
    }
}

void amend(int u,int v){
    if(manager[u]==manager[v]){
        return ;
    }
    int x=v;
    for(int i=p;i>=0;i--){
        int jump=st[x][i];
        if(dep[u]<dep[jump]){
            int tou=dep[jump]-dep[u]+dist[u];
            int tov=dep[v]-dep[jump]+dist[v];
            if(tov<tou||(tov==tou&&manager[v]<manager[u])){
                x=jump;
            }
        }
    }
    int delta=sz[x]-sz[v];
    ans[manager[u]]-=delta;
    ans[manager[v]]+=delta;
}

void dp3(int u){
    ans[manager[u]]+=sz[u];
    for(int i=headv[u];i;i=nxtv[i]){
        int v=tov[i];
        amend(u,v);
        ans[manager[u]]-=sz[v];
        dp3(v);
    }
}

void compute(){
    for(int i=1;i<=k;i++){
        arr[i]=order[i];
    }
    for(int i=1;i<=k;i++){
        iskey[arr[i]]=1;
        ans[arr[i]]=0;
    }
    int tree=buildvirtualtree();
    dp1(tree);
    dp2(tree);
    dp3(tree);
    for(int i=1;i<=k;i++){
        iskey[arr[i]]=0;
    }
}

int main()
{
    n=read();
    p=log2(n)+1;
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedgeg(u,v);
        addedgeg(v,u);
    }
    dfs(1,0);
    q=read();
    for(int t=1;t<=q;t++){
        k=read();
        for(int i=1;i<=k;i++){
            order[i]=read();
        }
        compute();
        for(int i=1;i<=k;i++){
            cout<<ans[order[i]]<<' ';
        }
        cout<<endl;
    }
    return 0;
}