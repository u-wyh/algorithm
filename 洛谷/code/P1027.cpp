// https://www.luogu.com.cn/problem/P1027
// 题意：每座城市有四个机场，组成一个矩形，输入其中三个机场的坐标。
// 城内任意两个机场之间可乘铁路，单价 T[i]，不同城市的机场之间可乘飞机，单价 t。
// 票价按直线距离乘单价。
// 起点城市 A 和终点城市 B 的机场任选，输出最低花费，保留一位小数。
// 数据范围：1 ≤ 测试组数 ≤ 10，1 ≤ S ≤ 100，1 ≤ A,B ≤ S，输入坐标和单价均在 [0,500]。
// 算法标签：Dijkstra、计算几何

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 405;
const int MAXM = 405*405+405*3;
const double INF = 1e9;

int n,t,a,b;
struct Point{
    int x,y;
};
int cnt;
Point p[MAXN];
int val[MAXN];
int bel[MAXN];

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
double weight[MAXM];
int cntg=1;

double dis[MAXN];
bool vis[MAXN];
struct node{
    int u;
    double d;
};
struct compare{
    bool operator()(node &a,node &b){
        return a.d>b.d;
    }
};
priority_queue<node,vector<node>,compare>heap;

void dijkstra(int s){
    for(int i=1;i<=cnt;i++){
        dis[i]=INF;
        vis[i]=false;
    }

    dis[s]=0;
    heap.push({s,0});
    while(!heap.empty()){
        int u=heap.top().u;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            double w=weight[i];
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                heap.push({v,dis[v]});
            }
        }
    }
}

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

int dot(Point a,Point b){
    return a.x*b.x+a.y*b.y;
}

Point calc(Point a,Point b,Point c){
    return {a.x+b.x-c.x,a.y+b.y-c.y};
}

bool check(Point a,Point b,Point c,Point d){
    if(dot(a-b,c-b)==0 && dot(b-c,c-d)==0 && dot(d-c,d-a)==0 && dot(d-a,a-b)==0){
        return true;
    }
    return false;
}

Point addPoint(int offset){
    Point p1=p[offset+1];
    Point p2=p[offset+2];
    Point p3=p[offset+3];
    Point p4;
    p4=calc(p1,p2,p3);
    if(check(p1,p3,p2,p4)){
        return p4;
    }
    p4=calc(p1,p3,p2);
    if(check(p1,p2,p3,p4)){
        return p4;
    }
    p4=calc(p2,p3,p1);
    if(check(p2,p1,p3,p4)){
        return p4;
    }
}

double len(Point x){
    return sqrt(dot(x,x));
}

double cost(int x,int y){
    if(bel[x]==bel[y]){
        return val[bel[x]]*len(p[x]-p[y]);
    }
    else{
        return t*len(p[x]-p[y]);
    }
}

void addedge(int u,int v,double w){
    nxt[cntg]=head[u];
    to[cntg]=v;
    weight[cntg]=w;
    head[u]=cntg++;
}

void prepare(){
    for(int i=1;i<=cnt;i++){
        head[i]=0;
    }
    cntg=1;
    for(int i=1;i<=n;i++){
        p[4*i]=addPoint((i-1)*4);
        // cout<<"   "<<i<<' '<<p[4*i].x<<' '<<p[4*i].y<<endl;
        bel[4*i]=i;
        bel[4*i-1]=i;
        bel[4*i-2]=i;
        bel[4*i-3]=i;
    }
    for(int i=1;i<=cnt;i++){
        for(int j=i+1;j<=cnt;j++){
            if(i==j){
                continue;
            }
            double w=cost(i,j);
            addedge(i,j,w);
            addedge(j,i,w);
        }
    }
}

void solve(){
    cin>>n>>t>>a>>b;
    cnt=0;
    for(int i=1;i<=n;i++){
        ++cnt;
        cin>>p[cnt].x>>p[cnt].y;
        ++cnt;
        cin>>p[cnt].x>>p[cnt].y;
        ++cnt;
        cin>>p[cnt].x>>p[cnt].y;
        ++cnt;
        cin>>val[i];
    }
    prepare();
    double ans=INF;
    for(int i=4*a-3;i<=4*a;i++){
        dijkstra(i);
        for(int j=4*b-3;j<=4*b;j++){
            ans=min(ans,dis[j]);
        }
    }
    cout<<fixed<<setprecision(1)<<ans<<endl;
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}