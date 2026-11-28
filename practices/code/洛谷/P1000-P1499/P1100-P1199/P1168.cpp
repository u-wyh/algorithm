// https://www.luogu.com.cn/problem/P1168
// 题意：给 N 个数。对长度为 1、3、5 等的每个前缀，求排序后正中间的数。
// 按照前缀变长的顺序逐行输出。
// 数据范围：1 ≤ N ≤ 10^5，0 ≤ A[i] ≤ 10^9。
// 难度评分：1200（洛谷分级换算）
// 算法标签：二分查找

#include <bits/stdc++.h>
using namespace std;
int n;
vector<int>a;
int main()
{
    cin>>n;
    for(int i=1,x;i<=n;i++){
        cin>>x;
        a.insert(upper_bound(a.begin(),a.end(),x),x);//二分插入保证单调性
        if(i%2==1){
        	printf("%d\n",a[(i-1)/2]);//是奇数个就输出
        }
    }
    return 0;
}
