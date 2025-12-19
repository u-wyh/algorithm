#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;
const int BASE = 499;
const int MOD = 1e9+7;

int n;
char s[MAXN];
int p[MAXN];
int h[MAXN];
int ans[MAXN];

void build(){
    p[0]=1;
    for(int i=1;i<=n;i++){
        p[i]=p[i-1]*BASE;
        p[i]%=MOD;
    }
    for(int i=1;i<=n;i++){
        h[i]=h[i-1]*BASE+s[i]-'a'+1;
        h[i]%=MOD;
    }
}

int gethash(int l,int r){
    return ((h[r]-h[l-1]*p[r-l+1])%MOD+MOD)%MOD;
}

signed main()
{
    scanf("%lld %s",&n,s+1);
    build();
    ans[(n-1)/2+1]=-1;
    for(int i=(n-1)/2;i>=0;i--){
        ans[i]=ans[i+1]+2;
        while(ans[i]!=-1){
            if(i*2+ans[i]>=n){
                ans[i]-=2;
            }
            else{
                break;
            }
        }
        while(ans[i]!=-1){
            if(gethash(i+1,i+ans[i])==gethash(n-ans[i]-i+1,n-i)){
                break;
            }
            ans[i]-=2;
        }
    }
    for(int i=0;i<=(n-1)/2;i++){
        printf("%lld ",ans[i]);
    }
    return 0;
}