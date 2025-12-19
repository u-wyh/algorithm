#include<bits/stdc++.h>
using namespace std;

int walk[8][2]={{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
struct node{
    int x,y;
    int h;
}arr[500000];
int k=1;
int nums[705][705];
bool flag[705][705];
int ans=0;
int n,m;

bool cmp(node a,node b){
    return a.h>b.h;
}

void dfs(int x,int y){
    flag[x][y]=true;
    for(int i=0;i<8;i++){
        int ux=walk[i][0]+x,uy=walk[i][1]+y;
        if(!flag[ux][uy]&&nums[ux][uy]<=nums[x][y]&&ux>0&&ux<=n&&uy>0&&uy<=m){
            dfs(ux,uy);
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>nums[i][j];
            arr[k].x=i;
            arr[k].y=j;
            arr[k++].h=nums[i][j];
        }
    }
    sort(arr+1,arr+k,cmp);
    k-=1;
    for(int i=1;i<=k;i++){
        if(!flag[arr[i].x][arr[i].y]){
            ans++;
            dfs(arr[i].x,arr[i].y);
        }
    }
    cout<<ans;
    return 0;
}
