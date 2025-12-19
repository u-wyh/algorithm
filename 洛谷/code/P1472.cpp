#include<bits/stdc++.h>
using namespace std;
const int MOD = 9901;

int n,m;
int f[205][105];

int main()
{
    cin>>n>>m;
    for(int k=1;k<=m;k++){
        f[1][k]=1;
    }
    for(int k=2;k<=m;k++){
        for(int i=3;i<=n;i+=2){
            for(int j=1;j<i;j+=2){
                f[i][k]+=(f[j][k-1]*f[i-j-1][k-1]);
                f[i][k]%=MOD;
            }
        }
    }
    cout<<((f[n][m]-f[n][m-1])%MOD+MOD)%MOD<<endl;
    return 0;
}
