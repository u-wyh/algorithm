// https://www.luogu.com.cn/problem/P1901
// 题意：一排 N 座塔，每座高度互异。第 i 座向左右各发出 V_i 能量，每侧只有最近且比它高的塔能接收。求接收能量最多的塔收到了多少。
// 数据范围：1 ≤ N ≤ 10^6，1 ≤ H_i ≤ 2×10^9，1 ≤ V_i ≤ 10^4，答案在有符号 32 位整数范围内。
// 算法标签：单调栈

#include<bits/stdc++.h>
using namespace std;

const int maxn=1e6+10;
int s1[maxn],h[maxn],v[maxn],sum[maxn],ans,n,top;

int main()
{
   cin>>n;
   for(int i=1;i<=n;i++){
   	cin>>h[i]>>v[i];
   	while(top&&h[s1[top]]<h[i])
        sum[i]+=v[s1[top--]];
   	sum[s1[top]]+=v[i];
   	s1[++top]=i;
   }
   for(int i=1;i<=n;i++)
        ans=max(ans,sum[i]);
   cout<<ans;
   return 0;
}
