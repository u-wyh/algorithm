#include<bits/stdc++.h>
using namespace std;

int n;
int nums[26][3];
map<pair<int,int>,int>mp;
map<pair<int,int>,int>stat;
int ans=INT_MIN;
int ans1,ans2;
int arr[26];

void dfs(int u,int a,int b,int c,int limit,int op,int sta){
    if(u==limit+1){
        if(op==1){
            if(mp[{a-b,a-c}]<a){
                mp[{a-b,a-c}]=a;
                stat[{a-b,a-c}]=sta;
            }
        }
        else{
            int s=stat[{b-a,c-a}];
            int v=mp[{b-a,c-a}]+a;
            if(s){
                if(v>ans){
                    ans=v;
                    ans1=s;
                    ans2=sta;
                }
            }
        }
    }
    else{
        dfs(u+1,a+nums[u][0],b+nums[u][1],c,limit,op,sta*3+2);
        dfs(u+1,a+nums[u][0],b,c+nums[u][2],limit,op,sta*3+1);
        dfs(u+1,a,b+nums[u][1],c+nums[u][2],limit,op,sta*3);
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i][0]>>nums[i][1]>>nums[i][2];
    }
    dfs(1,0,0,0,(n+1)/2,1,0);
    dfs((n+1)/2+1,0,0,0,n,2,0);
    if(ans==INT_MIN){
        cout<<"Impossible";
        return 0;
    }
    for(int i=(n+1)/2;i>=1;i--){
        arr[i]=ans1%3;
        ans1/=3;
    }
    for(int i=n;i>=(n+1)/2+1;i--){
        arr[i]=ans2%3;
        ans2/=3;
    }
    for(int i=1;i<=n;i++){
        if(arr[i]==0){
            cout<<"MW"<<endl;
        }
        else if(arr[i]==1){
            cout<<"LW"<<endl;
        }
        else{
            cout<<"LM"<<endl;
        }
    }
    // cout<<ans<<endl;
    return 0;
}