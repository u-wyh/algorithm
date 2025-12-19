#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int MAXM = 1e5+5;
const double eps = 1e-3;
int n,m;

double x=-1;

bool flag;

int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int weight[MAXM<<1];
int cnt=1;

int k[MAXN];
int b[MAXN];
double v[MAXN];
int fa[MAXN];

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

void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void compute(int k1,int b1,int k2,int b2){
    if(k1==k2&&b1==b2){
        return ;
    }
    if(k1==k2&&b1!=b2){
        return ;
    }
    x=(b2-b1)*1.0/(k1-k2);
}

void dfs(int u,int f,int wei,int top){
    if(fa[u]==top){
        compute(k[u],b[u],-k[f],wei-b[f]);
        return ;
    }
    k[u]=-k[f],b[u]=wei-b[f],fa[u]=top;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v==f){
            continue;
        }
        dfs(v,u,w,top);
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    for(int i=1;i<=n;i++){
        if(fa[i]==0){
            x=-1;
            k[i]=1,b[i]=0;
            for(int ei=head[i];ei;ei=nxt[ei]){
                int v=to[ei];
                int w=weight[ei];
                dfs(v,i,w,i);
            }
            v[i]=x;
        }
        if(flag){
            cout<<"IMPOSSIBLE"<<endl;
        }
    }

    for(int i=1;i<=n;i++){
        v[i]=v[fa[i]];
    }
    for(int i=1;i<=n;i++){
        v[i]=k[i]*v[i]+b[i];
        if(v[i]<0){
            cout<<"IMPOSSIBLE"<<endl;
            return 0;
        }
    }
    for(int i=1;i<=n;i++){
        for(int ei=head[i];ei;ei=nxt[ei]){
            int u=to[ei];
            int w=weight[ei];
            if(fabs(w-v[u]-v[i])>eps){
                cout<<"IMPOSSIBLE"<<endl;
                return 0;
            }
        }
    }
    for(int i=1;i<=n;i++){
        printf("%.2lf\n",v[i]);
    }
    return 0;
}