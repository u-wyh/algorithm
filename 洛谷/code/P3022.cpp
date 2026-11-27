// https://www.luogu.com.cn/problem/P3022
// 题意：输入城镇数 N、无向边数 M，以及 M 条无重边无自环的边 (A_i, B_i)（图不一定连通）。
// 选择并保留一个边子集（关闭其余边），使得每个城镇在保留后的子图中连接的边数均为奇数。
// 判断是否存在这样的边子集，存在则输出一种合法方案。
// 若无解输出一行 -1；否则第一行输出保留边数 K，随后 K 行每行输出一条保留边的原始编号（1..M，互不相同）。
// 数据范围：对于 100% 的数据，1 <= N <= 50000，1 <= M <= 100000。
#include<bits/stdc++.h>
// 算法标签：深度优先搜索、贪心、构造
using namespace std;
const int MAXN = 5e4+5;
const int MAXM = 1e5+5;

int n,m;
bool flag;
int in[MAXN];
bool vis[MAXN];
bool ok[MAXM];
vector<int>ans;

int cnt=1;
int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int weight[MAXM<<1];

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

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dfs(int u,int id){
    vis[u]=true;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(vis[v]){
            continue;
        }
        dfs(v,w);
        if(ok[w]){
            in[u]++;
        }
    }
    if((in[u]%2)==0){
        if(id==0){
            flag=true;
        }
        else{
            in[u]++;
            ok[id]=true;
            ans.push_back(id);
        }
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v,i);
        addedge(v,u,i);
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]&&!flag){
            dfs(i,0);
        }
    }
    if(flag){
        cout<<-1<<endl;
        return 0;
    }
    printf("%d\n",(int)ans.size());
    for(int i=0;i<(int)ans.size();i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}