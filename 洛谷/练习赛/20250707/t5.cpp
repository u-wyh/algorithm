#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
#define int long long

int n,m;

double t[MAXN];
int in[MAXN];
int out[MAXN];
queue<int>q;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
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

void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        out[u]++;
        in[v]++;
    }
    q.push(1);
    t[1]=10000.0;
    double ans=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        if(u==n){
            continue;
        }
        double choice=t[u]/out[u];
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            t[v]+=choice;
            ans+=choice*w;
            in[v]--;
            if(in[v]==0){
                q.push(v);
            }
        }
    }
    printf("%.2lf\n",ans/10000);
    return 0;
}