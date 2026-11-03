// https://www.luogu.com.cn/problem/P1452
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;

int n;
struct Point{
    int x,y;
};
Point nums[MAXN];
int top;
Point sta[MAXN];

bool cmp(Point a,Point b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    return a.y<b.y;
}

int cross(Point a,Point b,Point c){
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}

int dis2(Point a,Point b){
    return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

void Andrew(){
    sort(nums+1,nums+n+1,cmp);
    for(int i=1;i<=n;i++){
        while(top>1 && cross(sta[top-1],sta[top],nums[i])<=0){
            top--;
        }
        sta[++top]=nums[i];
    }
    int t=top;
    for(int i=n-1;i>=1;i--){
        while(top>t && cross(sta[top-1],sta[top],nums[i])<=0){
            top--;
        }
        sta[++top]=nums[i];
    }
    top--;
}

int rorating_calipers(){
    int res=0;
    for(int i=1,j=2;i<=top;i++){
        while(cross(sta[i],sta[i+1],sta[j])<cross(sta[i],sta[i+1],sta[j+1])){
            j=(j%top)+1;
        }
        res=max(res,max(dis2(sta[i],sta[j]),dis2(sta[i+1],sta[j])));
    }
    return res;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].x>>nums[i].y;
    }
    Andrew();
    cout<<rorating_calipers()<<endl;
    return 0;
}