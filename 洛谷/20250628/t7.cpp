#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

struct node{
    int to,w;
};

int a[MAXN];
bool good[MAXN];
int chain[MAXN],sum[MAXN],B[MAXN];
bool ok[MAXN];
int parent[MAXN];
vector<node> adj[MAXN];

void clear(int n) {
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
        good[i] = false;
        chain[i] = sum[i] = B[i] = 0;
        ok[i] = false;
        parent[i] = 0;
    }
}

signed main() {
    int T;
    scanf("%lld", &T);
    while(T--){
        int n;
        scanf("%lld",&n);
        clear(n);
        a[1]=0;
        for(int i=2;i<=n;i++) {
            scanf("%lld",&a[i]);
        }

        for(int i=0;i<n-1;i++) {
            int u,v;
            int w;
            scanf("%lld%lld%lld",&u,&v,&w);
            adj[u].push_back({v,w});
            adj[v].push_back({u,w});

            if(u==1){
                if(a[v]>2*w) {
                    good[v] = true;
                }
            } 
            else if(v==1) {
                if(a[u]>2*w) {
                    good[u]=true;
                }
            } 
            else{
                if(a[u]+a[v]>2*w) {
                    good[u]=true;
                    good[v]=true;
                }
            }
        }

        queue<int>q;
        q.push(1);
        parent[1]=0;
        chain[1]=0;
        sum[1]=0;
        B[1]=0;
        ok[1]=false;

        while (!q.empty()) {
            int u=q.front();
            q.pop();
            for (node e:adj[u]) {
                int v=e.to;
                int w=e.w;
                if (v==parent[u]) 
                    continue;
                parent[v] = u;
                if(ok[u]){
                    B[v]=B[u];
                    chain[v]=chain[u]+w;
                    sum[v]=sum[u]+a[v];
                    ok[v]=true;
                } else {
                    int need=chain[u]-sum[u]+w;
                    B[v]=max(B[u],need);
                    chain[v]=chain[u]+w;
                    sum[v]=sum[u]+a[v];
                    ok[v]=good[v];
                }
                q.push(v);
            }
        }

        for (int i=2;i<=n;i++) {
            printf("%lld ",B[i]);
        }
        cout<<endl;
    }
    return 0;
}