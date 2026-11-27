#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e4+5;
const int MAXM = 22;
const int MAXS = 1<<MAXM;
const int INF = 1e18;

int n,m;
int status;
int dp[MAXS];
int d[MAXN][MAXM];
int failmask[MAXN];

int t[MAXM][MAXS];

void print(int x){
    for(int i = 0; i < 3; i++){
        cout << ((x >> i) & 1);
    }
}

void prepare(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            // int s=status^(1<<(j-1));
            t[j][failmask[i]]+=d[i][j];
        }
    }

    for(int i = 0; i <= (1 << m) - 1; i++){
        print(i);
        cout << " ";
        for(int j = 1; j <= m; j++){
            cout << t[j][i] << " ";
        }
        cout << endl;
    }

    for(int j = 1; j <= m; j++){
        for(int k = 0; k < m; k++){
            for(int mask = 0; mask < (1 << m); mask++){
                if(mask &(1 << k)){
                    t[j][mask] += t[j][mask ^ ( 1  << k)]; 
                }
            }
        }
    }

    for(int i = 0; i <= (1 << m) - 1; i++){
        print(i);
        cout << " ";
        for(int j = 1; j <= m; j++){
            cout << t[j][i] << " ";
        }
        cout << endl;
    }
}

int cost(int s,int j){
    s=status^s;
    return t[j][s];
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    status=(1<<m)-1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>d[i][j];
        }

        string str;
        cin>>str;
        for(int j=1;j<=m;j++){
            if(str[j-1]=='R'){
                failmask[i]|=(1<<(j-1));
            }
        }
    }

    prepare();

    dp[0]=0;
    for(int i=1;i<=status;i++){
        dp[i]=INF;
    }
    for(int i=0;i<(1<<m);i++){
        for(int j=1;j<=m;j++){
            if(i&(1<<(j-1))){
                continue;
            }
            dp[i+(1<<(j-1))]=min(dp[i+(1<<(j-1))],dp[i]+cost(i,j));
        }
    }

    cout<<dp[status]<<endl;
    return 0;
}