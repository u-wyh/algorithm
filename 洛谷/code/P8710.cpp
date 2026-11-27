// https://www.luogu.com.cn/problem/P8710
// 题意：输入 n, m（初始 n 个点独立且存储信息量为 0）和 m 次操作：1 a b 用网线连接节点 a 和 b（a=b 为自环无影响）
// 2 p t 使当前与节点 p 直接或间接连通的所有节点（含 p）各存储一次大小为 t 的信息；
// 输出操作结束后 1..n 号节点各自存储的信息总大小。
// 数据范围：1 <= n <= 10000，1 <= m <= 10^5，1 <= t <= 100。
// 算法标签：并查集
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10005;

int n,m;
int fa[MAXN];
int dist[MAXN];
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

int find(int i){
    if(i!=fa[i]){
        int tmp=fa[i];
        fa[i]=find(fa[i]);
        dist[i]+=dist[tmp];
    }
    return fa[i];
}

void un(int l,int r){
    int lf=find(l),rf=find(r);
    if(lf!=rf){
        fa[lf]=rf;
        dist[lf]=val[lf]-val[rf];
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        int op,u,v;
        op=read(),u=read(),v=read();
        if(op==1){
            un(u,v);
        }
        else{
            u=find(u);
            val[u]+=v;
        }
    }
    for(int i=1;i<=n;i++){
        int fa=find(i);
        printf("%d ",val[fa]+dist[i]);
    }
    return 0;
}