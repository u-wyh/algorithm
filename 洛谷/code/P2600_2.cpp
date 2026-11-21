// https://www.luogu.com.cn/problem/P2600
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 305;
const long double INF = 1e100L;

int n;
struct Point{
    long double x,y;
};
Point p[MAXN];

long double k[MAXN],b[MAXN];
long double ans=INF;

long double calc(int i,long double x){
    long double h=-INF;

    // 求上包络线在x处的高度
    for(int j=1;j<n;j++){
        h=max(h,k[j]*x+b[j]);
    }

    // 减去当前山坡的实际高度
    return h-(k[i]*x+b[i]);
}

void compute(){
    for(int i=1;i<n;i++){
        long double l=p[i].x;
        long double r=p[i+1].x;

        // 每段山坡上的塔高函数是凸函数
        for(int j=1;j<=100;j++){
            long double m1=l+(r-l)/3;
            long double m2=r-(r-l)/3;

            if(calc(i,m1)<calc(i,m2)){
                r=m2;
            }
            else{
                l=m1;
            }
        }

        ans=min(ans,calc(i,(l+r)/2));
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x;
    }
    for(int i=1;i<=n;i++){
        cin>>p[i].y;
    }

    for(int i=1;i<n;i++){
        k[i]=(p[i+1].y-p[i].y)/(p[i+1].x-p[i].x);
        b[i]=p[i].y-k[i]*p[i].x;
    }

    compute();

    cout<<fixed<<setprecision(3)
        <<max(0.0L,ans)<<'\n';

    return 0;
}
