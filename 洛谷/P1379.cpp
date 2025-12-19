#include<bits/stdc++.h>
using namespace std;

int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

int main()
{
    int c[3][3];
    int n;
    queue<int>q;
    map<int,int>graph;
    cin>>n;
    q.push(n);
    graph[n]=1;
    while(!q.empty()){
        int u=q.front();
        int tmp=u;
        q.pop();
        int x,y;
        if(u==123804765){
            break;
        }
        for(int i=2;i>=0;i--){
            for(int j=2;j>=0;j--){
                c[i][j]=u%10;
                u/=10;
                if(c[i][j]==0){
                    x=i;
                    y=j;
                }
            }
        }
        for(int i=0;i<4;i++){
            int nx=x+walk[i][0];
            int ny=y+walk[i][1];
            if(nx<0||ny<0||nx>2||ny>2)
                continue; //越界就不执行
            swap(c[nx][ny],c[x][y]);
            int ns=0;
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    ns=ns*10+c[i][j];//矩阵转数列
                }
            }
            if(graph[ns]==0){
                graph[ns]=graph[tmp]+1;
                q.push(ns);
            }
            swap(c[nx][ny],c[x][y]);//状态复原
        }
    }
    cout<<graph[123804765]-1<<endl;
    return 0;
}
