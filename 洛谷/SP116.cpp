#include<bits/stdc++.h>
using namespace std;
const int MAXN = 500005;

int n,m;
int a[MAXN],b[MAXN],c[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXN*3];
int to[MAXN*3];
int weight[MAXN*3];

int dis[MAXN];
bool in[MAXN];
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

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void spfa(){
    dis[0]=0;
    q.push(0);
    in[0]=true;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        in[u]=false;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if(dis[u]+w>dis[v]){
                dis[v]=dis[u]+w;
                if(!in[v]){
                    q.push(v);
                    in[v]=true;
                }
            }
        }
    }
}

int main()
{
    int T;
    T=read();
    while(T--){
        n=read();
        m=0;
        for(int i=1;i<=n;i++){
            a[i]=read(),b[i]=read(),c[i]=read();
            m=max(m,b[i]);
        }
        for(int i=0;i<=m+1;i++){
            head[i]=0;
            dis[i]=INT_MIN;
            in[i]=false;
        }
        for(int i=1;i<=n;i++){
            addedge(a[i],b[i]+1,c[i]);
        }
        for(int i=1;i<=m+1;i++){
            addedge(i,i-1,-1);
            addedge(i-1,i,0);
        }
        spfa();
        if(T){
            printf("%d\n",dis[m+1]);
        }
        else{
            printf("%d",dis[m+1]);
        }
    }
    return 0;
}