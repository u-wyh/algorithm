// https://www.luogu.com.cn/problem/P5202
// 题意：给定长为 n、只含字符 H 和 G 的字符串，将其划分为若干个长度在 [1, k] 之间的连续区间。
// 求划分后满足「G 的数量不少于 H 的数量」的区间的最小可能个数。
// 数据范围：1 <= k <= n <= 3*10^5，字符串长度为 n 且只含 H 和 G。
#include<bits/stdc++.h>
// 算法标签：单调队列、动态规划、前缀和
using namespace std;
const int MAXN = 3e5+5;

int n,m;
char s[MAXN];
int sum[MAXN],dp[MAXN];
int q[MAXN],head,tail;

int main()
{
    cin>>n>>m;
    scanf("%s",s+1);
    for(int i=1;i<=n;i++){
        if(s[i]=='H'){
            sum[i]=1+sum[i-1];
        }
        else{
            sum[i]=sum[i-1]-1;
        }
        //cout<<sum[i]<<' ';
    }
    q[tail++]=0;
    for(int i=1;i<=n;i++){
        while(head<tail&&i-q[head]>m){
            head++;
        }
        dp[i]=dp[q[head]]+(sum[i]<=sum[q[head]]);
        while(head<tail&&(dp[i]<dp[q[tail-1]])||(dp[i]==dp[q[tail-1]]&&sum[q[tail-1]]>sum[i])){
            tail--;
        }
        q[tail++]=i;
    }
    cout<<dp[n]<<endl;
    return 0;
}
