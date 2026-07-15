#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXB = 500;

int n,m,g;

int blen;
int bnum;

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;

int op[MAXN];
int x[MAXN];
int y[MAXN];

int ans[MAXN];

int fa[MAXN];
int sz[MAXN];
int cnt[MAXN][MAXB];

int rollback[MAXN][2];
int opsize;

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

int find(int x){
    while(x!=fa[x]){
        x=fa[x];
    }
    return x;
}

void prepare(){
    blen=1400;
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=n;i++){
        cnt[i][(i-1)/blen+1]=1;
    }
    for(int i=1;i<=n;i++){
        fa[i]=i;
        sz[i]=1;
    }
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        if(sz[fx]>sz[fy]){
            swap(fx,fy);
        }
        ++opsize;
        rollback[opsize][0]=fx;
        rollback[opsize][1]=fy;

        fa[fx]=fy;
        sz[fy]+=sz[fx];
        for(int i=1;i<=bnum;i++){
            cnt[fy][i]+=cnt[fx][i];
        }
    }
}

void undo(){
    int fx=rollback[opsize][0];
    int fy=rollback[opsize][1];
    opsize--;
    fa[fx]=fx;
    sz[fy]-=sz[fx];
    for(int i=1;i<=bnum;i++){
        cnt[fy][i]-=cnt[fx][i];
    }
}

int query(int x,int k){
    int fx=find(x);
    if(sz[fx]<k){
        return -1;
    }

    int now=0;
    for(int i=1;i<=bnum;i++){
        if(now+cnt[fx][i]>=k){
            int l=(i-1)*blen+1;
            int r=i*blen;
            for(int j=l;j<=r;j++){
                if(find(j)==fx){
                    now++;
                    if(now==k){
                        return j;
                    }
                }
            }
        }
        else{
            now+=cnt[fx][i];
        }
    }
}

void dfs(int u){
    int now=opsize;
    if(op[u]==1){
        ans[u]=query(x[u],y[u]);
    }
    else if(op[u]==2){
        un(x[u],y[u]);
    }

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v);
    }
    while(now!=opsize){
        undo();
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>g;
    for(int i=1;i<=m;i++){
        cin>>op[i];
        if(op[i]==1){
            addedge(i-1,i);
            cin>>x[i]>>y[i];
        }
        else if(op[i]==2){
            addedge(i-1,i);
            cin>>x[i]>>y[i];
        }
        else{
            cin>>x[i];
            addedge(x[i],i);
        }
    }

    prepare();
    dfs(0);

    for(int i=1;i<=m;i++){
        if(op[i]==1){
            cout<<ans[i]<<endl;
        }
    }
    return 0;
}