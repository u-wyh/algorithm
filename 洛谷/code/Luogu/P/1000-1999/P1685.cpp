#include<bits/stdc++.h>
#define ll long long
#define R register
#define mod 10000
#define N 50005
using namespace std;

int n,m,s,t,ti,tot,h[N],in[N];
ll cnt[N],dis[N];
struct node{
    int nex,to,dis;
}edge[N<<1];

template<typename T>inline void read(T &a){
    char c=getchar();T x=0,f=1;
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
    a=f*x;
}

inline void add(R int u,R int v,R int w){
    edge[++tot].nex=h[u];
    edge[tot].to=v;
    edge[tot].dis=w;
    h[u]=tot;
    in[v]++;
}

inline void dfs(R int x){
    for(R int i=h[x];i;i=edge[i].nex){
        R int xx=edge[i].to;
        (dis[xx]+=dis[x]+cnt[x]*edge[i].dis)%=mod;
        (cnt[xx]+=cnt[x])%=mod;
        --in[xx];//ÍØÆËÅÅÐò
        if(!in[xx])dfs(xx);
    }
}
int main(){
    read(n);read(m);read(s);read(t);read(ti);
    for(R int i=1,u,v,w;i<=m;i++){
        read(u);read(v);read(w);
        if(u!=v)add(u,v,w);
    }
    cnt[s]=1;
    dfs(s);
    printf("%lld\n",(dis[t]+(cnt[t]-1)*ti)%mod);
    return 0;
}
