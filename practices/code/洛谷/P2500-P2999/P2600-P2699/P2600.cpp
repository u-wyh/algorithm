// https://www.luogu.com.cn/problem/P2600
// 题意：一维轮廓折线 (x_1,y_1)..(x_n,y_n)
// (x_1 < ... < x_n)。
// 在 [x_1, x_n] 建瞭望塔，使塔顶能看到轮廓上任意位置，求塔的最小高度。
// 输出最小高度，精确到小数点后三位。
// 数据范围：n <= 300，坐标绝对值 <= 10^6。
// 难度评分：2400（洛谷分级换算）
// 算法标签：计算几何、枚举、双指针
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 305;
const long double INF = 1e100L;
const long double eps = 1e-6L;

int n;
struct Point{
    long double x,y;
};
Point p[MAXN];
Point p1[MAXN*MAXN];
int cntp;

long double k[MAXN],b[MAXN];
long double k1[MAXN*MAXN],b1[MAXN*MAXN];
long double ans=INF;

long double xs[MAXN*MAXN];
int cntx;
long double h[MAXN*MAXN];
long double f[MAXN*MAXN];

bool cmp(Point a,Point b){
    return a.x<b.x;
}

void compute(){
    p1[++cntp]=p[1];
    p1[++cntp]=p[n];
    for(int i=1;i<n;i++){
        p1[1].y=max(p1[1].y,p[1].x*k[i]+b[i]);
        p1[2].y=max(p1[2].y,p[n].x*k[i]+b[i]);
        for(int j=i+1;j<n;j++){
            if(k[i]==k[j]){
                continue;
            }
            long double x=(b[j]-b[i])/(k[i]-k[j]);
            if(x<p[1].x || x>p[n].x){
                continue;
            }
            long double y=k[i]*x+b[i];
            bool flag=true;
            for(int l=1;l<n;l++){
                long double yy=k[l]*x+b[l];
                if(yy>y+eps){
                    flag=false;
                    break;
                }
            }
            if(flag){
                p1[++cntp]={x,y};
            }
        }
    }

    sort(p1+1,p1+cntp+1,cmp);
    for(int i=1;i<cntp;i++){
        k1[i]=(p1[i+1].y-p1[i].y)/(p1[i+1].x-p1[i].x);
        b1[i]=p1[i].y-k1[i]*p1[i].x;
    }

    for(int i=1;i<=cntp;i++){
        xs[++cntx]=p1[i].x;
    }
    for(int i=1;i<=n;i++){
        xs[++cntx]=p[i].x;
    }
    sort(xs+1,xs+cntx+1);
    int len=1;
    for(int i=2;i<=cntx;i++){
        if(xs[i]>xs[i-1]+eps){
            xs[++len]=xs[i];
        }
    }

    int j=1,r=1;
    for(int i=1;i<=len;i++){
        long double px=xs[i];
        while(j<n-1 && px>p[j+1].x){
            j++;
        }
        // 原山体高度
        f[i]=k[j]*px+b[j];

        while(r<cntp-1 &&px>p1[r+1].x){
            r++;
        }
        h[i]=k1[r]*px+b1[r];
        ans=min(ans,h[i]-f[i]);
    }
    cout<<fixed<<setprecision(3)<<max(0.0l,ans)<<endl;
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>p[i].x;
    for(int i=1;i<=n;i++) cin>>p[i].y;
    sort(p+1,p+n+1,cmp);
    for(int i=1;i<n;i++){
        k[i]=(p[i+1].y-p[i].y)/(p[i+1].x-p[i].x);
        b[i]=p[i].y-k[i]*p[i].x;
    }
    compute();
    return 0;
}