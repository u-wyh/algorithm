#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;
const int MAXN = 2e5+10; 
const int MAXM = 2e5+5;
const int MAXH = 20;

int n,m,k;
long long ans=0;
int nodecnt=0;

struct node{
    int u,v,w;
    bool operator<(node other){
        return w<other.w;
    }
};
node nums[MAXM];
bool vis[MAXM];

int fa[MAXN];

int head[MAXN<<1];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int cntu;
int key[MAXN<<1];
long long sz[MAXN<<1];
long long all[MAXN<<1];//这个子树有多少条边

int dep[MAXN<<1];
int st[MAXN<<1][MAXH];

int rk[MAXN<<1];
int dfncnt;

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

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void kruskalrebuild(){
    sort(nums+1,nums+m+1);
    for(int i=1;i<=n;i++){
        fa[i]=i;
        sz[i]=1;
        all[i]=0;
    }
    cntu=n;
    for(int i=1;i<=m;i++){
        int fx=find(nums[i].u);
        int fy=find(nums[i].v);
        if(fx!=fy){
            vis[i]=true;
            ++cntu;
            all[cntu]++;
            fa[fx]=fa[fy]=cntu;
            fa[cntu]=cntu;
            key[cntu]=nums[i].w;
            addedge(cntu,fx);
            addedge(cntu,fy);
        }
    }
}

void bfs(int u){
    dfncnt=0;
    rk[++dfncnt]=u;
    dep[u]=1;
    st[u][0]=0;
    for(int p=1;p<MAXH;p++){
        st[u][p]=st[st[u][p-1]][p-1];
    }
    queue<int>q;
    q.push(u);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            rk[++dfncnt]=v;
            dep[v]=dep[u]+1;
            st[v][0]=u;
            for(int p=1;p<MAXH;p++){
                st[v][p]=st[st[v][p-1]][p-1];
            }
            q.push(v);
        }
    }
}

void bfs1(){
    for(int i=dfncnt;i>=1;i--){
        if(rk[i]<=n){
            continue;
        }
        int u=rk[i];
        for(int j=head[u];j;j=nxt[j]){
            int v=to[j];
            sz[u]+=sz[v];
            all[u]+=all[v];
        }
    }
}

void bfs2(){
    for(int i=dfncnt;i>=1;i--){
        if(rk[i]<=n){
            continue;
        }
        int u=rk[i];
        int ls=0,rs=0;
        for(int j=head[u];j;j=nxt[j]){
            int v=to[j];
            if(ls==0){
                ls=v;
            }
            else{
                rs=v;
            }
        }
        ans=(ans+1ll*(key[u]-1)*((((1ll*sz[ls]*sz[rs])%MOD-all[u]+all[ls]+all[rs])%MOD+MOD)%MOD)%MOD)%MOD;
    }
}

inline int lca(int a, int b) {
    if (dep[a] < dep[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    for (int p = MAXH-1; p >= 0; p--) {
        if (dep[st[a][p]] >= dep[b]) {
            a = st[a][p];
        }
    }
    if (a == b) {
        return a;
    }
    for (int p = MAXH-1; p >= 0; p--) {
        if (st[a][p] != st[b][p]) {
            a = st[a][p];
            b = st[b][p];
        }
    }
    return st[a][0];
}

void prepare(){
    ans=0;
    for(int i=1;i<=2*n;i++){
        head[i]=0;
        sz[i]=0;
        all[i]=0;
    }
    cnt=1;
}

int main()
{
    int T=read();
    while(T--){
        n=read(),m=read(),k=read();
        prepare();
        for(int i=1;i<=m;i++){
            nums[i].u=read(),nums[i].v=read(),nums[i].w=read();
            vis[i]=false;
        }

        kruskalrebuild();

        int block=0;
        for(int i=1;i<=cntu;i++){
            if(i==find(i)){
                block++;
            }
        }

        if(block>2){
            printf("0\n");
            continue;
        }

        if(block==2){
            ans=k;
            for(int i=1;i<=cntu;i++){
                if(i==find(i)){
                    nodecnt=0;
                    for(int j=1;j<=n;j++){
                        if(find(j)==i){
                            nodecnt++;
                        }
                    }
                    ans=(ans*nodecnt)%MOD;
                }
            }
            printf("%lld\n",ans);
            continue;
        }
        
        bfs(cntu);

        for(int i=1;i<=m;i++){
            if(!vis[i]){
                int fa=lca(nums[i].u,nums[i].v);
                all[fa]++;
            }
        }

        bfs1();
        
        bfs2();

        ans=(ans%MOD+MOD)%MOD;
        printf("%lld\n",ans);
    }
    return 0;
}