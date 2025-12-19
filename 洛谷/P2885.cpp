#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 105;

int n,m,c;
int f[MAXN][MAXM];
int arr[MAXN];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>c;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        m=max(m,arr[i]);
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            f[i][j]=1e9;
        }
    }
    for(int i=arr[1];i<=m;i++){
        f[1][i]=(i-arr[1])*(i-arr[1]);
    }
    for(int i=2;i<=n;i++){
        int k=1e9;
        for(int j=arr[i-1];j<=m;j++){
            k=min(k,f[i-1][j]-j*c);
            if(j>=arr[i]){
                f[i][j]=k+(j-arr[i])*(j-arr[i])+c*j;
            }
        }
        k=1e9;
        for(int j=m;j>=arr[i];j--){
            k=min(k,f[i-1][j]+j*c);
            f[i][j]=min(f[i][j],k-c*j+(j-arr[i])*(j-arr[i]));
        }
    }
    int ans=1e9;
    for(int i=arr[n];i<=m;i++){
        ans=min(ans,f[n][i]);
    }
    cout<<ans<<endl;
    return 0;
}
