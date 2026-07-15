#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXM = 25005;
const int MAXK = 30;
const int MOD = 998244353;
const int BASE = 499;

int n,m,k;
int s[MAXN];
int t[MAXM];

int hasht;

int p[MAXM];
int all[MAXK];

int rk[MAXK];
int cnt[MAXK];

int anslen;
int ans[MAXN];

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

void build(){
    p[0]=1;
    for(int i=1;i<=m;i++){
        p[i]=(p[i-1]*BASE)%MOD;
    }
}

inline void buildrank(){
    for(int i=1;i<=k;i++){
        rk[i]=0;
    }
    int rank=0;
    for(int i=1;i<=k;i++){
        if(cnt[i]){
            rk[i]=++rank;
        }
    }
}

inline int gethash(){
    int val=0;
    for(int i=1;i<=k;i++){
        val=(val+(all[i]*rk[i]%MOD))%MOD;
    }
    val=(val%MOD+MOD)%MOD;
    return val;
}

signed main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=n;i++){
        s[i]=read();
    }
    for(int i=1;i<=m;i++){
        t[i]=read();
    }

    build();

    for(int i=1;i<=m;i++){
        cnt[t[i]]++;
    }
    buildrank();
    for(int i=1;i<=m;i++){
        hasht=(hasht+(p[m-i]*rk[t[i]]%MOD))%MOD;
    }

    for(int i=1;i<=k;i++){
        cnt[i]=0;
    }
    for(int i=1;i<=m;i++){
        cnt[s[i]]++;
        all[s[i]]=(all[s[i]]+p[m-i])%MOD;
    }
    buildrank();
    if(gethash()==hasht){
        ans[++anslen]=1;
    }

    for(int i=m+1;i<=n;i++){
        cnt[s[i-m]]--;
        cnt[s[i]]++;

        buildrank();
        for(int j=1;j<=k;j++){
            all[j]=(all[j]*BASE)%MOD;
        }
        all[s[i-m]]=(all[s[i-m]]-p[m])%MOD;
        all[s[i]]=(all[s[i]]+p[0])%MOD;

        if(gethash()==hasht){
            ans[++anslen]=i-m+1;
        }
    }

    cout<<anslen<<endl;
    for(int i=1;i<=anslen;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}