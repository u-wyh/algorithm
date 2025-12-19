#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int MAXM = 4e5+5;
const int MOD = 1e9+7;

int n,m;
int val[MAXN];
int vis[MAXN];

int col[MAXN];

int fac[MAXN];
int inv[MAXN];
int pw[MAXN];

int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
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

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
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

int comb(int a,int b){
    return fac[a]*inv[b]%MOD*inv[a-b]%MOD;
}

bool check(int u){
    bool flag=false;
    vis[u]=1;
    val[u]^=col[u];//这个地方实际上只对二分图有用

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]){
            col[v]=col[u]^1;
            flag|=check(v);
        }
        if(col[v]!=(col[u]^1)){
            flag=true;
        }
    }
    return flag;
}

pair<int,int> query(int u){
    vis[u]=2;
    pair<int,int>ans={1,val[u]};
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(vis[v]!=2){
            pair<int,int>tmp=query(v);
            ans.first+=tmp.first;
            ans.second+=tmp.second;
        }
    }
    return ans;
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int j=1;j<=m;j++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }

    fac[0]=1;
    inv[0]=1;
    pw[0]=1;
    for(int i=1;i<=n;i++){
        pw[i]=(pw[i-1]*2)%MOD;
        fac[i]=(fac[i-1]*i)%MOD;
    }
    inv[n]=power(fac[n],MOD-2);
    for(int i=n-1;i>=1;i--){
        inv[i]=(inv[i+1]*(i+1))%MOD;
    }

    int ans=1;
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            bool flag=check(i);
            pair<int,int>tmp=query(i);

            if(flag){
                ans=ans*pw[tmp.first-1]%MOD;
            }
            else{
                ans=ans*comb(tmp.first,tmp.second)%MOD;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}