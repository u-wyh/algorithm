#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;
const int MAXK = 55;

int n,m,k,mod;
bool flag=0;//≈–∂œ”–Œﬁ0ª∑

int dis[MAXN];
int dp[MAXN][MAXK];
bool vis[MAXN];
bool visit[MAXN][MAXK];

int cnt=1;
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];

int tot=1;
int head1[MAXN];
int nxt1[MAXM];
int to1[MAXM];
int weight1[MAXM];

struct Compare {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    }
};
priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> heap;

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

void build(){
    cnt=1;
    tot=1;
    for(int i=1;i<=n;i++){
        head[i]=0;
        head1[i]=0;
    }
}

inline void addedge(int u, int v, int w) {
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

inline void Addedge(int u, int v, int w) {
    nxt1[tot] = head1[u];
    to1[tot] = v;
    weight1[tot] = w;
    head1[u] = tot++;
}

void dijkstra(int st) {
    for (int i = 1; i <= n ; i++) {
        dis[i] = INT_MAX;
        vis[i]=false;
    }
    dis[st] = 0;
    heap.push({st, 0});
    while (!heap.empty()) {
        int u = heap.top().first;
        heap.pop();
        if (vis[u]) {
            continue;
        }
        vis[u] = true;
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            int w = weight[i];
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                heap.push({v, dis[v]});
            }
        }
    }
}

int dfs(int u,int val){
    if(visit[u][val]){
        flag=true;
        return 0;
    }
    if(dp[u][val]!=-1){
        return dp[u][val];
    }
    visit[u][val]=true;
    int ans=0;
    for(int i=head1[u];i;i=nxt1[i]){
        int v=to1[i];
        int w=weight1[i];
        int nk=dis[u]+val-dis[v]-w;
        if(nk<0||nk>k){
            continue;
        }
        ans+=dfs(v,nk);
        ans%=mod;
    }
    visit[u][val]=0;
    if(u==1&&val==0)
        ans=1;
    dp[u][val]=ans;
    return ans;
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        build();
        n=read(),m=read(),k=read(),mod=read();
        for(int i=1;i<=m;i++){
            int u,v,w;
            u=read(),v=read(),w=read();
            addedge(u,v,w);
            Addedge(v,u,w);
        }
        dijkstra(1);
        flag=false;
        int ans=0;
        for(int p=1;p<=n;p++){
            for(int j=0;j<=k;j++){
                visit[p][j]=0;
                dp[p][j]=-1;
            }
        }
        for(int i=0;i<=k;i++){
            ans=(ans+dfs(n,i))%mod;
            if(flag){
                ans=-1;
                break;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}