// https://www.luogu.com.cn/problem/P4515
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 11;
const int INF = 4e18;

int n;
struct Triangle{
    int x,y,r;
};
Triangle nums[MAXN];

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].x>>nums[i].y>>nums[i].r;
    }
    int ans=0;
    for(int mask=1;mask<(1<<n);mask++){
        int maxx=0,maxy=0,minsum=INF;
        int cnt=0;
        for(int i=1;i<=n;i++){
            if(mask&(1<<(i-1))){
                cnt++;
                maxx=max(maxx,nums[i].x);
                maxy=max(maxy,nums[i].y);
                minsum=min(minsum,nums[i].x+nums[i].y+nums[i].r);
            }
        }
        // cout<<maxx<<' '<<maxy<<' '<<minsum<<endl;
        int r=minsum-maxx-maxy;
        if(r<=0){
            continue;
        }

        int v=1<<(cnt-1);
        if(cnt%2==0){
            v=-v;
        }

        ans+=v*r*r;
        // cout<<mask<<":   "<<cnt<<' '<<r<<endl;
    }
    // cout<<ans<<endl;
    cout<<ans/2<<(ans%2?".5":".0")<<endl;

    return 0;
}
