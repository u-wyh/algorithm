// https://www.luogu.com.cn/problem/P2860
// 题意：给定 F 个点 R 条边的连通无向图（可能有重边）。
// 求最少新增多少条边，使任意两点间至少有两条边不相交的路径（即无桥）。
// 输出最少新增边数。
// 数据范围：1 <= F <= 5*10^3，F-1 <= R <= 10^4。
//P2860
//其实就是边双
#include<bits/stdc++.h>
// 算法标签：Tarjan、边双连通分量、缩点
using namespace std;
const int MAXN = 5005;
const int MAXM = 20010;

int n,m;
int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,Time;
int col[MAXN];
int in[MAXN];

bool vis[MAXM];
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt=2;

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

void tarjan(int x){
    dfn[x]=++Time;
    low[x]=Time;
    st[++top]=x;
    for(int i=head[x];i;i=Next[i]){
        if(vis[i]){
            continue;
        }
        vis[i]=vis[i^1]=true;
        int v=to[i];
        if(!dfn[v]){
            //表示这个节点没有被访问过
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
        else{
            //表示这个属于是回溯了 一定是同一个环上的
            low[x]=min(low[x],dfn[v]);
        }
    }
    if(dfn[x]==low[x]){
        col[x]=++color;
        //将所有节点按照颜色分类  完成缩点
        while(st[top]!=x){
            //属于同一个强联通分量
            col[st[top]]=color;
            top--;
        }
        top--;
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=head[i];j;j=Next[j]){
            int v=to[j];
            if(col[i]!=col[v]){
                in[col[i]]++,in[col[v]]++;
            }
        }
    }
    int cnt1=0;
    for(int i=1;i<=color;i++){
        if(in[i]==2){
            //因为上面in++的时候  实际上是加了两次
            //如果只加一次的话  就是in==1
            cnt1++;
        }
    }
    cout<<(cnt1+1)/2<<endl;
    return 0;
}
