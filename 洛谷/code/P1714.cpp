// https://www.luogu.com.cn/problem/P1714
// 题意：给定 n 块蛋糕的幸运值 p_i，选连续的 1 到 m 块，求幸运值之和最大是多少。
// 数据范围：1 ≤ m ≤ n ≤ 5×10^5，绝对值 （p_i） ≤ 500，答案绝对值 ≤ 2^31−1。

#include<bits/stdc++.h>
using namespace std;

int n,m;
int nums[500005];
int q[500005];
int h=0,t=0;
int ans=0;

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        nums[i]+=nums[i-1];
        //printf("%3d",nums[i]);
    }
    //printf("\n");
    for(int i=0;i<=n;i++){
        while(h<t&&i-q[h]>m){
            h++;
        }
        //ans=max(ans,nums[i]-nums[q[h]]);
        while(h<t&&nums[i]<=nums[q[t-1]]){
            t--;
        }
        q[t++]=i;
        ans=max(ans,nums[i]-nums[q[h]]);
    }
    cout<<ans;
    return 0;
}
