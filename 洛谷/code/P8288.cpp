// https://www.luogu.com.cn/problem/P8288
// 题意：n 个烟花，第 i 个美观度为 v_i。
// 关系一：若 i 与 a_i 同时燃放，i 的美观度减少 b_i。
// 关系二：给出 m 个系列，每个烟花至多属于一个系列，同一系列烟花必须同时燃放，其中主烟花为 p_i。
// 特别地，若系列 S_1 的主烟花 p_1 的关系一指向系列 S_2 中的烟花
// 则 S_1 内其余烟花与非 S_1, S_2 系列烟花之间形成的关系一不减少美观度。
// 选择若干烟花燃放（可不放），求最大总美观度。
// 数据范围：100% 数据满足 0 <= m <= n <= 5*10^5，0 <= b_i <= v_i <= 10^12，1 <= a_i <= n
// a_i != i。
// 算法标签：基环树、树形动态规划、拓扑排序
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;
const int INF = (1ll<<60);

int n,m;

// 分别表示价值  相损目标  造成的影响
int a[MAXN];
int b[MAXN];
int c[MAXN];

// 每个烟花属于的系列
int belong[MAXN];
// 每个系列的目标
int aim[MAXN];
// 每个系列的核心
int core[MAXN];
// 选择这个系列的收获
int val[MAXN];
int cost[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;

int state[MAXN];
int from[MAXN];
bool cycle[MAXN];

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs(int u){
    state[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(state[v]==0){
            from[v]=u;
            dfs(v);
        }
        else if(state[v]==1){
            cycle[v]=true;
            for(int i=u;i!=v;i=from[i]){
                cycle[i]=true;
            }
        }
    }
    state[u]=2;
}

int que[MAXN];
int dp0[MAXN];
int dp1[MAXN];
bool vis[MAXN];
int in[MAXN];
int ans;

int cnta;
int arr[MAXN];

void dpOnTree(){
    int ql=1,qr=0;
    for(int i=1;i<=m;i++){
        if(in[i]==0){
            que[++qr]=i;
        }
    }

    while(ql<=qr){
        int u=que[ql++];
        int fa=aim[u];

        if(fa==0){
            ans+=max(dp0[u],dp1[u]);
            continue;
        }

        dp0[fa]+=max(dp0[u],dp1[u]);
        dp1[fa]+=max(dp0[u],dp1[u]-cost[u]);

        in[fa]--;
        if(in[fa]==0){
            que[++qr]=fa;
        }
    }
}

int dpOnCycle(int start){
    cnta=0;
    int u=start;
    do{
        arr[++cnta]=u;
        vis[u]=true;
        u=aim[u];
    }while(u!=start);

    int res=-INF;
    for(int first=0;first<=1;first++){
        int f0=-INF;
        int f1=-INF;

        if(first==0){
            f0=dp0[arr[1]];
        }
        else{
            f1=dp1[arr[1]];
        }

        for(int i=2;i<=cnta;i++){
            int p=arr[i-1];
            int u=arr[i];

            int nf0=max(f0,f1)+dp0[u];
            int nf1=max(f0+dp1[u],dp1[u]+f1-cost[p]);

            f0=nf0;
            f1=nf1;
        }

        if(first==0){
            res=max(res,max(f0,f1));
        }
        else{
            res=max(res,max(f0,f1-cost[arr[cnta]]));
        }
    }
    return res;
}

int compute(){
    ans=0;
    for(int i=1;i<=m;i++){
        dp0[i]=0;
        dp1[i]=val[i];

        if(aim[i]!=0){
            in[aim[i]]++;
        }
    }

    dpOnTree();
    for(int i=1;i<=m;i++){
        if(cycle[i]&&!vis[i]){
            ans+=dpOnCycle(i);
        }
    }
    return ans;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i]>>c[i];
    }
    for(int i=1;i<=m;i++){
        int k;
        cin>>core[i]>>k;
        for(int j=1;j<=k;j++){
            int v;
            cin>>v;
            belong[v]=i;
        }
    }
    for(int i=1;i<=n;i++){
        if(belong[i]==0){
            belong[i]=++m;
            core[m]=i;
        }
    }

    for(int i=1;i<=m;i++){
        aim[i]=belong[b[core[i]]];
    }

    for(int i=1;i<=n;i++){
        int x=belong[i];
        int y=belong[b[i]];
        val[x]+=a[i];
        if(x==y){
            val[x]-=c[i];
        }
        else if(y==aim[x]){
            cost[x]+=c[i];
        }
    }

    for(int i=1;i<=m;i++){
        if(i==aim[i]){
            aim[i]=0;
        }
    }

    for(int i=1;i<=m;i++){
        if(aim[i]){
            addedge(i,aim[i]);
        }
    }

    for(int i=1;i<=m;i++){
        if(state[i]==0){
            dfs(i);
        }
    }

    cout<<compute()<<endl;
    return 0;
}