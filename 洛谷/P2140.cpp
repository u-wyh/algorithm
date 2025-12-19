#include<bits/stdc++.h>
using namespace std;

int n,m,k;
int arr[35][35];
int sum[35][35];
int limit;

int f1[35][35][35][35];
int f2[35][35][35][35];

int main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>arr[i][j];
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+arr[i][j];
        }
    }
    limit=sum[n][m]-k;
    for(int x1=1;x1<=n;x1++){
        for(int y1=1;y1<=m;y1++){
            for(int x2=x1;x2<=n;x2++){
                for(int y2=y1;y2<=m;y2++){
                    if(sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1]+sum[x1-1][y1-1]>=limit){
                        f1[x1][y1][x2][y2]=1;
                        f2[x1][y1][x2][y2]=sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1]+sum[x1-1][y1-1]-limit;
                    }
                }
            }
        }
    }
    for(int x1=1;x1<=n;x1++){
        for(int y1=1;y1<=m;y1++){
            for(int x2=x1;x2<=n;x2++){
                for(int y2=y1;y2<=m;y2++){
                    for(int k=x1;k<x2;k++){
                        if(f1[x1][y1][k][y2]==0||f1[k+1][y1][x2][y2]==0){
                            continue;
                        }
                        if(f1[x1][y1][x2][y2]<(f1[x1][y1][k][y2]+f1[k+1][y1][x2][y2])){
                            f1[x1][y1][x2][y2]=f1[x1][y1][k][y2]+f1[k+1][y1][x2][y2];
                            f2[x1][y1][x2][y2]=min(f2[x1][y1][k][y2],f2[k+1][y1][x2][y2]);
                        }
                        else if(f1[x1][y1][x2][y2]==(f1[x1][y1][k][y2]+f1[k+1][y1][x2][y2])){
                            f2[x1][y1][x2][y2]=max(f2[x1][y1][x2][y2],min(f2[x1][y1][k][y2],f2[k+1][y1][x2][y2]));
                        }
                    }
                    for(int k=y1;k<y2;k++){
                        if(f1[x1][y1][x2][k]==0||f1[x1][k+1][x2][y2]==0){
                            continue;
                        }
                        if(f1[x1][y1][x2][y2]<(f1[x1][y1][x2][k]+f1[x1][k+1][x2][y2])){
                            f1[x1][y1][x2][y2]=f1[x1][y1][x2][k]+f1[x1][k+1][x2][y2];
                            f2[x1][y1][x2][y2]=min(f2[x1][y1][x2][k],f2[x1][k+1][x2][y2]);
                        }
                        else if(f1[x1][y1][x2][y2]==(f1[x1][y1][x2][k]+f1[x1][k+1][x2][y2])){
                            f2[x1][y1][x2][y2]=max(f2[x1][y1][x2][y2],min(f2[x1][y1][x2][k],f2[x1][k+1][x2][y2]));
                        }
                    }
                }
            }
        }
    }
    cout<<f1[1][1][n][m]<<' '<<f2[1][1][n][m]<<endl;
    return 0;
}
