// https://www.luogu.com.cn/problem/P2110
// 题意：给定两个整数 L 和 R，
// 求闭区间 [L,R] 内满足十进制最高位与最低位相等的整数个数。
// 输出满足条件的整数个数。
// 数据范围：1 <= L <= R <= 10^18。
// 难度评分：1600（洛谷分级换算）
// 算法标签：数学、前缀和
#include<bits/stdc++.h>
using namespace std;

long long l,r;

long long sum(long long val){
    if(val<10){
        return val;
    }
    long long a=val%10;
    long long ans=val/10+9;
    long long b=val;
    while(b>10){
        b/=10;
    }
    if(b>a){
        ans--;
    }
    return ans;
}

int main()
{
    cin>>l>>r;
    cout<<sum(r)-sum(l-1)<<endl;
    return 0;
}
