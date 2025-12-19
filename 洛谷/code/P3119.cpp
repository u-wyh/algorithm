//https://www.cnblogs.com/jiangtaizhe001/p/14872758.html
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

vector<int>vec[MAXN];
int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,Time;
int col[MAXN];
bool instack[MAXN];
int n,m;
int sz[MAXN];

int head[MAXN];
int Next[MAXN];
int to[MAXN];
int cnt=1;
int f[MAXN];

int head1[MAXN];
int Next1[MAXN];
int to1[MAXN];
int cnt1=1;
int f1[MAXN];

bool vis[MAXN];

void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void addedge1(int u,int v){
    Next1[cnt1]=head1[u];
    to1[cnt1]=v;
    head1[u]=cnt1++;
}

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

void tarjan(int x){
    dfn[x]=++Time;
    low[x]=Time;
    st[++top]=x;
    instack[x]=true;
    for(int i=0;i<vec[x].size();i++){
        int v=vec[x][i];
        if(!dfn[v]){
            //表示这个节点没有被访问过
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
        else if(instack[v]){
            //表示这个属于是回溯了 一定是同一个环上的
            low[x]=min(low[x],dfn[v]);
        }
    }
    if(dfn[x]==low[x]){
        col[x]=++color;
        //将所有节点按照颜色分类  完成缩点
        while(st[top]!=x){
            //属于同一个强联通分量
            col[st[top]]=color;
            instack[st[top]]=false;
            top--;
        }
        instack[x]=false;
        top--;
    }
}

queue<int>q;

void spfa1(){
    f[col[1]]=sz[col[1]];
    q.push(col[1]);
    vis[col[1]]=true;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=false;
        for(int i=head[u];i;i=Next[i]){
            int v=to[i];
            if(f[u]+sz[v]>f[v]){
                f[v]=sz[v]+f[u];
                if(!vis[v]){
                    q.push(v);
                    vis[v]=true;
                }
            }
        }
    }
}

void spfa2(){
    f1[col[1]]=sz[col[1]];
    q.push(col[1]);
    vis[col[1]]=true;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=false;
        for(int i=head1[u];i;i=Next1[i]){
            int v=to1[i];
            if(f1[u]+sz[v]>f1[v]){
                f1[v]=sz[v]+f1[u];
                if(!vis[v]){
                    q.push(v);
                    vis[v]=true;
                }
            }
        }
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        vec[u].push_back(v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=n;i++){
        sz[col[i]]++;
    }
//    for(int i=1;i<=color;i++){
//        cout<<i<<' '<<sz[i]<<endl;
//    }
//    cout<<endl;
    if(sz[col[1]]==n){
        cout<<n<<endl;
        return 0;
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<vec[i].size();j++){
            int v=vec[i][j];
            if(col[v]==col[i]){
                continue;
            }
            addedge(col[i],col[v]);
            addedge1(col[v],col[i]);
        }
    }
    spfa1();
    spfa2();
//    for(int i=1;i<=color;i++){
//        cout<<i<<' '<<f[i]<<' '<<f1[i]<<endl;
//	}
//	cout<<endl;
    int ans=sz[col[1]];
    for(int i=1;i<=color;i++){
        if(f[i]){
            for(int j=head1[i];j;j=Next1[j]){
                if(f1[to1[j]]){
                    ans=max(ans,f1[to1[j]]+f[i]-sz[col[1]]);
                }
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
/*
7 10
1 2
3 1
2 5
2 4
3 7
3 5
3 6
6 5
7 2
4 7
*/
