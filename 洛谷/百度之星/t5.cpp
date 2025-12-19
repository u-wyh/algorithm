#include<bits/stdc++.h>
using namespace std;
#define int long long

int n,d,l;

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin>>T;
    while(T--){
        cin>>n>>d>>l;
        int maxx=1+d-n;
        int dis=l-n-1;

        int ans=dis/d*n;
        int res=dis%d;
        if(res<maxx){
            ans+=1;
        }
        else{
            ans+=1;
            res-=maxx;
            ans+=res+1;
        }
        cout<<ans<<' ';
        int ans1=(l-n-1)*n+1;
        cout<<ans1<<endl;
    }
    return 0;
}
/*
2
3 4 6
3 6 6
*/