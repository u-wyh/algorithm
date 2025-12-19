#include<bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
const int MAXN = 5e3+5;

int n;
int nums[MAXN];
int f[MAXN];
int g[MAXN];

int main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>nums[i];
        }
        for(int i=1;i<=n;i++){
            f[i]=(i>nums[1]||n-i>=nums[1]);
        }
        for(int len=2;len<=n;len++){
            for(int i=1;i<=n;i++){
                g[i]=f[i];
            }
            for(int l=1,r=len;r<=n;l++,r++){
                f[l]=((n-l>=nums[len])&&(nums[len]>=len-1))*g[l+1]+((r>nums[len])&&(nums[len]>=len-1))*g[l];
                f[l]%=MOD;
            }
        }
        cout<<f[1]<<endl;
        // for(int i=1;i<=n;i++){
        //     f[i][i]=(i>nums[1]||n-i>=nums[1]);
        // }
        // for(int len=2;len<=n;len++){
        //     for(int l=1,r=len;r<=n;l++,r++){
        //         f[l][r]=((n-l>=nums[len])&&(nums[len]>=len-1))*f[l+1][r]+((r>nums[len])&&(nums[len]>=len-1))*f[l][r-1];
        //         f[l][r]%=MOD;
        //     }
        // }
        // cout<<f[1][n]<<endl;
    }
    return 0;
}