#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 1005;
const int MAXM = 3005;

int n,m,w,r1,c1,h1,r2,c2,h2;
int f[MAXN][MAXN];

int fac[MAXM];
int inv[MAXM];

bool vis[MAXN];
int prime[MAXN];
int cnt;

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

void prepare(){
    for(int i=2;i<=1000;i++){
        if(!vis[i]){
            prime[++cnt]=i;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=1000;j++){
            vis[i*prime[j]]=true;
            if(i%prime[j]==0){
                break;
            }
        }
    }

    fac[0]=inv[0]=1;
    for(int i=1;i<=3000;i++){
        fac[i]=(fac[i-1]*i)%MOD;
    }
    inv[3000]=power(fac[3000],MOD-2);
    for(int i=2999;i>=1;i--){
        inv[i]=(inv[i+1]*(i+1))%MOD;
    }

    f[0][0]=1;
    for(int i=1;i<=1000;i++){
        for(int j=1;j<=i/2;j++){
            for(int k=1;k<=cnt;k++){
                int p=prime[k];
                if(p>i){
                    break;
                }
                f[i][j]=(f[i][j]+f[i-p][j-1])%MOD;
            }
        }
    }
}

int path(int x,int y,int z){
    int ans=0;
    for(int i=0;i<=(x+y)/2;i++){
        int tmp1=0;
        for(int j=0;j<=i;j++){
            if(j<=x/2&&(i-j)<=y/2){
                tmp1=(tmp1+(((((f[x][j]*f[y][i-j])%MOD)*inv[j])%MOD)*inv[i-j])%MOD)%MOD;
            }
        }
        int tmp2=0;
        for(int k=0;k<=z/2;k++){
            tmp2=(tmp2+((f[z][k]*inv[k]%MOD)*fac[i+k])%MOD)%MOD;
        }
        ans=(ans+tmp1*tmp2%MOD)%MOD;
    }
    return ans;
}

signed main()
{
    prepare();
    cin>>n>>m>>w>>r1>>c1>>h1>>r2>>c2>>h2;
    n--,m--,w--,r1--,c1--,h1--,r2--,c2--,h2--;
    int ans=path(n,m,w);
    ans=(ans-(path(r1,c1,h1)*path(n-r1,m-c1,w-h1)%MOD))%MOD;
    ans=(ans-(path(r2,c2,h2)*path(n-r2,m-c2,w-h2)%MOD))%MOD;
    int tmp=0;
    if(r1<=r2&&c1<=c2&&h1<=h2){
        tmp=(path(r1,c1,h1)*path(r2-r1,c2-c1,h2-h1)%MOD*path(n-r2,m-c2,w-h2)%MOD)%MOD;
    }
    else if(r1>=r2&&c1>=c2&&h1>=h2){
        tmp=(path(r2,c2,h2)*path(r1-r2,c1-c2,h1-h2)%MOD*path(n-r1,m-c1,w-h1)%MOD)%MOD;
    }
    // cout<<tmp<<endl;
    ans=(ans+tmp)%MOD;
    ans=(ans+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}