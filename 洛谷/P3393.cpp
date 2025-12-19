#include <bits/stdc++.h>
using namespace std;

const int N=100010;
const long long inf=214748364701;
queue <int> q;
int n,m,k,ss,P,Q;
long long dis[N],w[N<<2];
int s[N<<2][2],o[N],cnt;
bool ocp[N],vis[N],dgs[N];
inline void add(int,int);

inline void spfa(int now)
{
    memset(vis,0,sizeof(vis));
    for (int i=1;i<=n;++i) dis[i]=inf;
    while (!q.empty()) q.pop();
    q.push(now);dis[now]=0;vis[now]=1;
    while (!q.empty()) {
        int x=q.front();
        for (int i=o[x];i;i=s[i][1]) {
            int y=s[i][0];
            if (dis[y]>dis[x]+w[i]) {
                dis[y]=dis[x]+w[i];
                if (!vis[y])
                    vis[y]=1,q.push(y);
            }
        }
        vis[x]=0;q.pop();
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m>>k>>ss>>P>>Q;
    int x,y;
    for (int i=1;i<=k;++i)
        cin>>x,ocp[x]=1;
    for (int i=1;i<=m;++i) {
        cin>>x>>y;
        if (ocp[x]&&ocp[y]) continue;
        if (ocp[x]) add(0,y),add(y,0);
        else if (ocp[y]) add(0,x),add(x,0);
        else add(x,y),add(y,x);
    }
    for (int i=1;i<=cnt;++i) w[i]=1;
    spfa(0);
    for (int i=1;i<=n;++i)
        if (dis[i]<=ss) dgs[i]=1;
    for (int i=1;i<=cnt;++i) {
        if (dgs[s[i][0]]) w[i]=Q;
        else if (ocp[s[i][0]]) w[i]=inf;
        else w[i]=P;
        if (s[i][0]==1||s[i][0]==n) w[i]=0;
    }
    spfa(1);
    cout<<dis[n]<<endl;
    return 0;
}

inline void add(int x,int y)
{
    s[++cnt][0]=y;s[cnt][1]=o[x];o[x]=cnt;
}
