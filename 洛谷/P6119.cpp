#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;

int n;
int a[MAXN];
int b[MAXN];
int f[MAXN][MAXN];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            f[i][j]=max(f[i-1][j],f[i][j-1]);
            if(abs(a[i]-b[j])<=4){
                f[i][j]=max(f[i][j],f[i-1][j-1]+1);
            }
        }
    }
    cout<<f[n][n]<<endl;
    return 0;
}