#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
int nums[MAXN];
char str[MAXN];
int vis[MAXN];

int main()
{
    int t;
    cin>>t;
    while(t--){
        cin>>n>>m;
        for(int i=0;i<m*n;i++){
            cin>>str[i];
        }
        for(int i=0;i<m*n;i++){
            cin>>nums[i];
        }
        for(int i=0;i<m*n;i++){

            int x=i/m,y=i%m;
            if(str[i]=='u'){
                if(x-nums[i]>=0){
                    vis[i-nums[i]*m]++;
                }
            }
            if(str[i]=='d'){
                if(x+nums[i]<n){
                    vis[i+x*nums[i]]++;
                }
            }
            if(str[i]=='l'){
                if(y-nums[i]>=0){
                    vis[i-nums[i]]++;
                }
            }
            if(str[i]=='r'){
                if(y+nums[i]<m){
                    vis[i+nums[i]]++;
                }
            }
        }
        int cnt0=0,cnt2=0,f=0;
        for(int i=0;i<m*n;i++){
            if(vis[i]==0){
                cnt0++;
            }
            if(vis[i]==2){
                cnt2++;
            }
            if(vis[i]>=3){
                f=1;
                break;
            }
        }
        if(f){
            cout<<"No\n";
        }
        else{
            if((cnt0==0&&cnt2==0)||(cnt0==1&&cnt2==1)||(cnt0==1&&cnt2==0))
                cout<<"Yes\n";
            else
                cout<<"No\n";
        }

        for(int i=0;i<m*n;i++){
            nums[i]=0;
            str[i]=' ';
            vis[i]=0;
        }
    }
    return 0;
}
