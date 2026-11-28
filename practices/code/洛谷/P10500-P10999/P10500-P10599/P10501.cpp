// https://www.luogu.com.cn/problem/P10501
// 题意：给一块 W×H 的方格纸。两人轮流选一块现有纸片，沿格线横切或竖切为两块。
// 谁切出一块只含一格的纸片谁赢。
// 双方最优时，先手能赢输出 WIN，否则输出 LOSE。
// 数据范围：多组输入，2 ≤ W,H ≤ 200。
// 难度评分：2000（洛谷分级换算）
// 算法标签：SG函数、记忆化搜索

#include<bits/stdc++.h>
using namespace std;

int n,m;
int sg[205][205];

int dfs(int a,int b){
    if(sg[a][b]!=-1){
        return sg[a][b];
    }
    bool vis[1005]={0};

    for(int i=2;i<a-1;i++){
        int j=a-i;
        vis[dfs(i,b)^dfs(j,b)]=true;
    }
    for(int i=2;i<b-1;i++){
        int j=b-i;
        vis[dfs(i,a)^dfs(j,a)]=true;
    }
    int mex=0;
    while(vis[mex]){
        mex++;
    }
    sg[a][b]=sg[b][a]=mex;
    return mex;
}

void prepare(){
    for(int i=0;i<=200;i++){
        for(int j=0;j<=200;j++){
            sg[i][j]=-1;
        }
    }
    sg[1][1]=0;
    
    for(int i=0;i<=200;i++){
        for(int j=0;j<=200;j++){
            if(sg[i][j]==-1){
                dfs(i,j);
            }
        }
    }
}

int main()
{
    prepare();
    while(cin>>n>>m){
        if(sg[n][m]){
            cout<<"WIN"<<endl;
        }
        else{
            cout<<"LOSE"<<endl;
        }
    }
    return 0;
}