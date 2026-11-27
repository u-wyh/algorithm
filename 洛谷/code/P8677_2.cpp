// https://www.luogu.com.cn/problem/P8677
// 题意：输入 n、建设需求 B_1..B_n、维护人数 S_1..S_n 和 n-1 条带权无向树边；
// 任选一点建立空运站，从空运站出发沿树边运送设备建好所有油井后返回空运站（边可重复走），建第 i 个油井时当前可用人数须 >= B_i
// 建成后须永久留下 S_i 人维护；
// 输出最短总运输路程以及在总路程最短下的最少初始总人数。
// 数据范围：1 <= n <= 10^5，B_i, S_i 与边权 b（原文误写 c）均为不超过 10000 的正整数。
// 贪心 O(nlogn)
// 算法标签：贪心、排序
#include<bits/stdc++.h>
#define N 100010
using namespace std;

int n,B[N],S[N],t[N],len,ans,mx;

int main(){
  scanf("%d",&n);
  for(int i=1;i<=n;++i)scanf("%d",&B[i]),mx=max(mx,B[i]);
  for(int i=1;i<=n;++i)
    scanf("%d",&S[i]),ans+=S[i],t[i]=B[i]-S[i];
  for(int i=2,a,b;i<=n;++i){
    scanf("%d%d",&a,&b);
    len+=b*2;
  }
  sort(t+1,t+n+1);
  ans+=max(t[1],0);
  ans=max(ans,mx);
  printf("%d %d\n",len,ans);
}
