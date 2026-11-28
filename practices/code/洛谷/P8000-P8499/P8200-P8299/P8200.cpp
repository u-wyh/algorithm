// https://www.luogu.com.cn/problem/P8200
// 题意：给定 n 个点的树，每条边有边权 w_e。
// m 次询问给定 a, b, k，
// 判断是否存在节点 t 使得路径 (t, a) 与路径 (t, b) 的边权异
// 或和之异或等于 k
// 输出 Yes 或 No（大小写不敏感）。
// 数据范围：1 < n <= 5*10^5，1 <= m <= 5*10^5，
// 0 <= w_i, k < 2^64
// 1 <= a, b <= n 且 a != b。
// 难度评分：1400（洛谷分级换算）
// 算法标签：深度优先搜索、位运算
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int MAXN = 5e5+5;

int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
ull weight[MAXN<<1];
int cnt=1;
ull dis[MAXN];//从顶点出发到达该点的异或值
int n,q;

 inline int read()
{
	int x=0,c; bool f=0;
	for(;(c=getchar())<'0'||c>'9';f|=c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+c-48;
	return f?-x:x;
}

 inline ull Read()
{
	int x=0,c; bool f=0;
	for(;(c=getchar())<'0'||c>'9';f|=c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+c-48;
	return f?-x:x;
}

void addedge(int u,int v,ull w){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dfs(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        int w=weight[i];
        if(v==f){
            continue;
        }
        dis[v]=dis[u]^w;
        dfs(v,u);
    }
}

int main()
{
    cin>>n>>q;
    for(int i=1;i<n;i++){
        int u,v;
        ull w;
        u=read();
        v=read();
        w=Read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dis[1]=0;
    dfs(1,0);
//    for(int i=1;i<=n;i++){
//        copydis[i]=dis[i];
//    }
//    sort(copydis+1,copydis+n+1);
//    for(int i=1;i<=n;i++){
//        m[dis[i]]=i;
//    }
    for(int i=1;i<=q;i++){
        int u,v;
        ull w;
        u=read();
        v=read();
        w=Read();
        if((dis[u]^dis[v])==w)
            cout<<"yes"<<endl;
        else
            cout<<"no"<<endl;
    }
    return 0;
}
