// https://www.luogu.com.cn/problem/P4873
// 题意：有 N 头奶牛按初始位置递增站在无限长跑道上，各以恒定速度跑 T 分钟，同一赛道内的任意两头奶牛任意时刻不能处于同一位置（不能追上或超越）
// 求最少需要多少条赛道。
// 数据范围：1 <= N <= 10^5，1 <= T, v_i <= 10^9，0 <= x_i <= 10^9。
#include<bits/stdc++.h>
// 算法标签：贪心、二分查找、最长上升子序列
using namespace std;
#define int long long

long long a[100010],c[100010],top,n,t;

//int fun(long long num){
//    int l = 1, r = top, ans = 0; // 将 ans 初始化为 0，表示如果找不到则应该插入的位置
//    while(l <= r){
//        int mid = l + (r - l) / 2; // 避免整数溢出
//        if(c[mid] >= num){
//            ans = mid; // 更新 ans 为当前 mid，因为 c[mid] >= num
//            r = mid - 1; // 继续在左半部分查找
//        } else {
//            l = mid + 1; // 在右半部分查找
//        }
//    }
//    return ans;
//}

int fun(long long num){
    int l=1,r=top,ans=0;
    while(l<=r){
        //cout<<666<<endl;
        int mid=l+(r-l)/2;
        if(c[mid]>num){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

signed main()
{
    long long p,v;
    cin>>n>>t;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld%lld",&p,&v);
        a[i]=p+v*t;
    }
    for(int i=n;i>=1;i--)
    {
        if(!top||a[i]>=c[top])
            c[++top]=a[i];
        else{
            int t=fun(a[i]);
            //system("pause");
            c[t]=a[i];
        }
    }
    printf("%lld\n",top);
}
