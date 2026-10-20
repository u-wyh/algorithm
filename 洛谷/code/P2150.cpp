// https://www.luogu.com.cn/problem/P2150
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int MAXS = (1<<8);
const int prime[8] = {2,3,5,7,11,13,17,19};

int n,p;

// dp[i][j]：G和W占用的小质因数集合
int dp[MAXS][MAXS];
int g[MAXS][MAXS];
int h[MAXS][MAXS];

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>p;

    // 按照大质因数分组
    // 每组存储对应数字的小质因数状态
    map<int,vector<int>> groups;

    for(int x=2;x<=n;x++){
        int tmp=x;
        int mask=0;

        // 提取8个小质因数
        for(int i=0;i<8;i++){
            if(tmp%prime[i]==0){
                mask|=(1<<i);

                while(tmp%prime[i]==0){
                    tmp/=prime[i];
                }
            }
        }

        // tmp=1说明没有大质因数
        // 这种数字需要单独分组
        int key;
        if(tmp==1){
            key=-x;
        }else{
            key=tmp;
        }

        groups[key].push_back(mask);
    }

    dp[0][0]=1%p;

    // 枚举每个大质因数组
    for(auto &[key,items]:groups){

        // g：本组全部只能给G
        // h：本组全部只能给W
        memcpy(g,dp,sizeof(dp));
        memcpy(h,dp,sizeof(dp));

        for(int mask:items){

            // 倒序枚举，保证每个数字只选一次
            for(int i=MAXS-1;i>=0;i--){
                for(int j=MAXS-1;j>=0;j--){

                    if(i&j)continue;

                    // 当前数字交给G
                    if((mask&j)==0){
                        int ni=i|mask;

                        g[ni][j]+=g[i][j];
                        if(g[ni][j]>=p){
                            g[ni][j]-=p;
                        }
                    }

                    // 当前数字交给W
                    if((mask&i)==0){
                        int nj=j|mask;

                        h[i][nj]+=h[i][j];
                        if(h[i][nj]>=p){
                            h[i][nj]-=p;
                        }
                    }
                }
            }
        }

        // 合并两种情况
        // 减去本组一个都不选的重复部分
        for(int i=0;i<MAXS;i++){
            for(int j=0;j<MAXS;j++){
                dp[i][j]=g[i][j]+h[i][j]-dp[i][j];

                if(dp[i][j]<0){
                    dp[i][j]+=p;
                }
                if(dp[i][j]>=p){
                    dp[i][j]-=p;
                }
            }
        }
    }

    int ans=0;

    for(int i=0;i<MAXS;i++){
        for(int j=0;j<MAXS;j++){
            if(i&j)continue;

            ans+=dp[i][j];
            if(ans>=p){
                ans-=p;
            }
        }
    }

    cout<<ans<<"\n";
    return 0;
}