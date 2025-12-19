#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5005;

int n,m;
int arr[MAXN];
int f[MAXN];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        f[i]=1e9;
    }
    f[1]=1;
    for(int i=1;i<=n;i++){
        double x=INT_MIN;
        for(int j=1;j<=m&&i+j<=n;j++){
            if(x<=1.0*(arr[i+j]-arr[i])/j){
                f[i+j]=min(f[i+j],f[i]+1);
                x=1.0*(arr[i+j]-arr[i])/j;
            }
        }
    }
    cout<<f[n]<<endl;
    return 0;
}
