#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int val[MAXN];
int fa[MAXN];
int f[MAXN][2];
double k;
int s,t;

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

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void dfs(int u,int fa){
    f[u][1]=val[u];
    f[u][0]=0;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs(v,u);
        f[u][0]+=max(f[v][1],f[v][0]);
        f[u][1]+=f[v][0];
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        fa[i]=i;
        val[i]=read();
    }
    for(int i=1;i<=n;i++){
        int u,v;
        u=read(),v=read();
        u++,v++;
        int fx=find(u);
        int fy=find(v);
        if(fx==fy){
            s=u;
            t=v;
            continue;
        }
        else{
            fa[fx]=fy;
            addedge(u,v);
            addedge(v,u);
        }
    }
    scanf("%lf",&k);
    dfs(s,0);
    double ans=f[s][0];
    dfs(t,0);
    ans=max(ans,1.0*f[t][0]);
    printf("%.1lf",ans*k);
    return 0;
}