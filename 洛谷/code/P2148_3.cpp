// https://www.luogu.com.cn/problem/P2148
#include<bits/stdc++.h>
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