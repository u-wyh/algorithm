// https://www.luogu.com.cn/problem/P1354
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 85;
const int MAXM = 85*85;
const double INF = 1e9;

int n;

double arr[MAXN];

struct Point{
    double x,y;
};
Point p[MAXN];
int cnt;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
double weight[MAXM];
int cntg=1;

double x[21];
double a1[21];
double b1[21];
double a2[21];
double b2[21];

void addedge(int u,int v,double w){
    nxt[cntg]=head[u];
    to[cntg]=v;
    weight[cntg]=w;
    head[u]=cntg++;
}

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

double len(Point a){
    return sqrt(a.x*a.x+a.y*a.y);
}

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
                dis[v]=w+dis[u];
                heap.push({v,dis[v]});
            }
        }
    }
}

bool check(int u,int v){
    if(p[u].x==p[v].x){
        return true;
    }
    for(int i=1;i<=n;i++){
        if(x[i]>=p[v].x || x[i]<=p[u].x){
            continue;
        }
        double y=(p[v].y-p[u].y)*(x[i]-p[u].x)/(p[v].x-p[u].x)+p[u].y;
        if((a1[i]<=y&&y<=b1[i]) || (a2[i]<=y&&y<=b2[i])){
            continue;
        }
        else{
            return false;
        }
    }
    return true;
}

int main()
{
    cin>>n;

    p[++cnt]={0,5};
    for(int i=1;i<=n;i++){
        cin>>x[i]>>a1[i]>>b1[i]>>a2[i]>>b2[i];
        p[++cnt]={x[i],a1[i]};
        p[++cnt]={x[i],b1[i]};
        p[++cnt]={x[i],a2[i]};
        p[++cnt]={x[i],b2[i]};
    }
    p[++cnt]={10,5};
    for(int i=1;i<=cnt;i++){
        for(int j=1;j<=cnt;j++){
            if(p[j].x<p[i].x){
                continue;
            }
            if(check(i,j)){
                addedge(i,j,len(p[i]-p[j]));
            }
            else{
                continue;
            }
        }
    }
    dijkstra(1);
    cout<<fixed<<setprecision(2)<<dis[cnt]<<endl;
    return 0;
}