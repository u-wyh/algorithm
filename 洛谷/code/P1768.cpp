// https://www.luogu.com.cn/problem/P1768
// 题意：给定 N 个景点和 M 条单向路线，每条有趣味值 V_i 和票价 P_i。
// 找一条不重复使用路线的回路，使总趣味值除以总票价最大。
// 输出比值并保留一位小数，无回路输出 -1。
// 数据范围：1 ≤ N ≤ 7000，1 ≤ M ≤ 20000，1 ≤ V_i,P_i ≤ 1000，答案不超过 200，允许平行边。

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 7005;
const int MAXM = 2e4+5;
const double eps = 1e-2;

int n,m;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int val[MAXM];
int cost[MAXM];
int cnt=1;

double dis[MAXN];
int updatecnt[MAXN];
bool enter[MAXN];
queue<int>q;

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

void addedge(int u,int v,int w,int c){
    nxt[cnt]=head[u];
    to[cnt]=v;
    val[cnt]=w;
    cost[cnt]=c;
    head[u]=cnt++;
}

bool spfa(double k){
    while(!q.empty()){
        q.pop();
    }
    for(int i=1;i<=n+1;i++){
        dis[i]=INT_MAX;
        updatecnt[i]=0;
        enter[i]=false;
    }
    dis[n+1]=0;
    updatecnt[n+1]++;
    enter[n+1]=false;
    q.push(n+1);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        enter[u]=false;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int va=val[i];
            int c=cost[i];
            double w=k*c-1.0*va;
            if(dis[u]+w<dis[v]){
                dis[v]=dis[u]+w;
                if(!enter[v]){
                    if(++updatecnt[v]>n){
                        return true;
                    }
                    enter[v]=true;
                    q.push(v);
                }
            }
        }
    }
    return false;
}   

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u,v,w,c;
        u=read(),v=read(),w=read(),c=read();
        addedge(u,v,w,c);
    }
    for(int i=1;i<=n;i++){
        addedge(n+1,i,0,0);//设置虚拟源点
    }
    double l=0,r=INT_MAX,ans=-1;
    while(r-l>=eps){
        double mid=(l+r)/2;
        if(spfa(mid)){
            ans=mid;
            l=mid;
        }
        else{
            r=mid;
        }
    }
    if(ans<0){
        cout<<-1;
    }
    else{
        printf("%.1lf\n",ans);
    }
    return 0;
}