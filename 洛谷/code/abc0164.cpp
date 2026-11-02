// https://atcoder.jp/contests/abc016/tasks/abc016_4
// https://atcoder.jp/contests/abc016/tasks/abc016_4
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;

int n;

struct Point{
    int x,y;
};

Point a,b;
Point p[MAXN];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

// 叉积
long long operator*(Point a,Point b){
    return 1LL*a.x*b.y-1LL*a.y*b.x;
}

long long cross(Point a,Point b,Point c){
    return (b-a)*(c-a);
}

// 严格判断两条线段是否相交
bool check(Point a,Point b,Point c,Point d){
    long long x1=cross(a,b,c);
    long long x2=cross(a,b,d);
    long long x3=cross(c,d,a);
    long long x4=cross(c,d,b);

    return x1*x2<0 && x3*x4<0;
}

int main(){
    cin>>a.x>>a.y>>b.x>>b.y;
    cin>>n;

    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }

    p[n+1]=p[1];

    int cnt=0;

    // 枚举多边形的每一条边
    for(int i=1;i<=n;i++){
        if(check(a,b,p[i],p[i+1])){
            cnt++;
        }
    }

    cout<<cnt/2+1<<endl;

    return 0;
}