// https://www.luogu.com.cn/problem/P12848
// 题意：n 槽位初始第 n 槽为空，前 n-1 槽有石块，求加最少边使石块归位。
// 输入：首行 n，次行 n-1 个互异整数 a_1..a_{n-1}（初始槽中石块编号）。
// 规则：初始 i 与 i+1 相连；空槽可移入相邻槽石块；加一条新边代价为 1。
// 输出：输出使所有石块 i 都能移到第 i 槽所需的最小加边代价。
// 数据范围：1 <= n <= 3*10^5，1 <= a_i < n 且互不相同。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

int n;
int nums[MAXN];

int main()
{
    cin>>n;
    for(int i=1;i<n;i++){
        cin>>nums[i];
    }
    int l=0,r=0;
    for(int i=1;i<n;i++){
        if(nums[i]!=i){
            l=i;
            break;
        }
    }
    for(int i=n-1;i>=1;i--){
        if(nums[i]!=i){
            r=i;
            break;
        }
    }
    if(l==0&&r==0){
        cout<<0<<endl;
        return 0;
    }
    int flag=0;
    for(int i=l+1;i<=r;i++){
        if(nums[i]!=nums[i-1]+1){
            flag++;
        }
    }
    if(flag<=1){
        cout<<1<<endl;
    }
    else{
        cout<<2<<endl;
    }
    return 0;
}