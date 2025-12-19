#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5005;
const int MAXK = 1e6+5;
const int INF = 1e9;

int n,m,k;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

struct node{
    int v,w,id;
};
vector<node>vec[MAXN];

bool ans[MAXK];

int dis[MAXN][2];
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

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void spfa(int s){
    for(int i=1;i<=n;i++){
        dis[i][0]=dis[i][1]=INF;
        in[i]=false;
    }
    queue<int>q;
    dis[s][0]=0;
    in[s]=true;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        in[u]=false;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(dis[u][0]+1<dis[v][1]){
                dis[v][1]=1+dis[u][0];
                if(!in[v]){
                    in[v]=true;
                    q.push(v);
                }
            }
            if(dis[u][1]+1<dis[v][0]){
                dis[v][0]=1+dis[u][1];
                if(!in[v]){
                    in[v]=true;
                    q.push(v);
                }
            }
        }
    }
}

int main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();

        addedge(u,v);
        addedge(v,u);
    }
    for(int i=1;i<=k;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        // if(u>v){
        //     swap(u,v);
        // }
        vec[u].push_back({v,w,i});
    }
    for(int u=1;u<=n;u++){
        if(vec[u].size()&&head[u]){
            spfa(u);
            for(int i=0;i<(int)vec[u].size();i++){
                int v=vec[u][i].v;
                int w=vec[u][i].w;
                int id=vec[u][i].id;
                ans[id]=(w>=dis[v][w&1]);
            }   
        }
    }
    for(int i=1;i<=k;i++){
        if(ans[i]){
            printf("TAK\n");
        }
        else{
            printf("NIE\n");
        }
    }
    return 0;
}