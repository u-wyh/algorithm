// https://www.luogu.com.cn/problem/P1135
// 题意：第 i 层电梯装有数字 K[i]，在这层按上或下，会移动恰好 K[i] 层，越界时按键无效。求从 A 到 B 最少按几次，无法到达输出 -1。
// 数据范围：1 ≤ N ≤ 200，1 ≤ A,B ≤ N，0 ≤ K[i] ≤ N。

#include<iostream>
#include<queue>

using namespace std;

#define MAXN 310

struct node{
    int floor,d;
};
queue<node>Q;
int n,a,b;
int k[300],vis[300];

int main()
{
    cin>>n>>a>>b;
    for(int i=1;i<=n;i++){
        cin>>k[i];
    }
    Q.push((node){a,0});
    vis[a]=1;
    node now;
    while(!Q.empty()){
        now=Q.front();
        Q.pop();
        if(now.floor==b)
            break;
        for(int sign=-1;sign<=1;sign+=2){
            int dist =now.floor+k[now.floor]*sign;
            if(dist>=1 && dist<=n && vis[dist]==0){
                Q.push((node){dist,now.d+1});
                vis[dist]=1;
            }
        }
    }
    if(now.floor==b)
        cout<<now.d<<endl;
    else
        cout<<-1<<endl;
    return 0;
}

