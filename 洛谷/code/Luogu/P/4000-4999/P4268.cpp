#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int n;
int val[MAXN];
int leaf[MAXN];
int son[MAXN];
int f[MAXN];

int cnt=1;
int head[MAXN];
int Next[MAXN];
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

void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs1(int u){
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        dfs1(v);
        leaf[u]+=leaf[v];
        f[u]+=val[v]*leaf[v]+f[v];
    }
    //cout<<u<<' '<<f[u]<<' '<<leaf[u]<<endl;
}

void dfs2(int u,int fa){
    f[u]=f[fa]+3*(leaf[1]-leaf[u])-leaf[u]*val[u];
    for(int i=head[u];i;i=Next[i]){
        dfs2(to[i],u);
    }
}

signed main()
{
    n=read();
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        val[i]=s.length()+1;
        //cout<<i<<' '<<val[i]<<endl;
        int m=read();
        son[i]=m;
        if(m==0){
            leaf[i]=1;
        }
        for(int j=1;j<=m;j++){
            int u=read();
            addedge(i,u);
        }
    }
    dfs1(1);
    f[1]-=leaf[1];
    int ans=f[1];
    //cout<<f[1]<<endl;
    for(int i=head[1];i;i=Next[i]){
        dfs2(to[i],1);
    }
    for(int i=2;i<=n;i++){
        //cout<<i<<' '<<f[i]<<endl;
        ans=min(ans,f[i]);
    }
    cout<<ans<<endl;
    return 0;
}
