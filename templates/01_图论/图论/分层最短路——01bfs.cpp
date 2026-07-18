//P7297
//非常巧妙的一道分层最短路
//这道题可以用01bfs完成
#include<bits/stdc++.h>
using namespace std;
const int MAXK = 55;
const int MAXN = 2550000;
const int MAXM = 4*MAXN;

int n,k;
int val[MAXN];
int edge[MAXK][MAXK];

int dis[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];

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

int main()
{
    n=read(),k=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=k;i++){
        for(int j=1;j<=k;j++){
            char c;
            cin>>c;
            edge[i][j]=c-'0';
        }
    }
    for(int p=1;p<=k;p++){
        //这里我不知道为什么第0层不用建边  第0层是中转层
        //后来我知道了 0层就是一个中转层  他的所有信息都在和其它层的连线上了
        //每一层各个节点之间连边
        for(int i=1;i<n;i++){
            addedge(i+p*n,i+1+p*n,1);
            addedge(i+1+p*n,i+p*n,1);
        }
    }
    //层际之间连边
    for(int i=1;i<=n;i++){
        addedge(i,val[i]*n+i,0);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=k;j++){
            if(edge[j][val[i]]){
                addedge(j*n+i,i,0);
            }
        }
    }

    for(int i=1;i<=n*k+n;i++){
        dis[i]=INT_MAX;
    }
    dis[1]=0;
    deque<int>dq;
    dq.push_back(1);
    while(!dq.empty()){
        int u=dq.front();
        dq.pop_front();
        if(u==n){
            break;
        }
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if(w+dis[u]<dis[v]){
                dis[v]=w+dis[u];
                if(w==0){
                    dq.push_front(v);
                }
                else{
                    dq.push_back(v);
                }
            }
        }
    }
    if(dis[n]==INT_MAX){
        dis[n]=-1;
    }
    cout<<dis[n]<<endl;
    return 0;
}