#include<bits/stdc++.h>
using namespace std;
const int MAXN = 55;

int n,m,h;
int arr[MAXN][MAXN];

int main()
{
    cin>>n>>m>>h;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>arr[i][j];
            if(arr[i][j]<0){
                arr[i][j]=1;
            }
            else if(arr[i][j]>0&&arr[i][j]<h){
                arr[i][j]=2;
            }
            else if(arr[i][j]>0&&arr[i][j]>=h){
                arr[i][j]=3;
            }
            else{
                arr[i][j]=0;
            }
        }
    }
    // cout<<endl;
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=m;j++){
    //         cout<<arr[i][j]<<' ';
    //     }
    //     cout<<endl;
    // }
    int cnt=0;
    int ans=0,x=0,y=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(arr[i][j]!=0){
                continue;
            }
            int res=0;
            int up=i-1,dn=i+1,l=j-1,r=j+1;
            while(up>0){
                if(arr[up][j]==3){
                    break;
                }
                if(arr[up][j]==1){
                    res++;
                }
                up--;
            }
            while(dn<=n){
                if(arr[dn][j]==3){
                    break;
                }
                if(arr[dn][j]==1){
                    res++;
                }
                dn++;
            }
            while(l>0){
                if(arr[i][l]==3){
                    break;
                }
                if(arr[i][l]==1){
                    res++;
                }
                l--;
            }
            while(r<=m){
                if(arr[i][r]==3){
                    break;
                }
                if(arr[i][r]==1){
                    res++;
                }
                r++;
            }
            if(res>=3){
                cnt++;
            }
            if(res>ans){
                x=i,y=j;
                ans=res;
            }
        }
    }
    cout<<cnt<<endl;
    cout<<(x-1)<<' '<<(y-1)<<endl;

    return 0;
}