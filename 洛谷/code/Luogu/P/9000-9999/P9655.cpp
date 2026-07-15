#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXH = 22;

int n,p;
char s[MAXN];
int st[MAXN][MAXH];

int fa[MAXN];
int sz[MAXN];
vector<int>block[MAXN];

int dep[MAXN];
int dfn[MAXN];
int dfncnt;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int sta[MAXN];
int top;
int match[MAXN];

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
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

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx==fy){
        return ;
    }
    if(sz[fx]<sz[fy]){
        swap(fx,fy);
    }
    fa[fy]=fx;
    sz[fx]+=sz[fy];
    for(int i=0;i<sz[fy];i++){
        block[fx].push_back(block[fy][i]);
    }
}

void dfs1(int u,int fa){
    if(s[u]=='('){
        sta[++top]=u;
    }
    else{
        if(top){
            match[u]=sta[top--];
        }
        else{
            match[u]=-1;
        }
    }

    dep[u]=dep[fa]+1;
    dfn[u]=++dfncnt;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs1(v,u);
        }
    }

    if(s[u]=='('){
        top--;
    }
    else if(match[u]>0){
        sta[++top]=match[u];
    }
}

int dist(int x,int y){
    return dep[x]+dep[y]-2*dep[lca(x,y)];
}

void dfs2(int u,int fa){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs2(v,u);
        }
    }

    int m=match[u];
    if(m<=0){
        return ;
    }

    un(m,u);
    if(st[m][0]>0&&match[st[m][0]]>0){
        un(st[m][0],m);
    }
}

bool cmp(int a,int b){
    return dfn[a]<dfn[b];
}

int main()
{
    scanf("%d",&n);
    p=log2(n)+1;
    scanf("%s",s+1);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=1;i<=n;i++){
        fa[i]=i;
        sz[i]=1;
        block[i].push_back(i);
    }
    dfs1(1,0);
    dfs2(1,0);
    int ans=0;
    for(int i=1;i<=n;i++){
        if(i!=find(i)){
            continue;
        }
        sort(block[i].begin(),block[i].end(),cmp);
        int total=0;
        int sz=block[i].size();
        for(int j=0;j<sz;j++){
            int x=block[i][j];
            int y=block[i][(j+1)%sz];
            total+=dist(x,y);
        }
        ans=max(ans,total/2+1);
    }
    if(ans<2){
        ans=0;
    }
    cout<<ans<<endl;
    return 0;
}