// https://www.luogu.com.cn/problem/P12596
// 题意：给定凸包和其内部一点 P，连 PA, PB 分割凸包求最小面积差。
// 输入：首行 n，后 n 行逆时针给凸包顶点坐标，最后一行给点 P 坐标。
// 规则：选凸包两不同顶点 A, B 并连接 PA, PB，将凸包分成两部分。
// 输出：输出两部分面积差的绝对值的最小值乘以 2（保证为整数）。
// 数据范围：3 <= n <= 10^5，所有坐标为 [0, 10^9] 内整数，P 在凸包内。
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int n;
struct Point{
    int x,y;
};
Point p[MAXN];
Point u;

int area[MAXN<<1];

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

void compute(){
    p[n+1]=p[1];
    int sum=0;
    for(int i=1;i<=n;i++){
        area[i]=area[i+n]=abs(cross(p[i]-u,p[i+1]-u));
        sum+=area[i];
    }
    int l=1,r=0;
    int now=0;
    int ans=sum;
    for(;l<=n;l++){
        while(r+1<=2*n && 2*(now+area[r+1])<=sum){
            r++;
            now+=area[r];
        }
        ans=min(ans,max(now,sum-now)-min(now,sum-now));
        now-=area[l];
    }
    cout<<ans<<endl;
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }
    cin>>u.x>>u.y;

    compute();
    return 0;
}