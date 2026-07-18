// https://www.luogu.com.cn/problem/CF786B
// 这道题是需要线段树优化建图的模板题  我们准备两个线段树
// 第一个线段树父亲节点到儿子节点的距离是0  第二个是儿子节点到父亲节点的距离是0
// 那么第二个操作 就是节点向正向图连边  表示达到这个区间的新边
// 第三个操作就是在反向图上建边  表示这个区间到达这个节点
// 其实两个线段树的叶节点代表的节点是一样的  他们之间距离是0（如果点相同的话）
// 这道题直接将两个树使用同样的一批叶节点  也很巧妙
// P6348 P9331 P7984 P5025也是线段树优化建图
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 9*MAXN;
const long long INF = 1e18;

int n,q,st;

long long dis[MAXM];
bool vis[MAXM];
struct node{
    int pos;
    long long d;
};
struct compare{
    bool operator()(node a,node b){
        return a.d>b.d;
    }
};
priority_queue<node,vector<node>,compare>heap;

int nodecnt;
int root1,root2;
int ls1[MAXM];
int rs1[MAXM];
int ls2[MAXM];
int rs2[MAXM];

int head[MAXM];
int nxt[MAXM<<2];
int to[MAXM<<2];
int weight[MAXM<<2];
int cnt=1;

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

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

int build1(int l,int r){
    if(l==r){
        return l;
    }
    else{
        int mid=(l+r)>>1;
        int now=++nodecnt;
        ls1[now]=build1(l,mid);
        rs1[now]=build1(mid+1,r);
        addedge(now,ls1[now],0);
        addedge(now,rs1[now],0);
        return now;
    }
}

int build2(int l,int r){
    if(l==r){
        return l;
    }
    else{
        int mid=(l+r)>>1;
        int now=++nodecnt;
        ls2[now]=build2(l,mid);
        rs2[now]=build2(mid+1,r);
        addedge(ls2[now],now,0);
        addedge(rs2[now],now,0);
        return now;
    }
}

void update1(int jobl,int jobr,int jobv,int jobw,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        addedge(jobv,i,jobw);
    }
    else{
        int mid=(l+r)>>1;
        if(jobl<=mid){
            update1(jobl,jobr,jobv,jobw,l,mid,ls1[i]);
        }
        if(jobr>mid){
            update1(jobl,jobr,jobv,jobw,mid+1,r,rs1[i]);
        }
    }
}

void update2(int jobl,int jobr,int jobv,int jobw,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        addedge(i,jobv,jobw);
    }
    else{
        int mid=(l+r)>>1;
        if(jobl<=mid){
            update2(jobl,jobr,jobv,jobw,l,mid,ls2[i]);
        }
        if(jobr>mid){
            update2(jobl,jobr,jobv,jobw,mid+1,r,rs2[i]);
        }
    }
}

void dijkstra(){
    for(int i=1;i<=nodecnt;i++){
        dis[i]=INF;
    }
    dis[st]=0;
    heap.push({st,0});
    while(!heap.empty()){
        node tmp=heap.top();
        heap.pop();
        int u=tmp.pos;
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                heap.push({v,dis[v]});
            }
        }
    }
}

int main()
{
    n=read(),q=read(),st=read();
    nodecnt=n;

    root1=build1(1,n);
    root2=build2(1,n);

    while(q--){
        int op=read();
        if(op==1){
            int v,u,w;
            v=read(),u=read(),w=read();
            addedge(v,u,w);
        }
        else if(op==2){
            int v,l,r,w;
            v=read(),l=read(),r=read(),w=read();
            update1(l,r,v,w,1,n,root1);
        }
        else{
            int v,l,r,w;
            v=read(),l=read(),r=read(),w=read();
            update2(l,r,v,w,1,n,root2);
        }
    }
    dijkstra();
    for(int i=1;i<=n;i++){
        if(dis[i]==INF){
            dis[i]=-1;
        }
        printf("%lld ",dis[i]);
    }
    return 0;
}