#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3e5+5;
const int INF = 2e18;

int n,m;
int val[MAXN];
// bool vis[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt=1;

int least[MAXN];
int profit[MAXN];

int ls[MAXN];
int rs[MAXN];
int dist[MAXN];
int fa[MAXN];

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

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

int merge(int i,int j){
    if (i == 0 || j == 0) {
        //遇到了空节点 那么就以非空作为头结点
        return i + j;
    }
    if (least[i] > least[j] ) {
        //谁小谁做头 后面是题目规定  一般都是这个规定
        int tmp = i;
        i = j;
        j = tmp;
    }
    rs[i] = merge(rs[i], j);//将右儿子和它做合并
    //检查dist有没有问题 是否需要交换
    if (dist[ls[i]] < dist[rs[i]]) {
        int tmp = ls[i];
        ls[i] = rs[i];
        rs[i] = tmp;
    }
    dist[i] = dist[rs[i]] + 1;
    fa[ls[i]] = fa[rs[i]] = i;
    return i;
}

void compute(int u){
    int now=0;
    
}

void dfs(int u){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v);
        fa[u]=merge(find(u),find(v));
    }
    compute(u);
}

struct compare{
    bool operator()(const int a,const int b){
        return least[a]>least[b];
    }
};
priority_queue<int,vector<int>,compare>heap;

int compute(){
    int now=m;
    heap.push(1);
    while(!heap.empty()){
        int u=heap.top();
        heap.pop();

        if(now<least[u]){
            break;
        }
        now+=val[u];
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            heap.push(v);
        }
    }
    return now-m;
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        int fa;
        val[i+1]=read(),fa=read()+1;
        addedge(fa,i+1);
    }
    dist[0]=-1;
    for(int i=1;i<=n+1;i++){
        // least[i]=INF;
        fa[i]=i;
        ls[i]=rs[i]=dist[i]=0;
    }
    dfs(1);
    cout<<compute()<<endl;
    return 0;
}