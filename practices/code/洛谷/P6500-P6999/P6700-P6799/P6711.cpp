// https://www.luogu.com.cn/problem/P6711
// 题意：给定一个凸包按逆时针（或依次）相邻点之间的 N 条边长 a_1..a_N
// 严格按逆时针方向输出一组满足 |x_i|,
// |y_i| <= 10^7 的凸包顶点坐标，无解输出 NO SOLUTION。
// 数据范围：3 <= N <= 1000，1 <= a_i <= 10^4。
// 难度评分：1900（洛谷分级换算）
// 算法标签：二分答案、计算几何
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;
const double PI = acos(-1);

int n,pos;
double a[MAXN];
double b[MAXN];
double ang[MAXN];

double calc1(double r){
    double res=0;
    for(int i=1;i<=n;i++){
        res+=2*asinl(b[i]/(2*r));
    }
    return res;
}

double calc2(double r){
    double res=0;
    for(int i=1;i<n;i++){
        res+=2*asinl(b[i]/(2*r));
    }
    res-=2*asinl(b[n]/(2*r));
    return res;
}

int main()
{
    cin>>n;
    double sum=0;
    double mx=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum+=a[i];
        if(a[i]>mx){
            mx=a[i];
            pos=i;
        }
    }
    for(int i=1;i<=n;i++){
        b[i]=a[(i+pos-1)%n+1];
    }

    if(mx>=sum-mx){
        cout<<"NO SOLUTION"<<endl;
        return 0;
    }

    double l=mx/2,r=l;
    if(calc1(l)>2*PI){
        while(calc1(r)>2*PI){
            r*=2;
        }
        for(int i=1;i<=200;i++){
            double mid=(l+r)/2;
            if(calc1(mid)>2*PI) l=mid;
            else r=mid;
        }

        r=(l+r)/2;
        for(int i=1;i<=n;i++){
            ang[i]=2*asinl(b[i]/(2*r));
        }
    }else{
        while(calc2(r)<=0) r*=2;

        for(int i=1;i<=200;i++){
            double mid=(l+r)/2;
            if(calc2(mid)<0) l=mid;
            else r=mid;
        }

        r=(l+r)/2;
        for(int i=1;i<=n;i++){
            ang[i]=2*asinl(b[i]/(2*r));
        }
        ang[n]=2*PI-ang[n];
    }

    double cur=0;
    cout<<fixed<<setprecision(12);

    for(int i=1;i<=n;i++){
        cout<<r*cosl(cur)<<" "<<r*sinl(cur)<<"\n";
        cur+=ang[i];
    }


    return 0;
}