#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2005;

int n;
int f[MAXN][MAXN/2];
int arr[MAXN];

int main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>arr[i];
        }
        for(int i=1;i<=n;i++){
            for(int j=0;j<=n/2;j++){
                f[i][j]=2e9;
            }
        }
        f[1][0]=-2e9;
        for(int i=2;i<=n;i++){
            for(int j=0;j<=min(n/2,i);j++){
                if(arr[i]>arr[i-1]){
                    f[i][j]=min(f[i][j],f[i-1][j]);
                }
                if(arr[i]>f[i-1][j]){
                    f[i][i-j]=min(f[i][i-j],arr[i-1]);
                }
            }
        }
        if(f[n][n/2]==2e9){
            cout<<"No!"<<endl;
        }
        else{
            cout<<"Yes!"<<endl;
        }
    }
    return 0;
}
