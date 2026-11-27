// https://www.luogu.com.cn/problem/P8677
// 题意：n 个油井由 n - 1 条道路连成一棵树。
// 任选一个油井建空运站，从这里出发，
// 沿道路走遍所有油井并运回设备。
// 建第 i 个油井时至少要有 B_i 人，
// 建成后要留下 S_i 人，不能再参与后续建造。
// 第 i 条道路连接 i + 1 与 a，长度为 b。
// 输出：最短运输路程及此路程下最少初始人数。
// 数据范围：1 <= n <= 10^5。
// B_i、S_i 和 b 均为 1 到 10000 的整数。
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
