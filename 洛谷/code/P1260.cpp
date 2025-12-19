#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int MAXM = 10005;

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;
int n,m;
int dis[MAXN];
int updateCnt[MAXN];
bool enter[MAXN];
queue<int >q;

void build() {
    cnt = 1;
    fill(head+1, head+n + 1, 0);
    fill(enter+1,enter+ n + 1, false);
    fill(dis+ 1,dis+ n + 1, INT_MAX);
    fill(updateCnt+1,updateCnt+ n + 1, 0);
    while(!q.empty()){
        q.pop();
    }
}

void addEdge(int u, int v, int w) {
    Next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

bool spfa() {
    dis[0] = 0;
    updateCnt[0]++;
    q.push(0) ;
    enter[0] = true;
    //这道题目中的源点都是0 保持不变   所以以上的操作都针对1
    //实际上应该理解为是针对源点的
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        enter[u] = false;
        for (int ei = head[u], v, w; ei > 0; ei = Next[ei]) {
            v = to[ei];
            w = weight[ei];
            if (dis[u] + w < dis[v]) {
                //如果值变小了  那么就要改变
                dis[v] = dis[u] + w;
                if (!enter[v]) {
                    //如果不在队列中才会加入
                    // 松弛次数超过n-1就有负环
                    if (++updateCnt[v] > n) {
                        return true;
                    }
                    q.push(v);
                    enter[v] = true;
                }
            }
        }
    }
    return false;
}

int main()
{
    cin>>n>>m;
    build();
    for(int i=1;i<=n;i++){
        addEdge(0,i,0);
    }
    for(int i=1,u,v,w;i<=m;i++){
        cin>>u>>v>>w;
        addEdge(v,u,w);
    }
    if(spfa()){
        cout<<"NO SOLUTION";
    }
    else{
        int ans=INT_MAX;
        for(int i=1;i<=n;i++){
            ans=min(ans,dis[i]);
        }
        for(int i=1;i<=n;i++){
            dis[i]-=ans;
            cout<<dis[i]<<endl;
        }
    }
    return 0;
}
