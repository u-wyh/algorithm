#include<bits/stdc++.h>
using namespace std;
const int MAXN = 55;
const int MAXM = 20005;

auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};

priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);
int m;
int dis[MAXN];
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;
bool vis[MAXN];

int main()
{
    cin>>m;
    for(int i=1;i<=m;i++){
        char a,b;
        int u,v,w;
        cin>>a>>b>>w;
        u=a-'A'+1;
        v=b-'A'+1;

        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=w;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        weight[cnt]=w;
        head[v]=cnt++;
    }//这道题建议使用邻接表  有重边
    for(int i=1;i<=54;i++){
        dis[i]=1e9;
    }
    dis[26]=0;
    heap.push({26,0});
    while(!heap.empty()){
        int u=heap.top().first;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=head[u];i>0;i=Next[i]){
            int v=to[i];
            int w=weight[i];
            if(!vis[v]&&w+dis[u]<dis[v]){
                dis[v]=w+dis[u];
                heap.push({v,dis[v]});
            }
        }
    }
    int ans1=1e9,ans2=0;
    for(int i=1;i<=25;i++){
        if(ans1>dis[i]){
            ans2=i;
            ans1=dis[i];
        }
    }
    printf("%c %d",ans2+'A'-1,dis[ans2]);
    return 0;
}
