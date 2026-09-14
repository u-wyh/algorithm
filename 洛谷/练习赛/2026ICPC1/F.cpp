#include<bits/stdc++.h>
using namespace std;
const int MAXN = 55;

int n,m;
int val[MAXN][14];
int sum[MAXN];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>val[i][j];
            sum[i]+=val[i][j];
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(sum[i]<sum[i-1]){
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}
/*
5 3
-100 -200 -300
-100 -200 -250
-150 -200 -200
-100 -150 -250
-200 -200 -250

4 2
-5 -5
-6 -5
-10 -1
-6 -6
*/