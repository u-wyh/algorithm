#include<bits/stdc++.h>
using namespace std;

int n,m;
int arr[55];

double f[55][55];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>arr[i];
    }
    f[1][1]=1.0;
    for(int i=2;i<=n;i++){
        for(int j=1;j<=m;j++){
            int p=(arr[j]%i==0)?i:arr[j]%i;
            for(int k=1;k<=i-1;k++){
                p++;
                if(p>i){
                    p=1;
                }
                f[i][p]+=f[i-1][k]/(1.0*m);
            }
        }
    }
    for(int i=1;i<=n;i++){
        printf("%.2lf%% ",f[n][i]*100.0);
    }
    return 0;
}
