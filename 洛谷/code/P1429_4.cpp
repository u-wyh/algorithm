// https://www.luogu.com.cn/problem/P1429
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;
struct Point{
    double x,y;
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

double dot(Point a,Point b){
    return a.x*b.x+a.y*b.y;
}

double dis(Point a,Point b){
    return sqrt(dot(a-b,a-b));
}

bool cmpy(Point a,Point b){
    return a.y<b.y;
}
Point val[MAXN];

double solve(int l,int r){
    if(l==r){
        return 2e9;
    }
    if(l+1==r){
        return dis(nums[l],nums[r]);
    }
    int mid=(l+r)>>1;
    double d1=solve(l,mid);
    double d2=solve(mid+1,r);
    double d=min(d1,d2);
    int cnt=0;
    for(int i=l;i<=r;i++){
        if(fabs(nums[i].x-nums[mid].x)<d){
            val[++cnt]=nums[i];
        }
    }
    sort(val+1,val+cnt+1,cmpy);
    for(int i=1;i<=cnt;i++){
        for(int j=i+1;j<=cnt&&(val[j].y-val[i].y<d);j++){
            d=min(d,dis(val[i],val[j]));
        }
    }
    return d;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].x>>nums[i].y;
    }
    sort(nums+1,nums+n+1,cmp);
    cout<<fixed<<setprecision(4)<<solve(1,n)<<endl;
    return 0;
}