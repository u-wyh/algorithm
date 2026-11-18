// https://www.luogu.com.cn/problem/P9568
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
using i128 = __int128_t;

int n,k;
i128 ans,sum;
int ptr;

struct Point{
    int x,y;
};
Point p[MAXN];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

i128 operator*(Point a,Point b){
    return (i128)a.x*b.y-(i128)a.y*b.x;
}

i128 cross(Point a,Point b,Point c){
    return (b-a)*(c-a);
}

void solve(){
    cin>>n>>k;
    ans=0;
    sum=0;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
        p[n+i]=p[i];
    }
    for(int i=1;i<=k;i++){
        sum+=p[i]*p[i+1];
    }
    ptr=k+2;
    for(int l=1;l<=n;l++){
        int r=l+k;
        if(ptr<r+1){
            ptr=r+1;
        }
        while(ptr<l+n-1 && cross(p[l],p[r],p[ptr])<= cross(p[l],p[r],p[ptr+1])){
            ptr++;
        }
        
        i128 res=sum+p[r]*p[ptr]+p[ptr]*p[l];
        ans=max(ans,res);

        sum-=p[l]*p[l+1];
        sum+=p[r]*p[r+1];
    }
    cout<<fixed<<setprecision(12)<<(long double)ans/2.0L<<'\n';
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