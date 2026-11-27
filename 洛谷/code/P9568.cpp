// https://www.luogu.com.cn/problem/P9568
// 题意：多组数据（共 T 组）。
// 给定按逆时针顺序给出顶点的 n 个顶点凸多边形 P（面积为正，无重合顶点，可能有三点共线），选出逆时针顺序的三个顶点 a, b, c
// 要求 b 沿逆时针到 c 之间恰有 k 条边（a 不是这 k 条边的端点）。
// 用线段 ab, ac 和这 k 条边围成 (k+2) 边形 Q，求 Q 的最大面积（ab, ac 可与 P 的边重合）。
// 题意：第一行输入 T，每组输入 n, k 及 n 行 (x_i, y_i)；输出每组一行实数，相对误差或绝对误差 < 10^-9 视为正确。
// 数据范围：3 <= n <= 10^5，1 <= k <= n-2，sum(n) <= 10^5
// -10^9 <= x_i, y_i <= 10^9（未显式写 T 的上界，受 sum(n) <= 10^5 限制）。
// 算法标签：旋转卡壳、计算几何
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
using i128 = __int128_t;

int n,k;
i128 ans,sum;
int ptr;

struct Point{
    int x,y;
};
Point p[MAXN];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

i128 operator*(Point a,Point b){
    return (i128)a.x*b.y-(i128)a.y*b.x;
}

i128 cross(Point a,Point b,Point c){
    return (b-a)*(c-a);
}

void solve(){
    cin>>n>>k;
    ans=0;
    sum=0;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
        p[n+i]=p[i];
    }
    for(int i=1;i<=k;i++){
        sum+=p[i]*p[i+1];
    }
    ptr=k+2;
    for(int l=1;l<=n;l++){
        int r=l+k;
        if(ptr<r+1){
            ptr=r+1;
        }
        while(ptr<l+n-1 && cross(p[l],p[r],p[ptr])<= cross(p[l],p[r],p[ptr+1])){
            ptr++;
        }
        
        i128 res=sum+p[r]*p[ptr]+p[ptr]*p[l];
        ans=max(ans,res);

        sum-=p[l]*p[l+1];
        sum+=p[r]*p[r+1];
    }
    cout<<fixed<<setprecision(12)<<(long double)ans/2.0L<<'\n';
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