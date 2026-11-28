// https://www.luogu.com.cn/problem/P3603
// 题意：输入树点数 n、询问数 m、加密标记 f，n 个点权，n-1 条树边；
// 之后 m 次询问，每次给出链数 a 及 a 条树链 (x_k, y_k)。
// 若 f=1，
// 输入中的 2a 个端点均需异
// 或上一次询问两个答案之和 lastans（首次为 0）；
// 每次询问求这 a 条树链的
// 并集中不同点权的种类数与点权集合的 mex（最小未出现的非负整数）。
// 输出 m 行，每行两个整数，分别为不同点权种数与 mex。
// 数据范围：设所有询问的 a 之和为 q，n, q <= 10^5，
// 点权 <= 3*10^4（非负整数）。
// 难度评分：2500（洛谷分级换算）
// 算法标签：树分块、倍增、位集
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXV = 3e4+5;
const int MAXB = 401;
const int MAXH = 20;

int n,m,f,p;
int val[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int marknum;
// 表示这个节点的被标记编号 没有就是0
int kthnum[MAXN];
int marknode[MAXN];
// 记录每个节点上方的第一个被标记的节点
int up[MAXN];

int dep[MAXN];
int st[MAXN][MAXH];

bitset<MAXV>downset[MAXB];

bitset<MAXV>ans;

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

int lca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int i=p;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b){
        return a;
    }

    for(int i=p;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs(v,u);
        }
    }
}

void query(int x,int y){
    while(kthnum[x]==0&&x!=y){
        ans[val[x]]=1;
        x=st[x][0];
    }
    while(up[x]&&dep[up[x]]>dep[y]){
        ans|=downset[kthnum[x]];
        x=up[x];
    }
    while(x!=y){
        ans[val[x]]=1;
        x=st[x][0];
    }
}

void prepare(){
    p=log2(n);
    dfs(1,0);
    int len=(int)sqrt(n*10);
    marknum=(n+len-1)/len;
    for(int b=1,pick;b<=marknum;b++){
        do{
            pick=rand()%n+1;
        }while(kthnum[pick]);
        kthnum[pick]=b;
        marknode[b]=pick;
    }
    for(int b=1,cur;b<=marknum;b++){
        downset[b][val[marknode[b]]]=1;
        cur=st[marknode[b]][0];
        while(cur!=0){
            if(kthnum[cur]){
                up[marknode[b]]=cur;
                break;
            }
            else{
                downset[b][val[cur]]=1;
                cur=st[cur][0];
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    srand(time(0));
    cin>>n>>m>>f;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }

    prepare();

    int lastans=0;
    for(int i=1;i<=m;i++){
        ans.reset();
        int k;
        cin>>k;
        for(int i=1;i<=k;i++){
            int a,b;
            cin>>a>>b;
            if(f){
                a^=lastans;
                b^=lastans;
            }
            int fa=lca(a,b);
            query(a,fa);
            query(b,fa);
            ans[val[fa]]=1;
        }
        int ans1=ans.count();
        int ans2=MAXV;
        for(int i=0;i<MAXV;i++){
            if(ans[i]==0){
                ans2=i;
                break;
            }
        }
        cout<<ans1<<' '<<ans2<<endl;
        lastans=ans1+ans2;
    }
    return 0;
}