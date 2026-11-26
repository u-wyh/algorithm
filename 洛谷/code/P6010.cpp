// https://www.luogu.com.cn/problem/P6010
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n;
struct Point{
    int x,y,id;
};
Point p[MAXN];
Point hull[MAXN];
int cnt;

int q[MAXN];
int id[MAXN];
int ansa[MAXN];
int ansb[MAXN];
int pos[MAXN];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

bool cmp(Point a,Point b){
    return a.x<b.x;
}

int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

int query(Point p){
    int l=1,r=cnt;
    while(l<r){
        int mid=(l+r)>>1;
        if(cross(hull[mid+1]-hull[mid],p-hull[mid])>=0){
            l=mid+1;
        }
        else{
            r=mid;
        }
    }
    return l;
}

void solve(){
    sort(p+1,p+n+1,cmp);
    for(int i=1;i<=n;i++){
        pos[p[i].id]=i;
    }
    cnt=0;
    for(int i=1;i<=n;i++){
        int s=p[i].id;
        int t=q[s];

        while(cnt>=2 && cross(hull[cnt]-hull[cnt-1],p[i]-hull[cnt-1])<=0){
            cnt--;
        }
        hull[++cnt]=p[i];

        if(p[pos[t]].x<=p[i].x){
            continue;
        }
        int res=query(p[pos[t]]);
        int a=p[pos[t]].x-hull[res].x;
        int b=p[pos[t]].y-hull[res].y;
        if(b<=0){
            continue;
        }
        int g=gcd(a,b);
        ansa[s]=a/g;
        ansb[s]=b/g;
    }
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x;
        p[i].y=i;
        p[i].id=i;
    }
    for(int i=1;i<=n;i++){
        cin>>q[i];
    }

    solve();

    for(int i=1;i<=n;i++){
        p[i].x=-p[i].x;
        p[i].y=-p[i].y;
    }
    solve();

    for(int i=1;i<=n;i++){
        if(ansb[i]==0){
            cout<<-1<<endl;
        }
        else{
            cout<<ansa[i]<<'/'<<ansb[i]<<endl;
        }
    }
    return 0;
}
