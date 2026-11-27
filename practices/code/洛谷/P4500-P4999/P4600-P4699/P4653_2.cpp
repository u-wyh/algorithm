// https://www.luogu.com.cn/problem/P4653
// 题意：有 n 组灯泡，每组含 A、B 各一个并有权值，每选一个花 1 代价，
// 最后只点亮 A 类或 B 类中某一类
// 求最大化的最小可能净收益（保留 4 位小数）。
// 数据范围：
// 0 <= n <= 10^5，1.0 <= A_i,
// B_i <= 1000.0（最多四位小数）。
// 算法标签：贪心、双指针、排序
#include<bits/stdc++.h>
using namespace std;

int n;
double a[100005],b[100005];

int cmp(double a,double b){
    return a>b;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i]>>b[i];
    sort(a+1,a+n+1,cmp);
    sort(b+1,b+n+1,cmp);
    int l=0,r=1;
    double suma=0,sumb=0,ans=0;
    for(r=1;r<=n;r++){
        sumb+=b[r];
        ans=max(ans,min(suma-l-r,sumb-l-r));
        while(suma<sumb&&l<n){
            suma+=a[++l];
            ans=max(ans,min(suma-l-r,sumb-l-r));
        }
    }
    printf("%.4lf\n",ans);
    return 0;
}
