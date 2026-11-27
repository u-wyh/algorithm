// https://www.luogu.com.cn/problem/P5157
// 题意：给一棵 N 个点的树和 M 条有向先序限制 (a_i, b_i)（a_i 必须先于 b_i 离开）
// 每次只能让当前剩余图中度数 <= 1 的点离开（剩最后 1 点时除外），判断每个点能否成为最后一个离开的点。
// 数据范围：1 <= N, M <= 10^5。
#include<bits/stdc++.h>
// 算法标签：拓扑排序、深度优先搜索
using namespace std;
const int MAXN = 1e5+5;

int n,m;

int head[MAXN];
int nxt[MAXN<<2];
int to[MAXN<<2];
int cnt=1;
int now;
int in[MAXN];
bool limit[MAXN];
bool ans[MAXN];

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
    nxt[cnt]=head[u];
    to[cnt]=v;
    in[v]++;
    head[u]=cnt++;
}

int findroot(){
    queue<int>q;
    for(int i=1;i<=n;i++){
        if(in[i]==1){
            q.push(i);
        }
    }
    int cnt=0;
    int root=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        cnt++;
        root=u;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(--in[v]==1){
                q.push(v);
            }
        }
    }
    if(cnt!=n){
        return -1;
    }
    return root;
}

void dfs(int u,int fa){
    ans[u]=true;
    for(int i=head[u];i;i=nxt[i]){
        if(i>=now){
            continue;
        }
        int v=to[i];
        if(v!=fa&&!limit[v]){
            dfs(v,u);
        }
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    now=cnt;
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        limit[u]=true;
    }
    int root=findroot();
    if(root!=-1){
        dfs(root,0);
    }
    for(int i=1;i<=n;i++){
        if(ans[i]){
            cout<<1<<endl;
        }
        else{
            cout<<0<<endl;
        }
    }
    return 0;
}