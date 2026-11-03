// https://www.luogu.com.cn/problem/P3194
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;

struct Point{
    double x,y;
    int id;
};
Point nums[MAXN];
int n;
int top;
Point sta[MAXN];

bool cmp(Point &a,Point &b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    return a.y<b.y;
}

double cross(Point a,Point b,Point c){
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}

double dis(Point a,Point b){
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

int ans[MAXN];
void Andrew(){
    sort(nums+1,nums+n+1,cmp);
    for(int i=n;i>=1;i--){
        if(i<n && nums[i].x==nums[i+1].x){
            continue;
        }
        while(top>1 && cross(sta[top-1],sta[top],nums[i])<=0){
            top--;
        }
        sta[++top]=nums[i];
    }
    double res=0;
    for(int i=1;i<=top;i++){
        // res+=dis(sta[i],sta[i+1]);
        ans[i]=sta[i].id;
    }
    sort(ans+1,ans+top+1);
    for(int i=1;i<=top;i++){
        cout<<ans[i]<<' ';
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].x>>nums[i].y;
        nums[i].id=i;
    }
    Andrew();
    return 0;
}