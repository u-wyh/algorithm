#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e7+5;

int n,k;
int comb[1005][15];
int pos[15];

int ans[MAXN];
signed main()
{
    cin>>k>>n;
    if(n==1){
        cout<<1;
        for(int i=1;i<k;i++){
            cout<<0;
        }
        return 0;
    }
    comb[0][0]=1;
    comb[1][0]=1;
    comb[1][1]=1;
    for(int i=2;i<=1000;i++){
        comb[i][0]=1;
        if(i<=n) comb[i][i]=1;
        for(int j=1;j<=min(i-1,n);j++){
            comb[i][j]=comb[i-1][j-1]+comb[i-1][j];
        }
    }
    for(int i=n;i>=1;i--){
        bool flag=false;
        for(int j=i;j;j++){
            if(comb[j-1][i-1]>k){
                pos[i]=j;
                // cout<<i<<' '<<pos[i]<<' '<<k<<' '<<comb[j-1][i-1]<<endl;
                break;
            }
            k-=comb[j-1][i-1];
            if(k==0){
                flag=true;
                for(int k=i;k>=1;k--){
                    pos[k]=j--;
                    // cout<<k<<' '<<pos[k]<<endl;
                }
                break;
            }
        }
        if(flag){
            break;
        }
    }
    for(int i=1;i<=n;i++){
        ans[pos[i]]=1;
    }
    for(int i=pos[n];i>=1;i--){
        cout<<ans[i];
    }
    return 0;
}