#include<bits/stdc++.h>
using namespace std;
const int MAXN = 55;
const int MAXM = 2550;

int k;

int n[MAXN];
int go[MAXN][MAXN][2];
bool out[MAXN][MAXN];

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cntg=1;

bool vis[MAXN][MAXN];
int qx[MAXM];
int qy[MAXM];

int dfncnt;
int dfn[MAXN];
int low[MAXN];
int sta[MAXN];
int top;
int belong[MAXN];
int sccsz[MAXN];
int scccnt;

bool dag[MAXN][MAXN];
int indeg[MAXN];
int dp[MAXN];
int que[MAXN];

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

bool compare(int a,int b){
    for(int i=1;i<=n[a];i++){
        for(int j=1;j<=n[b];j++){
            vis[i][j]=false;
        }
    }

    int l=1,r=0;
    qx[++r]=1;
    qy[r]=1;
    vis[1][1]=true;

    while(l<=r){
        int x=qx[l];
        int y=qy[l++];

        if(out[a][x]&&!out[b][y]){
            return false;
        }

        for(int c=0;c<=1;c++){
            int nx=go[a][x][c];
            int ny=go[b][y][c];
            if(!vis[nx][ny]){
                vis[nx][ny]=true;
                qx[++r]=nx;
                qy[r]=ny;
            }
        }
    }
    return true;
}

void prepare(){
    for(int i=1;i<=k;i++){
        for(int j=1;j<=k;j++){
            if(i!=j&&compare(i,j)){
                addedge(i,j);
            }
        }
    }
}

void tarjan(int u){
    dfn[u]=low[u]=++dfncnt;
    sta[++top]=u;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];

        if(dfn[v]==0){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(dfn[v]<dfn[u]){
            if(belong[v]==0){
                low[u]=min(low[u],dfn[v]);
            }
        }
    }
    if (dfn[u] == low[u]) {
        scccnt++;

        int pop;
        do {
            pop = sta[top--];
            belong[pop] = scccnt;
            sccsz[scccnt]++;
        } while (pop != u);
    }
}

int compute(){
    for (int u = 1; u <= k; u++) {
        for (int e = head[u]; e > 0; e = nxt[e]) {
            int v = to[e];

            int a = belong[u];
            int b = belong[v];

            if (a != b && !dag[a][b]) {
                dag[a][b] = true;
                indeg[b]++;
            }
        }
    }

    int l = 1;
    int r = 0;
    int ans = 0;

    for (int i = 1; i <= scccnt; i++) {
        dp[i] = sccsz[i];

        if (indeg[i] == 0) {
            que[++r] = i;
        }
    }

    while (l <= r) {
        int u = que[l++];

        ans = max(ans, dp[u]);

        for (int v = 1; v <= scccnt; v++) {
            if (!dag[u][v]) {
                continue;
            }

            dp[v] = max(dp[v], dp[u] + sccsz[v]);

            if (--indeg[v] == 0) {
                que[++r] = v;
            }
        }
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>k;
    for(int id=1;id<=k;id++){
        int m;
        cin>>n[id]>>m;
        for(int i=1;i<=m;i++){
            int x;
            cin>>x;
            out[id][x+1]=true;
        }
        for(int i=1;i<=n[id];i++){
            int p0,p1;
            cin>>p0>>p1;
            go[id][i][0]=p0+1;
            go[id][i][1]=p1+1;
        }
    }

    prepare();

    for(int i=1;i<=k;i++){
        if(dfn[i]==0){
            tarjan(i);
        }
    }

    cout<<compute()<<endl;
    return 0;
}