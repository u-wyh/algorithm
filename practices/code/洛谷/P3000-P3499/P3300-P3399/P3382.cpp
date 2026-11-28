// https://www.luogu.com.cn/problem/P3382
// 题意：给 n 次多项式 f 和区间 [l, r]，
// 输入的 n + 1 个系数按次数从高到低排列。
// 区间内存在一点 x，使函数在 x 左侧递增、右侧递减。
// 输出这个峰值点的横坐标 x。
// 答案的横坐标或对应函数值，任一项的绝对或相对误差不超过 10^-5 即可。
// 数据范围：满分数据中 6 ≤ n ≤ 13，系数在 [-100, 100]，
// -10 ≤ l ≤ r ≤ 10。
// 系数以及 l、r 最多有 15 位小数。
// 难度评分：1200（洛谷分级换算）
// 算法标签：三分查找

#include<bits/stdc++.h>
using namespace std;
const double eps=1e-10;

int n;
double l,r;
double arr[14];

int main()
{
    cin>>n>>l>>r;
    double ans=0;
    for(int i=n;i>=0;i--){
        cin>>arr[i];
    }
    while(r-l>=eps){
        double midl=(r-l)/3+l;
        double midr=(r-l)/3*2+l;
        double k1=0;
        for(int i=0;i<=n;i++){
            k1+=arr[i]*pow(midl,i);
        }
        double k2=0;
        for(int i=0;i<=n;i++){
            k2+=arr[i]*pow(midr,i);
        }
        if(k1<=k2){
            l=midl;
            ans=midr;
        }
        else{
            r=midr;
            ans=midl;
        }
    }
    printf("%.8lf",ans);
    return 0;
}