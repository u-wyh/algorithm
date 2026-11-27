#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int INF = 1e16;

int n;
int val[MAXN];
int edge[MAXN];

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        edge[i]=0;
    }
    if(n==1){
        cout<<val[1]<<endl;
        return ;
    }

    for(int i=1;i<n;i++){
        edge[i]=val[i]+val[i+1];
    }
    edge[n]=val[n]+val[1];

    int ans=INF;
    int minn=INF;
    int sum=0;
    for(int i=1;i<n;i++){
        sum+=edge[i];
        minn=min(minn,edge[i]);
        ans=min(ans,val[1]+sum+(n-1-i)*minn);
    }

    minn=INF;
    sum=0;
    for(int i=n;i>=2;i--){
        sum+=edge[i];
        minn=min(minn,edge[i]);
        ans=min(ans,val[1]+sum+(n-1-(n-i+1))*minn);
    }
    cout<<ans<<endl;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
/*
7
4
3 4 2 1
1
7
5
8 0 9 0 1
7
5 1 9 0 0 9 9
4
1 1000 1000 1
6
4 0 9 0 1 9
3
1000000000 1000000000 1000000000
*/