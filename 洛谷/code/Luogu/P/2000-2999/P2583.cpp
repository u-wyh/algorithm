#include<bits/stdc++.h>
using namespace std;
const int MAXN = 55;
const int MAXT = 2005;

int n,m,m1,m2;
int t[MAXN];
bool train[MAXT][MAXN][2];
int dp[MAXT][MAXN];
int cnt=0;

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
    while(n=read()){
        memset(train,0,sizeof(train));
        memset(t,0,sizeof(t));
        memset(dp,127,sizeof(dp));//2139062143
        m=read();
        for(int i=1;i<n;i++){
            t[i]=read();
        }
        m1=read();
        while(m1--){
            int d = read();
			for(int j = 1; j <= n; j++){
				train[d][j][0] = 1;
				d += t[j];
			}
        }
        m2=read();
        while(m2--){
            int d = read();
			for(int j = n; j >= 1; j--){
				train[d][j][1] = 1;
				d += t[j-1];
			}
        }
        dp[m][n]=0;
        for(int i=m-1;i>=0;i--){
            for(int j=1;j<=n;j++){
                dp[i][j]=dp[i+1][j]+1;
                if(j<n&&train[i][j][0]&&i+t[j]<=m){
                    dp[i][j]=min(dp[i][j],dp[i+t[j]][j+1]);
                }
                if(i>1&&train[i][j][1]&&i+t[j-1]<=m){
                    dp[i][j]=min(dp[i][j],dp[i+t[j-1]][j-1]);
                }
            }
        }
        cout << "Case Number " << ++cnt << ": ";
		if(dp[0][1] >= 2139062143)
            cout << "impossible" << endl;
		else
            cout << dp[0][1] << endl;
    }
    return 0;
}
