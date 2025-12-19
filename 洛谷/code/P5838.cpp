#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10,M = N*2;
int h[N],e[M],ne[M],idx;
int c[N],top[N],q[N],ans[N];
vector<int> query[N];
int n,m;

void add(int a,int b)
{
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}

void dfs(int u,int fa)
{
    int buf = top[c[u]];
    for(int i=0;i<query[u].size();i++)
    {
        auto id = query[u][i];
        if(~ans[id]) ans[id] = (top[q[id]]!=ans[id]);
        else ans[id] = top[q[id]];
    }
    for(int i=h[u];~i;i=ne[i])
    {
        int j = e[i];
        if(j==fa) continue;
        top[c[u]] = j;
        dfs(j,u);
    }
    top[c[u]] = buf;
}

int main()
{
    scanf("%d%d",&n,&m);
    memset(h,-1,sizeof h);
    for(int i=1;i<=n;i++) scanf("%d",c+i);
    for(int i=0;i<n-1;i++)
    {
        int u,v;scanf("%d%d",&u,&v);
        add(u,v),add(v,u);
    }
    for(int i=0;i<m;i++)
    {
        int u,v,col;
        scanf("%d%d%d",&u,&v,&col);
        if(c[u]==col||c[v]==col) ans[i] = 1;
        else ans[i] = -1;
        q[i] = col;
        query[u].push_back(i);
        query[v].push_back(i);
    }
    dfs(1,-1);
    for(int i=0;i<m;i++) printf("%d",ans[i]);
    return 0;
}
