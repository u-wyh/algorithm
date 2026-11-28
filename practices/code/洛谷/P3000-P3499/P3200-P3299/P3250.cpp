// https://www.luogu.com.cn/problem/P3250
// 题意：输入树点数 n、事件数 m、n-1 条树边，
// 以及按时刻 1..m 依次发生的 m 个事件。
// 事件 0 在路径 (a, b) 上新增重要度为 v 的交互请求；
// 事件 1 结束第 t 时刻新增的请求；
// 事件 2 询问若当前时刻节点 x 故障，
// 所有尚未结束且路径不经过 x 的请求中重要度的最大值（无则输出 -1）。
// 对每个事件 2 输出一行最大重要度。
// 数据范围：2 <= n <= 10^5，1 <= m <= 2*10^5，
// 其余输入值不超过 10^9。
// 难度评分：2700（洛谷分级换算）
// 算法标签：整体二分、树状数组、倍增
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;
const int MAXH = 20;
const int INF = 1e9+5;

int n,m;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int fa[MAXN];
int dep[MAXN];
int st[MAXN][MAXH];
int dfn[MAXN];
int sz[MAXN];
int dfncnt;

int tree[MAXN];

// 事件编号组成的数组
int eid[MAXM];
// 如果op == 0，添加点x到点y，重要度为v的路径
// 如果op == 1，删除点x到点y，重要度为v的路径
// 如果op == 2，查询和x相关的答案，y表示问题的编号
int op[MAXM];
int x[MAXM];
int y[MAXM];
int v[MAXM];
int cntq = 0;

int lset[MAXM];
int rset[MAXM];

int ans[MAXM];

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
    head[u]=cnt++;
}

void dfs(int u,int f){
    fa[u]=f;
    dep[u]=dep[f]+1;
    sz[u]=1;
    dfn[u]=++dfncnt;
    st[u][0]=f;
    for(int i=1;i<MAXH;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==f){
            continue;
        }
        dfs(v,u);
        sz[u]+=sz[v];
    }
}

int lca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int i=MAXH-1;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b){
        return a;
    }
    for(int i=MAXH-1;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

inline int lowbit(int x){
    return x&(-x);
}

void add(int x,int v){
    while(x<=n){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

void pathadd(int a,int b,int v){
    int lcaab=lca(a,b);
    int falca=st[lcaab][0];
    add(dfn[a],v);
    add(dfn[b],v);
    add(dfn[lcaab],-v);
    if(falca!=0){
        add(dfn[falca],-v);
    }
}

int pathquery(int x){
    return query(dfn[x]+sz[x]-1)-query(dfn[x]-1);
}

void compute(int el,int er,int vl,int vr){
    if(el>er){
        return ;
    }
    if(vl==vr){
        for(int i=el;i<=er;i++){
            int id=eid[i];
            if(op[id]==2){
                ans[y[id]]=vl;
            }
        }
    }
    else{
        int mid=(vl+vr)/2;
        int lsz=0,rsz=0;
        int request=0;
        for(int i=el;i<=er;i++){
            int id=eid[i];
            if(op[id]==0){
                if(v[id]<=mid){
                    lset[++lsz]=id;
                }
                else{
                    pathadd(x[id],y[id],1);
                    request++;
                    rset[++rsz]=id;
                }
            }
            else if(op[id]==1){
                if(v[id]<=mid){
                    lset[++lsz]=id;
                }
                else{
                    pathadd(x[id],y[id],-1);
                    request--;
                    rset[++rsz]=id;
                }
            }
            else{
                if(pathquery(x[id])==request){
                    lset[++lsz]=id;
                }
                else{
                    rset[++rsz]=id;
                }
            }
        }
        for (int i = 1; i <= lsz; i++) {
            eid[el + i - 1] = lset[i];
        }
        for (int i = 1; i <= rsz; i++) {
            eid[el + lsz + i - 1] = rset[i];
        }
        //复原操作
        for (int i = 1; i <= rsz; i++) {
            int id = rset[i];
            if (op[id] == 0 && v[id] > mid) {
                pathadd(x[id], y[id], -1);
            }
            if (op[id] == 1 && v[id] > mid) {
                pathadd(x[id], y[id], 1);
            }
        }
        compute(el, el + lsz - 1, vl, mid);
        compute(el + lsz, er, mid + 1, vr);
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
    for(int i=1;i<=m;i++){
        op[i]=read();
        x[i]=read();
        if(op[i]==0){
            y[i]=read(),v[i]=read();
        }
        else if(op[i]==1){
            y[i]=y[x[i]];
            v[i]=v[x[i]];
            x[i]=x[x[i]];
        }
        else{
            y[i]=++cntq;
        }
        eid[i]=i;
    }
    dfs(1,0);
    compute(1,m,0,INF);
    for(int i=1;i<=cntq;i++){
        if (ans[i] == 0) {
            cout << -1 << '\n';
        } else {
            cout << ans[i] << '\n';
        }
    }
    return 0;
}