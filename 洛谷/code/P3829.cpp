// https://www.luogu.com.cn/problem/P3829
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;

struct Point{
    double x,y;
};
Point nums[MAXN*4];
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

double Andrew(){
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
    double res=0;
    for(int i=1;i<top;i++){
        res+=dis(sta[i],sta[i+1]);
    }
    return res;
}

Point rorate(Point a,double b){
    return {a.x*cos(b)-a.y*sin(b),a.x*sin(b)+a.y*cos(b)};
}

int walk[4][2]={{1,1},{1,-1},{-1,1},{-1,-1}};

int main()
{
    cin>>n;
    double a,b,r;
    cin>>a>>b>>r;
    a=a/2-r;
    b=b/2-r;
    for(int i=1;i<=n;i++){
        double x,y,c;
        cin>>x>>y>>c;
        for(int k=0;k<4;k++){
            Point t=rorate({walk[k][0]*b,walk[k][1]*a},c);
            nums[4*(i-1)+k+1]={x+t.x,y+t.y};
        }
    }
    n*=4;
    double ans=Andrew();
    ans+=2*r*acos(-1);
    cout<<fixed<<setprecision(2)<<ans<<endl;
    return 0;
}