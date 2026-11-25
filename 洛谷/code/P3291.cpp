// https://www.luogu.com.cn/problem/P3291
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;

int n,cnt;
struct Point{
    int x,y;
};
Point p[MAXN];
Point q[MAXN];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

bool cmp(Point a,Point b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    return a.y<b.y;
}

long double calc(Point p,long double t){
    return p.x+p.y+p.y*t+p.x/t;
}

long double gett(Point a,Point b){
    return (long double)(a.x-b.x)/(b.y-a.y);
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }
    sort(p+1,p+n+1,cmp);

    for(int i=n;i>=1;i--){
        if(cnt&&p[i].y<=q[cnt].y){
            continue;
        }

        while(cnt>=2 && cross(q[cnt]-q[cnt-1],p[i]-q[cnt])<=0){
            cnt--;
        }
        q[++cnt]=p[i];
    }

    long double ans=1e100l;
    for(int i=1;i<=cnt;i++){
        long double t=sqrtl((long double)q[i].x/q[i].y);

        if(i>1){
            t=max(t,gett(q[i-1],q[i]));
        }
        if(i<cnt){
            t=min(t,gett(q[i],q[i+1]));
        }
        ans=min(ans,calc(q[i],t));
    }

    cout<<fixed<<setprecision(4)<<ans<<endl;
    return 0;
}