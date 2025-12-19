#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;
const int MAXM = 2e6+5;
const int MAXK = 1e4+5;

int n,m,k;
vector<int>vec[MAXN];
int arr[MAXK];
int fa[MAXN];
int dis[MAXN];
bool vis[MAXN];
queue<pair<int,int>>q;

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

bool un(int x,int y){
    int fx=find(x),fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
        return true;
    }
    return false;
}

signed main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=k;i++){
        int u=read();
        q.push({u,0});
        dis[u]=1;
    }
    if(m==n-1){
        cout<<"Poor D!"<<endl;
        return 0;
    }
    int ans=INT_MAX;
    while(!q.empty()){
        int u=q.front().first;
        int f=q.front().second;
        q.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=0;i<vec[u].size();i++){
            int v=vec[u][i];
            if(v==f){
                continue;
            }
            if (!dis[v]) {
                dis[v] = dis[u] + 1;
                q.push({v, u});
                fa[find(v)] = find(u);
            }
            else if (!(dis[v] + 1 == dis[u] || (vis[v] && dis[v] == dis[u]))) {
                if (find(v) == find(u)) // 已经同属一个集合 统计答案
                    ans = min(max(dis[v], dis[u]) - 1, ans);
                else
                    fa[find(v)] = find(u);
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
