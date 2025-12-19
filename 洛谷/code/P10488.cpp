#include<bits/stdc++.h>
using namespace std;
const int MAXN = 17;

int n;
int arr[MAXN];
int help[6][MAXN];//如果只用一维数组 中间递归时会发生变化  导致错误
int ans;

int predict(){
    int cnt=0;
    for(int i=1;i<n;i++){
        if(arr[i+1]-arr[i]!=1){
            cnt++;
        }
    }
    return (cnt+2)/3;
}

bool IDAdfs(int t){
    int pre=predict();
    if(pre+t>ans){
        return false;
    }
    if(pre==0){
        return true;
    }
//    for(int i=1;i<=n;i++){
//        help[t][i]=arr[i];
//    }
    for(int len=1;len<=n;len++){
        for(int l=1;l+len-1<=n;l++){
            int r=l+len-1;
            for(int k=r+1;k<=n;k++){

                memcpy(help[t],arr,sizeof(arr));
                int y=l;
                for(int x=r+1;x<=k;x++,y++){
                    arr[y]=help[t][x];
                }
                for(int x=l;x<=r;x++,y++){
                    arr[y]=help[t][x];
                }

                if(IDAdfs(t+1)){
                    return true;
                }
                memcpy(arr,help[t],sizeof(arr));
//
//                for(int i=l;i<=k;i++){
//                    arr[i]=help[t][i];
//                }
            }
        }
    }
    return false;
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>arr[i];
        }
        ans=predict();
        while(!IDAdfs(0)){
            ans++;
            if(ans==5){
                break;
            }
        }
        if(ans>=5){
            cout<<"5 or more"<<endl;
        }
        else
            cout<<ans<<endl;
    }
    return 0;
}
