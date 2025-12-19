// https://www.luogu.com.cn/problem/P5363
// https://blog.csdn.net/qq_60008251/article/details/124238470
//阶梯博弈是奇数位置上的堆的尼姆博弈
//这个奇数位置指的是地面不算的第1、3、5、7堆
//如果他们的异或值为0  那么先手必败  否则必胜
//我们的思路是求出所有的方案  然后减去所有必败的方案  得到我们的答案
//具体来说  我们通过枚举二进制位来计算答案
//并且关键堆上的二进制必须为偶数   其余的无所谓
// 类似的题目还有P3480
// 阶梯博弈的思路是偶数层的操作是完全可以被抵消的  也就是偶数层的操作对答案没有任何影响
// 奇数层的石子只能拿到偶数层   但是偶数层对答案是没有影响的  也就是这些石子算是消失了 
// 虽然奇数层的石子数量可能会增加  但是这一定是从偶数层拿到奇数层的  那么对手完全可以抵消这次操作
// 也就是对奇数层进行nim博弈
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+9;
const int MAXN = 150005;
const int MAXM = 55;
const int LEN = 18;

int n,m,all;
int t1,t0;//分别表示关键堆的数量  和  非关键堆的数量
int comb[MAXM][MAXM];
int ways[MAXM];//表示任意一个二进制位上有i个1的方案数
int dp[LEN+1][MAXN];//表示二进制位处理到第i位  剩余j个空格的方案数

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(a*ans)%MOD;
        }
        a=(a*a)%MOD;
        b>>=1;
    }
    return ans;
}

int C(int a,int b){
    int ans=1;
    for(int i=1;i<=b;i++){
        ans=(ans*i)%MOD;
    }
    ans=power(ans,MOD-2);
    for(int i=a;i>=a-b+1;i--){
        ans=(ans*i)%MOD;
    }
    return ans;
}

signed main()
{
    cin>>n>>m;
    all=n-m;
    if(m>=n){
        cout<<0<<endl;
        return 0;
    }

    t1=(m+1)/2;
    t0=m+1-t1;

    for(int i=0;i<MAXM;i++){
        comb[i][0]=comb[i][i]=1;
        for(int j=1;j<=i;j++){
            comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%MOD;
        }
    }

    for(int i=0;i<=m+1;i++){
        //表示选i个1
        for(int j=0;j<=min(i,t1);j+=2){
            //枚举关键堆中1的个数  一定是偶数  这是要求
            int k=i-j;
            if(k<=t0){
                ways[i]=(ways[i]+comb[t1][j]*comb[t0][k]%MOD)%MOD;
            }
        }
    }

    int ans=C(n,m);//总方案数

    dp[0][all]=1;
    for(int i=0;i<LEN;i++){
        int val=(1<<i);
        for(int j=0;j<=all;j++){
            if(dp[i][j]==0){
                continue;
            }
            int k=min(m+1,j/val);//表示这一个二进制位上最多可以选多少个1
            for(int p=0;p<=k;p++){
                int jj=j-val*p;
                dp[i+1][jj]=(dp[i+1][jj]+dp[i][j]*ways[p]%MOD)%MOD;
            }
        }
    }

    ans=(ans-dp[LEN][0]+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}