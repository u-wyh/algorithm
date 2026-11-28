// https://codeforces.com/problemset/problem/429/D
// 题意：给长为 n 的序列 a。
// 对一对下标 i < j，令 s 为 a_{i+1} 到 a_j 的和。
// 定义 f(i, j) = (j-i)^2 + s^2。
// 输出：所有 1 <= i < j <= n 中 f(i, j) 的最小值。
// 数据范围：2 <= n <= 10^5，
// -10^4 <= a_i <= 10^4。
// 难度评分：2200（CF 官方）
// 算法标签：分治、计算几何、前缀和
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
    int sum=0;
    int val;
    for(int i=1;i<=n;i++){
        cin>>val;
        sum+=val;
        nums[i]={i,sum};
    }
    sort(nums+1,nums+n+1,cmp);
    cout<<solve(1,n)<<endl;
    return 0;
}