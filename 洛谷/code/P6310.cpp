#include<bits/stdc++.h>
using namespace std;
const int MAXN = 6e5+5;
const int MAXM = 3e5+5;

int n,m;

struct node{
    int u,v,w;
}nums[MAXM];

int val[MAXN];
int cntu;

int fa[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXN];
int to[MAXN];

int pos[MAXM];

int ans;
int ans1;

int val1[MAXN],val2[MAXN];
int from1[MAXN],from2[MAXN];

inline int read(){
    int x=0;
    char c=getchar();
    while(c<'0'||c>'9') 
        c=getchar();
    while(c<='9'&&c>='0'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x;
}

bool cmp(node a,node b){
    return a.w<b.w;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void kruskalrebuild(){
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    cntu=n;
    sort(nums+1,nums+m+1,cmp);
    for(int i=1;i<=m;i++){
        int fx=find(nums[i].u);
        int fy=find(nums[i].v);
        if(fx!=fy){
            fa[fx]=fa[fy]=++cntu;
            fa[cntu]=cntu;
            val[cntu]=nums[i].w;
            addedge(cntu,fx);
            addedge(cntu,fy);
        }
    }
}

inline void update(int u,int v){
    if(val1[v]>val1[u]){
        val2[u]=val1[u];
        val1[u]=val1[v];
        from2[u]=from1[u];
        from1[u]=from1[v];
    }
    else if(val1[v]>val2[u]&&from1[u]!=from1[v]){
        val2[u]=val1[v];
        from2[u]=from1[v];
    }

    if(val2[v]>val2[u]){
        val2[u]=val2[v];
        from2[u]=from2[v];
    }
}

void dfs(int u){
    if(u<=n){
        val1[u]=val[u];from1[u]=u;
        val2[u]=0;
        return ;
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v);
        update(u,v);
    }
}

void dfs1(int u,int fa){
    update(u,fa);
    if(u<=n){
        return ;
    }
    if(val2[u]<val[u]){
        val2[u]=0;
    }
    if(val1[u]<val[u]){
        val1[u]=0;
    }
    if(val2[u]==0&&val1[u]!=0){
        pos[from1[u]]=u;
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs1(v,u);
    }
}

void dfs2(int u){
    if(u<=n){
        ans++;
        return ;
    }
    if(val1[u]>=val[u]){
        ans++;
        return ;
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs2(v);
    }
}

void dfs3(int u){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(val2[v]!=0){
            ans1++;
        }
        else{
            dfs3(v);
        }
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        nums[i].u=read();
        nums[i].v=read();
        nums[i].w=read();
    }
    kruskalrebuild();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    dfs(cntu);
    dfs1(cntu,0);
    dfs2(cntu);
    printf("%d ",ans);
    for(int i=1;i<=n;i++){
        if(val1[i]!=val2[i]&&val1[i]==val[i]){
            if(val2[i]==0){
                printf("-1 ");
            }
            else{
                ans1=0;
                if(pos[i]!=0){
                    dfs3(pos[i]);
                }
                if(ans1!=0){
                    ans1--;
                }
                printf("%d ",ans+ans1);
            }
        }
        else{
            printf("%d ",ans);
        }
    }
    return 0;
}