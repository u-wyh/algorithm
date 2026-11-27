// https://www.luogu.com.cn/problem/P11993
// 题意：
// N 个城市构成以 1 为根的内向树（i 连向 P_i < i），
// 危险度为到 1 经过的边数，初始各点有 K_i 只海狸。
// 共 Q 天操作：
// 1 X Y 将当前危险度 X 的所有点上全部海狸迁至路径上可达的危险度 Y
// 的点。
// 2 A L 使点 A 增加 L 只海狸；3 B 查询点 B 当前海狸数量。
// 对每个 3 类操作输出一行查询结果。
// 数据范围：
// 2 <= N <= 2000000
// 1 <= Q <= 2000000
// 0 <= K_i <= 100
// 1 <= P_i < i
// 0 <= Y_j < X_j <= N - 1
// 1 <= A_j, B_j <= N
// 1 <= L_j <= 100
// 算法标签：线段树合并、DFS序
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e6+5;
const int MAXT = MAXN*60;

int n,m;
int val[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt=1;

int dfn[MAXN];
// int seg[MAXN];
int sz[MAXN];
int dfncnt;
int dep[MAXN];

int root[MAXN<<1];
int ls[MAXT];
int rs[MAXT];
int sum[MAXT];
// bool tag[MAXT];
int cntv;

int id[MAXN];

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

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    dfn[u]=++dfncnt;
    // seg[dfncnt]=u;
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v,u);
        sz[u]+=sz[v];
    }
}

void up(int x){
    sum[x]=sum[ls[x]]+sum[rs[x]];
}

int add(int pos,int jobv,int l,int r,int i){
    int rt=i;
    if(rt==0){
        rt=++cntv;
    }
    if(l==r){
        sum[rt]+=jobv;
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            ls[rt]=add(pos,jobv,l,mid,ls[rt]);
        }
        else{
            rs[rt]=add(pos,jobv,mid+1,r,rs[rt]);
        }
        up(rt);
    }
    return rt;
}

int merge(int l,int r,int t1,int t2){
    if(t1==0||t2==0){
        return t1+t2;
    }
    if(l==r){
        sum[t1]+=sum[t2];
    }
    else{
        int mid=(l+r)>>1;
        ls[t1]=merge(l,mid,ls[t1],ls[t2]);
        rs[t1]=merge(mid+1,r,rs[t1],rs[t2]);
        up(t1);
    }
    return t1;
}

int query(int jobl,int jobr,int l,int r,int i){
    if(i==0){
        return 0;
    }
    if(jobl<=l&&r<=jobr){
        return sum[i];
    }
    else{
        int mid=(l+r)>>1;
        int ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,ls[i]);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,rs[i]);
        }
        return ans;
    }
}

int main()
{
    n=read();
    for(int i=2;i<=n;i++){
        int u=read();
        addedge(u,i);
    }
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    // dep[0]=-1;
    dfs(1,0);

    int maxdep=0;
    for(int i=1;i<=n;i++){
        root[dep[i]]=add(dfn[i],val[i],1,n,root[dep[i]]);
        id[dep[i]]=dep[i];
        maxdep=max(maxdep,dep[i]);
    }

    m=read();
    while(m--){
        int op,x,y;
        op=read(),x=read();
        if(op==1){
            y=read();
            x++,y++;
            root[id[y]]=merge(1,n,root[id[y]],root[id[x]]);
            id[x]=++maxdep;
        }
        else if(op==2){
            y=read();
            root[id[dep[x]]]=add(dfn[x],y,1,n,root[id[dep[x]]]);
        }
        else{
            cout<<query(dfn[x],dfn[x]+sz[x]-1,1,n,root[id[dep[x]]])<<endl;
        }
    }
    return 0;
}