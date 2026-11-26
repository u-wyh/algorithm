// https://www.luogu.com.cn/problem/P1674
// 题意：给定 N 个点、P 条无向边（可能有重边），每条边长度为 L_i。
// 需找到 T 条从 1 到 N 的路径，且每条边在所有路径中至多经过一次。
// 求这 T 条路径所经过的所有边中，最长边长度的最小值，输出该值。
// 数据范围：
// 2 <= N <= 200（点数）
// 1 <= P <= 4*10^4（边数）
// 1 <= T <= 200（路径条数）
// L_i <= 10^6（边长，题干说明小于 10^6）
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;
const int MAXM = 4e4+5;
const int INF = 1e9;

int n,m,need,s,t;

struct node{
    int u,v,w;
};
node nums[MAXM];

int dep[MAXN];
int iter[MAXN];

int cnt=2;
int head[MAXN];
int nxt[MAXM<<2];
int to[MAXM<<2];
int now[MAXM<<2];
int cap[MAXM<<2];

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

void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    cap[cnt]=w;
    now[cnt]=0;
    head[u]=cnt++;

    nxt[cnt]=head[v];
    to[cnt]=u;
    cap[cnt]=0;
    now[cnt]=0;
    head[v]=cnt++;
}

bool cmp(node a,node b){
    return a.w<b.w;
}

bool bfs(){
    for(int i=1;i<=n;i++){
        dep[i]=-1;
    }
    queue<int>q;
    dep[s]=0;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=cap[i];
            int k=now[i];
            if(dep[v]<0&&(k<w)){
                dep[v]=dep[u]+1;
                q.push(v);
            }
        }
    }
    return dep[t]>=0;
}

int dfs(int u,int f){
    if(u==t){
        return f;
    }
    int flow=0;
    for(int &i=iter[u];i;i=nxt[i]){
        int v=to[i];
        int w=cap[i];
        int k=now[i];
        if(dep[u]+1==dep[v]&&k<w){
            int d=dfs(v,min(f,w-k));
            if(d>0){
                now[i]+=d;
                now[i^1]-=d;
                flow+=d;
                f-=d;
                if(f==0){
                    break;
                }
            }
        }
    }
    return flow;
}

// Dinic算法主函数
int maxflow(){
    int flow=0;
    while(bfs()){
        //当前弧全部初始化为最初值
        for(int i=1;i<=n;i++){
            iter[i]=head[i];
        }
        int maxflow;
        while((maxflow=dfs(s,INF))>0){
            flow+=maxflow;
        }
    }
    return flow;
}


bool check(int limit){
    cnt=2;
    for(int i=1;i<=n;i++){
        head[i]=0;
    }

    s=1,t=n;
    for(int i=1;i<=m;i++){
        if(nums[i].w>limit){
            break;
        }
        addedge(nums[i].u,nums[i].v,1);
        addedge(nums[i].v,nums[i].u,1);
    }
    int flow=maxflow();
    return flow>=need;
}

int main()
{
    n=read(),m=read(),need=read();
    int l=1,r=1,ans=0;
    for(int i=1;i<=m;i++){
        nums[i].u=read(),nums[i].v=read(),nums[i].w=read();
        r=max(r,nums[i].w);
    }
    sort(nums+1,nums+m+1,cmp);
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