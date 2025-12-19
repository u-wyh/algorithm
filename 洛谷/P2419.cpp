#include<bits/stdc++.h>
using namespace std;

int nums[105][105];
int n,m;

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            nums[i][j]=0;
        }
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        nums[u][v]=1;
        nums[v][u]=-1;
    }
    for (int bridge = 1; bridge <= n; bridge++) { // Ìø°å
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (nums[i][bridge] != 0&& nums[bridge][j] != 0&& nums[bridge][j] == nums[i][bridge] ) {
                    nums[i][j] = nums[i][bridge] ;
                    nums[j][i] = -nums[i][j];
                }
            }
        }
    }
//    for(int i=1;i<=n;i++){
//        for(int j=1;j<=n;j++){
//            cout<<nums[i][j]<<' ';
//        }
//        cout<<endl;
//    }
    int ans=0;
    for(int i=1;i<=n;i++){
        int k=1;
        for(int j=1;j<=n;j++){
            if(nums[i][j]!=0){
                k++;
            }
        }
        if(k==n)
            ans++;
    }
    cout<<ans;
    return 0;
}
