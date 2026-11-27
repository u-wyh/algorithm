// https://www.luogu.com.cn/problem/P1302
// 题意：给 n 个内部互不重叠的正方形，求从原点能看到多少个。
// 某正方形可见，指它的边界上能找到不同两点 A、B，使原点与这两点形成的三角形内部没有碰到其他正方形。
// 数据范围：1 ≤ n ≤ 1000，左下角坐标 X,Y 和边长 L 都在 [1,10000]。
// 算法标签：计算几何、极角排序、枚举

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e3+5;
const int INF = 1e16;

int n;
struct Rect{
    int x,y,len;
};
Rect rect[MAXN];

struct Point{
    int x,y;
};
Point p[MAXN<<1];
int cnt;

bool ok[MAXN];

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

bool cmp(Point a,Point b){
    return cross(a,b)>0;
}

void compute(){
    sort(p+1,p+2*n+1,cmp);
    for(int i=1;i<2*n;i++){
        if(cross(p[i],p[i+1])==0){
            continue;
        }

        int a=p[i].y*p[i+1].x+p[i+1].y*p[i].x;
        int b=2*p[i].x*p[i+1].x;

        int best=INF;
        int id=0;

        for(int j=1;j<=n;j++){
            int x=rect[j].x;
            int y=rect[j].y;
            int len=rect[j].len;

            // 判断射线是否穿过正方形内部
            if(a*(x+len)<=b*y || a*x>=b*(y+len)){
                continue;
            }

            // 计算射线第一次进入正方形的位置
            int dis=max(a*x,b*y);

            if(dis<best){
                best=dis;
                id=j;
            }
        }

        if(id){
            ok[id]=true;
        }
    }
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        int x,y,len;
        cin>>x>>y>>len;
        rect[i]={x,y,len};
        p[i]={x+len,y};
        p[i+n]={x,y+len};
    }
    compute();
    int ans=0;
    for(int i=1;i<=n;i++){
        if(ok[i]){
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}