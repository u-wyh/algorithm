// https://www.luogu.com.cn/problem/P3554
// 题意：输入树上节点数 n 和 n-1 条树边。
// 初始 1 号点为黑、其余为白，B 初始在 1 号点；每轮 A 先选至多 k 个点染黑，然后 B 移动到相邻节点，B 踩到白点则 B 胜，全黑则 A 胜。
// 输出能让 A 必胜的最小 k。
// 数据范围：1 <= n <= 3*10^5。
#include<bits/stdc++.h>
// 算法标签：二分答案、深度优先搜索
using namespace std;
const int MAXN = 3e5+5;

int n;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int son[MAXN];
int sonson1[MAXN];
int sonson2[MAXN];
int dep[MAXN];
int val[MAXN];

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
    dep[u]=dep[f]+1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==f){
            continue;
        }
        son[u]++;
        dfs(v,u);
    }
}

void dfs1(int u,int fa){
    sonson1[u]=0,sonson2[u]=0;
    // val[u]=son[fa]+val[fa];
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        if(son[v]>=sonson1[u]){
            sonson2[u]=sonson1[u];
            sonson1[u]=son[v];
        }
        else if(son[v]>=sonson2[u]){
            sonson2[u]=son[v];
        }
        dfs1(v,u);
    }
}

void dfs2(int u,int fa,int fafa){
    val[u]=son[fa]+val[fa]+((son[fa]==sonson1[fafa])?sonson2[fafa]:sonson1[fafa]);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs2(v,u,fa);
    }
}

bool check(int k){
    for(int i=1;i<=n;i++){
        if(dep[i]*k<val[i]){
            return false;
        }
    }
    return true;
}

int main()
{
    n=read();
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dep[0]=-1;
    dfs(1,0);
    dfs1(1,0);
    dfs2(1,0,0);
    // for(int i=1;i<=n;i++){
    //     cout<<i<<": "<<son[i]<<' '<<sonson1[i]<<' '<<sonson2[i]<<' '<<dep[i]<<' '<<val[i]<<endl;
    // }
    int l=1,r=n,ans=1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    cout<<ans<<endl;
    return 0;
}