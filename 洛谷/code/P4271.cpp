#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXH = 17;

int q,n;
int dep[MAXN];
int st[MAXN][MAXH];
int u[MAXN],v[MAXN];//直径端点
int fa[MAXN];//集合代表点

inline int lca(int u,int v){
    if(dep[u] < dep[v]) swap(u,v);
    for(int i=MAXH-1;i>=0;i--)
        if(dep[st[u][i]] >= dep[v]) u = st[u][i];
    if(u == v) return u;
    for(int i=MAXH-1;i>=0;i--)
        if(st[u][i] != st[v][i]) u = st[u][i], v = st[v][i];
    return st[u][0];
}

int dist(int a,int b){
    int f=lca(a,b);
    return dep[a]+dep[b]-2*dep[f];
}

int main()
{
    cin>>q;
    while(q--){
        char op;
        int p;
        cin>>op>>p;
        if(op=='B'){
            n++;
            if(p==-1){
                dep[n]=1;
                fa[n]=n;
                u[n]=n,v[n]=n;
            }
            else{
                dep[n]=dep[p]+1;
                st[n][0]=p;
                for(int i=1;i<MAXH;i++){
                    st[n][i]=st[st[n][i-1]][i-1];
                }
                fa[n]=fa[p];
                int len=dist(u[fa[n]],v[fa[n]]);
                int d1=dist(n,u[fa[n]]);
                int d2=dist(n,v[fa[n]]);
                if(d1>len&&d1>=d2){
                    v[fa[n]]=u[fa[n]];
                    u[fa[n]]=n;
                }
                else if(d2>len&&d2>=d1){
                    u[fa[n]]=v[fa[n]];
                    v[fa[n]]=n;
                }
            }
        }
        else{
            cout<<max(dist(p,u[fa[p]]),dist(p,v[fa[p]]))<<endl;
        }
    }
    return 0;
}