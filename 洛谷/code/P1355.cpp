// https://www.luogu.com.cn/problem/P1355
// 题意：给三角形的三个顶点和一个待判定点。点在严格内部输出 1，严格外部输出 2，在边上但不在顶点输出 3，恰好为顶点输出 4。
// 数据范围：坐标为整数，各横纵坐标均在 [0,100]。

#include<bits/stdc++.h>
using namespace std;

struct Point{
    int x,y;
};
Point a,b,c,d;
Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}
int operator*(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}
int cross(Point a,Point b,Point c){
    return (b-a)*(c-a);
}

int main()
{
    char ch;
    cin>>ch>>a.x>>ch>>a.y>>ch;
    cin>>ch>>b.x>>ch>>b.y>>ch;
    cin>>ch>>c.x>>ch>>c.y>>ch;
    cin>>ch>>d.x>>ch>>d.y>>ch;

    if((a.x==d.x&&a.y==d.y) ||(b.x==d.x&&b.y==d.y) || (c.x==d.x&&c.y==d.y)){
        cout<<4<<endl;
        return 0;
    }

    int val1=abs(cross(a,b,c));
    int val2=abs(cross(a,b,d))+abs(cross(a,c,d))+abs(cross(c,b,d));

    if(val1!=val2){
        cout<<2<<endl;
        return 0;
    }

    if(cross(a,b,d)==0 || cross(a,c,d)==0 || cross(c,b,d)==0){
        cout<<3<<endl;
        return 0;
    }

    cout<<1<<endl;

    // if( (cross(a,b,d)==0) ||(cross(a,c,d)==0) ||(cross(c,b,d)==0)){
    //     cout<<3<<endl;
    //     return 0;
    // }

    // int val1=abs(cross(a,b,c));
    // int val2=abs(cross(a,b,d))+abs(cross(a,c,d))+abs(cross(c,b,d));
    // if(val1==val2){
    //     cout<<1<<endl;
    // }
    // else{
    //     cout<<2<<endl;
    // }
    return 0;
}