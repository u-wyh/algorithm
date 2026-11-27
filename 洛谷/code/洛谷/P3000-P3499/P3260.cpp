// https://www.luogu.com.cn/problem/P3260

// 题意：输入通道右上角 C 点坐标
// (x, y)
// （通道由平行于 x 轴的镜面 AC 和 BD 构成，B 在 (0,0)）
// 、光学元件数 n
// 以及 n 个圆形或轴对齐矩形元件参数。
// 元件外表面也是镜面，元件之间或与通道边界接触（如相切）则光线无法通过；
// 光线可从 AB 上任意点以任意角度射入并多次反射，目标是射出 CD 边。
// 输出至少需要拿走多少个光学元件才能存在一条从 AB 穿出到 CD 的光线路径。
// 数据范围：x <= 10^5，y <= 1000，n <= 300。
// 算法标签：最大流、最小割、计算几何
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 305;
const int MAXV = MAXN*2;
const int MAXM = MAXN*MAXN*2;
const int INF = 1e15;

int X,Y;
int n,m,s,t;

struct Object{
    int op;
    int x,y,r;
    int x1,y1,x2,y2;
};
Object object[MAXN];

int head[MAXV];
int nxt[MAXM];
int to[MAXM];
int limit[MAXM];
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

int sqr(int x){
    return x*x;
}

// 判断元件是否与高度为 h 的通道边界相交
bool checkwall(Object o,int h){
    if(o.op==1){
        // 找到边界线段上距离圆心最近的点
        int px=min(max(o.x,0LL),X);
        return sqr(o.x-px)+sqr(o.y-h)<=sqr(o.r);
    }
    else{
        // 矩形与水平线段相交
        return o.x1<=X&&o.x2>=0
            &&o.y1<=h&&h<=o.y2;
    }
}

// 判断两个元件是否相交或相切
bool check(Object o1,Object o2){
    // 圆与圆
    if(o1.op+o2.op==2){
        return sqr(o1.x-o2.x)+sqr(o1.y-o2.y)
            <=sqr(o1.r+o2.r);
    }
    // 圆与矩形
    else if(o1.op+o2.op==3){
        // 保证 o1 为矩形，o2 为圆
        if(o1.op==1){
            swap(o1,o2);
        }

        // 矩形中距离圆心最近的点
        int px=min(max(o2.x,o1.x1),o1.x2);
        int py=min(max(o2.y,o1.y1),o1.y2);

        return sqr(px-o2.x)+sqr(py-o2.y)<=sqr(o2.r);
    }
    // 矩形与矩形
    else{
        // 两个矩形在 x、y 轴上的投影均有交集
        return max(o1.x1,o2.x1)<=min(o1.x2,o2.x2)
            &&max(o1.y1,o2.y1)<=min(o1.y2,o2.y2);
    }
}

void bfs(int s){
    // 重置距离和当前弧数组
    for(int i=1;i<=n;i++){
        dis[i]=n;
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
            if(dis[v]==n && lim>0){
                dis[v]=dis[u]+1;
                que[++r]=v;
            }
        }
    }
}

// 目前来到了 u 这个点，还有 rest 的流量，遇到 t 停止
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
            int k=dfs(v,min(rest,lim),t);
            flow+=k;
            rest-=k;
            limit[i]-=k;
            limit[i^1]+=k;
        }
    }
    return flow;
}

int maxflow(int s,int t){
    int ans=0;
    bfs(s);
    while(dis[t]!=n){
        ans+=dfs(s,INF,t);
        bfs(s);
    }
    return ans;
}

signed main()
{
    cin>>X>>Y>>m;
    for(int i=1;i<=m;i++){
        cin>>object[i].op;
        if(object[i].op==1){
            cin>>object[i].x>>object[i].y>>object[i].r;
        }
        else{
            cin>>object[i].x1>>object[i].y1
               >>object[i].x2>>object[i].y2;
        }
    }

    // 每个元件拆成入点 i 和出点 i+m
    // s 表示上边界，t 表示下边界
    s=2*m+1;
    t=2*m+2;
    n=t;

    for(int i=1;i<=m;i++){
        // 删除一个元件的代价为 1
        addedge(i,i+m,1);
        addedge(i+m,i,0);

        // 元件与上边界相交
        if(checkwall(object[i],Y)){
            addedge(s,i,INF);
            addedge(i,s,0);
        }

        // 元件与下边界相交
        if(checkwall(object[i],0)){
            addedge(i+m,t,INF);
            addedge(t,i+m,0);
        }
    }

    // 两两判断元件是否相交
    for(int i=1;i<=m;i++){
        for(int j=i+1;j<=m;j++){
            if(check(object[i],object[j])){
                // 元件 i 可以连通到元件 j
                addedge(i+m,j,INF);
                addedge(j,i+m,0);

                // 元件 j 可以连通到元件 i
                addedge(j+m,i,INF);
                addedge(i,j+m,0);
            }
        }
    }

    // 最小点割等于拆点之后的最大流
    cout<<maxflow(s,t)<<endl;
    return 0;
}
