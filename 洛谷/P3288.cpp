#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e3+5;
const int MAXM = 3e3+5;
const double INF = 1e9;
const double eps = 1e-8;

int n,m;

struct node{
    int u,v,a,b,c,d;
};
node nums[MAXM];

int head[MAXN];
int to[MAXM<<1];
int nxt[MAXM<<1];
double weight[MAXM<<1];
int cnt=1;

double dis[MAXN];
int cntg[MAXN];
bool in[MAXN];

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

inline void addedge(int u,int v,double w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

bool spfa(){
    queue<int>q;
    for(int i=1;i<=n+2;i++){
        dis[i]=0;
        in[i]=true;
        q.push(i);
        cntg[i]=0;
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        in[u]=false;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            double w=weight[i];

            if(dis[u]+w<dis[v]){
                dis[v]=dis[u]+w;
                if(!in[v]){
                    in[v]=true;
                    cntg[v]++;
                    q.push(v);
                    if(cntg[v]>n+2){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool check(double mid){
    cnt=1;
    for(int i=1;i<=n+2;i++){
        head[i]=0;
    }
    for(int i=1;i<=m;i++){
        int u=nums[i].u,v=nums[i].v;
        if(nums[i].c){
            addedge(v,u,nums[i].a-nums[i].d+mid);
        }
        addedge(u,v,nums[i].b+nums[i].d+mid);
    }
    return spfa();
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        nums[i].u=read(),nums[i].v=read();
        nums[i].a=read(),nums[i].b=read();
        nums[i].c=read(),nums[i].d=read();
    }

    double l=0,r=1000,ans=0;
    while(l+eps<=r){
        double mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            l=mid;
        }
        else{
            r=mid;
        }
    }
    cout << fixed << setprecision(2) << ans << endl;
    return 0;
}