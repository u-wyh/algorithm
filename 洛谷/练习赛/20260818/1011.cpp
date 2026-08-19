#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MOD = 998244353;
const int MAXN = 5500;
const int MAXH = 16;

int n;

int headg[MAXN];
int nxtg[MAXN<<1];
int tog[MAXN<<1];
int cntg=1;

int st[MAXN][MAXH];
int dep[MAXN];

int leaf[MAXN];
int cntl;

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans*=a;
            ans%=MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

void addedge(int u,int v){
    nxtg[cntg]=headg[u];
    tog[cntg]=v;
    headg[u]=cntg++;
}

void init(){
    for(int i=1;i<=n;i++){
        headg[i]=0;
    }
    cntg=1;
    cntl=0;
}

void dfs(int u,int f){
    dep[u]=dep[f]+1;
    st[u][0]=f;
    for(int i=1;i<MAXH;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    int son=0;
    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        if(v!=f){
            son++;
            dfs(v,u);
        }
    }
    if(son==0){
        leaf[++cntl]=u;

    }
}

int lca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }

    for(int i=MAXH-1;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }

    if(a==b){
        return a;
    }

    for(int i=MAXH-1;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;
    while(T--){
        cin>>n;
        init();
        for(int i=1;i<n;i++){
            int u,v;
            cin>>u>>v;
            addedge(u,v);
            addedge(v,u);
        }
        dfs(1,0);

        int a=n+1;
        dep[a]=n+1;
        for(int i=1;i<=cntl;i++){
            if(dep[leaf[i]]<=dep[a]){
                a=leaf[i];
            }
        }

        double ans=1.0;
        int x=1,y=1;
        for(int i=1;i<=cntl;i++){
            int b=leaf[i];
            if(a!=b){
                int c=lca(a,b);
                int x1=dep[a]+dep[b]-2*dep[c];
                int y1=dep[b]-dep[c];
                double tmp=1.0*y1/x1;
                if(tmp<ans){
                    ans=tmp;
                    x=x1;
                    y=y1;
                }
            }
        }

        int g=gcd(x,y);
        x/=g;
        y/=g;

        int res=y*power(x,MOD-2)%MOD;
        cout<<res<<endl;
    }
    return 0;
}