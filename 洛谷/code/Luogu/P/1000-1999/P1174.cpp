#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;

int n,m,k;

int arr[MAXN][MAXN];
int op[MAXN][MAXN];
int sum[MAXN][MAXN];
int f[MAXN][MAXN];

int main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>arr[i][j];
            char c;
            cin>>c;
            if(c=='N'){
                op[i][j]=0;
            }
            else{
                op[i][j]=1;
            }
        }
    }
    for(int j=1;j<=m;j++){
        int u=n;
        while(op[u][j]&&u){
            sum[j][0]+=arr[u][j];
            u--;
        }
        for(int p=1;p<=k;p++){
            sum[j][p]=sum[j][p-1];
            if(u<=0){
                continue;
            }
            sum[j][p]+=arr[u][j];
            u--;
            while(op[u][j]&&u){
                sum[j][p]+=arr[u][j];
                u--;
            }
        }
    }
//    for(int j=1;j<=m;j++){
//        for(int p=0;p<=k;p++){
//            cout<<sum[j][p]<<' ';
//        }
//        cout<<endl;
//    }
    for(int j=1;j<=m;j++){
        f[j][0]=f[j-1][0]+sum[j][0];
        for(int p=1;p<=k;p++){
            f[j][p]=f[j-1][p]+sum[j][0];
            for(int q=1;q<=p;q++){
                f[j][p]=max(f[j][p],f[j-1][p-q]+sum[j][q]);
            }
        }
    }
    int ans=0;
    for(int i=0;i<=k;i++){
        ans=max(ans,f[m][i]);
    }
    cout<<ans<<endl;
    return 0;
}

