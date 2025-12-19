#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MAXN = 2e5+5;
const int INF = 2e9;

int n,m;
bool flag;
int l[MAXN];
int r[MAXN];

int ans;

int f[MAXN];//这个节点的父亲 为了避免走回头路
int k[MAXN];
int b[MAXN];
int val[MAXN];//在有环的情况下  并且确定了这个集合中的所有值都是固定的

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;

int fa[MAXN];//并查集
int sz[MAXN];//记录这个集合中有多少个节点
int all[MAXN];//记录这个集合中有多少条边

int dfn[MAXN];
int dfncnt;

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void bfs1(int st){
    dfncnt=0;
    queue<int>q;
    q.push(st);
    dfn[++dfncnt]=st;
    k[st]=1;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if(v!=f[u]){
                f[v]=u;
                k[v]=-k[u];
                b[v]=w-b[u];
                q.push(v);
                dfn[++dfncnt]=v;
            }
        }
    }
    int minn=-INF,maxx=INF;
    int kk=0,bb=0;
    for(int i=1;i<=dfncnt;i++){
        int u=dfn[i];
        kk+=k[u];
        bb+=b[u];
        int lt,rt;
        if(k[u]>=1){
            lt=l[u]-b[u];
            rt=r[u]-b[u];
        }
        else{
            lt=b[u]-r[u];
            rt=b[u]-l[u];
        }
        minn=max(minn,lt);
        maxx=min(maxx,rt);
        if(minn>maxx){
            flag=true;
            return ;
        }
    }
    if(kk>=0){
        ans+=kk*maxx+bb;
    }
    else{
        ans+=kk*minn+bb;
    }
}

void bfs2(int st){
    dfncnt=0;
    int x=0;
    bool op=false;
    queue<int>q;
    q.push(st);
    dfn[++dfncnt]=st;
    k[st]=1;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if(v==f[u]){
                continue;
            }
            if(k[v]!=0){
                if(k[v]!=k[u]){
                    if(b[v]+b[u]!=w){
                        flag=true;
                        return ;
                    }
                }
                else{
                    if((w-b[u]-b[v])%2==0){
                        op=true;
                        x=(w-b[u]-b[v])/(k[u]+k[v]);
                    }
                    else{
                        flag=true;
                        return ;
                    }
                }
            }
            else{
                f[v]=u;
                k[v]=-k[u];
                b[v]=w-b[u];
                dfn[++dfncnt]=v;
                q.push(v);
            }
        }
    }
    if(op){
        for(int i=1;i<=dfncnt;i++){
            int u=dfn[i];
            val[u]=k[u]*x+b[u];
            if(val[u]<l[u]||val[u]>r[u]){
                flag=true;
                return ;
            }
            ans+=val[u];
        }
        for(int i=1;i<=dfncnt;i++){
            int u=dfn[i];
            for(int ei=head[u];ei;ei=nxt[ei]){
                int v=to[ei];
                int w=weight[ei];
                if(val[u]+val[v]!=w){
                    flag=true;
                    break;
                }
            }
        }
    }
    else{
        int minn=-INF,maxx=INF;
        int kk=0,bb=0;
        for(int i=1;i<=dfncnt;i++){
            int u=dfn[i];
            kk+=k[u];
            bb+=b[u];
            int lt,rt;
            if(k[u]>=1){
                lt=l[u]-b[u];
                rt=r[u]-b[u];
            }
            else{
                lt=b[u]-r[u];
                rt=b[u]-l[u];
            }
            minn=max(minn,lt);
            maxx=min(maxx,rt);
            if(minn>maxx){
                flag=true;
                return ;
            }
        }
        if(kk>=0){
            ans+=kk*maxx+bb;
        }
        else{
            ans+=kk*minn+bb;
        }
    }
}

signed main()
{
    // cout<<(-4%-2)<<endl;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>l[i]>>r[i];
    }

    for(int i=1;i<=n;i++){
        fa[i]=i,sz[i]=1;
    }

    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
        int fx=find(u);
        int fy=find(v);
        if(fx!=fy){
            fa[fx]=fy;
            sz[fy]+=sz[fx];
            all[fy]+=all[fx]+1;
        }
        else{
            all[fx]++;
        }
    }

    for(int i=1;i<=n;i++){
        if(i==find(i)){
            if(sz[i]<=all[i]){
                bfs2(i);//有环
            }
            else{
                bfs1(i);//无环
            }
            if(flag){
                break;
            }
        }
    }
    if(flag){
        cout<<"NO"<<endl;
        return 0;
    }
    cout<<"YES"<<endl;
    cout<<ans<<endl;
    return 0;
}