// https://www.luogu.com.cn/problem/P1995
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e3+5;
const int MAXP = 2*MAXN+5;
const double INF = 1e100;

int n,m,cnt;
struct Rect{
    int x1,y1,x2,y2;
};
Rect rect[MAXN];

struct Point{
    int x,y;
};
Point p[MAXP];
Point s,t;

int l[MAXN],r[MAXN];
double dp[MAXP];
double v;
double extra;
double ans;

void add(int x,int y1,int y2){
    m++;
    l[m]=++cnt;
    p[cnt]={x,y1};

    r[m]=l[m];
    if(y1!=y2){
        r[m]=++cnt;
        p[cnt]={x,y2};
    }
}

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

double dist(Point a){
    return sqrt(a.x*a.x+a.y*a.y);
}

void compute(){
    for(int i=1;i<=cnt;i++){
        dp[i]=INF;
    }
    dp[1]=0;
    for(int i=1;i<=m;i++){
        if(l[i]!=r[i]){
            double w=abs(p[l[i]].y-p[r[i]].y);
            double a=dp[l[i]];
            double b=dp[r[i]];

            dp[l[i]]=min(a,b+w);
            dp[r[i]]=min(b,a+w);
        }
        for(int k=l[i];k<=r[i];k++){
            if(dp[k]>=INF/2){
                continue;
            }
            int lower=0,upper=0;
            for(int j=i+1;j<=m;j++){
                for(int t=l[j];t<=r[j];t++){
                    if((lower==0 || cross(p[lower]-p[k],p[t]-p[k])>=0)&&
                       (upper==0 || cross(p[upper]-p[k],p[t]-p[k])<=0)){
                        dp[t]=min(dp[t],dp[k]+dist(p[t]-p[k]));
                    }
                }
                if(!lower || cross(p[lower]-p[k],p[l[j]]-p[k])>0){
                    lower=l[j];
                }

                // 当前门上端点降低斜率上界
                if(!upper || cross(p[upper]-p[k],p[r[j]]-p[k])<0){
                    upper=r[j];
                }

                // 斜率下界大于上界，后面的点都无法直达
                if(cross(p[lower]-p[k],p[upper]-p[k])<0){
                    break;
                }
            }
        }
    }
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>rect[i].x1>>rect[i].y1;
        cin>>rect[i].x2>>rect[i].y2;
    }
    cin>>s.x>>s.y>>t.x>>t.y>>v;

    if(s.x>t.x){
        swap(s,t);
    }
    if(s.x==t.x){
        cout<<fixed<<setprecision(10) <<abs(s.y-t.y)/v<<'\n';
        return 0;
    }
    for(int i=1;i<n;i++){
        if(rect[i].x2==s.x){
            int y=min(max(s.y,rect[i+1].y1),rect[1+i].y2);
            extra+=abs(s.y-y);
            s.y=y;
        }
        if(rect[i].x2==t.x){
            int y=min(max(t.y,rect[i].y1),rect[i].y2);
            extra+=abs(t.y-y);
            t.y=y;
        }
    }

    add(s.x,s.y,s.y);
    for(int i=1;i<n;i++){
        int x=rect[i].x2;
        if(x<=s.x||x>=t.x){
            continue;
        }
        int y1=max(rect[i].y1,rect[i+1].y1);
        int y2=min(rect[i].y2,rect[i+1].y2);
        add(x,y1,y2);
    }
    add(t.x,t.y,t.y);

    compute();
    cout<<fixed<<setprecision(10)<<(dp[cnt]+extra)/v<<endl;
    return 0;
}