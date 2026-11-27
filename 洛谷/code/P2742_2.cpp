// https://www.luogu.com.cn/problem/P2742
// 题意：给定平面上 n 个点坐标 (x_i, y_i)，求围住所有点的最小凸包周长。
// 输出周长，四舍五入保留两位小数。
// 数据范围：3 <= n <= 10^5，-10^6 <= x_i, y_i <= 10^6。
#include<bits/stdc++.h>
// 算法标签：凸包、单调栈、计算几何
using namespace std;
const int MAXN = 1e5+5;

struct Point{
    double x,y;
};
Point nums[MAXN];
int n;
int top;
Point sta[MAXN];

bool cmp(Point &a,Point &b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    return a.y<b.y;
}

double cross(Point a,Point b,Point c){
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}

double dis(Point a,Point b){
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

double Andrew(){
    sort(nums+1,nums+n+1,cmp);
    for(int i=1;i<=n;i++){
        while(top>1 && cross(sta[top-1],sta[top],nums[i])<=0){
            top--;
        }
        sta[++top]=nums[i];
    }
    int t=top;
    for(int i=n-1;i>=1;i--){
        while(top>t && cross(sta[top-1],sta[top],nums[i])<=0){
            top--;
        }
        sta[++top]=nums[i];
    }
    double res=0;
    for(int i=1;i<top;i++){
        res+=dis(sta[i],sta[i+1]);
    }
    return res;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].x>>nums[i].y;
    }
    cout<<fixed<<setprecision(2)<<Andrew();
    return 0;
}