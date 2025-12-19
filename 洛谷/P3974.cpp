#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;

int n,m;
int val[MAXN][MAXN];
long long dp[MAXN][MAXN];

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

int main()
{
    int T=read();
    while(T--){
        n=read(),m=read();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                val[i][j]=read();
            }
        }
        for(int i=0;i<=n;i++){
            for(int j=1;j<=m+1;j++){
                dp[i][j]=0;
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=m;j>=1;j--){
                dp[i][j]=max(max(dp[i-1][j],dp[i][j+1]),dp[i-1][j+1]+val[i][j]);
            }
        }
        cout<<dp[n][1]<<endl;
    }
    return 0;
}