#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2505;
const int MAXM = 10005;

int n,m,k;

int val[MAXN];

bool ok[MAXN][MAXN];
vector<int>f[MAXN];
int dis[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];

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

void bfs(int st){
    memset(dis,-1,sizeof(dis));
    queue<int>q;
    q.push(st);
    dis[st]=0;

    while(!q.empty()){
        int u=q.front();
        q.pop();
        if(u!=st){
            ok[st][u]=true;
            if(st!=1&&ok[1][u]){
                f[st].push_back(u);
                std :: sort(f[st].begin(), f[st].end(), [](int u, int v) {
                    return val[u] > val[v];
                });
                if(f[st].size()>3){
                    f[st].pop_back();
                }
            }
        }

        if(dis[u]==k+1){
            continue;
        }
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(dis[v]==-1){
                dis[v]=dis[u]+1;
                q.push(v);
            }
        }
    }
}

signed main()
{
    n=read(),m=read(),k=read();
    for(int i=2;i<=n;i++){
        val[i]=read();
    }

    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=1;i<=n;i++){
        bfs(i);
    }
    int ans=0;
    for(int b=2;b<=n;b++){
        for(int c=2;c<=n;c++){
            if(ok[b][c]){
                for (int a : f[b]){
                    for (int d : f[c]){
                    if (a != c && b != d && a != d)
                        if(a!=c&&b!=d&&a!=d){
                            ans=max(ans,val[a]+val[b]+val[c]+val[d]);
                        }
                    }
                }
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}