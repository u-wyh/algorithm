//两次dfs
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

int n;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
// 直径的开始点
int start;
// 直径的结束点
int en;
// 直径长度
int diameter;
// dist[i] : 从规定的头节点出发，走到i的距离
int dist[MAXN];

void dfs(int u,int f){
    dist[u]=dist[f]+1;
    for(int i=head[u];i>0;i=Next[i]){
        if(to[i]!=f){
            dfs(to[i],u);
        }
    }
}

void road() {
    dist[0]=-1;
    dfs(1, 0);
    //这个起点是随机的  一般都是1
    start = 1;
    for (int i = 2; i <= n; i++) {
        if (dist[i] > dist[start]) {
            start = i;
        }
    }
    //选择离他距离最大的点  作为头结点
    dfs(start, 0);
    en = 1;
    for (int i = 2; i <= n; i++) {
        if (dist[i] > dist[en]) {
            en = i;
        }
    }
    diameter = dist[en];
}
//两次调用dfs

int main()
{
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;
    }
    road();
    cout<<diameter;
    return 0;
}
