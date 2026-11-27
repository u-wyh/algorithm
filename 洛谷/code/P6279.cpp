// https://www.luogu.com.cn/problem/P6279
// 题意：N 头奶牛和 M 对仰慕关系 (a,b)（b 仰慕 a）。
// 若 x 和 y 都仰慕喜欢同一种颜色的奶牛，则 x 和 y 喜欢的颜色相同。
// 在最大化不同颜色数量的前提下，输出字典序最小的颜色分配方案（颜色在 1..N 内）。
// 数据范围：1 <= N, M <= 2*10^5，1 <= a, b <= N。
// 算法标签：并查集
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,m;
int cnt;
int fa[MAXN<<1];
int vis[MAXN];

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

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx==fy){
        return ;
    }
    if(fx<=n){
        swap(fx,fy);
    }
    fa[fx]=fy;
    if(fx<=n&&fy<=n){
        un(fx+n,fy+n);
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n*2;i++){
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        un(u+n,v);
    }
    for(int i=1;i<=n;i++){
        int f=find(i);
        if(vis[f]){
            cout<<vis[f]<<endl;
        }
        else{
            vis[f]=++cnt;
            cout<<cnt<<endl;
        }
    }
    return 0;
}