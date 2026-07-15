#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
int col[MAXN];

int headg[MAXN];
int nxtg[MAXN<<1];
int tog[MAXN<<1];
int cntg=1;

int headq[MAXN];
int nxtq[MAXN];
int ql[MAXN];
int qr[MAXN];
int qid[MAXN];
int cntq=1;

bool vis[MAXN];
int sz[MAXN];

struct Node{
    int l,r,col;
};
Node nodearr[MAXN];
int cntnode;

bool ok[MAXN];
struct Ques{
    int l,r,qid;
};
Ques quesarr[MAXN];
int cntques;

int pos[MAXN];
int tree[MAXN];
int ans[MAXN];

bool nodecmp(Node &a,Node &b){
    return a.r<b.r;
}

bool quescmp(Ques &a,Ques &b){
    return a.r<b.r;
}

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
    nxtg[cntg]=headg[u];
    tog[cntg]=v;
    headg[u]=cntg++;
}

inline void addquery(int u,int l,int r,int id){
    nxtq[cntq]=headq[u];
    ql[cntq]=l;
    qr[cntq]=r;
    qid[cntq]=id;
    headq[u]=cntq++;
}

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int v){
    if(x==0){
        return ;
    }
    while(x<=n){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

int sum(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

int query(int l,int r){
    return sum(r)-sum(l-1);
}

void getsize(int u,int fa){
    sz[u]=1;
    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        if(v!=fa&&!vis[v]){
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
        for(int i=headg[u];i;i=nxtg[i]){
            int v=tog[i];
            if(v!=fa&&!vis[v]&&sz[v]>half){
                find=false;
                fa=u;
                u=v;
                break;
            }
        }
    }
    return u;
}

void dfs(int u,int fa,int nl,int nr){
    nodearr[++cntnode]={nl,nr,col[u]};
    for(int i=headq[u];i;i=nxtq[i]){
        if(!ok[qid[i]]&&ql[i]<=nl&&nr<=qr[i]){
            quesarr[++cntques]={ql[i],qr[i],qid[i]};
            ok[qid[i]]=true;
        }
    }
    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        if(v!=fa&&!vis[v]){
            dfs(v,u,min(nl,v),max(nr,v));
        }
    }
}

void calc(int u){
    cntnode=0;
    cntques=0;
    dfs(u,0,u,u);
    sort(nodearr+1,nodearr+cntnode+1,nodecmp);
    sort(quesarr+1,quesarr+cntques+1,quescmp);
    for(int i=1,j=1;i<=cntques;i++){
        while(j<=cntnode&&nodearr[j].r<=quesarr[i].r){
            if(nodearr[j].l>pos[nodearr[j].col]){
                add(pos[nodearr[j].col],-1);
                pos[nodearr[j].col]=nodearr[j].l;
                add(pos[nodearr[j].col],1);
            }
            j++;
        }
        ans[quesarr[i].qid]=query(quesarr[i].l,n);
    }
    for(int i=1;i<=cntnode;i++){
        add(pos[nodearr[i].col],-1);
        pos[nodearr[i].col]=0;
    }
}

void solve(int u){
    vis[u]=true;
    calc(u);
    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        if(!vis[v]){
            solve(getcentroid(v,u));
        }
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        col[i]=read();
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=1;i<=m;i++){
        int l,r,x;
        l=read(),r=read(),x=read();
        addquery(x,l,r,i);
    }
    solve(getcentroid(1,0));
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}