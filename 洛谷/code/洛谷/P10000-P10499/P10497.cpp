// https://www.luogu.com.cn/problem/P10497
// 题意：n 头牛的编号是 1 到 n，各出现一次。
// 对队列中除第一位外的每个位置，给出它前面编号比它小的牛数。
// 恢复从前到后的编号，每行输出一头牛。
// 数据范围：2 ≤ n ≤ 8000，第 i 位的计数在 [0,i-1] 内。
// 算法标签：贪心、线性扫描

#include<bits/stdc++.h>
using namespace std;
int n,a[10001],s,st[10001];
bool vis[10001];
int main()
{
  cin>>n;
  for(int i = 2;i <= n;i++)
    cin>>a[i];
  for(int i = n;i >= 1;i--){
    s = 0;
    for(int j = 1;j <= n;j++)
      if(vis[j] == 0)
      {
            s++;
        if(s == a[i] + 1)
        {
            vis[j] = 1;
            st[i] = j;
            break;
        }
      }
  }
  for(int i = 1;i <= n;i++) cout<<st[i]<<'\n';
  return 0;
}
