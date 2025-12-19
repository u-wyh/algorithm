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
