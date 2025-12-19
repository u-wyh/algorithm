#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXM = 2005;
const int MOD = 998244353;

int n,m;
int arr[MAXN][MAXM];
int sum[MAXN][MAXM];
long long f[MAXN][MAXN<<1];
long long g[MAXN][MAXN];

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
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            arr[i][j]=read();
            sum[i][0]=(sum[i][0]+arr[i][j])%MOD;//sum[i][0]计算整行的所有值总和
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            sum[i][j]=(sum[i][0]-arr[i][j]+MOD)%MOD;
        }
    }
    //合法的方案数=总方案书-不合法的方案数
    long long ans=0;//这个用于记录所有不合法的方案数
    for(int col=1;col<=m;col++){
        //枚举每一个不合法的列
        for(int i=1;i<=n;i++){
            for(int j=0;j<=2*n;j++){
                f[i][j]=0;//初始化  f[i][j]最终表示的是  前i行中 选定的不合法的列比其他列多(j-n)的方案数
                //这里加上n是为了使得所有量都为正数
            }
        }
        f[0][n] = 1;
        for(int i = 1; i<=n; i++){
            for(int j = n-i; j<=n+i; j++) {
                f[i][j] = (f[i-1][j]+f[i-1][j-1]*arr[i][col]%MOD+f[i-1][j+1]*sum[i][col]%MOD)%MOD;
            }
        }
        for(int j = 1; j<=n; j++){
            ans = (ans+f[n][n+j])%MOD;//计算不合法的方案数
        }
    }
    g[0][0] = 1;
	for(int i = 1; i<=n; i++){
	    for(int j = 0; j<=i; j++){
		    g[i][j] = (g[i-1][j]+(j>0?g[i-1][j-1]*sum[i][0]%MOD:0))%MOD;//计算总方案数
            //g[i][j]表示的前i行选j个总方案数  并且每一行最多只可以选一个
        }
    }
    for(int j = 1; j<=n; j++){
	    ans = (ans-g[n][j]+MOD)%MOD; 
    } 
	cout << ans*(MOD-1)%MOD << endl;//相当于乘-1
    return 0;
}