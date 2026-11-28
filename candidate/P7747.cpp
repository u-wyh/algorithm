// https://www.luogu.com.cn/problem/P7747
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int n,m,ans;
int sum[MAXN];
int f[MAXN];

struct Point{
    int x,y;
};
Point p[MAXN];
Point hull[MAXN];
int cnt;

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

int calc(Point p,int a,int b){
    return a*p.x+b*p.y;
}

int query(int a,int b){
    int l=1,r=cnt;
    while(l<r){
        int mid=(l+r)>>1;
        if(calc(hull[mid],a,b)<=calc(hull[mid+1],a,b)){
            l=mid+1;
        }
        else{
            r=mid;
        }
    }
    return calc(hull[l],a,b);
}

void Andrew(){
    for(int i=1;i<=n;i++){
        while(cnt>=2 && cross(hull[cnt]-hull[cnt-1],p[i]-hull[cnt-1])>=0){
            cnt--;
        }
        hull[++cnt]=p[i];
    }
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int t;
        cin>>t;
        sum[i]=sum[i-1]+t;
        p[i]={sum[i-1],sum[i]};
    }
    for(int i=1;i<=m;i++){
        cin>>f[i];
    }

    Andrew();

    ans=sum[n]*f[m];
    for(int i=2;i<=m;i++){
        ans+=query(-f[i],f[i-1]);
    }

    cout<<ans<<endl;
    return 0;
}
