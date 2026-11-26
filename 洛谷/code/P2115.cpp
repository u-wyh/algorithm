// https://www.luogu.com.cn/problem/P2115
// 题意：有 N 台排成一行的挤奶机，第 i 台产奶 M_i 单位。
// 需移除一段连续的挤奶机 [i,j]（2 <= i <= j <= N-1，至少移除 1 台且不能移除首尾）。
// 求剩余机器平均产奶量的最小值，四舍五入保留三位小数。
// 数据范围：3 <= N <= 100000，1 <= M_i <= 10000。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const double eps = 1e-5;

int n;

double nums[MAXN];
double val[MAXN];
double pre[MAXN];
double suf[MAXN];

bool check(double limit){
    for(int i=1;i<=n;i++){
        val[i]=limit-nums[i];
    }
    for(int i=1;i<=n;i++){
        pre[i]=pre[i-1]+val[i];
    }
    for(int i=n;i>=1;i--){
        suf[i]=suf[i+1]+val[i];
    }
    double maxx=pre[1];
    for(int i=3;i<=n;i++){
        if(suf[i]+maxx>0){
            return true;
        }
        maxx=max(maxx,pre[i-1]);
    }
    return false;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lf",&nums[i]);
    }
    double l=1,r=10000,ans=1;
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
    printf("%.3lf",ans);
    return 0;
}