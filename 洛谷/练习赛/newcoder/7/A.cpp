#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXB = 30;
const int INF = 1<<30;

int n;
int a[MAXN];

// 求能够由 x 得到的、不小于 lim 的最小值
int getmin(int x,int mask,int lim){
    int dp[2]={INF,INF};
    dp[0]=0;

    for(int p=MAXB-1;p>=0;p--){
        int ndp[2]={INF,INF};
        int lb=(lim>>p)&1;

        for(int s=0;s<2;s++){
            if(dp[s]==INF)
                continue;

            for(int b=0;b<=1;b++){
                // 这一位不能修改，只能保持 x 原来的值
                if(((mask>>p)&1)==0&&b!=((x>>p)&1))
                    continue;

                // 前面仍然和 lim 相等，则当前位不能比 lim 小
                if(s==0&&b<lb)
                    continue;

                int ns=s;
                if(s==0&&b>lb)
                    ns=1;

                int val=dp[s]|(b<<p);
                ndp[ns]=min(ndp[ns],val);
            }
        }

        dp[0]=ndp[0];
        dp[1]=ndp[1];
    }

    int ans=min(dp[0],dp[1]);

    if(ans==INF)
        return -1;

    return ans;
}

// 判断开放 mask 中的位后，能否使数组单调不下降
bool check(int mask){
    int pre=0;

    for(int i=1;i<=n;i++){
        int cur=getmin(a[i],mask,pre);

        if(cur==-1)
            return false;

        pre=cur;
    }

    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin>>T;

    while(T--){
        cin>>n;

        for(int i=1;i<=n;i++)
            cin>>a[i];

        int ans=0;

        // 从高位到低位确定答案
        for(int p=MAXB-1;p>=0;p--){
            // 当前位暂时不选，低位全部开放
            int mask=ans|((1<<p)-1);

            if(!check(mask))
                ans|=1<<p;
        }

        cout<<ans<<"\n";
    }

    return 0;
}