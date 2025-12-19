#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 105;

int n,m;
int arr[MAXN];
int sum[MAXN];
vector<int>nums[MAXM];
int all[MAXM];
bool vis[MAXM];
vector<int>ans;

void dfs(int u){
    if(u==n){
        cout<<ans[0];
        for(int i=1;i<m;i++){
            cout<<' '<<ans[i];
        }
        exit(0);
    }
    for(int i=1;i<=m;i++){
        if(vis[i]){
            continue;
        }
        int k=nums[i].size();
        if(nums[i][0]==arr[u]&&nums[i][k-1]==arr[u+k-1]&&all[i]==(sum[u+k-1]-sum[u-1])){
            u=u+k-1;
            ans.push_back(i);
            vis[i]=true;

            dfs(u);

            u=u+1-k;
            vis[i]=false;
            ans.pop_back();
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        sum[i]=sum[i-1]+arr[i];
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        int k;
        cin>>k;
        for(int j=1;j<=k;j++){
            int v;
            cin>>v;
            all[i]+=v;
            nums[i].push_back(v);
        }
        // cout<<all[i]<<' ';
    }
    // cout<<endl;
    dfs(1);
    // int u=1;
    // while(u<n){
    //     for(int i=1;i<=m;i++){
    //         if(vis[i]){
    //             continue;
    //         }
    //         int k=nums[i].size();
    //         if(nums[i][0]==arr[u]&&nums[i][k-1]==arr[u+k-1]&&all[i]==(sum[u+k-1]-sum[u-1])){
    //             u=u+k-1;
    //             ans.push_back(i);
    //             vis[i]=true;
    //             break;
    //         }
    //     }
    // }

    // cout<<ans[0];
    // for(int i=1;i<m;i++){
    //     cout<<' '<<ans[i];
    // }
    return 0;
}