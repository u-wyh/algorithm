#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXM = 10005;

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;
int dis[MAXN];
int updateCnt[MAXN];
bool enter[MAXN];
queue<int >q;
int n,m;

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

bool spfa(int s) {
    dis[s] = 0;
    updateCnt[s]++;
    q.push(s) ;
    enter[s] = true;
    cout<<666<<endl;
    while (!q.empty()) {
        cout<<1<<endl;
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
                    if (++updateCnt[v] > n+1) {
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
    int t;
    cin>>t;
    while(t--){
        cin>>n>>m;
        build();
        for(int i=0;i<=n;i++){
            addEdge(n+1,i,0);
        }
        for(int i=1;i<=m;i++){
            int l,r,w;
            cin>>l>>r>>w;
            addEdge(l-1,r,w);
            addEdge(r,l-1,-w);
        }
        if(!spfa(n+1)){
            cout<<"true"<<endl;
        }else
            cout<<"false"<<endl;
    }
    return 0;
}
