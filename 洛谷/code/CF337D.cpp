#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m,d;
bool vis[MAXN];
int st,en;
int dis[MAXN];

bool ok[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];

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

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u,int fa){
    dis[u]=dis[fa]+1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs(v,u);
    }
}

int main()
{
    n=read(),m=read(),d=read();
    st=read();
    vis[st]=true;
    for(int i=2;i<=m;i++){
        vis[read()]=true;
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs(st,0);
    int dia=0;
    for(int i=1;i<=n;i++){
        if(vis[i]){
            if(dis[i]>dia){
                dia=dis[i];
                st=i;
            }
        }
    }
    // cout<<' '<<dia<<' '<<st<<endl;
    dis[0]=-1;
    dfs(st,0);
    en=st;
    dia=0;
    for(int i=1;i<=n;i++){
        if(vis[i]){
            if(dis[i]>dia){
                dia=dis[i];
                en=i;
            }
        }
        if(dis[i]>d){
            ok[i]=1;
        }
    }
    // cout<<' '<<dia<<' '<<en<<endl;
    dfs(en,0);
    // cout<<st<<' '<<en<<endl;
    for(int i=1;i<=n;i++){
        if(dis[i]>d){
            ok[i]=true;
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(!ok[i]){
            ans++;
        }
    }
    printf("%d\n",ans);
    return 0;
}