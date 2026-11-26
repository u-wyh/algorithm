// https://www.luogu.com.cn/problem/P2866
// 题意：N 头牛站成一排面向右（第 N 头在最前），第 i 头身高 h_i。
// 每头牛能看到前面连续严格比它矮的牛，求所有牛能看到的牛数量总和。
// 输出总数。
// 数据范围：1 <= N <= 8*10^4，1 <= h_i <= 10^9。
#include<bits/stdc++.h>
using namespace std;

int n;
int nums[80005];
int q[80005];
int r=0;
long long ans=0;

int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>nums[i];
    for(int i=0;i<n;i++){
        while(r>0&&nums[q[r-1]]<=nums[i]){
            ans+=(i-q[--r]-1);
            //printf("%d\n",ans);
        }
        q[r++]=i;
    }
    while(r>0){
        ans+=(n-1-q[--r]);
        //printf("%d\n",ans);
    }
    cout<<ans;
    return 0;
}
