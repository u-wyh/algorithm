// https://www.luogu.com.cn/problem/P4048
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 205;
const int MAXV = 405;
const int MAXM = 5e4+5;
const int INF = 1e15;

int n,m,k;

struct Point{
    int x,y;
};
struct Lich{
    Point p;
    int r,t;
};
struct Tree{
    Point p;
    int r;
};
Lich lich[MAXN];
Point elf[MAXN];
Tree tree[MAXN];

bool can[MAXN][MAXN];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

int len2(Point a){
    return a.x*a.x+a.y*a.y;
}

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

int dot(Point a,Point b){
    return a.x*b.x+a.y*b.y;
}

// 判断线段ab是否与圆有公共点
bool block(Point a,Point b,Tree tr){
    Point v=b-a;
    Point w=tr.p-a;
    int d2=len2(v);
    int r2=tr.r*tr.r;

    // 线段退化为一个点
    if(d2==0){
        return len2(w)<=r2;
    }

    int d=dot(v,w);

    // 投影在a外侧
    if(d<=0){
        return len2(w)<=r2;
    }

    // 投影在b外侧
    if(d>=d2){
        return len2(tr.p-b)<=r2;
    }

    // 投影在线段内部
    int c=cross(v,w);
    return c*c<=r2*d2;
}

void prepare(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            can[i][j]=true;
            if(len2(lich[i].p-elf[j])>lich[i].r*lich[i].r){
                can[i][j]=false;
                continue;
            }
            for(int t=1;t<=k;t++){
                if(block(lich[i].p,elf[j],tree[t])){
                    can[i][j]=false;
                    break;
                }
            }
        }
    }
}

int s,t,tot;
int head[MAXV];
int nxt[MAXM<<1];
int to[MAXM<<1];
int limit[MAXM<<1];
int cntg=2;

int dis[MAXV];
int que[MAXV];
int cur[MAXV];

void addedge(int u,int v,int w){
    nxt[cntg]=head[u];
    to[cntg]=v;
    limit[cntg]=w;
    head[u]=cntg++;
}

void bfs(int s){
    for(int i=1;i<=tot;i++){
        dis[i]=tot;
        cur[i]=head[i];
    }
    dis[s]=0;
    int l=1,r=0;
    que[++r]=s;
    while(l<=r){
        int u=que[l++];
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int lim=limit[i];
            if(dis[v]==tot &&lim>0){
                dis[v]=dis[u]+1;
                que[++r]=v;
            }
        }
    }
}

int dfs(int u,int rest,int t){
    if(u==t){
        return rest;
    }
    int flow=0;
    for(int i=cur[u];i && rest>0;i=nxt[i]){
        cur[u]=i;
        int v=to[i];
        int lim=limit[i];
        if(dis[u]+1==dis[v] && lim>0){
            int w=dfs(v,min(rest,lim),t);
            flow+=w;
            rest-=w;
            limit[i]-=w;
            limit[i^1]+=w;
        }
    }
    return flow;
}

int maxflow(int s,int t){
    int ans=0;
    bfs(s);
    while(dis[t]!=tot){
        ans+=dfs(s,INF,t);
        bfs(s);
    }
    return ans;
}

bool check(int limit){
    for(int i=1;i<=tot;i++){
        head[i]=0;
    }
    cntg=2;

    for(int i=1;i<=n;i++){
        int c;
        if(lich[i].t==0){
            c=m;
        }
        else{
            c=min(m,limit/lich[i].t+1);
        }
        addedge(s,i,c);
        addedge(i,s,0);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(can[i][j]){
                addedge(i,n+j,1);
                addedge(n+j,i,0);
            }
        }
    }
    for(int i=1;i<=m;i++){
        addedge(n+i,t,1);
        addedge(t,n+i,0);
    }

    return maxflow(s,t)==m;
}

signed main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        cin>>lich[i].p.x>>lich[i].p.y>>lich[i].r>>lich[i].t;
    }
    for(int i=1;i<=m;i++){
        cin>>elf[i].x>>elf[i].y;
    }
    for(int i=1;i<=k;i++){
        cin>>tree[i].p.x>>tree[i].p.y>>tree[i].r;
    }

    prepare();

    for(int i=1;i<=m;i++){
        bool flag=true;
        for(int j=1;j<=n;j++){
            if(can[j][i]){
                flag=false;
                break;
            }
        }
        if(flag){
            cout<<"-1"<<endl;
            return 0;
        }
    }

    s=n+m+1;
    t=s+1;
    tot=t;

    int l=0,r=m*20000,ans=r;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    cout<<ans<<endl;
    return 0;
}