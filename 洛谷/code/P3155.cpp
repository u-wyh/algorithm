// https://www.luogu.com.cn/problem/P3155
// 题意：输入无根树总节点数 m、叶子数 n（编号 1..n 为叶子），1..n 号叶子要求的颜色 c_i（0 或 1），以及 m-1 条树边。
// 可任选一个度数大于 1 的节点作根，再给任意部分节点染成 0 或 1，要求根到每个叶子路径上至少有一个有色节点，且路径上最后一个有色节点的颜色恰好等于 c_u。
// 求最少需要给多少个节点染色。
// 输出一个整数表示最少染色节点数。
// 数据范围：1 <= m <= 10^4，1 <= n <= 5021，1 <= a < b <= m。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 155;

int cnt=1;
int head[MAXN];
int Next[MAXN];
int to[MAXN];

int n,m;
int f[MAXN][MAXN];
int sum[MAXN];

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
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u){
    sum[u]=1;
    f[u][1]=0,f[u][0]=1;
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        dfs(v);
        sum[u]+=sum[v];
        for(int j=sum[u];j;j--){
            f[u][j]+=1;
            for(int k=0;k<=min(sum[v],j-1);k++){
                f[u][j]=min(f[u][j],f[u][j-k]+f[v][k]);
            }
        }
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            f[i][j]=1e9;
        }
    }
    dfs(1);
    int ans=f[1][m];
    for(int i=2;i<=n;i++){
        ans=min(ans,f[i][m]+1);
    }
    cout<<ans<<endl;
    return 0;
}
