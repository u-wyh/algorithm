// https://www.luogu.com.cn/problem/P1183
#include<bits/stdc++.h>
using namespace std;

struct Point{
    int x,y;
};
int n;
Point nums[205];
Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}
int operator*(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}
int cross(Point a,Point b,Point c){
    return (b-a)*(c-a);
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].x>>nums[i].y;
    }
    int ans=0;
    for(int i=2;i<=n-1;i++){
        ans+=cross(nums[1],nums[i],nums[i+1]);
    }
    ans/=2;
    ans=abs(ans);
    cout<<ans<<endl;
    return 0;
}