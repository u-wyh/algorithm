
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e3+5;

int n;
struct Point{
    int x,y;
};
Point p[MAXN<<1];
int f[MAXN][MAXN];

int dis(Point a,Point b){
    int x=a.x-b.x;
    int y=a.y-b.y;
    return x*x+y*y;
}

int cross(Point a,Point b,Point c){
    return (b.x-a.x)*(c.y-a.y)
          -(b.y-a.y)*(c.x-a.x);
}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
        p[n+i]=p[i];
    }

    for(int i=1;i<=n+1;i++)
        f[i][1]=0;

    for(int len=2;len<=n;len++){
        for(int i=1;i<=n;i++){
            int j=(i+len-2)%n+1;
            f[i][len]=max({
                f[i][len-1],
                f[i+1][len-1],
                dis(p[i],p[j])
            });
        }
        f[n+1][len]=f[1][len];
    }

    int ans=LLONG_MAX;

    for(int i=1;i<=n;i++){
        for(int j=i+2;j<=n;j++){
            int len=j-i+1;
            int len1=n-len+2;

            if(len1<3) continue;

            int pre=(i+n-2)%n+1;
            int nxt=i%n+1;

            if(cross(p[pre],p[i],p[j])==0) continue;
            if(cross(p[i],p[nxt],p[j])==0) continue;

            ans=min(ans,f[i][len]+f[j][len1]);
        }
    }

    cout<<ans<<'\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
