// https://www.luogu.com.cn/problem/P5974
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 505;
const double PI = acos(-1);
const double eps = 1e-7;

int n,m;

struct Point{
    int x,y;
};
Point p[MAXN];

struct Event{
    double x;
    int v;
};
Event e[MAXN<<1];

double dis[MAXN][MAXN];
double ang[MAXN][MAXN];
double angle;
int ansid;

bool cmp(Event a,Event b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    return a.v>b.v;
}

bool check(int id,double r){
    if(r<=0){
        return false;
    }

    int cnt=0,cur=1;
    double len=2*r;
    for(int j=1;j<=n;j++){
        if(j==id || dis[id][j]>len){
            continue;
        }
        double theta=ang[id][j];
        double alpha=acos(min(1.0,dis[id][j]/len));

        double l=theta-alpha;
        double rr=theta+alpha;

        // 区间跨越 0 度
        if(l<0){
            cur++;
            e[++cnt]={rr,-1};
            e[++cnt]={l+2*PI,1};
        }
        else if(rr>=2*PI){
            cur++;
            e[++cnt]={rr-2*PI,-1};
            e[++cnt]={l,1};
        }
        else{
            e[++cnt]={l,1};
            e[++cnt]={rr,-1};
        }
    }

    if(cur>=m) {
        angle=0;
        ansid=id;
        return true;
    }

    sort(e+1,e+cnt+1,cmp);

    for(int i=1;i<=cnt;i++){
        cur+=e[i].v;
        if(cur>=m) {
            ansid=id;
            angle=e[i].x;
            return true;
        }
    }

    return false;
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }

    if(m==2){
        double ans=1e100;
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                double dx=p[j].x-p[i].x;
                double dy=p[j].y-p[i].y;
                ans=min(ans,sqrt(dx*dx+dy*dy)/2);
            }
        }
        cout<<fixed<<setprecision(10)<<ans<<"\n";
        return 0;
    }
    
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    shuffle(p+1,p+n+1,rng);

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j){
                continue;
            }

            int dx=p[j].x-p[i].x;
            int dy=p[j].y-p[i].y;
            dis[i][j]=sqrt(dx*dx+dy*dy);
            ang[i][j]=atan2((double)dy,(double)dx);
            if(ang[i][j]<0){
                ang[i][j]+=2*PI;
            }
        }
    }

    double ans=20000;
    for(int i=1;i<=n;i++){
        if(!check(i,ans)){
            continue;
        }

        double l=0,r=ans;
        for(int j=1;j<=40;j++){
            double mid=(l+r)/2;
            if(check(i,mid)){
                r=mid;
            }
            else{
                l=mid;
            }
        }
        ans=r;
    }

    cout<<fixed<<setprecision(10);
    cout<<ans<<endl;
    cout<<(p[ansid].x+ans*cos(angle))<<' '<<(p[ansid].y+ans*sin(angle));
    return 0;
}