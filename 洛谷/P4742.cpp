#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXM = 5e5+5;

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt=1;

vector<int>vec[MAXN];
int arr[MAXN];
int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,Time;
int col[MAXN];
bool instack[MAXN];
int n,m;
int sum[MAXN],val[MAXN];//这个颜色的总和以及单个最大值

int big[MAXN],fun[MAXN];//分别表示这条链上最大值  以及总和最大值
bool vis[MAXN];

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
    //cout<<' '<<u<<endl;
    int biggest=0,most=0;
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(vis[v]){
            if(fun[v]>most){
                most=fun[v];
                biggest=big[v];
            }
        }
        else{
            dfs(v);
            if(fun[v]>most){
                most=fun[v];
                biggest=big[v];
            }
        }
    }
    fun[u]=sum[u]+most;
    big[u]=max(val[u],biggest);
    vis[u]=1;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
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
        sum[col[i]]+=arr[i];
        val[col[i]]=max(val[col[i]],arr[i]);
    }
//    for(int i=1;i<=color;i++){
//        cout<<i<<": "<<sum[i]<<' '<<val[i]<<endl;
//    }
//    cout<<endl;
    for(int i=1;i<=n;i++){
        for(int j=0;j<vec[i].size();j++){
            int v=vec[i][j];
            //cout<<col[i]<<' '<<col[v]<<endl;
            if(col[v]!=col[i]){
                //cout<<col[i]<<' '<<col[v]<<endl;
                addedge(col[i],col[v]);
            }
        }
    }
    for(int i=1;i<=color;i++){
        if(!vis[i]){
            dfs(i);
        }
    }
//    for(int i=1;i<=color;i++){
//        cout<<i<<' '<<fun[i]<<' '<<big[i]<<endl;
//    }
//    cout<<endl;
    int ans1=0,ans2=0;
    for(int i=1;i<=color;i++){
        if(fun[i]>ans1){
            ans1=fun[i];
            ans2=big[i];
        }
        else if(fun[i]==ans1&&big[i]>ans2){
            ans2=big[i];
        }
    }
    cout<<ans1<<' '<<ans2<<endl;
    return 0;
}
