#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4e5+5;
const int MAXM = 1e6+5;
const int MAXV = MAXN<<1;
const int MAXE = MAXV<<1;

int n,m;

int ex[MAXM];
int ey[MAXM];
int ew[MAXM];

int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int cntg=2;

int head2[MAXN];
int nxt2[MAXM];
int to2[MAXM];
int cnte=2;

int dfncnt;
int dfn[MAXN];
int low[MAXN];
int edgesta[MAXM];
int top;

int bccCnt;
int belong[MAXM];
int mask[MAXN];
int node[MAXN];
int vmask[MAXN];

int fa[MAXN];
int sz[MAXN];

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

inline void addedge2(int u,int v){
    nxt2[cnte]=head2[u];
    to2[cnte]=v;
    head2[u]=cnte++;
}

void tarjan(int u,int preedge)
{
    dfn[u]=low[u]=++dfncnt;

    for(int i=head[u];i;i=nxt[i]){
        if(i==(preedge^1)) continue;

        int v=to[i];

        if(dfn[v]==0){
            edgesta[++top]=i>>1;

            tarjan(v,i);

            low[u]=min(low[u],low[v]);

            if(low[v]>=dfn[u]){
                bccCnt++;

                int pop;
                do{
                    pop=edgesta[top--];
                    belong[pop]=bccCnt;
                }while(pop!=(i>>1));
            }
        }
        else if(dfn[v]<dfn[u]){
            edgesta[++top]=i>>1;
            low[u]=min(low[u],dfn[v]);
        }
    }
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        if(sz[fx]>sz[fy]){
            swap(fx,fy);
        }
        fa[fx]=fy;
        sz[fy]+=sz[fx];
    }
}

long long compute(int v){
    for(int i=1;i<=n;i++){
        fa[i]=i;
        sz[i]=1;
    }

    int b=1<<v;
    for(int i=1;i<=m;i++){
        if(mask[belong[i]]==b){
            un(ex[i],ey[i]);
        }
    }

    long long ans=0;
    for(int i=1;i<=n;i++){
        if(i==find(i)){
            ans+=1ll*sz[i]*(sz[i]-1)/2;
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int CASE;
    cin>>CASE;

    cin>>n>>m;
    for(int i=1;i<=m;i++){
        char c;
        cin>>ex[i]>>ey[i]>>c;
        ew[i]=(c=='D');

        addedge(ex[i],ey[i]);
        addedge(ey[i],ex[i]);
    }

    tarjan(1,0);

    for(int i=1;i<=m;i++){
        int b=belong[i];
        addedge2(b,i);
        mask[b]|=1<<ew[i];
    }

    long long ans=1ll*(n-1)*n/2;

    ans-=compute(0);
    ans-=compute(1);

    for(int b=1;b<=bccCnt;b++){
        if(mask[b]!=3){
            continue;
        }

        int cnt=0;
        for(int i=head2[b];i;i=nxt2[i]){
            int v=to2[i];

            int x=ex[v];
            int y=ey[v];
            int w=ew[v];
            if(vmask[x]==0){
                node[++cnt]=x;
            }
            if(vmask[y]==0){
                node[++cnt]=y;
            }

            vmask[x]|=1<<w;
            vmask[y]|=1<<w;
        }

        int both=0;
        for(int i=1;i<=cnt;i++){
            int u=node[i];
            if(vmask[u]==3){
                both++;
            }
            vmask[u]=0;
        }
        if(both==2){
            ans--;
        }
    }

    cout<<ans<<endl;
    return 0;
}