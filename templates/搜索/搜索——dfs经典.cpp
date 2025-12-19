//P1123
//这道题目虽然简单  但确实是一道比较好的题目了
//d[x][y]表示的是这个位置上是否可以选择  如果是0  可以选择 否则不行
//并且如果选择了  那么周围8个数字不能选
//dfs过程是每一行从左到右进行
#include<bits/stdc++.h>
using namespace std;

int t,n,m;
int d[8][8],nums[8][8];
int ans=0,now=0;
int walk[8][2]={{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};

void dfs(int x,int y){
    if(y==m+1){
        //表示换行  去下一行找
        dfs(x+1,1);
        return ;
    }
    if(x==n+1){
        //说明结束了  统计答案
        ans=max(ans,now);
        return ;
    }
    dfs(x,y+1);
    if(d[x][y]==0){
        //表示这个数字可以选择
        now+=nums[x][y];
        for(int k=0;k<8;k++){
            int ux=x+walk[k][0],uy=y+walk[k][1];
            d[ux][uy]++;
        }
        dfs(x,y+1);
        //恢复数据
        now-=nums[x][y];
        for(int k=0;k<8;k++){
            int ux=x+walk[k][0],uy=y+walk[k][1];
            d[ux][uy]--;
        }
    }
}

int main()
{
    cin>>t;
    while(t--){
        memset(d,0,sizeof(d));
        memset(nums,0,sizeof(nums));
        ans=0;
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                cin>>nums[i][j];
            }
        }
        now=0;
        ans=0;
        dfs(1,1);
        cout<<ans<<endl;
    }
    return 0;
}
