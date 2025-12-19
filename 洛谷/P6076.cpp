#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 405;
const int MAXM = 160005;

int n,m,k;
int comb[MAXN][MAXN];
int power[MAXM];

signed main()
{
    cin>>n>>m>>k;
    int all=n*m;
    for(int i=0;i<=400;i++){
        comb[i][0]=comb[i][i]=1;
        for(int j=1;j<i;j++){
            comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%MOD;
        }
    }
    int ans=0;
    for(int p=0;p<=k;p++){
        int d=(k-p+1);//表示如果至少p种颜色不能用  这个位置可以有多少种选择
        power[0]=1;
        for(int i=1;i<=all;i++){
            power[i]=(power[i-1]*d)%MOD;
        }
        for(int i=0;i<=n;i++){//至少i行没有格子
            for(int j=0;j<=m;j++){//至少j列没有格子
                int area=(n-i)*(m-j);
                int ways=(((comb[n][i]*comb[m][j])%MOD*comb[k][p])%MOD*power[area])%MOD;
                if((i+j+p)%2==1){
                    ans=(ans-ways)%MOD;
                }
                else{
                    ans=(ans+ways)%MOD;
                }
            }
        }
    }
    ans=(ans+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}