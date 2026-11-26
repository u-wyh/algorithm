// https://www.luogu.com.cn/problem/P3068
// 题意：输入奶牛总数 N、朋友圈个数 G，以及每个朋友圈的大小 k 和其中的 k 头牛编号（朋友圈两两不完全相同，初始 1 号牛已被邀请）。
// 若某个大小为 k 的朋友圈中已有 k - 1 头牛被邀请，则剩下那 1 头牛也必须被邀请（具有连锁传递性）。
// 求最终至少需要邀请多少头奶牛参加聚会。
// 输出一行一个整数，表示最少需要邀请的奶牛头数。
// 数据范围：对于 100% 的数据，1 <= N <= 10^6，所有朋友圈大小之和 M 满足 1 <= M <= 2.5*10^5。
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5e4+50,maxm=1e6+50;
int n,m,num;
int in[maxn];
bool vis[maxm];
vector<int>G[maxm],g[maxm];
queue<int>q;
void Push(int a){
    int i,u;
    for(i=0;i<g[a].size();i++){
        u=g[a][i];
        if(!vis[u]){
            vis[u]=1;
            q.push(u);
            num++;
        }
    }
}
int main(){
    cin>>n>>m;
    int i,k,j,u;
    for(i=1;i<=m;i++){
        scanf("%d",&j);
        in[i]=j;
        for(;j;j--){
            scanf("%d",&k);
            G[k].push_back(i);
            g[i].push_back(k);
        }
    }
    q.push(1);
    vis[1]=1;
    while(!q.empty()){
        k=q.front();
        q.pop();
        for(i=0;i<G[k].size();i++){
            u=G[k][i];
            in[u]--;
            if(in[u]==1){
                Push(u);
            }
        }
    }
    printf("%d",num+1);
    return 0;
}
