#include<bits/stdc++.h>
using namespace std;

int nums[105][105];
int n,sti,stj,eni,enj;
int walk[4][2]={{1,0},{0,-1},{-1,0},{0,1}};
int ans=INT_MAX;
bool vis[105][105];

void dfs(int x,int y,int dire,int k){
    if(k>=ans)
        return ;
    if(x==eni&&y==enj){
        ans=min(ans,k);
        return ;
    }
    for(int i=0;i<4;i++){
        int ux=x+walk[i][0],uy=y+walk[i][1];
        if(ux==0||ux>n||uy==0||uy>n||vis[ux][uy]||nums[ux][uy]==0){
            continue;
        }
        vis[ux][uy]=true;
        if(dire==4||dire==i){
            dfs(ux,uy,i,k);
        }else{
            if(k+1<ans)
                dfs(ux,uy,i,k+1);
        }
        vis[ux][uy]=false;
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            char c;
            cin>>c;
            if(c=='A')
                sti=i,stj=j,nums[i][j]=1;
            else if(c=='B')
                eni=i,enj=j,nums[i][j]=1;
            else if(c=='.')
                nums[i][j]=1;
            else
                nums[i][j]=0;
        }
    }
    vis[sti][stj]=true;
    dfs(sti,stj,4,0);
    if(ans==INT_MAX)
        ans=-1;
    cout<<ans;
    return 0;
}
