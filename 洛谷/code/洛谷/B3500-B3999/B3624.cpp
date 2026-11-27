// https://www.luogu.com.cn/problem/B3624
// 题意：有 n 份食物，第 i 份能量是 w[i]。
// 选若干份，使总能量落在 [l, r] 内，输出可选的方案数。
// 数据范围：1 ≤ n ≤ 40，20 ≤ w[i] ≤ 100，
// 1 ≤ l ≤ r ≤ 300。
// 算法标签：深度优先搜索、剪枝

#include<bits/stdc++.h>
using namespace std;

int n,l,r;
int nums[45],ans=0,lastsum[45];

void dfs(int x,int y){
    if(y>r||y+lastsum[x]<l)
        return ;
    if(x>n){
        ans++;
        return ;
    }
    dfs(x+1,y);
    dfs(x+1,y+nums[x]);
}

int main()
{
    cin>>n>>l>>r;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    for(int i=n;i>=1;i--){
        lastsum[i]=lastsum[i+1]+nums[i];
    }
    dfs(1,0);
    printf("%d\n",ans);
    return 0;
}
