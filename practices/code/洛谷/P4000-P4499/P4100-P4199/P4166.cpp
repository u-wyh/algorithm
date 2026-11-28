// https://www.luogu.com.cn/problem/P4166
// 题意：平面上有 N 个点，从中任选 4 个点围成一个多边形，
// 求能围出的最大面积（保留 3 位小数）。
// 数据范围：5 <= N <= 2000，
// 0 <= |x|, |y| <= 100000。
// 难度评分：2400（洛谷分级换算）
// 算法标签：凸包、旋转卡壳、计算几何
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e3+5;

int n;
struct Point{
    double x,y;
};
Point p[MAXN];
int top;
Point sta[MAXN<<1];
double ans;

bool cmp(Point a,Point b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    return a.y<b.y;
}

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

double cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

void Andrew(){
    sort(p+1,p+n+1,cmp);
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(cnt==0 || p[i].x!=p[i-1].x || p[i].y!=p[i-1].y){
            p[++cnt]=p[i];
        }
    }
    int n=cnt;
    for(int i=1;i<=n;i++){
        while(top>1&& cross(sta[top]-sta[top-1],p[i]-sta[top-1])<=0){
            top--;
        }
        sta[++top]=p[i];
    }
    int t=top;
    for(int i=n-1;i>=1;i--){
        while(top>t && cross(sta[top]-sta[top-1],p[i]-sta[top-1])<=0){
            top--;
        }
        sta[++top]=p[i];
    }
    top--;
}

bool operator==(Point a,Point b){
    if(a.x==b.x&&a.y==b.y){
        return true;
    }
    return false;
}

double area(Point a,Point b,Point c){
    return abs(cross(b-a,c-a));
}

double cross(Point a,Point b,Point c){
    return cross(b-a,c-a);
}

void rotating_calipers(){
    for(int i=1;i<=top;i++){
        sta[i+top]=sta[i];
    }
    for(int l=1;l<=top;l++){
        int lptr=l+1,rptr=l+3;
        for(int r=l+2;r<=l+top-2;r++){
            while(cross(sta[l],sta[lptr+1],sta[r])>cross(sta[l],sta[lptr],sta[r])){
                lptr++;
            }
            rptr=max(rptr,r+1);
            while(cross(sta[l],sta[r],sta[rptr+1])>cross(sta[l],sta[r],sta[rptr])){
                rptr++;
            }
            ans=max(ans,cross(sta[l],sta[lptr],sta[r])+cross(sta[l],sta[r],sta[rptr]));
        }
    }
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }

    Andrew();

    cout<<fixed<<setprecision(3);

    if(top<=2){
        ans=0;
    }
    else if(top==3){
        ans=area(sta[1],sta[2],sta[3]);
        double res=ans;
        for(int i=1;i<=n;i++){
            if((p[i]==sta[1])||(p[i]==sta[2])||(p[i]==sta[3])){
                continue;
            }
            res=min(res,area(p[i],sta[1],sta[2]));
            res=min(res,area(p[i],sta[1],sta[3]));
            res=min(res,area(p[i],sta[3],sta[2]));
        }
        ans-=res;
    }
    else if(top==4){
        for(int i=2;i<top;i++){
            ans+=cross(sta[i]-sta[1],sta[i+1]-sta[1]);
        }
    }
    else{
        rotating_calipers();
    }
    double res=ans/2.0;
    cout<<res<<endl;
    return 0;
}