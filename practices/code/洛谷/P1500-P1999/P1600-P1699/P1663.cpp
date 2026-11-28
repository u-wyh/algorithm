// https://www.luogu.com.cn/problem/P1663
// 题意：给山的截面折线，从左到右给各折点。
// 求灯放在能照到山上所有部位的位置时，灯的最小纵坐标。
// 数据范围：1 ≤ N ≤ 5000，横坐标严格递增，
// 0 ≤ X[i],Y[i] ≤ 100000，答案不超过 10^6，
// 容许绝对误差 0.01。
// 难度评分：1900（洛谷分级换算）
// 算法标签：二分答案、计算几何

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5005;
const double eps = 1e-4;

int n;
double x[MAXN],y[MAXN];
double k[MAXN],b[MAXN];

bool check(double y){
    double l=-1e9,r=1e9;
    for(int i=2;i<=n;i++){
        if(k[i]>0){
            r=min(r,(y-b[i])/k[i]);
        }
        else if(k[i]<0){
            l=max(l,(y-b[i])/k[i]);
        }
        else{
            if(b[i]>y){
                return 0;
            }
        }
    }
    return l<=r;
}

int main()
{
    cin>>n>>x[1]>>y[1];
    for(int i=2;i<=n;i++){
        cin>>x[i]>>y[i];
        k[i]=(y[i]-y[i-1])/(x[i]-x[i-1]);
        b[i]=y[i]-k[i]*x[i];
    }
    double l=0,r=1000000,ans=0;
    while(r-l>=eps){
        double mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            r=mid;
        }
        else{
            l=mid;
        }
    }
    printf("%.2lf\n",ans);
    return 0;
}