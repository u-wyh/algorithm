#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;
const int MAXM = MAXN*2;

int q,n;
struct node{
    int u,v,w,id;
};
node nums[MAXN];

int fa[MAXM];
int head[MAXM];
int nxt[MAXM];
int to[MAXM];
int cnt=1;

int father[MAXM];
int key[MAXM];
int pos[MAXM];
int sz[MAXM];
int cntu;

int ans=0;

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

bool cmp(node a,node b){
    return a.w<b.w;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void kruskalrebuild(){
    sort(nums+1,nums+n,cmp);
    cntu=n;
    for(int i=1;i<n;i++){
        int fx=find(nums[i].u);
        int fy=find(nums[i].v);
        fa[fx]=fa[fy]=++cntu;
        fa[cntu]=cntu;
        key[cntu]=nums[i].w;
        pos[nums[i].id]=cntu;
        addedge(cntu,fx);
        addedge(cntu,fy);
    }
}

void dfs(int u,int fa){
    if(u<=n){
        sz[u]=1;
    }
    father[u]=fa;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v,u);
        sz[u]+=sz[v];
    }
}

void dfs1(int u,int t){
    if(key[u]<=t){
        ans+=sz[u]*(sz[u]-1);
    }
    else{
        for(int i=head[u];i;i=nxt[i]){
            dfs1(to[i],t);
        }
    }
}

int main()
{
    q=read(),n=read();
    for(int i=1;i<n;i++){
        nums[i].u=read(),nums[i].v=read(),nums[i].w=read();
        nums[i].id=i;
    }
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    kruskalrebuild();
    dfs(cntu,0);
    while(q--){
        int t,sub;
        t=read(),sub=read();
        ans=0;
        t--;
        dfs1(cntu,t);
        cout<<ans<<' ';
        if(key[pos[sub]]<=t){
            if(key[cntu]<=t){
                ans=(n-sz[pos[sub]])*(n-sz[pos[sub]]-1);
                for(int i=head[pos[sub]];i;i=nxt[i]){
                    int v=to[i];
                    ans+=(sz[v]-1)*sz[v];
                }
            }
            else{
                for(int i=head[pos[sub]];i;i=nxt[i]){
                    int v=to[i];
                    ans+=(sz[v]-1)*sz[v];
                }
                int u=pos[sub];
                while(u){
                    if(key[father[u]]>t){
                        break;
                    }
                    u=father[u];
                }
                ans-=sz[u]*(sz[u]-1);
                ans+=(sz[u]-sz[pos[sub]])*(sz[u]-sz[pos[sub]]-1);

            }
        }
        cout<<ans<<endl;
    }
    return 0;
}