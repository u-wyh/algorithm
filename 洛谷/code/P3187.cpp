// https://www.luogu.com.cn/problem/P3187
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const double PI = acos(-1);

int n;
struct Point{
    double x,y;
};
Point nums[MAXN];
int top;
Point sta[MAXN];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

Point operator+(Point a,Point b){
    return {a.x+b.x,a.y+b.y};
}

Point operator*(Point a,double k){
    return {a.x*k,a.y*k};
}

bool cmp(Point a,Point b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    return a.y<b.y;
}

double cross(Point a,Point b,Point c){
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}

double dot(Point a,Point b,Point c){
    return (b.x-a.x)*(c.x-a.x)+(b.y-a.y)*(c.y-a.y);
}

double dis(Point a,Point b){
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
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

Point rorate(Point a,double b){
    return {a.x*cos(b)-a.y*sin(b),a.x*sin(b)+a.y*cos(b)};
}

void rorating_calipers(){
    double ans=1e20;
    int a,b,c;
    a=b=2;
    for(int i=1;i<=top;i++){
        while(cross(sta[i],sta[i+1],sta[a])<cross(sta[i],sta[i+1],sta[a+1])){
            a=a%top+1;
        }
        while(dot(sta[i],sta[i+1],sta[b])<dot(sta[i],sta[i+1],sta[b+1])){
            b=b%top+1;
        }
        if(i==1){
            c=a;
        }
        while(dot(sta[i+1],sta[i],sta[c])<dot(sta[i+1],sta[i],sta[c+1])){
            c=c%top+1;
        }
        double d=dis(sta[i],sta[i+1]);
        double h=cross(sta[i],sta[i+1],sta[a])/d;
        double r=dot(sta[i],sta[i+1],sta[b])/d;
        double l=dot(sta[i+1],sta[i],sta[c])/d;
        if(ans>(r+l-d)*h){
            ans=(r+l-d)*h;
            nums[1]=sta[i+1]+(sta[i]-sta[i+1])*(l/d);
            nums[2]=sta[i]+(sta[i+1]-sta[i])*(r/d);
            nums[3]=nums[2]+rorate(sta[i+1]-sta[i],PI/2)*(h/d);
            nums[4]=nums[1]+rorate(sta[i+1]-sta[i],PI/2)*(h/d);
        }
    }

    cout<<fixed<<setprecision(5);
    cout<<ans<<endl;
    for(int i=1;i<=4;i++){
        cout<<nums[i].x<<' '<<nums[i].y<<endl;
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].x>>nums[i].y;
    }
    Andrew();
    rorating_calipers();
    return 0;
}