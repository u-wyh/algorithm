#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;

int n,m;
int nums[MAXN][MAXN];
int sti,stj,eni,enj;
int walk[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
int t1[MAXN][MAXN],t2[MAXN][MAXN];
queue<pair<int,int>>q;

int main()
{
    cin>>m>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>nums[i][j];
            if(nums[i][j]==2){
                sti=i;
                stj=j;
            }
            if(nums[i][j]==3){
                eni=i;
                enj=j;
            }
            t1[i][j]=INT_MAX/2;
            t2[i][j]=INT_MAX/2;
        }
    }
    q.push({sti,stj});
    t1[sti][stj]=0;
    while(!q.empty()){
        int x=q.front().first;
        int y=q.front().second;
        q.pop();
        for(int i=0;i<4;i++){
            int ux=x+walk[i][0];
            int uy=y+walk[i][1];
            if(nums[ux][uy]==1||ux>n||uy>m||ux<=0||uy<=0||t1[ux][uy]!=INT_MAX/2)
                continue;
            t1[ux][uy]=t1[x][y]+1;
            q.push({ux,uy});
        }
    }
    q.push({eni,enj});
    t2[eni][enj]=0;
    while(!q.empty()){
        int x=q.front().first;
        int y=q.front().second;
        q.pop();
        for(int i=0;i<4;i++){
            int ux=x+walk[i][0];
            int uy=y+walk[i][1];
            if(nums[ux][uy]==1||ux>n||uy>m||ux<=0||uy<=0||t2[ux][uy]!=INT_MAX/2)
                continue;
            t2[ux][uy]=t2[x][y]+1;
            q.push({ux,uy});
        }
    }
//    for(int i=1;i<=n;i++){
//        for(int j=1;j<=m;j++){
//            cout<<t1[i][j]<<' ';
//        }
//        cout<<endl;
//    }
//    for(int i=1;i<=n;i++){
//        for(int j=1;j<=m;j++){
//            cout<<t2[i][j]<<' ';
//        }
//        cout<<endl;
//    }
    int ans=INT_MAX;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(nums[i][j]==4){
                //cout<<i<<' '<<j<<' '<<t1[i][j]<<' '<<t2[i][j]<<endl;
                ans=min(ans,t1[i][j]+t2[i][j]);
                //cout<<ans<<' '<<t1[i][j]<<' '<<t2[i][j]<<endl;
            }
        }
    }
    cout<<ans;
    return 0;
}
