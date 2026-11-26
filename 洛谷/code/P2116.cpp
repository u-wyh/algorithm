// https://www.luogu.com.cn/problem/P2116
// 题意：给定一个 n 边形城堡的顶点坐标，在其外修建围墙。
// 要求围墙离城堡的最近距离不能少于 L，求所需围墙的最小长度（四舍五入到整数）。
// 数据范围：3 <= n <= 1000，1 <= L <= 1000，-10^4 <= x_i, y_i <= 10^4。
#include<bits/stdc++.h>
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
    int len;
    cin>>n>>len;
    for(int i=1;i<=n;i++){
        cin>>nums[i].x>>nums[i].y;
    }
    double ans=Andrew();
    ans+=2*len*acos(-1);
    cout<<(long long)(ans+0.5)<<endl;
    return 0;
}