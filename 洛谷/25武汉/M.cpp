#include <bits/stdc++.h>
#define int long long
const int mod=998244353;
using namespace std;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    int matrix[20][20];
    for(int i=1;i<=n;i++) cin>>matrix[i][i];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            matrix[i][j]=matrix[i][i];
    for(int i=1;i<=n;i++){
        matrix[i][i]=(matrix[i][i]+1)%mod;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            cout<<matrix[i][j]<<' ';
        cout<<'\n';
    }
    return 0;
}