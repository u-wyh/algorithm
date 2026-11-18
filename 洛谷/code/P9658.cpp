// https://www.luogu.com.cn/problem/P9658
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e6+5;

int n,ans;
struct Point{
    int x,y;
};
Point p[MAXN];

int half(Point a){
    return (a.y>0 || (a.y==0 && a.x>0))?0:1;
}

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

bool cmp(Point a,Point b){
    int ha=half(a);
    int hb=half(b);
    if(ha!=hb){
        return ha<hb;
    }
    return cross(a,b)>0;
}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }
    sort(p+1,p+n+1,cmp);
    for(int i=1;i<=n;i++){
        p[i+n]=p[i];
    }
    int r=1,maxx=0;
    for(int l=1;l<=n;l++){
        r=max(l,r);
        while(r<l+n && cross(p[l],p[r])>=0){
            r++;
        }
        maxx=max(maxx,r-l);
    }
    cout<<(n-maxx)<<endl;
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}