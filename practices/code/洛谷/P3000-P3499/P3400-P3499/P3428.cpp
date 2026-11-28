// https://www.luogu.com.cn/problem/P3428
// 题意：输入空降士兵数量 n，
// 以及按跳伞顺序给出的每位士兵的着陆坐标 (x_i, y_i) 和生存半径
// r_i。
// 第 i 个士兵着陆时前 i-1 人均已着陆；
// 若隐藏炸弹到某士兵距离 <= 其生存半径，该士兵引爆炸弹并牺牲，
// 需在最坏情况下仍有至少一名士兵生还。
// 若能做到，输出最少需派出的前若干名士兵数量；否则输出 NIE。
// 数据范围：2 <= n <= 2000，
// -1000 <= x_i, y_i <= 1000，
// 1 <= r_i <= 5000。
// 难度评分：2400（洛谷分级换算）
// 算法标签：计算几何
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e3+5;
const long double eps = 1e-8L;

int n;
struct Point{
    long double x,y;
};
struct Circle{
    int x,y,r;
};
Circle circle[MAXN];

bool inside(Point p,int id){
    long double dx=p.x-circle[id].x;
    long double dy=p.y-circle[id].y;
    return dx*dx+dy*dy<=(long double)circle[id].r*circle[id].r+eps;
}


bool getpair(int i,int j,Point &p){
    int dx=circle[i].x-circle[j].x;
    int dy=circle[i].y-circle[j].y;
    int d2=dx*dx+dy*dy;
    int d3=(circle[i].r+circle[j].r)*(circle[i].r+circle[j].r);

    // 两圆相离
    if(d2>d3){
        return false;
    }

    // 圆 j 的最右端点在圆 i 内
    if(inside({circle[j].x+circle[j].r,circle[j].y},i)){
        p={circle[j].x+circle[j].r,circle[j].y};
        return true;
    }

    // 圆 i 的最右端点在圆 j 内
    if(inside({circle[i].x+circle[i].r,circle[i].y},j)){
        p={circle[i].x+circle[i].r,circle[i].y};
        return true;
    }

    // 之前的情况都不满足，只需要考虑圆周交点
    if(d2==0) return false;

    long double d=sqrtl(d2);

    // 圆 j 到公共弦中点的距离
    long double t=(
        (long double)d2
        +circle[j].r*circle[j].r
        -circle[i].r*circle[i].r
    )/(2*d);

    // 公共弦半长
    long double h=sqrtl(max(
        0.0L,
        (long double)circle[j].r*circle[j].r-t*t
    ));

    // 公共弦中点
    Point mid={
        circle[j].x+dx*t/d,
        circle[j].y+dy*t/d
    };

    // 两个圆周交点
    Point p1={
        mid.x-dy*h/d,
        mid.y+dx*h/d
    };

    Point p2={
        mid.x+dy*h/d,
        mid.y-dx*h/d
    };

    // 取横坐标最大的交点
    p=p1.x>p2.x?p1:p2;

    return true;
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>circle[i].x>>circle[i].y>>circle[i].r;
    }
    Point p={circle[1].x+circle[1].r,circle[1].y};

    for(int i=1;i<=n;i++){
        if(inside(p,i)){
            continue;
        }
        for(int j=1;j<i;j++){
            Point q;
            if(!getpair(i,j,q)){
                cout<<i<<endl;
                return 0;
            }
            if(q.x<p.x){
                p=q;
            }
        }
        for(int j=1;j<=i;j++){
            if(!inside(p,j)){
                cout<<i<<endl;
                return 0;
            }
        }
    }
    cout<<"NIE"<<endl;
    return 0;
}