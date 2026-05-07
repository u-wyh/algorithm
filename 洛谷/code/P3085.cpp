#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int OFFSET = 1e5+5;

int n;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cntg=1;

bool vis[MAXN];
int sz[MAXN];

void addedge(int u,int v,int w){
    nxt[cntg]=head[u];
    to[cntg]=v;
    weight[cntg]=w;
    head[u]=cntg++;
}

void getsize(int u,int fa){
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa&&!vis[v]){
            getsize(v,u);
            sz[u]+=sz[v];
        }
    }
}

int getcentroid(int u,int fa){
    getsize(u,fa);
    int half=sz[u]>>1;
    bool flag=false;
    while(!flag){
        flag=true;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v!=fa&&!vis[v]&&sz[v]>half){
                fa=u;
                u=v;
                flag=false;
                break;
            }
        }
    }
    return u;
}

int allval[MAXN*2];
int allbad[MAXN*2];
int curval[MAXN*2];
int curbad[MAXN*2];
vector<int>alltouched;
vector<int>curtouched;
int ok[MAXN*2];
int pathcnt[MAXN*2];

int center;

void dfs(int u,int fa,int w){
    if(w==0&&pathcnt[OFFSET]>=2){
        center++;
    }
    bool flag=false;
    if(pathcnt[w+OFFSET]){
        flag=true;
    }
    curval[w+OFFSET]++;
    pathcnt[w+OFFSET]++;
    if(!flag){
        curbad[w+OFFSET]++;
    }
    curtouched.push_back(w+OFFSET);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int ww=weight[i];
        if(!vis[v]&&v!=fa){
            dfs(v,u,w+ww);
        }
    }
    pathcnt[w+OFFSET]--;
}

int calc(int u){
    int ans=0;
    alltouched.clear();

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(!vis[v]){
            curtouched.clear();
            center=0;
            pathcnt[OFFSET]++;
            dfs(v,u,w);
            pathcnt[OFFSET]--;


            ans+=center;

            for(int i=0;i<(int)curtouched.size();i++){
                int val=curtouched[i];
                if(ok[val]==1){
                    continue;
                }
                ok[val]=1;
                alltouched.push_back(val);

                int need=2*OFFSET-val;
                int a=curval[val];
                int b=curbad[val];
                a=a-b;

                ans+=a*(allval[need])+b*(allval[need]-allbad[need]);
            }

            for(int i=0;i<(int)curtouched.size();i++){
                int val=curtouched[i];
                if(ok[val]==2){
                    continue;
                }
                ok[val]=2;
                alltouched.push_back(val);

                allval[val]+=curval[val];
                allbad[val]+=curbad[val];
            }

            
            for(int i=0;i<(int)curtouched.size();i++){
                int val=curtouched[i];
                curval[val]=0;
                curbad[val]=0;
            }
        }
    }

    for(int i=0;i<(int)alltouched.size();i++){
        int val=alltouched[i];
        allval[val]=0;
        allbad[val]=0;
    }
    return ans;
}

int solve(int u){
    int ans=0;
    vis[u]=true;
    ans+=calc(u);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]){
            ans+=solve(getcentroid(v,u));
        }
    }
    return ans;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        w=(w==0)?-1:1;
        addedge(u,v,w);
        addedge(v,u,w);
    }

    int centroid=getcentroid(1,0);
    int ans=solve(centroid);
    cout<<ans<<endl;
    return 0;
}