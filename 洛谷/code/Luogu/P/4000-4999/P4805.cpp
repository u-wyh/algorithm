#include<bits/stdc++.h>
using namespace std;
const int MAXN = 405;

int n;
int f[MAXN][MAXN];
int ans=0;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>f[i][i];
        ans=max(ans,f[i][i]);
    }
    for(int len=2;len<=n;len++){
        for(int l=1,r=len;r<=n;l++,r++){

            for(int k=l;k<r;k++){
                if(f[l][k]==0||f[k+1][r]==0||f[l][k]!=f[k+1][r]){
                    continue;
                }
                f[l][r]=f[l][k]+f[k+1][r];
            }

            for(int k=l+1,p=r-1;k<=p;){
                if(f[l][r]){
                    break;
                }
                if(f[l][k-1]==0){
                    k++;
                }
                else if(f[p+1][r]==0){
                    p--;
                }
                else if(f[l][k-1]>f[p+1][r]){
                    p--;
                }
                else if(f[l][k-1]<f[p+1][r]){
                    k++;
                }
                else{
                    if(f[k][p])
                        f[l][r]=f[l][k-1]+f[k][p]+f[p+1][r];
                    else{
                        k++,p--;
                    }
                }
            }

            ans=max(ans,f[l][r]);
        }
    }
    cout<<ans<<endl;
    return 0;
}