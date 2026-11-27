// https://www.luogu.com.cn/problem/P3476
// 题意：输入平面上点的数量 n，以及这 n 个互不相同的整数点坐标 (x_i, y_i)。
// 计算以这 n 个点中任意三个不同点为顶点的全部 n(n-1)(n-2)/6 个三角形的面积总和（共线退化三角形面积记为 0）。
// 输出一个实数表示面积之和，保留一位小数（误差不超过 0.1）。
// 数据范围：3 <= n <= 3000，0 <= x_i, y_i <= 10^4，所有点坐标互异。
#include<bits/stdc++.h>
// 算法标签：极角排序、双指针、前缀和
using namespace std;
#define int long long
const int MAXN = 3e3+5;

int n;
struct Point{
    int x,y;
};
Point p[MAXN];
Point p1[MAXN<<1];

int prex[MAXN<<1];
int prey[MAXN<<1];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

Point operator+(Point a,Point b){
    return {a.x+b.x,a.y+b.y};
}

int half(Point a){
    return (a.y>0 || (a.y==0&&a.x>0))?0:1;
}

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

bool cmp(Point a,Point b){
    int ha=half(a),hb=half(b);
    if(ha!=hb){
        return ha<hb;
    }
    return cross(a,b)>0;
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        int cnt=0;
        for(int j=1;j<=n;j++){
            if(i==j){
                continue;
            }
            p1[++cnt]=p[j]-p[i];
        }
        sort(p1+1,p1+n,cmp);
        int m=1;
        for(int j=2;j<n;j++){
            if(cross(p1[j-1],p1[j])==0&& half(p1[j-1])==half(p1[j])){
                p1[m]=p1[m]+p1[j];
            }
            else{
                p1[++m]=p1[j];
            }
        }
        for(int i=1;i<=m;i++){
            p1[i+m]=p1[i];
        }
        for(int j=1;j<=2*m;j++){
            prex[j]=prex[j-1]+p1[j].x;
            prey[j]=prey[j-1]+p1[j].y;
        }
        int r=1;
        for(int l=1;l<=m;l++){
            r=max(r,l+1);
            while(r<l+m&&cross(p1[l],p1[r])>0){
                r++;
            }
            int dx=prex[r-1]-prex[l];
            int dy=prey[r-1]-prey[l];
            ans+=cross(p1[l],{dx,dy});
        }
    }
    int res=ans/3;
    cout<<res/2<<'.'<<(res%2?5:0)<<endl;
    return 0;
}