// https://www.luogu.com.cn/problem/P2919
// 题意：输入矩阵行数 N、列数 M，以及 N 行 M 列的整数高度矩阵 H_{ij}。
// 由高度相同的八连通（横纵坐标差绝对值均 <= 1）元素构成的连通块，若其所有外部相邻格子高度都严格低于它，则称该连通块为一个山顶。
// 统计矩阵中一共有多少个山顶。
// 输出一行一个整数，表示山顶的数量。
// 数据范围：对于 100% 的数据，1 < N <= 700，1 < M <= 700，0 <= H_{ij} <= 10000。
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
