#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n;
int val[MAXN];
int f[MAXN];
int ans[MAXN];
int cost[MAXN];
int gain[MAXN];
bool ok[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
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

void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dfs(int u,int fa){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v==fa){
            continue;
        }
        f[v]=max(w-val[u],0ll);
        ok[v]=(val[v]>2*w)?1:0;
        val[v]+=max(0ll,val[u]-w);
        dfs(v,u);
    }
}

void dfs1(int u,int fa){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        // int w=weight[i];
        if(v==fa){
            continue;
        }
        // cost[v]=cost[u]+w;
        // gain[v]=gain[u]+val[u];
        ans[v]=ans[u]+f[v];
        dfs1(v,u);
    }
}

signed main()
{
    int T;
    T=read();
    while(T--){
        n=read();
        for(int i=2;i<=n;i++){
            val[i]=read();
        }
        for(int i=1;i<=n;i++){
            head[i]=0;
            ok[i]=0;
            cost[i]=0;
            gain[i]=0;
        }
        for(int i=1;i<n;i++){
            int u,v,w;
            u=read(),v=read(),w=read();
            addedge(u,v,w);
            addedge(v,u,w);
        }
        dfs(1,0);
        dfs1(1,0);
        int res=LLONG_MAX;
        for(int i=2;i<=n;i++){
            // cout<<i<<": "<<ans[i]<<' '<<cost[i]<<' '<<gain[i]<<' '<<ok[i]<<endl;
            if(ok[i]){
                res=min(res,ans[i]);
            }
        }
        for(int i=2;i<=n;i++){
            ans[i]=min(ans[i],res);
        }

        for(int i=2;i<=n;i++){
            cout<<ans[i]<<' ';
        }
        cout<<endl;
    }
    return 0;
}