// https://www.luogu.com.cn/problem/P13378
// 题意：上下两条折线在 [0, W] 围成蛋糕，
// 求 G-1 条竖直线将其面积 G 等分。
// 输入：首行 T，每组给 W, L, U, G，
// 后跟 L 个下边界点和 U 个上边界点。
// 规则：边界点按 x 严格递增且最左 x=0 最右 x=W，下边界严格在下方。
// 输出：每组输出 Case #x:
// 后跟 G-1 行切割 x 坐标（相对或绝对误差 <= 10^-6）。
// 数据范围：1 <= T <= 100，1 <= W <= 1000，
// 2 <= L, U <= 100。
// 数据范围：2 <= G <= 101，
// 所有输入坐标均为 [-1000, 1000] 内整数。
// 算法标签：二分查找、计算几何
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;

int T,W,L,U,G;

struct Point{
    long double x,y;
};
Point low[MAXN],up[MAXN];

// 计算折线与x轴从0到x之间的有向面积
long double calc(Point p[],int n,long double x){
    long double res=0;
    for(int i=1;i<n;i++){
        if(p[i].x>=x){
            break;
        }

        long double r=min(x,p[i+1].x);
        long double y=p[i].y+(p[i+1].y-p[i].y)*(r-p[i].x)/(p[i+1].x-p[i].x);

        res+=(p[i].y+y)*(r-p[i].x)/2;

        if(r>=x){
            break;
        }
    }
    return res;
}

// 计算蛋糕从0到x之间的面积
long double area(long double x){
    return calc(up,U,x)-calc(low,L,x);
}

int main(){
    cin>>T;
    cout<<fixed<<setprecision(12);

    for(int tc=1;tc<=T;tc++){
        cin>>W>>L>>U>>G;

        for(int i=1;i<=L;i++){
            cin>>low[i].x>>low[i].y;
        }
        for(int i=1;i<=U;i++){
            cin>>up[i].x>>up[i].y;
        }

        long double s=area(W);

        cout<<"Case #"<<tc<<":\n";

        for(int i=1;i<G;i++){
            long double l=0,r=W;
            long double target=s*i/G;

            for(int j=1;j<=75;j++){
                long double mid=(l+r)/2;
                if(area(mid)<target){
                    l=mid;
                }
                else{
                    r=mid;
                }
            }

            cout<<(l+r)/2<<'\n';
        }
    }

    return 0;
}
