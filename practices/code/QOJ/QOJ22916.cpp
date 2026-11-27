// https://qoj.ac/problem/22916/statement/en
// 题意：每组给长度为 n 的 01 串 A、B 和 m 个区间。
// 每次操作选一个允许的区间，把区间内的 0 和 1 互换。
// 对每个 k，独立判断禁用第 k 个区间时
// 能否经过若干次操作把 A 变成 B。
// 输出：每组输出长为 m 的 01 串，可行记 1，否则记 0。
// 数据范围：1 <= T <= 1000，
// 1 <= n, m <= 2*10^5，
// 1 <= l_i <= r_i <= n，区间互不相同。
// 所有组的 n 之和、m 之和各不超过 2*10^5。
// 算法标签：Tarjan、桥、异或差分
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n,m,T;
string a,b;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int id[MAXN<<1];
int cntg=1;

int val[MAXN];

int dfn[MAXN];
int low[MAXN];
int dfncnt;
int sum[MAXN];

char ans[MAXN];

inline void addedge(int u,int v,int w){
    nxt[cntg]=head[u];
    to[cntg]=v;
    id[cntg]=w;
    head[u]=cntg++;
}

void tarjan(int u,int preEdge){
    dfn[u]=low[u]=++dfncnt;
    sum[u]=val[u];
    for(int i=head[u];i;i=nxt[i]){
        if((i^1)==preEdge){
            continue;
        }
        int v=to[i];
        if(!dfn[v]){
            tarjan(v,i);
            low[u]=min(low[u],low[v]);
            sum[u]^=sum[v];
            if(low[v]>dfn[u] && sum[v]){
                ans[id[i]]='0';
            }
        }
        else{
            low[u]=min(low[u],dfn[v]);
        }
    }
}

void solve(){
    cin>>n>>m>>a>>b;
    for(int i=1;i<=n+1;i++){
        head[i]=0;
        val[i]=0;
        dfn[i]=low[i]=0;
    }

    for(int i=1;i<=n;i++){
        val[i]=(a[i-1]!=b[i-1]);
    }
    for(int i=n+1;i>=2;i--){
        val[i]^=val[i-1];
    }

    cntg=2;
    for(int i=1;i<=m;i++){
        int l,r;
        cin>>l>>r;
        addedge(l,r+1,i);
        addedge(r+1,l,i);
        ans[i]='1';
    }
    
    dfncnt=0;
    bool flag=false;
    for(int i=1;i<=n+1;i++){
        if(!dfn[i]){
            tarjan(i,0);
            if(sum[i]){
                flag=true;
                break;
            }
        }
    }

    if(flag){
        for(int i=1;i<=m;i++){
            ans[i]='0';
        }
    }
    ans[m+1]='\0';
    cout<<(ans+1)<<endl;
}

int main()
{
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}