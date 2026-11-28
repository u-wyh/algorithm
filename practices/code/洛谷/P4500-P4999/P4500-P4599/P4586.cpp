// https://www.luogu.com.cn/problem/P4586
// 题意：多组数据，给定平面上 n 个点，用两个半径相同的圆覆盖所有点，
// 求所需的最小圆半径（保留两位小数）。
// 数据范围：n <= 1000，
// |x_i|, |y_i| <= 10^5，T <= 10。
// 难度评分：3000（洛谷分级换算）
// 算法标签：最小圆覆盖、计算几何、二分答案
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const double PI = acos(-1);
const double EPS = 1e-8;

int n;
struct Point{
    double x,y;
};
Point p[MAXN];
Point origin[MAXN];
Point val[MAXN];

struct Circle{
    Point p;
    double r;
};
Circle C;

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

Point operator+(Point a,Point b){
    return {a.x+b.x,a.y+b.y};
}

Point operator/(Point a,double k){
    return {a.x/k,a.y/k};
}

double operator*(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

Point operator*(Point a,double k){
    return {a.x*k,a.y*k};
}

double len(Point a){
    return sqrt(a.x*a.x+a.y*a.y);
}

double dis(Point a,Point b){
    return len(a-b);
}

Circle cover(Point a,Point b){
    return {(a+b)/2,dis(a,b)/2};
}

Point rorate(Point a,double b){
    return {a.x*cos(b)-a.y*sin(b),a.x*sin(b)+a.y*cos(b)};
}

pair<Point,Point> midperp(Point a,Point b){
    Point v=b-a;
    return {(a+b)/2,{-v.y,v.x}};
}

Point cross(Point a,Point u,Point b,Point v){
    double t=(a-b)*v/(v*u);
    return a+u*t;
}

Circle cover(Point a,Point b,Point c){
    auto u=midperp(a,b),v=midperp(a,c);

    // 三点共线时，取最远两点确定的圆
    if(fabs(v.second*u.second)<EPS){
        Circle c1=cover(a,b);
        Circle c2=cover(a,c);
        Circle c3=cover(b,c);

        if(c1.r>=c2.r && c1.r>=c3.r){
            return c1;
        }
        if(c2.r>=c3.r){
            return c2;
        }
        return c3;
    }

    Point o=cross(u.first,u.second,v.first,v.second);
    return {o,dis(o,a)};
}

// 求区间 [l,r] 的最小圆覆盖
void increment(int l,int r){
    if(l>r){
        C={{0,0},0};
        return;
    }

    for(int i=l;i<=r;i++){
        val[i]=p[i];
    }
    random_shuffle(val+l,val+r+1);

    C={val[l],0};

    for(int i=l+1;i<=r;i++){
        if(C.r+EPS<dis(C.p,val[i])){
            C={val[i],0};

            for(int j=l;j<i;j++){
                if(C.r+EPS<dis(C.p,val[j])){
                    C=cover(val[i],val[j]);

                    for(int k=l;k<j;k++){
                        if(C.r+EPS<dis(C.p,val[k])){
                            C=cover(val[i],val[j],val[k]);
                        }
                    }
                }
            }
        }
    }
}

bool cmp(Point a,Point b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    return a.y<b.y;
}

double solve(){
    if(n<=2){
        return 0;
    }

    double ans=1e18;

    // 枚举分割直线的方向
    for(int a=0;a<180;a++){
        double rad=a*PI/180;

        // 旋转点集
        for(int i=1;i<=n;i++){
            p[i]=rorate(origin[i],rad);
        }

        sort(p+1,p+n+1,cmp);

        // 二分分割位置
        int l=1,r=n-1;

        while(l<=r){
            int mid=(l+r)>>1;

            increment(1,mid);
            double r1=C.r;

            increment(mid+1,n);
            double r2=C.r;

            ans=min(ans,max(r1,r2));

            // 当前两边半径均超过答案，可以剪枝
            if(min(r1,r2)>ans+EPS){
                break;
            }

            if(r1<r2){
                l=mid+1;
            }
            else{
                r=mid-1;
            }
        }
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout<<fixed<<setprecision(2);

    while(cin>>n && n){
        for(int i=1;i<=n;i++){
            cin>>origin[i].x>>origin[i].y;
        }

        cout<<solve()<<endl;
    }

    return 0;
}