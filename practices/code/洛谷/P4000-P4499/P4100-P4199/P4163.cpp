// https://www.luogu.com.cn/problem/P4163
// 题意：多组询问，每组给一个只含数字 0~9 的字符串 s 和正整数 d，
// 求 s 有多少种不同的排列（允许前导 0）能被 d 整除。
// 数据范围：1 <= T <= 15，|s| <= 10，
// 1 <= d <= 1000。
// 难度评分：2000（洛谷分级换算）
// 算法标签：状态压缩动态规划、组合数学
#include<bits/stdc++.h>
using namespace std;

int dp[1024][1005];
int fac[10];
int cnt[10];

int main()
{
    int T;
    cin>>T;
    fac[0]=1;
    for(int i=1;i<=10;i++){
        fac[i]=i*fac[i-1];
    }
    while(T--){
        string str;
        cin>>str;
        int n,m;
        cin>>m;
        n=str.length();
        for(int i=0;i<(1<<n);i++){
            for(int j=0;j<m;j++){
                dp[i][j]=0;
            }
        }
        for(int i=0;i<=9;i++){
            cnt[i]=0;
        }
        dp[0][0]=1;
        for(int i=1;i<(1<<n);i++){
            for(int j=0;j<n;j++){
                if(i&(1<<j)){
                    for(int k=0;k<m;k++){
                        dp[i][(k*10+str[j]-'0')%m]+=dp[i-(1<<j)][k];
                    }
                }
            }
        }
        for(int i=0;i<n;i++){
            cnt[str[i]-'0']++;
        }
        int ans=dp[(1<<n)-1][0];
        for(int i=0;i<=9;i++){
            ans/=fac[cnt[i]];
        }
        cout<<ans<<endl;
    }
    return 0;
}