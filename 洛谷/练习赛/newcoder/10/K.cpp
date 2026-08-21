#include<bits/stdc++.h>
using namespace std;
const int MAXN = 30;
const int MAXM = (1<<24)+5;
const long long INF = 1e15;

int n;
int val[MAXN][MAXN];
long long dp[MAXM];
int score[MAXM];

// int comb(int x,int y){
//     int ans=1;
//     y=min(y,x-y);
//     for(int i=1;i<=y;i++){
//         ans*=x-i+1;
//         ans/=i;
//     }
//     return ans;
// }

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    // cout<<(1ll*(1<<24)*24*8)<<endl;

    // int res=0;
    // for(int i=0;i<=7;i++){
    //     res+=comb(24,3*i)*comb(24-3*i-1,2);
    // }
    // cout<<res<<endl;

    cin>>n;
    int N=3*n;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin>>val[i][j];
        }
    }

    for(int i=0;i<N;i++){
        for(int j=i+1;j<N;j++){
            for(int k=j+1;k<N;k++){
                int tmp=val[i][j]+val[j][k]+val[i][k];
                int s=(1<<i)|(1<<j)|(1<<k);
                score[s]=tmp;
            }
        }
    }

    for(int i=0;i<(1<<N);i++){
        dp[i]=-INF;
    }

    dp[0]=0;
    // cout<<"   "<<(1<<N)<<endl;
    for(int s=0;s<(1<<N);s++){
        if(s==(1<<N)-1){
            continue;
        }
        if(dp[s]==-INF){
            continue;
        }

        int a=0;
        while(s&(1<<a)){
            a++;
        }
        // cout<<s<<"     "<<a<<endl;
        for(int b=a+1;b<N;b++){
            if(s&(1<<b)){
                continue;
            }

            for(int c=b+1;c<N;c++){
                if(s&(1<<c)){
                    continue;
                }

                int status=(1<<a)|(1<<b)|(1<<c);
                // cout<<"    "<<s<<' '<<a<<' '<<b<<' '<<c<<endl;
                dp[status|s]=max(dp[status|s],dp[s]+score[status]);
            }
        }
    }
    cout<<dp[(1<<N)-1]<<endl;
    return 0;
}