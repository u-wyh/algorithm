// https://www.luogu.com.cn/problem/P1672
// 题意：某日运来 F1 份饲料，直到第 D 天吃完后还剩 F2。
// 每头牛从到达日至离开日每天吃一份，运来当天也计当天消耗。
// 求符合消耗量的最晚到货日期。
// 数据范围：1 ≤ C ≤ 100，1 ≤ F2 ≤ F1 ≤ 10^6，
// 1 ≤ D ≤ 2000。
// 算法标签：差分、枚举

#include<bits/stdc++.h>
using namespace std;

int f1,f2,n,D;
int nums[2005],sum[2005];

int main()
{
    cin>>n>>f1>>f2>>D;
    int a,b;
    for(int i=1;i<=n;i++){
        cin>>a>>b;
        nums[a]+=1;
        if(b>=D)
            nums[D+1]+=-1;
        else
            nums[b+1]+=-1;
    }
    for(int i=1;i<=D;i++){
        nums[i]+=nums[i-1];
    }
    int f=f1-f2;
    for(int i=D;i>=1;i--){
        f-=nums[i];
        if(f==0){
            cout<<i;
            return 0;
        }
    }
    return 0;
}
