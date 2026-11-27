#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXB = 30;
const int INF = 1<<30;

int n;
int val[MAXN];

int compute(int x,int mask,int limit){
    int dp[2]={INF,INF};
    dp[0]=0;
    for(int p=MAXB-1;p>=0;p--){
        int ndp[2]={INF,INF};
        int lb=(limit>>p)&1;

        for(int s=0;s<=1;s++){
            if(dp[s]==INF){
                continue;
            }

            for(int b=0;b<=1;b++){
                if(((mask>>p)&1)==0&&b!=((x>>p)&1)){
                    continue;
                }

                if(s==0&&b<lb){
                    continue;
                }

                int ns=s;
                if(s==0&&b>lb){
                    ns=1;
                }

                int val=dp[s]|(b<<p);
                ndp[ns]=min(ndp[ns],val);
            }
        }
        dp[0]=ndp[0];
        dp[1]=ndp[1];

        if(dp[0]==dp[1]&&dp[0]==INF){
            return -1;
        }
    }

    int ans=min(dp[0],dp[1]);
    return ans;
}

bool check(int mask){
    int pre=0;
    for(int i=1;i<=n;i++){
        int cur=compute(val[i],mask,pre);
        if(cur==-1){
            return false;
        }
        pre=cur;
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>val[i];
        }

        int ans=0;
        for(int p=MAXB-1;p>=0;p--){
            int mask=ans|((1<<p)-1);
            if(!check(mask)){
                ans|=(1<<p);
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}