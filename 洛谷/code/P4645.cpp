#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const int MAXM = 1e5+5;
const int MOD = 1e9;

int n,m;
//这道题准备用  拓扑排序入度删除法  并查集(不是严格意义上的）  建立正反图
//在2返回1的路上（反图）  所有经过的点再正图上一定是可以到达2
//将这些点的父亲设置为1
//对于所有的点而言  如果val不为0  那么一定是1可以到达的
//如果最终经过入度删除后的不为0的节点  父亲是1  那么就是inf
int in[MAXN];
int val[MAXN];//只有节点1要初始化为1
int fa[MAXN];//也不用初始化 反正我们只需要将需要的点设置为1  剩余的就不用管了
bool vis[MAXN];//防止dfs遇到环时死循环

int head[MAXN];
int Next[MAXM<<1];
int to[MAXM<<1];
int cnt=1;

int headr[MAXN];
int Nextr[MAXM<<1];
int tor[MAXM<<1];
int cntr=1;

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


void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void addedger(int u,int v){
    Nextr[cntr]=headr[u];
    tor[cntr]=v;
    headr[u]=cntr++;
}

void dfs(int u){
    vis[u]=true;//防止环上死循环
    for(int i=headr[u];i;i=Nextr[i]){
        int v=tor[i];
        if(!vis[v]){
            fa[v]=1;
            dfs(v);
        }
    }
}

bool ok[MAXN];//所有1可以到达的点
bool visit[MAXN];

void dfs1(int u){
    visit[u]=true;
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(!visit[v]){
            ok[v]=true;
            dfs1(v);
        }
    }
}

int main()
{
    cin>>n>>m;
    val[1]=1;
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedger(v,u);
        in[v]++;
    }
    ok[1]=1;
    dfs1(1);
    for(int i=1;i<=n;i++){
        if(!ok[i]){
            for(int j=head[i];j;j=Next[j]){
                int v=to[j];
                in[v]--;
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(in[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        if(!ok[u]){
            continue;
        }
        for(int i=head[u];i;i=Next[i]){
            int v=to[i];
            val[v]+=val[u];
            val[v]%=MOD;
            in[v]--;
            if(in[v]==0){
                q.push(v);
            }
        }
    }
    fa[2]=1;
    dfs(2);
    for(int i=1;i<=n;i++){
        if(in[i]&&val[i]&&fa[i]){
            //表示在环上的点  1可以到达的点  可以到达2的点
            //这不就是inf的条件吗  为什么有问题
            cout<<"inf"<<endl;
            return 0;
        }
    }
    cout<<val[2]<<endl;
    return 0;
}
/*
5 5
1 4
4 2
3 5
5 3
3 4
*/
