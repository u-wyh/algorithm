#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n,m,q,k;

struct Edge{
    int u,v,w;
}edge[MAXN];

struct Query{
    int u,v,w,i;
}query[MAXN];

bool ans[MAXN];

int fa[MAXN];
int sz[MAXN];

int sta[MAXN<<1][2];
int top;

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

bool edgecmp(Edge a,Edge b){
    return a.w<b.w;
}

bool querycmp(Query a,Query b){
    return (a.w==b.w)?a.i<b.i:a.w<b.w;
}

int find(int i) {
    while (i != fa[i]) {
        i = fa[i];//没有扁平化
    }
    return i;
}

void un(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (sz[fx] < sz[fy]) {
        int tmp = fx;
        fx = fy;
        fy = tmp;
    }
    fa[fy] = fx;
    sz[fx] += sz[fy];
    //将操作入栈
    sta[++top][0] = fx;
    sta[top][1] = fy;
}

void undo(){
    int fx=sta[top][0];
    int fy=sta[top--][1];
    sz[fx]-=sz[fy];
    fa[fy]=fy;
}

void compute(){
    int u=1,cnt=0,id=0;
    for(int l=1,r=1;l<=k;l=++r){
        id=query[l].i;
        while(r+1<=k&&query[r+1].w==query[l].w&&query[r+1].i==id){
            r++;
        }
        for(;u<=m&&edge[u].w<query[l].w;u++){
            if(find(edge[u].v)!=find(edge[u].u))
                un(edge[u].v,edge[u].u);
        }
        if(!ans[id]){
            continue;
        }
        cnt=0;
        for(int i=l;i<=r;i++){
            if(find(query[i].u)==find(query[i].v)){
                ans[id]=false;
                break;
            }
            else{
                un(query[i].u,query[i].v);
                cnt++;
            }
        }
        for(int i=1;i<=cnt;i++){
            undo();
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= m; i++){
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
    }
    cin >> q;
    k=0;
    for(int i=1,p;i<=q;i++){
        cin>>p;
        for(int j=1,t;j<=p;j++){
            cin>>t;
            query[++k].u=edge[t].u;
            query[k].v=edge[t].v;
            query[k].w=edge[t].w;
            query[k].i=i;
        }
    }
    sort(edge+1,edge+m+1,edgecmp);
    sort(query+1,query+k+1,querycmp);
    for(int i=1;i<=n;i++){
        fa[i]=i;
        sz[i]=1;
    }
    for(int i=1;i<=q;i++){
        ans[i]=true;
    }
    compute();
    for (int i = 1; i <= q; i++) {
        if (ans[i]) {
            cout << "YES" << "\n";
        } 
        else {
            cout << "NO" << "\n";
        }
    }
    return 0;
}