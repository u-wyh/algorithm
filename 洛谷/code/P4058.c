// https://www.luogu.com.cn/problem/P4058
// 题意：第一行输入树的数量 n、订单总量 S 和单块木料最小长度要求 L；第二行输入初始树高 H_1..H_n，第三行输入每月生长高度 A_1..A_n。
// 只能整棵砍下长度不小于 L 的树来凑足总长度不少于 S 的木料，求最少需要等待多少个月才能完成订单。
// 输出一行一个整数表示最少月数。
// 数据范围：对于全部测试点，1 <= n <= 200000，1 <= S, L <= 10^{18}，1 <= H_i, A_i <= 10^9。
#include<stdio.h>
#include<stdbool.h>
// 算法标签：二分答案

#define MAX 100000000+5

long long  h[MAX],a[MAX];
long long  s,L;
int n;

bool check(long long  x){
    long long  ans=0;
    for(int i=1;i<=n;i++){
        if((a[i]*x+h[i])>=L)
            ans+=(a[i]*x+h[i]);
        if(ans>=s)
            return true;
    }
    return false;
}

int main()
{
    scanf("%d %lld %lld",&n,&s,&L);
    for(int i=1;i<=n;i++){
        scanf("%lld",&h[i]);
    }
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    long long l=1,r=1e8,mid,ans;
    while(l<=r){
        mid=l+((r-l)>>1);
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
