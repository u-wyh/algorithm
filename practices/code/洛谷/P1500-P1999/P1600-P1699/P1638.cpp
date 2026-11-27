// https://www.luogu.com.cn/problem/P1638
// 题意：给 n 幅按顺序展出的画，每幅有画家编号。
// 买票只能看一段连续画作，要包含所有 m 位画家的作品。
// 输出最短的一段的左右端点，多解取左端点最小。
// 数据范围：1 ≤ n ≤ 10^6，1 ≤ a[i] ≤ m ≤ 2000，
// 保证有解。
// 算法标签：双指针

#include<bits/stdc++.h>
using namespace std;

int n,m;
int a[1000005];
int sum[2005];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    int l=1,r=1,num=0,ans=n,ans1=1,ans2=n;
    while(l<=r&&r<=n+1){
        if(num<m){
            r++;
            sum[a[r-1]]++;
            if(sum[a[r-1]]==1)
                num++;
        }else{
            if(ans>r-l){
                ans=r-l;
                ans1=l;
                ans2=r-1;
            }
            sum[a[l]]--;
            if(sum[a[l]]==0)
                num--;
            l++;
        }
    }
    cout<<ans1<<' '<<ans2;
    return 0;
}
