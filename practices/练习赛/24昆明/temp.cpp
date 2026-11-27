#include <iostream>
#include <bits/stdc++.h>
#define int long long
const int N=1005;
using namespace std;

int a[N][N];
void solve(){
    int n,m;
    cin>>n>>m;
    //int x=min(n,m);
    int cnt=1;
    for(int i=1;i<=n;i++){
        int x=max(1LL,i-m+1);
        int y=min(i,m);
        while(x>=1&&y<=m){
            a[x][y]=cnt;
            cnt++;
            x--;
            y++;
        }
    }
    cout<<"Yes\n";
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cout<<a[i][j]<<" ";
        }
        cout<<"\n";
    }
    return ;


}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}