#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2005;
const int MOD = 1e9+7;

int n;
int p[MAXN*MAXN];
int sum;
int ans;

char s[MAXN][MAXN];

void dfs(int x,int y,int k,int dir){
    if(x==n&&y==n){
        ans=(ans+p[sum-k])%MOD;
        return ;
    }
    if(dir==0){
        if(x+1<=n){
            dfs(x+1,y,k,0);
        }
        if(y+1<=n&&s[x][y+1]!='W'){
            dfs(x,y+1,k+1,1);
        }
    }
    else{
        if(x+1<=n&&s[x+1][y]!='W'){
            dfs(x+1,y,k+1,0);
        }
        if(y+1<=n){
            dfs(x,y+1,k,1);
        }
    }
}

signed main()
{
    cin>>n;
    p[0]=1;
    for(int i=1;i<=n*n;i++){
        p[i]=(p[i-1]*2)%MOD;
    }
    for(int i=1;i<=n;i++){
        scanf("%s",s[i]+1);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(s[i][j]=='.'){
                sum++;
            }
        }
    }

    dfs(1,0,0,0);
    dfs(0,1,0,1);

    cout<<ans<<endl;
    return 0;
}