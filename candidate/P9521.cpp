// https://www.luogu.com.cn/problem/P9521
// https://www.luogu.com.cn/problem/P9521
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int H,W,ans;
int a[MAXN];
int b[MAXN];

struct Point{
    int x,y;
};
Point hulla[MAXN];
Point hullb[MAXN];
int cnta,cntb;

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

// 构建下凸壳
void Andrew(int *a,int n,Point *hull,int &cnt){
    for(int i=1;i<=n;i++){
        Point p={i,a[i]};
        while(cnt>=2 && cross(hull[cnt]-hull[cnt-1],p-hull[cnt])<=0){
            cnt--;
        }
        hull[++cnt]=p;
    }
}

void solve(){
    int i=1,j=1;
    while(i<cnta && j<cntb){
        Point u=hulla[i+1]-hulla[i];
        Point v=hullb[j+1]-hullb[j];

        // A 的斜率更小，优先向下移动
        if(u.y*v.x<=v.y*u.x){
            ans+=u.x*hullb[j].y;
            i++;
        }
        // B 的斜率更小，优先向右移动
        else{
            ans+=v.x*hulla[i].y;
            j++;
        }
    }

    // 剩余的向下移动
    while(i<cnta){
        ans+=(hulla[i+1].x-hulla[i].x)*hullb[j].y;
        i++;
    }

    // 剩余的向右移动
    while(j<cntb){
        ans+=(hullb[j+1].x-hullb[j].x)*hulla[i].y;
        j++;
    }
}

signed main(){
    cin>>H>>W;
    for(int i=1;i<=H;i++){
        cin>>a[i];
    }
    for(int i=1;i<=W;i++){
        cin>>b[i];
    }

    Andrew(a,H,hulla,cnta);
    Andrew(b,W,hullb,cntb);

    solve();

    cout<<ans<<endl;
    return 0;
}