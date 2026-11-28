// https://www.luogu.com.cn/problem/P5147
// 题意：定义随机递归 work(x)：x=1 返回 0，
// 否则等概率选 y in [1, x] 并返回 work(y)+1；
// 输入正整数 n，求 work(n) 返回值的数学期望（保留 5 位小数）。
// 数据范围：1 <= n < 2^31。
// 难度评分：1700（洛谷分级换算）
// 算法标签：数学、调和级数
#include<bits/stdc++.h>
using namespace std;
#define int long long
const double delta = 0.57721566490153286060651209;

signed main()
{
    int n;
    cin>>n;
    if(n<=1000000){
        if(n==1){
            printf("0.00000");
        }
        else{
            double ans=1;
            for(int i=1;i<n;i++){
                ans+=1.0/i;
            }
            printf("%.5lf",ans);
        }
    }
    else{
        double ans=delta+1+log(n);
        printf("%.5lf",ans);
    }
    return 0;
}