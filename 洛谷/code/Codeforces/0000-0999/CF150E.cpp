#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int INF = 1e9+1;

int n,limitl,limitr,cntw;
int ans,ansu,ansv;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;

bool vis[MAXN];
int sz[MAXN];

struct Edge{
    int u,v,w;
};
Edge edge[MAXN];

struct Node{
    int id,w,sz;
};
Node node[MAXN];
int cntn;

int preval[MAXN];
int prenode[MAXN];
int prelen;

int curval[MAXN];
int curnode[MAXN];
int curlen;

int que[MAXN];

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

bool cmp(Edge &a,Edge &b){
    return a.w<b.w;
}

bool cmp1(Node &a,Node &b){
    return a.sz<b.sz;
}

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void getsize(int u,int fa){
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]&&v!=fa){
            getsize(v,u);
            sz[u]+=sz[v];
        }
    }
}

int getcentroid(int u,int fa){
    getsize(u,fa);
    int half=sz[u]>>1;
    bool find=false;
    while(!find){
        find=true;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(!vis[v]&&v!=fa&&sz[v]>half){
                fa=u;
                u=v;
                find=false;
                break;
            }
        }
    }
    return u;
}

void dfs(int u,int fa,int edge,int val,int limit){
    curlen=max(curlen,edge);
    if(val>curval[edge]){
        curval[edge]=val;
        curnode[edge]=u;
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=fa&&!vis[v]){
            dfs(v,u,edge+1,val+(w>=limit?1:-1),limit);
        }
    }
}

bool check(int u,int limit){
    preval[0]=0;
    prenode[0]=u;
    prelen=0;
    for(int k=1;k<=cntn;k++){
        int v=node[k].id;
        int w=node[k].w;
        for(int i=1;i<=sz[v];i++){
            curval[i]=-INF;
        }
        curlen=0;

        dfs(v,u,1,w>=limit?1:-1,limit);

        int ql=1,qr=0;
        for(int i=min(prelen,limitr);i>=limitl;i--){
            while(ql<=qr&&preval[que[qr]]<=preval[i]){
                qr--;
            }
            que[++qr]=i;
        }
        int down=limitr,up=limitl;
        for(int i=1;i<=curlen;i++){
            up--;
            if(up>=0&&up<=prelen){
                while(ql<=qr&&preval[que[qr]]<=preval[up]){
                    qr--;
                }
                que[++qr]=up;
            }
            if(ql<=qr&&que[ql]==down){
                ql++;
            }
            down--;
            if(ql<=qr&&preval[que[ql]]+curval[i]>=0){
                if(limit>ans){
                    ans=limit;
                    ansu=curnode[i];
                    ansv=prenode[que[ql]];
                }
                return true;
            }
        }

        for(int i=1;i<=curlen;i++){
            if(i>prelen||curval[i]>preval[i]){
                preval[i]=curval[i];
                prenode[i]=curnode[i];
            }
        }
        prelen=max(prelen,curlen);
    }
    return false;
}

void calc(int u){
    getsize(u,0);
    cntn=0;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(!vis[v]){
            node[++cntn]={v,w,sz[v]};
        }
    }
    sort(node+1,node+cntn+1,cmp1);
    int l=1,r=cntw;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(u,mid)){
            l=mid+1;
        }
        else{
            r=mid-1;
        }
        if(r<=ans){
            break;
        }
    }
}

void solve(int u){
    vis[u]=true;
    calc(u);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]){
            solve(getcentroid(v,u));
        }
    }
}

int main()
{
    n=read(),limitl=read(),limitr=read();
    for(int i=1;i<n;i++){
        edge[i].u=read();
        edge[i].v=read();
        edge[i].w=read();
    }
    sort(edge+1,edge+n,cmp);
    cntw=0;
    for(int i=1;i<n;i++){
        if(i==1||edge[i-1].w!=edge[i].w){
            ++cntw;
        }
        addedge(edge[i].u,edge[i].v,cntw);
        addedge(edge[i].v,edge[i].u,cntw);
    }
    solve(getcentroid(1,0));
    cout<<ansu<<' '<<ansv<<endl;
    return 0;
}