#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int LIMIT = 16;

int n,m;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int sum[1<<20];
int deep[MAXN],stjump[MAXN][LIMIT],val[MAXN][LIMIT];
int power;
int nums[MAXN];

void dfs(int u,int f){
    deep[u]=deep[f]+1;
    stjump[u][0]=f;
    val[u][0]=(nums[u]|nums[f]);

    for (int p = 1; p <= power; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
        val[u][p]=(val[stjump[u][p-1]][p-1]|val[u][p-1]);
    }

    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs(v,u);
        }
    }
}

int lca(int a, int b) {
    if (deep[a] < deep[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    int ans1=nums[a],ans2=nums[b];
    //确定大小关系

    for (int p = power; p >= 0; p--) {
        if (deep[stjump[a][p]] >= deep[b]) {
            ans1|=val[a][p];
            a = stjump[a][p];
        }
    }
    //首先将两者变为同一高度
    if (a == b) {
        return sum[ans1|ans2];
    }
    //如果相同说明就是祖先关系
    for (int p = power; p >= 0; p--) {
        if (stjump[a][p] != stjump[b][p]) {
            ans1|=val[a][p];
            a = stjump[a][p];
            ans2|=val[a][p];
            b = stjump[b][p];
        }
        //判断跳完后是否符合规则
    }
    return sum[ans1|ans2];
    //我们将头结点的祖先设置为0  实际上没有0
}

int main()
{
    cin>>n>>m;
    power=log2(n);
    for(int i=1;i<=n;i++){
        int k;
        cin>>k;
        nums[i]|=(1<<(k-1));//赋予权值
    }

    sum[0]=0;
    for(int i=1;i<(1<<n);i++){
        int k=i&-i;
        sum[i]=sum[k^i]+1;//统计1的个数
    }

    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;
        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;
        //链式前向星建双向图
    }
    dfs(1,0);//建立st表
    for(int i=1,u,v;i<=m;i++){
        cin>>u>>v;
        cout<<lca(u,v)<<endl;
    }
    return 0;
}

