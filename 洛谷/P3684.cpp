#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;
const int MAXM = 1e6+1e4;
const int MAXE = MAXM*4;  // 增大边数组大小
const int MAXH = 22;

int n,q;
char s[MAXN][MAXN];
const int dx8[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy8[] = {-1, 0, 1, -1, 1, -1, 0, 1};
int walk[2][2]={{1,0},{0,1}};
int val[MAXN][MAXN];
int dist[MAXN][MAXN];

int fa[MAXE];
int id[MAXM];
int idcnt;

int m;
struct node{
    int u,v,w;
};
node nums[MAXE];

int cntu;
int key[MAXE];  // 增大数组大小
int dep[MAXE];
int st[MAXE][MAXH];
int in[MAXE] = {0};  // 添加入度数组

int head[MAXE];
int nxt[MAXE*4];  // 增大边数组
int to[MAXE*4];
int cnt_edge=0;  // 使用cnt_edge代替cnt

void multiSourceBFS() {
    queue<pair<int, int>> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (s[i][j] == '#') {
                dist[i][j] = 0;
                q.push({i, j});
            } else {
                dist[i][j] = -1;
            }
        }
    }
    
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        
        for (int d = 0; d < 8; d++) {
            int nx = x + dx8[d];
            int ny = y + dy8[d];
            if (nx < 1 || nx > n || ny < 1 || ny > n) continue;
            if (dist[nx][ny] != -1) continue;
            dist[nx][ny] = dist[x][y] + 1;
            q.push({nx, ny});
        }
    }
}

void computeMaxSquares() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (s[i][j] == '#') {
                val[i][j] = 0;
                continue;
            }
            int up = i-1, down = n-i, left = j-1, right = n-j;
            int bound = min({up, down, left, right});
            int safe_radius = (dist[i][j] == -1) ? bound : min(dist[i][j]-1, bound);
            safe_radius = max(safe_radius, 0);
            val[i][j] = 2 * safe_radius + 1;
        }
    }
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

bool cmp(node a,node b){
    return a.w>b.w;
}

inline void addedge(int u,int v){
    nxt[++cnt_edge]=head[u];
    to[cnt_edge]=v;
    head[u]=cnt_edge;
}

void kruskalrebuild(){
    for(int i=1;i<=idcnt;i++){
        fa[i]=i;
    }
    sort(nums+1,nums+m+1,cmp);
    cntu=idcnt;
    for(int i=1;i<=m;i++){
        int u = nums[i].u, v = nums[i].v;
        int fu=find(u), fv=find(v);
        if(fu==fv) continue;
        cntu++;
        key[cntu]=nums[i].w;
        fa[fu]=fa[fv]=cntu;
        fa[cntu]=cntu;
        addedge(cntu,fu); in[fu]++;
        addedge(cntu,fv); in[fv]++;
    }
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<MAXH;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa) continue;
        dfs(v,u);
    }
}

inline int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    for (int p = MAXH-1; p >= 0; p--) {
        if (dep[st[a][p]] >= dep[b]) {
            a = st[a][p];
        }
    }
    if (a == b) return a;
    for (int p = MAXH-1; p >= 0; p--) {
        if (st[a][p] != st[b][p]) {
            a = st[a][p];
            b = st[b][p];
        }
    }
    return st[a][0];
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",s[i]+1);
    }
    
    multiSourceBFS();
    computeMaxSquares();

    // 初始化并查集
    for(int i=1;i<=n*n;i++){
        fa[i]=i;
    }

    // 构建连通块 (水平+垂直)
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(s[i][j]=='#') continue;  // 跳过障碍物
            
            int idx=(i-1)*n+j;
            for(int k=0;k<2;k++){
                int ni=i+walk[k][0];
                int nj=j+walk[k][1];
                if(ni>n || nj>n) continue;
                if(s[ni][nj]=='#') continue;  // 跳过障碍物
                
                if(val[i][j]==val[ni][nj]){
                    int nidx=(ni-1)*n+nj;
                    int fu=find(idx), fv=find(nidx);
                    if(fu!=fv) fa[fu]=fv;
                }
            }
        }
    }

    // 分配连通块ID
    idcnt=0;
    vector<int> block_val(MAXE,0);  // 存储连通块权值
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(s[i][j]=='#') continue;  // 跳过障碍物
            
            int idx=(i-1)*n+j;
            int root=find(idx);
            if(fa[root]==root){
                id[root]=++idcnt;
                block_val[idcnt]=val[i][j];  // 记录连通块权值
            }
        }
    }
    // 设置叶子节点权值 (关键修复)
    for(int i=1;i<=idcnt;i++){
        key[i]=block_val[i];
    }
    // 传播连通块ID
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int idx=(i-1)*n+j;
            if(s[i][j]=='#') continue;
            id[idx]=id[find(idx)];
        }
    }

    // 构建连通块之间的边
    m=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(s[i][j]=='#') continue;
            
            int u=id[(i-1)*n+j];
            for(int k=0;k<2;k++){
                int ni=i+walk[k][0];
                int nj=j+walk[k][1];
                if(ni>n || nj>n) continue;
                if(s[ni][nj]=='#') continue;
                
                int v=id[(ni-1)*n+nj];
                if(u!=v){
                    // 避免重复边
                    if(u < v) nums[++m]={u, v, min(val[i][j], val[ni][nj])};
                    else if(u > v) nums[++m]={v, u, min(val[i][j], val[ni][nj])};
                }
            }
        }
    }

    // 构建Kruskal重构树
    kruskalrebuild();
    
    // 添加虚拟根节点 (关键修复)
    int root = cntu+1;
    key[root] = 0;
    for(int i=1;i<=cntu;i++){
        if(in[i]==0){ // 连接所有根节点
            addedge(root, i);
        }
    }
    cntu = root;
    
    // DFS初始化LCA
    dep[0]=0;
    dfs(root,0);

    // 处理查询
    scanf("%d",&q);
    while(q--){
        int x1,y1,x2,y2;
        scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
        // 注意: 题目保证查询点不是障碍物
        int id1=id[(x1-1)*n+y1];
        int id2=id[(x2-1)*n+y2];
        int l = lca(id1, id2);
        printf("%d\n", key[l]);
    }
    return 0;
}