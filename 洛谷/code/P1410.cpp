#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2005;

int n;
int arr[MAXN];
int dp[MAXN][MAXN];

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
    while(scanf("%d",&n)==1){
        for(int i=1;i<=n;i++){
            arr[i]=read();
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                dp[i][j]=1e9;
            }
        }
        dp[1][1]=-1;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=i;j++){
                if(dp[i][j]!=1e9){
                    if(arr[i]<arr[i+1]){
                        dp[i+1][j+1]=min(dp[i+1][j+1],dp[i][j]);
                    }
                    if(dp[i][j]<arr[i+1]){
                        dp[i+1][i+1-j]=min(arr[i],dp[i+1][i-j+1]);
                    }
                }
            }
        }
        if(dp[n][n/2]!=1e9){
            cout<<"Yes!"<<endl;
        }
        else{
            cout<<"No!"<<endl;
        }
    }
    return 0;
}
