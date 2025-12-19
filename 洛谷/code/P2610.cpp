#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;
// 直径的开始点
int start;
// 直径的结束点
int en;
// 直径长度
int diameter;
// dist[i] : 从规定的头节点出发，走到i的距离
int dist[MAXN];

map<pair<int,int>,int>graph;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

void addedge(int u,int v){
    //cout<<cnt<<": "<<u<<' '<<v<<endl;
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u,int f){
    dist[u]=dist[f]+1;
    for(int i=head[u];i>0;i=Next[i]){
        if(to[i]!=f){
            dfs(to[i],u);
        }
    }
}

void road() {
    dfs(1, 0);
    //这个起点是随机的  一般都是1
    start = 1;
    for (int i = 2; i <= n; i++) {
        if (dist[i] > dist[start]) {
            start = i;
        }
    }
    //选择离他距离最大的点  作为头结点
    //因为边权为正  所以对于任意节点而言  最远的点一定是直径端点中的一个
    dfs(start, 0);
    en = 1;
    for (int i = 2; i <= n; i++) {
        if (dist[i] > dist[en]) {
            en = i;
        }
    }
    diameter = dist[en];
}

int main()
{
    n=read();
    n-=2;
    for(int i=1;i<=n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        int sum=u+v+w,tmp=min(u,min(v,w));
        u=max(u,max(v,w));
        w=tmp;
        v=sum-u-w;
        //cout<<u<<' '<<v<<' '<<w<<endl;
        //cout<<graph[(u,v)]<<' '<<graph[(u,w)]<<' '<<graph[(v,w)]<<endl;
        if(graph[make_pair(u,v)]!=0){
            //cout<<111<<endl;
            addedge(i,graph[make_pair(u,v)]);
            addedge(graph[make_pair(u,v)],i);
        }
        else{
            graph[make_pair(u,v)]=i;
        }
        if(graph[make_pair(u,w)]!=0){
            //cout<<222<<endl;
            addedge(i,graph[make_pair(u,w)]);
            addedge(graph[make_pair(u,w)],i);
        }
        else{
            graph[make_pair(u,w)]=i;
        }
        if(graph[make_pair(v,w)]!=0){
            //cout<<333<<endl;
            addedge(i,graph[make_pair(v,w)]);
            addedge(graph[make_pair(v,w)],i);
        }
        else{
            graph[make_pair(v,w)]=i;
        }
    }
    road();
    cout<<diameter<<endl;
    return 0;
}
