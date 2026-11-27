// https://www.luogu.com.cn/problem/P3489
// 题意：输入城镇数 n（1 为起点，n 为终点）、道路数 m、怪物种类数
// p、铁匠数 k，接下来 k 个铁匠所在城镇及能锻造克制的怪物列表
// 再输入 m 条双向边耗时与路上怪物列表。
// 主角初始无剑，经过有铁匠的城镇可免费拿到对应能对付部分怪物的剑（携剑数量不限）；
// 只有拥有路上全部怪物种类对应的剑才能通过该道路。
// 输出一个整数，表示从 1 号城镇走到 n 号城镇的最短总时间；
// 若无法到达输出 -1。
// 数据范围：1 <= n <= 200，0 <= m <= 3000，
// 1 <= p <= 13，0 <= k <= n，1 <= t_i <= 500
// 无重边。
// 算法标签：Dijkstra、状态压缩
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;
const int MAXM = 3005;
const int INF = 1e9;

int n,m,p,k;
int val[MAXN];
int f[MAXN][1<<13];
bool vis[MAXN][1<<13];

int cnt=1;
int head[MAXN];
int to[MAXM<<1];
int nxt[MAXM<<1];
int weight[MAXM<<1];
int limit[MAXM<<1];

struct node{
    int pos,st,val;
};
struct compare{
    bool operator()(const node &a,const node &b){
        return a.val>b.val;
    }
};
priority_queue<node,vector<node>,compare>heap;

void addedge(int u,int v,int w,int t){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    limit[cnt]=t;
    head[u]=cnt++;
}

int dijkstra(){
    for(int i=1;i<=n;i++){
        for(int j=0;j<(1<<p);j++){
            f[i][j]=INF;
        }
    }
    f[1][val[1]]=0;
    heap.push({1,val[1],0});
    while(!heap.empty()){
        node u=heap.top();
        //cout<<u.pos<<' '<<u.st<<' '<<u.val<<endl;
        heap.pop();
        if(vis[u.pos][u.st]){
            continue;
        }
        vis[u.pos][u.st]=true;
        if(u.pos==n){
            return u.val;
        }
        for(int i=head[u.pos];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if((u.st&limit[i])==limit[i]){
                if(f[v][u.st|val[v]]>f[u.pos][u.st]+w){
                    f[v][u.st|val[v]]=f[u.pos][u.st]+w;
                    heap.push({v,u.st|val[v],f[v][u.st|val[v]]});
                }
            }
        }
    }
    return -1;
}

int main()
{
    cin>>n>>m>>p>>k;
    for(int i=1;i<=k;i++){
        int pos,num;
        cin>>pos>>num;
        for(int i=1;i<=num;i++){
            int v;
            cin>>v;
            v--;
            val[pos]|=(1<<v);
        }
    }
    for(int i=1;i<=m;i++){
        int u,v,w,num,t=0;
        cin>>u>>v>>w>>num;
        for(int i=1;i<=num;i++){
            int val;
            cin>>val;
            val--;
            t|=(1<<val);
        }
        //cout<<' '<<i<<' '<<t<<endl;
        addedge(u,v,w,t);
        addedge(v,u,w,t);
    }
    // for(int i=1;i<=n;i++){
    //     cout<<i<<' '<<val[i]<<endl;
    // }
    cout<<dijkstra();
    return 0;
}