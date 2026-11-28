// https://www.luogu.com.cn/problem/P3237
// 题意：输入树节点数 N（以 1 为根）、各节点初始正整数点权 A_1..A_N，
// 以及 N-1 条树边。
// 要求一个好方案 w，
// 使每个非叶节点 u 的所有子节点 w_v 均相等且 ∑w_v = w_u，
// 允许将任意点权修改为任意正实数。
// 输出最少需要修改点权的节点个数。
// 数据范围：N < 500000，A_j < 10^8。
// 难度评分：1900（洛谷分级换算）
// 算法标签：深度优先搜索、排序、数学
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const double eps = 1e-8;

int n;
int val[MAXN];
int son[MAXN];
double f[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt=1;

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

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u,double now){
    f[u]=now+log(val[u]);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v,now+log(son[u]));
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        son[u]++;
    }
    dfs(1,0);
    sort(f+1,f+n+1);
    int cnt=1,maxx=1;
    for(int i=2;i<=n;i++){
        if(fabs(f[i]-f[i-1])<=eps){
            cnt++;
            maxx=max(maxx,cnt);
        }
        else{
            cnt=1;
        }
    }
    cout<<(n-maxx)<<endl;
    return 0;
}