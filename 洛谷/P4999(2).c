#include <stdio.h>
#include <stdlib.h>
#define mod 1000000007

long long count(long long num, int d) {
    long long ans = 0;
    for (long long right = 1, tmp = num, left, cur; tmp != 0; right *= 10, tmp /= 10) {
        left = tmp / 10;
        //left是这一位左边可以有的情况数  从0开始
        if (d == 0) {
            left--;
        }
        //如果d就是0   那么left从1开始
        ans =(ans+(left * right)%mod)%mod;
        //ans首先是左边的情况种类和右边相乘
        cur = tmp % 10;
        //cur是当前位置上的数字
        if (cur > d) {
            ans =(ans+ (right%mod))%mod;
            //如果cur大于d   那么左边情况要加上1  右边是从0  到right-1
        } else if (cur == d) {
            ans =(ans+((num % right)%mod)+1)%mod;
            //如果cur等于d   那么就是把右边剩余的数字加上
        }
    }
    return ans;
}
//right的取值始终都是10 100 1000 10000 这样的数字

long long digitsCount(int d, long long  a, long long b) {
    return (count(b, d)%mod - count(a - 1, d)%mod +mod)%mod;
}
//d的含义是数码d  0 1 2 3 4 5 6 7 8 9
//计算从a到b的所有数字的数码个数   相当于求从1到b的  减去从1到a的

int main() {
    int t;
    scanf("%d",&t);
    long long a, b;
    while(t--)
    {
        scanf("%lld %lld",&a,&b);
        long long ans=0;
        for (int i = 1; i <= 9; i++) {
            ans=(ans+(digitsCount(i,a,b)*i)%mod)%mod;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
