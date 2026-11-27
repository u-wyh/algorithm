// https://www.luogu.com.cn/problem/P9702

// 题意：多组数据（共 T 组）。
// 给定按逆时针给出顶点的 n 个顶点凸多边形
// P（面积为正，无重合顶点，可能有三点共线）。
// 选择 P 的两个顶点并作过两点的直线，
// 将 P 分为两个面积均为正数的多边形 Q 和 R。
// 记 d(Q) 为多边形直径（内或边界上两点最大欧氏距离），
// 求 (d(Q))^2 + (d(R))^2 的最小值。
// 题意：第一行输入 T，每组输入 n 及 n 行顶点坐标 (x_i, y_i)；
// 每组输出一行一个整数。
// 数据范围：4 <= n <= 5 * 10^3，
// 0 <= x_i,
// y_i <= 10^9，
// sum(n) <= 5 * 10^3（未显式给出 T 上界
// 受 sum(n) 限制）。
// 算法标签：区间动态规划、环形数组
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e3+5;

int n;
struct Point{
    int x,y;
};
Point p[MAXN<<1];
int f[MAXN][MAXN];

int dis(Point a,Point b){
    int x=a.x-b.x;
    int y=a.y-b.y;
    return x*x+y*y;
}

int cross(Point a,Point b,Point c){
    return (b.x-a.x)*(c.y-a.y)
          -(b.y-a.y)*(c.x-a.x);
}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
        p[n+i]=p[i];
    }

    for(int i=1;i<=n+1;i++)
        f[i][1]=0;

    for(int len=2;len<=n;len++){
        for(int i=1;i<=n;i++){
            int j=(i+len-2)%n+1;
            f[i][len]=max({
                f[i][len-1],
                f[i+1][len-1],
                dis(p[i],p[j])
            });
        }
        f[n+1][len]=f[1][len];
    }

    int ans=LLONG_MAX;

    for(int i=1;i<=n;i++){
        for(int j=i+2;j<=n;j++){
            int len=j-i+1;
            int len1=n-len+2;

            if(len1<3) continue;

            int pre=(i+n-2)%n+1;
            int nxt=i%n+1;

            if(cross(p[pre],p[i],p[j])==0) continue;
            if(cross(p[i],p[nxt],p[j])==0) continue;

            ans=min(ans,f[i][len]+f[j][len1]);
        }
    }

    cout<<ans<<'\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
