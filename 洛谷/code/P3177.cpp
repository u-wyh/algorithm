// https://www.luogu.com.cn/problem/P3177
// 题意：输入树节点数 n、需染成黑色的点数 k，以及 n-1 条带权无向边 (u, v, w)。
// 选择恰好 k 个点染成黑色、其余 n-k 个点染成白色，收益定义为所有黑点两两间路径距离之和加上所有白点两两间路径距离之和。
// 输出能获得的最大收益值。
// 数据范围：0 <= k <= n <= 2000，1 <= w <= 10^4。
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2005;

int cnt=1;
int head[MAXN];
int Next[MAXN<<1];
int weight[MAXN<<1];
int to[MAXN<<1];
int n,m;
int sz[MAXN];
int f[MAXN][MAXN];

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

void addedge(int u,int v,int w){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dfs(int u,int fa){
    sz[u]=1;
    f[u][0]=f[u][1]=0;
	for(int i=head[u];i;i=Next[i]){
		int v=to[i];
		if(v==fa)
            continue;
		dfs(v,u);
		sz[u]+=sz[v];
		for(int j=min(m,sz[u]);j>=0;--j){   //此处倒序枚举是为了避免重复选取
			if(f[u][j]!=-1)    //在DP前应先加上当前子节点的子树纯白色的情况，这是下面也倒序枚举的前提
				f[u][j]+=f[v][0]+sz[v]*(n-m-sz[v])*weight[i];
			for(int k=min(j,sz[v]);k;k--){
				if(f[u][j-k]==-1)continue;
				int val=(k*(m-k)+(sz[v]-k)*(n-m-sz[v]+k))*weight[i];   //当前情况下连接子节点的边的贡献
				f[u][j]=max(f[u][j],f[u][j-k]+f[v][k]+val);
			}
		}
	}
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    memset(f,-1,sizeof(f));
    dfs(1,0);
    cout<<f[1][m]<<endl;
    return 0;
}
