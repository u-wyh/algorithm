//https://www.luogu.com.cn/problem/P1656
// 桥其实和tarjan没有什么本质上的区别  都是一样的
// 桥的判断方法是对于一条边  如果下面的点的low大于上面点的dfn  说明是桥
// 如果这条边是回溯的  那不算
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 155;
const int MAXM = 5005;

int n,m;
vector<pair<int,int>>bridges;

int dfn[MAXN];
int low[MAXN];
int dfncnt;

int cnt=1;
int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int weight[MAXM<<1];//记录这条边的编号

void addedge(int u,int v,int i){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=i;
    head[u]=cnt++;
}

void tarjan(int u,int id){
    //表示当前来到了点u  是通过真实编号id这条边来的
    dfn[u]=low[u]=++dfncnt;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(!dfn[v]){
            tarjan(v,w);
            low[u]=min(low[u],low[v]);
            if(low[v]>dfn[u]){
                bridges.push_back({u,v});
            }
        }
        else if(w!=id){
            //不能走回头路  其实也就是为了防止走上父亲的点
            low[u]=min(low[u],dfn[v]);
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v,i);
        addedge(v,u,i);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i,0);
        }
    }
    sort(bridges.begin(), bridges.end());
    for (auto &p : bridges) {
        cout << p.first << " " << p.second << endl;
    }
    return 0;
}