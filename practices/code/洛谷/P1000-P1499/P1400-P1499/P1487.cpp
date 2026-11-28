// https://www.luogu.com.cn/problem/P1487
// 题意：输入整数 n, m 和实数 d, A_1, A_n。
// 已知长为 n 的实数数列
// 满足 A_i = (A_{i-1} - A_{i+1})/2 + d。
// 输出第 m 项 A_m 的值，保留 3 位小数。
// 数据范围：
// 1 <= n <= 60（数列长度）
// 0 <= m <= n（查询下标）
// |d|, |A_1|, |A_n| < 10^4（实数）
// 难度评分：1600（洛谷分级换算）
// 算法标签：递推、数学
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 65;

int n,m;
long long f[MAXN];
double d,a1,an;
double k;

int main()
{
    cin>>n>>m>>d>>a1>>an;
    if(n)
    f[0]=0;
    f[1]=1;
    for(int i=2;i<n;i++){
        f[i]=2*f[i-1]+f[i-2];
    }
    if(m==0){
        printf("0.000");
        return 0;
    }
    if(a1==d){
        printf("%.3lf",d);
        return 0;
    }
    an=(an-d)/(a1-d);
    long long a=f[n-2];
    long long b=f[n-1];
    if(n%2==0){
        k=1.0*(an+a)/b;
    }
    else{
        k=1.0*(a-an)/b;
    }
    a=f[m-2];
    b=f[m-1];
    double kk;
    if(m%2==0){
        kk=1.0*k*b-a;
    }
    else{
        kk=1.0*a-1.0*b*k;
    }
    double ans=(a1-d)*kk;
    ans+=d;
    printf("%.3lf",ans);
    return 0;
}