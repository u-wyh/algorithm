// https://www.luogu.com.cn/problem/P3111
// 题意：输入奶牛数 N、时间 T，
// 以及按初始位置递增给出的每头牛初始位置 x_i 和速度 v_i。
// 在单向跑道上不能超车，快牛追上慢牛后必须降速并与其并入同一小组同行。
// 求经过 T 单位时间后，跑道上共有多少个奶牛小组。
// 输出一个整数表示小组数量。
// 数据范围：1 <= N <= 10^5，
// 1 <= T, x_i, v_i <= 10^9，x_i 严格递增。
// 算法标签：贪心、模拟
#include<bits/stdc++.h>

using namespace std;
long long n,t,last[100005];
struct cow
{
    long long x,y;
}a[100005];

int main()
{
    cin >> n >> t;
    for(int i=1;i<=n;i++)
    {
        cin >> a[i].y >> a[i].x;
        last[i]=a[i].y+a[i].x*t;
    }
    int res=1;
    for(int i=n-1;i>=1;i--){
        if(last[i]>=last[i+1]){
            last[i]=last[i+1];
        }else{
            res++;
        }
    }
    cout<< res;
    return 0;
}
