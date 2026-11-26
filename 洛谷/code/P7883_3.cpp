// https://www.luogu.com.cn/problem/P7883
// 题意：给定二维平面上 n 个互不相同的整点 p_i = (x_i, y_i)，求距离最近的两个点的欧氏距离的平方 D^2。
// 第一行输入 n，接下来 n 行每行 x_i, y_i。
// 输出一行一个整数 D^2。
// 数据范围：2 <= n <= 4*10^5，-10^7 <= x_i, y_i <= 10^7，保证无重合点。
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 4e5+5;

int n;
struct Point{
    int x,y;
};
Point nums[MAXN];

bool cmp(Point a,Point b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    return a.y<b.y;
}

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

int dot(Point a,Point b){
    return a.x*b.x+a.y*b.y;
}

int dis2(Point a,Point b){
    return dot(a-b,a-b);
}

bool cmpy(Point a,Point b){
    return a.y<b.y;
}
Point val[MAXN];

int solve(int l,int r){
    if(l==r){
        return 2e17;
    }
    if(l+1==r){
        return dis2(nums[l],nums[r]);
    }
    int mid=(l+r)>>1;
    int d1=solve(l,mid);
    int d2=solve(mid+1,r);
    int d=min(d1,d2);
    int cnt=0;
    for(int i=l;i<=r;i++){
        if(fabs(nums[i].x-nums[mid].x)*fabs(nums[i].x-nums[mid].x)<d){
            val[++cnt]=nums[i];
        }
    }
    sort(val+1,val+cnt+1,cmpy);
    for(int i=1;i<=cnt;i++){
        for(int j=i+1;j<=cnt&&((val[j].y-val[i].y)*(val[j].y-val[i].y)<d);j++){
            d=min(d,dis2(val[i],val[j]));
        }
    }
    return d;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].x>>nums[i].y;
    }
    sort(nums+1,nums+n+1,cmp);
    cout<<fixed<<setprecision(4)<<solve(1,n)<<endl;
    return 0;
}