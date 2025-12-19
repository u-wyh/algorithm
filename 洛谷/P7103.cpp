#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e6+5;
const int LIMIT = 23;

int n,m,h;

int dfncnt;
int dfn[MAXN];
int seg[MAXN];

int dep[MAXN];
int st[MAXN][LIMIT];

vector<int>vec[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXN];
int to[MAXN];

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

void dfs(int u,int f){
    dfn[u]=++dfncnt;
    seg[dfncnt]=u;

    st[dfncnt][0]=dfn[f];

    dep[dfncnt]=dep[dfn[f]]+1;
    vec[dep[dfncnt]].push_back(dfncnt);

    for(int i=1;i<=h;i++){
        st[dfncnt][i]=st[st[dfncnt][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        dfs(to[i],u);
    }
}

int lca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int i=h;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b){
        return a;
    }
    for(int i=h;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

int main()
{
    n=read(),m=read();
    h=log2(n)+1;
    for(int i=1;i<=n;i++){
        int u=read();
        addedge(u,i);
    }
    dfs(1,0);
    for(int i=1;i<=m;i++){
        int d=read();
        int sz=vec[d].size();
        if(sz==0){
            printf("0\n");
        }
        else if(sz==1){
            printf("%d\n",seg[vec[d][0]]);
        }
        else{
            sort(vec[d].begin(),vec[d].end());
            printf("%d\n",seg[lca(vec[d][0],vec[d][sz-1])]);
        }
    }
    return 0;
}