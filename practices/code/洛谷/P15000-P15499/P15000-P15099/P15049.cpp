// https://www.luogu.com.cn/problem/P15049
// 题意：支持加边、回滚历史版本、查询连通块内第 k 小顶点编号。
// 输入：首行 n, q, g，后 q 行操作：1 v k、2 v u 或 3 x。
// 规则：1 查 v 所在块第 k 小编号（无则 -1）；2 连边；
// 3 回退到第 x 次操作后。
// 输出：对每个 1 类操作输出一行查询结果。
// 数据范围：1 <= n, q <= 5*10^5，0 <= g <= 9。
// 数据范围：1 <= v, u, k <= n，
// 0 <= x < i（i 为当前操作编号）。
// 难度评分：2500（洛谷分级换算）
// 算法标签：并查集、分块
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXB = 500;

int n,m,g;

int blen;
int bnum;

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;

int op[MAXN];
int x[MAXN];
int y[MAXN];

int ans[MAXN];

int fa[MAXN];
int sz[MAXN];
int cnt[MAXN][MAXB];

int rollback[MAXN][2];
int opsize;

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

int find(int x){
    while(x!=fa[x]){
        x=fa[x];
    }
    return x;
}

void prepare(){
    blen=1400;
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=n;i++){
        cnt[i][(i-1)/blen+1]=1;
    }
    for(int i=1;i<=n;i++){
        fa[i]=i;
        sz[i]=1;
    }
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        if(sz[fx]>sz[fy]){
            swap(fx,fy);
        }
        ++opsize;
        rollback[opsize][0]=fx;
        rollback[opsize][1]=fy;

        fa[fx]=fy;
        sz[fy]+=sz[fx];
        for(int i=1;i<=bnum;i++){
            cnt[fy][i]+=cnt[fx][i];
        }
    }
}

void undo(){
    int fx=rollback[opsize][0];
    int fy=rollback[opsize][1];
    opsize--;
    fa[fx]=fx;
    sz[fy]-=sz[fx];
    for(int i=1;i<=bnum;i++){
        cnt[fy][i]-=cnt[fx][i];
    }
}

int query(int x,int k){
    int fx=find(x);
    if(sz[fx]<k){
        return -1;
    }

    int now=0;
    for(int i=1;i<=bnum;i++){
        if(now+cnt[fx][i]>=k){
            int l=(i-1)*blen+1;
            int r=i*blen;
            for(int j=l;j<=r;j++){
                if(find(j)==fx){
                    now++;
                    if(now==k){
                        return j;
                    }
                }
            }
        }
        else{
            now+=cnt[fx][i];
        }
    }
}

void dfs(int u){
    int now=opsize;
    if(op[u]==1){
        ans[u]=query(x[u],y[u]);
    }
    else if(op[u]==2){
        un(x[u],y[u]);
    }

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v);
    }
    while(now!=opsize){
        undo();
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>g;
    for(int i=1;i<=m;i++){
        cin>>op[i];
        if(op[i]==1){
            addedge(i-1,i);
            cin>>x[i]>>y[i];
        }
        else if(op[i]==2){
            addedge(i-1,i);
            cin>>x[i]>>y[i];
        }
        else{
            cin>>x[i];
            addedge(x[i],i);
        }
    }

    prepare();
    dfs(0);

    for(int i=1;i<=m;i++){
        if(op[i]==1){
            cout<<ans[i]<<endl;
        }
    }
    return 0;
}