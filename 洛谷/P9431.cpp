#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3005;
const int MAXM = 5e6+5;

vector<int>vec[MAXN];
int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,Time;
int col[MAXN];
bool instack[MAXN];
int n,d,c;

struct node{
    int x,y,sub;
}nums[MAXN];

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt=1;

int sz[MAXN];
int sum[MAXN];
bool vis[MAXN];

void build(){
    top=0,color=0,Time=0,cnt=1;
    for(int i=1;i<=n;i++){
        vec[i].clear();
        head[i]=0;
        sz[i]=0;
        sum[i]=0;
        vis[i]=0;
        dfn[i]=0;
        low[i]=0;
    }
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

void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
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

void dfs(int u){
    int most=0;
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(vis[v]){
            most=max(most,sum[v]);
            continue;
        }
        else{
            dfs(v);
            most=max(most,sum[v]);
        }
    }
    vis[u]=true;
    sum[u]=most+sz[u];
}

int main()
{
    int T,id;
    T=read(),id=read();
    while(T--){
        n=read(),d=read(),c=read();
        build();
        for(int i=1;i<=n;i++){
            nums[i].sub=i;
            nums[i].x=read(),nums[i].y=read();
        }
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                if(nums[i].y+d-abs(nums[j].x-nums[i].x)>=nums[j].y){
                    vec[i].push_back(j);
                }
                if(nums[j].y+d-abs(nums[j].x-nums[i].x)>=nums[i].y){
                    vec[j].push_back(i);
                }
            }
        }
        for(int i=1;i<=n;i++){
            if(!dfn[i]){
                tarjan(i);
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=0;j<vec[i].size();j++){
                int v=vec[i][j];
                if(col[i]!=col[v]){
                    addedge(col[i],col[v]);
                }
            }
        }
        for(int i=1;i<=n;i++){
            sz[col[i]]++;
        }
        dfs(col[c]);
        int ans=0;
        for(int i=1;i<=color;i++){
            ans=max(ans,sum[i]);
        }
        cout<<ans<<endl;
    }
    return 0;
}

