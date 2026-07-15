#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const double eps = 1e-8;

int n;
double f[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
double weight[MAXN<<1];
int cnt=1;

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

inline void addedge(int u,int v,double w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dfs1(int u,int fa){
    double ans=(1-f[u]);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        double w=weight[i];
        if(v!=fa){
            dfs1(v,u);
            ans*=(1-f[v]*w);
        }
    }
    f[u]=1-ans;
}

void dfs2(int u,int fa){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        double w=weight[i];
        if(v!=fa){
            double x;
            if(1-f[v]*w>eps){
                x=(f[u]-f[v]*w)/(1-f[v]*w);
            }
            else{
                x=0;
            }
            f[v]=1-(1-f[v])*(1-x*w);
            dfs2(v,u);
        }
    }
}

int main()
{
    n=read();
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        double ww=w*0.01;
        addedge(u,v,ww);
        addedge(v,u,ww);
    }
    for(int i=1;i<=n;i++){
        int u=read();
        f[i]=u*0.01;
    }
    dfs1(1,0);
    dfs2(1,0);
    double ans=0;
    for(int i=1;i<=n;i++){
        ans+=f[i];
    }
    printf("%.6lf\n",ans);
    return 0;
}