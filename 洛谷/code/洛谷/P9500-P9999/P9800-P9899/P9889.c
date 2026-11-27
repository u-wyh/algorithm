// https://www.luogu.com.cn/problem/P9889
// 题意：多组数据（共 T 组）。
// 直线上房屋东边 1..n 米处有 n 株植物，初始防御值 d_i = 0，
// 生长速度 a_i。
// 机器人从房屋（坐标 0）出发，
// 至多移动 m 步（每步向东或向西走 1 米，可走到 <= 0 或 > n 处），
// 到达某植物位置时为其加 a_i 防御值。
// 求最大化 min_{1 <= i <= n} d_i。
// 题意：第一行输入 T，每组输入 n, m 及 a_1..a_n；
// 每组输出一行一个整数。
// 数据范围：2 <= n <= 10^5，0 <= m <= 10^12，
// 1 <= a_i <= 10^5
// sum(n) <= 10^6（未显式给出 T 上界，受 sum(n) 限制）。
// 算法标签：二分答案、贪心
#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define MAX 100000+5

int t;
long long n,m,a[MAX],d[MAX];

bool check(long long x){
    memset(d,0,sizeof(d));
    m-=1;
    for(int i=1;i<=n;i++){
        d[i]+=a[i];
        if(d[i]<x){
            //d[i]+=a[i]*((x-d[i]+a[i]-1)/a[i]);
            d[i+1]+=a[i+1]*((x-d[i]+a[i]-1)/a[i]);
            m-=2*((x-d[i]+a[i]-1)/a[i]);
        }else
            continue;
        if(m<0)
            return false;
        m--;
    }
    return true;
}

int main()
{

    scanf("%d",&t);
    while(t--){
        scanf("%lld %lld",&n,&m);
        for(int i=1;i<=n;i++){
            scanf("%lld",&a[i]);
        }
        long long l=0,r=1e18,mid,ans;
        while(l<=r){
            mid=(l+r)/2;
            if(check(mid)){
                ans=mid;
                l=mid+1;
            }else{
                r=mid-1;
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
