#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MOD = 1e9+7;

int n,m;

int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;
int ans;

int f[MAXN][105];

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
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dfs1(int u,int f){
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=f){
            if(w==0){
                ans*=(m-1);
            }
            else if(w==1){
                ans*=m;
            }
            ans%=MOD;
            dfs1(v,u);
        }
    }
}

void dfs(int u, int fa) {
    for (int i=head[u];i;i=Next[i]) {
        int v=to[i];
        int t=weight[i];
        if (v == fa) continue;
        dfs(v, u); // 先递归处理子节点
        for (int c = 1; c <= m; c++) {
            int min_sum = LLONG_MAX;
            if (t == 0) {
                for (int d = 1; d <= m; d++) {
                    if (d == c) continue;
                    min_sum = min(min_sum, f[v][d]);
                }
            } else if (t == 1) {
                // 无限制
                for (int d = 1; d <= m; d++) {
                    min_sum = min(min_sum, f[v][d]);
                }
            } else if (t == 2) {
                // w_u == w_v
                min_sum = f[v][c];
            }
            f[u][c] += min_sum;
        }
    }
    // 加上当前节点的点权
    for (int c = 1; c <= m; c++) {
        f[u][c] += c;
    }
}
signed main()
{
    n=read(),m=read();
    bool flag=false;
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
        if(w==0){
            flag=true;
        }
    }
    if(flag&&m==1){
        cout<<"0 0"<<endl;
        return 0;
    }
    ans=m;
    dfs1(1,0);
    cout<<ans<<' ';
    ans=LLONG_MAX;
    dfs(1,0);
    for(int i=1;i<=m;i++){
        ans=min(ans,f[1][i]);
    }
    cout<<ans<<endl;
    return 0;
}
