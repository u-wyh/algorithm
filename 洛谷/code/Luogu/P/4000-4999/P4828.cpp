#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXM = 2005;
const int MAXN = 1e6+5;

int n,q;
int nums[MAXN];
int comb[MAXM][MAXM];

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

signed main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    for(int i=0;i<=2001;i++){
        comb[i][0]=comb[i][i]=1;
        for(int j=1;j<i;j++){
            comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%MOD;
        }
    }
    q=read();
    while(q--){
        int x,y;
        x=read(),y=read();
        int ans=0;
        for(int i=0;i<=x;i++){
            ans=(ans+comb[x][i]*nums[(y+i-1)%n+1])%MOD;
        }
        cout<<ans<<endl;
    }
    return 0;
}