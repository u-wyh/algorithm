#include<bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e15+5;
const int MAXN = 1e5+5;
const int MAXM = 3e5+5;
const int MAXH = 17;

int n,m;
struct node{
    int u,v,w;
    bool vis;
};
node nums[MAXM];
int fa[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;

int dep[MAXN];
int st[MAXN][MAXH];
int d1[MAXN][MAXH];
int d2[MAXN][MAXH];

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

bool cmp(node a,node b){
    return a.w<b.w;
}

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    for(int i=1;i<MAXH;i++){
        st[u][i]=st[st[u][i-1]][i-1];
        int arr[4]={d1[u][i-1],d2[u][i-1],d1[st[u][i-1]][i-1],d2[st[u][i-1]][i-1]};
        d1[u][i]=d2[u][i]=-INF;
        for(int val:arr){
            if (val > d1[u][i]) {
                d2[u][i] = d1[u][i];
                d1[u][i] = val;
            } else if (val < d1[u][i] && val > d2[u][i]) {
                d2[u][i] = val;
            }
        }
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v==fa){
            continue;
        }
        st[v][0]=u;
        d1[v][0]=w;
        d2[v][0]=-INF;
        dfs(v,u);
    }
}

void update(int &m1,int &m2,int &val){
    if (val > m1) {
        m2 = m1;
        m1 = val;
    } else if (val < m1 && val > m2) {
        m2 = val;
    }
}

pair<int,int>query(int u,int v){
    if(u==v){
        return {-INF,-INF};
    }
    if(dep[u]<dep[v]){
        swap(u,v);
    }
    int ans1=-INF,ans2=-INF;
    for(int i=MAXH-1;i>=0;i--){
        if(dep[st[u][i]]>=dep[v]){
            update(ans1,ans2,d1[u][i]);
            update(ans1,ans2,d2[u][i]);
            u=st[u][i];
        }
    }
    if(u==v){
        return {ans1,ans2};
    }
    for(int i=MAXH-1;i>=0;i--){
        if(st[u][i]!=st[v][i]){
            update(ans1,ans2,d1[u][i]);
            update(ans1,ans2,d2[u][i]);
            update(ans1,ans2,d1[v][i]);
            update(ans1,ans2,d2[v][i]);
            u=st[u][i];
            v=st[v][i];
        }
    }
    update(ans1,ans2,d1[u][0]);
    update(ans1,ans2,d2[u][0]);
    update(ans1,ans2,d1[v][0]);
    update(ans1,ans2,d2[v][0]);
    return {ans1,ans2};
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        nums[i].u=read(),nums[i].v=read(),nums[i].w=read();
        nums[i].vis=false;
    }
    sort(nums+1,nums+m+1,cmp);
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    int all=0;
    for(int i=1;i<=m;i++){
        int fx=find(nums[i].u);
        int fy=find(nums[i].v);
        if(fx!=fy){
            fa[fx]=fy;
            addedge(nums[i].u,nums[i].v,nums[i].w);
            addedge(nums[i].v,nums[i].u,nums[i].w);
            all+=nums[i].w;
            nums[i].vis=true;
        }
    }
    d1[1][0]=d2[1][0]=-INF;
    dfs(1,0);
    int ans=INT_MAX;
    for(int i=1;i<=m;i++){
        if(!nums[i].vis&&(nums[i].u!=nums[i].v)){
            int u=nums[i].u,v=nums[i].v;
            int w=nums[i].w;
            pair<int,int> tmp=query(u,v);
            if(w>tmp.first){
                ans=min(ans,w-tmp.first);
            }
            else if(w==tmp.first&&tmp.second!=INF){
                ans=min(ans,w-tmp.second);
            }
        }
    }
    ans+=all;
    cout<<ans<<endl;
    return 0;
}