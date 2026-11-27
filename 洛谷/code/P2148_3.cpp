// https://www.luogu.com.cn/problem/P2148
// 题意：T 组数据，每组有 N 堆石子（N 为偶数），第 2k-1 与 2k 堆为一组。
// 每次任选一堆移走，并将同组另一堆分成两堆（均 > 0），无法操作（全为 1）者输。
// 判断先手是否必胜，每组输出 YES 或 NO。
// 数据范围：1 <= T <= 20，1 <= N <= 2*10^4，1 <= S_i <= 2*10^9。
#include<bits/stdc++.h>
// 算法标签：SG函数、记忆化搜索
using namespace std;

int n;
int sg[21][21];

int dfs(int a,int b){
    if(a>b){
        swap(a,b);
    }
    if(sg[a][b]!=-1){
        return sg[a][b];
    }
    bool vis[400];
    for(int i=0;i<400;i++){
        vis[i]=false;
    }
    for(int i=1;i<a;i++){
        int j=a-i;
        if(i&&j){
            vis[dfs(i,j)]=true;
        }
    }
    for(int i=1;i<b;i++){
        int j=b-i;
        if(i&&j){
            vis[dfs(i,j)]=true;
        }
    }
    int mex=0;
    while(vis[mex]){
        mex++;
    }
    sg[a][b]=sg[b][a]=mex;
    return mex;
}

void prepare(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            sg[i][j]=-1;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(sg[i][j]==-1){
                dfs(i,j);
            }
        }
    }
}

int main()
{
    cin>>n;
    prepare();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            // cout<<i<<' '<<j<<endl;
            cout<<setw(5)<<sg[i][j];
        }
        cout<<endl;
    }
    return 0;
}