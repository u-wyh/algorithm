// https://www.luogu.com.cn/problem/P3738
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 55;

int n;
struct Point{
    double x,y;
};
Point p[MAXN];
Point u;
Point nums[MAXN];

bool cmp(Point a,Point b){
    return a.y<b.y;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }
    p[n+1]=p[1];
    cin>>u.x>>u.y;
    int cnt=0;
    for(int i=1;i<=n;i++){
        Point a=p[i];
        Point b=p[i+1];
        if(a.x<b.x){
            swap(a,b);
        }
        
        if((a.x<=u.x && u.x<b.x) ||  (b.x<=u.x && u.x<a.x)){
            nums[++cnt]={u.x, (u.x-a.x)/(b.x-a.x)*(b.y-a.y)+a.y};
        }
    }
    sort(nums+1,nums+cnt+1,cmp);
    double ans=0;
    for(int i=1;i<=cnt;i+=2){
        ans+=nums[i+1].y-nums[i].y;
    }
    cout<<(int )ans<<endl;
    return 0;
}