#include<bits/stdc++.h>
using namespace std;
const int MAXN=5e5+10, MAXM=1e6+10;
int n, m;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

void write(int x)
{
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}

struct {
    int nxt, to;
} e[MAXM]; int head[MAXN], tot=1; // 双向边优化
inline void add(int u, int v) {
    e[++tot].to=v, e[tot].nxt=head[u], head[u]=tot;
}
bitset<MAXM> vis, in_stack;
int stk[MAXN], r;
inline void dfs(int u) { // 感谢rzy神！！！
    for (int i=head[u]; i; i=head[u]) {
    // 注意这里的循环赋值
        int to=e[i].to;
        head[u]=e[i].nxt; // 优化1
        if (vis[i]) continue;
        vis[i]=vis[i^1]=true;
        dfs(e[i].to);
    }
    // 进出栈过程
    if (in_stack[u]) {
        while (stk[r]!=u && r) {
            in_stack[stk[r]]=false;
            write(stk[r--]); putchar(' ');
        }
        write(stk[r--]); putchar('\n'); // 本题专属的SPJ优化
    }
    else in_stack[u]=true;
    stk[++r]=u;
}
int main() {
    n=read(), m=read();
    int x, y;
    for (int i=1; i<=m; ++i) {
        x=read(), y=read();
        add(x,y), add(y,x);
    }
    dfs(1);
    return 0;
}
