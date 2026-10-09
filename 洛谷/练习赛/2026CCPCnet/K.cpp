#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXN = 2e5+5;
const int INF = 1e16;

int n,m,root;

int dis[MAXN];
int out[MAXN];
int tim[MAXN];
bool okay[MAXN];
int in[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cntg=1;

int ans[MAXN];

int inv[MAXN];

void addedge(int u,int v,int w){
    in[v]++;
    out[v]++;

    nxt[cntg]=head[u];
    to[cntg]=v;
    weight[cntg]=w;
    head[u]=cntg++;
}

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

int q[MAXN];

void compute(){
    int ql=1,qr=0;
    q[++qr]=root;

    for(int i=1;i<=n;i++){
        dis[i]=INF;
        tim[i]=1;
    }
    dis[root]=0;
    while(ql<=qr){
        int u=q[ql++];
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];

            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                tim[v]=tim[u];
            }
            else if(dis[v]==dis[u]+w){
                tim[v]+=tim[u];
                tim[v]%=MOD;
            }

            in[v]--;
            if(in[v]==0){
                q[++qr]=v;
            }
        }
    }

    for(int i=1;i<=n;i++){
        in[i]=out[i];
    }
    ql=1,qr=0;
    q[++qr]=root;
    ans[root]=0;
    while(ql<=qr){
        int u=q[ql++];
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];

            if(okay[v]){
                if(dis[u]+w==dis[v]){
                    ans[v]=(ans[v]+(((ans[u]+w)%MOD)*((tim[u]*power(tim[v],MOD-2))%MOD)%MOD))%MOD;
                }
            }
            else{
                ans[v]=(ans[v]+((((ans[u]+w)%MOD)*power(out[v],MOD-2))%MOD))%MOD;
            }

            in[v]--;
            if(in[v]==0){
                q[++qr]=v;
            }
        }
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>root;
    string s;
    cin>>s;
    for(int i=0;i<n;i++){
        if(s[i]=='1'){
            okay[i+1]=true;
        }
        else{
            okay[i+1]=false;
        }
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(v,u,w);
    }

    compute();
    
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<' ';
    }
    return 0;
}