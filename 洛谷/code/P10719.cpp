#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;

int nums[MAXN][MAXN];
char c;
int n,m,k;

bool check(int x){
    for(int l=n;l>0;l--){
        for(int w=x/l;w>0;w--){
            for(int i=l;i<=n;i++){
                for(int j=w;j<=m;j++){
                    if(nums[i][j]+nums[i-l][j-w]-nums[i][j-w]-nums[i-l][j]>=k)
                        return true;
                }
            }
        }
    }
    return false;
}

int main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>c;
            nums[i][j]=c-'0';
            //printf("%3d",nums[i][j]);
        }
        //cout<<endl;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            nums[i][j]+=nums[i][j-1]+nums[i-1][j]-nums[i-1][j-1];
            //printf("%3d",nums[i][j]);
        }
        //cout<<endl;
    }
    if(k>nums[n][m]){
        cout<<0;
        return 0;
    }
    int l=k,r=n*m,mid,ans=r;
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    cout<<ans;
    return 0;
}
