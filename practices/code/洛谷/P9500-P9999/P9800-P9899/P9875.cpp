// https://www.luogu.com.cn/problem/P9875
// 题意：多组数据（共 T 组）。
// 二维平面上有起点 A、终点 B
// 以及两堵线段墙 CD 和 EF（可能退化为点，A, B 不在墙上，保证可达）。
// 机器人不能碰到墙（含端点），求从 A 到 B 所需的最少转弯（改变方向）次数。
// 题意：第一行输入 T
// 每组四行依次输入
// (x_A, y_A)、(x_B, y_B)
// 、(x_C, y_C, x_D, y_D)
// 、(x_E, y_E, x_F, y_F)；
// 每组输出一行一个整数。
// 数据范围：1 <= T <= 10^5，
// 所有坐标值在 [-10^9, 10^9] 内。
// 算法标签：计算几何、线段相交
#include<bits/stdc++.h>
using namespace std;
#define int long long
using i128 = __int128_t;

struct Point{
    int x,y;
};
Point a,b,c,d,e,f;
Point x[5],y[5];
int cntx,cnty;

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

i128 cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

bool onSegment(Point a,Point b,Point c){
    if(cross(b-a,c-a)==0 && min(a.x,b.x)<=c.x && max(a.x,b.x)>=c.x
       && min(a.y,b.y)<=c.y && c.y<=max(a.y,b.y)){
        return true;
    }
    return false;
}

bool intersect(Point a,Point b,Point c,Point d){
    i128 x1=cross(b-a,c-a);
    i128 x2=cross(b-a,d-a);
    i128 x3=cross(d-c,a-c);
    i128 x4=cross(d-c,b-c);
    return ((x1<0&&x2>0)||(x1>0&&x2<0))&&((x3>0&&x4<0)||(x3<0&&x4>0));
}

int sgn(i128 x){
    return (x>0)-(x<0);
}

bool rayIntersect(Point a,Point b,Point c,Point d){
    int s=sgn(cross(b-a,d-c));
    if(s==0) return false;

    return sgn(cross(d-c,a-c))==s &&
           sgn(cross(b-a,c-a))==-s;
}

int solve(){
    cin>>a.x>>a.y;
    cin>>b.x>>b.y;
    cin>>c.x>>c.y;
    cin>>d.x>>d.y;
    cin>>e.x>>e.y;
    cin>>f.x>>f.y;

    if(onSegment(a,b,c)|| onSegment(a,b,d)|| onSegment(a,b,e)|| onSegment(a,b,f)){
        return 1;
    }
    if(!intersect(a,b,c,d)&&!intersect(a,b,e,f)){
        return 0;
    }
    if(!intersect(c,d,e,f)){
        return 1;
    }

    cntx=cnty=0;

    // 枚举第一堵墙的两个端点
    for(Point p:{c,d}){
        if(!intersect(a,p,e,f)){
            x[++cntx]=p;
        }
        if(!intersect(b,p,e,f)){
            y[++cnty]=p;
        }
    }

    // 枚举第二堵墙的两个端点
    for(Point p:{e,f}){
        if(!intersect(a,p,c,d)){
            x[++cntx]=p;
        }
        if(!intersect(b,p,c,d)){
            y[++cnty]=p;
        }
    }
    for(int i=1;i<=cntx;i++){
        for(int j=1;j<=cnty;j++){
            if(rayIntersect(a,x[i],b,y[j])){
                return 1;
            }
        }
    }
    return 2;
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        cout<<solve()<<endl;;
    }
    return 0;
}