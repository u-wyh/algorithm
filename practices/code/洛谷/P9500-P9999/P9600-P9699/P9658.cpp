// https://www.luogu.com.cn/problem/P9658
// 题意：多组数据（共 T 组）。
// 二维平面上有 n 个互不重合的激光发生器 (x_i, y_i)，
// 每对发生器之间都会发射一条激光线段（共 n(n-1)/2 对）。
// 从 (0, 0) 出发逃到
// (10^{10^{10}}, 10^{10^{10}})，
// 路线可任意弯曲但不能触碰任何激光线段或发生器。
// 每次可移除一个发生器及其相连的所有激光线段，求逃脱所需移除的最少发生器数量。
// 题意：第一行输入 T，每组输入 n 及 n 行 (x_i, y_i)；
// 每组输出一行一个整数。
// 数据范围：1 <= n <= 10^6，
// -10^9 <= x_i, y_i <= 10^9，sum(n) <= 10^6
// 保证没有发生器或线段经过
// (0, 0)（未显式给出 T 上界，受 sum(n) 限制）。
// 算法标签：极角排序、双指针
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e6+5;

int n,ans;
struct Point{
    int x,y;
};
Point p[MAXN];

int half(Point a){
    return (a.y>0 || (a.y==0 && a.x>0))?0:1;
}

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

bool cmp(Point a,Point b){
    int ha=half(a);
    int hb=half(b);
    if(ha!=hb){
        return ha<hb;
    }
    return cross(a,b)>0;
}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }
    sort(p+1,p+n+1,cmp);
    for(int i=1;i<=n;i++){
        p[i+n]=p[i];
    }
    int r=1,maxx=0;
    for(int l=1;l<=n;l++){
        r=max(l,r);
        while(r<l+n && cross(p[l],p[r])>=0){
            r++;
        }
        maxx=max(maxx,r-l);
    }
    cout<<(n-maxx)<<endl;
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}