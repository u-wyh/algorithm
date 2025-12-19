#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 8e5+5;

struct node{
    int r,c,sub,op;
}nums[MAXN];
vector<int>vec[MAXN];
int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,Time;
int col[MAXN];
bool instack[MAXN];
int n,r,c;
map<pair<int,int>,int>graph;

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt=1;

int walk[8][2]={{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};

int sz[MAXN];
int sum[MAXN];
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

bool cmp1(node a,node b){
    return a.r==b.r?a.op<b.op:a.r<b.r;
}

bool cmp2(node a,node b){
    return a.c==b.c?(a.op%2)<(b.op%2):a.c<b.c;
}

bool cmp3(node a,node b){
    return a.op>b.op;
}

void dfs(int u){
    int most=0;
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(vis[v]){
            most=max(most,sum[v]);
        }
        else{
            dfs(v);
            most=max(most,sum[v]);
        }
    }
    //cout<<u<<' '<<sz[u]<<' '<<most<<endl;
    sum[u]=sz[u]+most;
    vis[u]=true;
}

vector<int>ans;

int main()
{
    n=read(),r=read(),c=read();
    for(int i=1;i<=n;i++){
        nums[i].sub=i;
        nums[i].r=read(),nums[i].c=read(),nums[i].op=read();
        graph[make_pair(nums[i].r,nums[i].c)]=nums[i].sub;
    }
    sort(nums+1,nums+n+1,cmp1);
    int i=1;
    while(i<=n){
        int row;
        if(nums[i].op==1){
            row=nums[i].r;
            ans.push_back(nums[i].sub);
        }
        else{
            i++;
            continue;
        }
        i++;
        while(nums[i].op==1&&nums[i].r==row){
            ans.push_back(nums[i++].sub);
        }
        while(nums[i].r==row){
            int v=nums[i++].sub;
            for(int j=0;j<ans.size();j++){
                int u=ans[j];
                vec[u].push_back(v);
                //cout<<u<<' '<<v<<endl;
            }
        }
        for(int k=0;k<ans.size();k++){
            int u=ans[k];
            for(int j=0;j<ans.size();j++){
                int v=ans[j];
                if(v!=u){
                    vec[u].push_back(v);
                    //cout<<u<<' '<<v<<endl;
                }
            }
        }
        ans.clear();
    }
    sort(nums+1,nums+n+1,cmp2);
    i=1;
    //cout<<endl;
    while(i<=n){
        int col;
        if(nums[i].op==2){
            col=nums[i].c;
            ans.push_back(nums[i].sub);
        }
        else{
            i++;
            continue;
        }
        i++;
        while(nums[i].op==2&&nums[i].c==col){
            ans.push_back(nums[i++].sub);
        }
        while(nums[i].c==col){
            int v=nums[i++].sub;
            for(int j=0;j<ans.size();j++){
                int u=ans[j];
                vec[u].push_back(v);
                //cout<<u<<' '<<v<<endl;
            }
        }
        for(int k=0;k<ans.size();k++){
            int u=ans[k];
            for(int j=0;j<ans.size();j++){
                int v=ans[j];
                if(v!=u){
                    vec[u].push_back(v);
                    //cout<<u<<' '<<v<<endl;
                }
            }
        }
        ans.clear();
    }
    //cout<<endl;
    i=1;
    sort(nums+1,nums+n+1,cmp3);
    while(nums[i].op==3){
        int x=nums[i].r,y=nums[i].c,u=nums[i].sub;
        for(int j=0;j<8;j++){
            int nx=x+walk[j][0];
            int ny=y+walk[j][1];
            int v=graph[make_pair(nx,ny)];
            if(v!=0){
                vec[u].push_back(v);
                //cout<<u<<' '<<v<<endl;
            }
        }
        i++;
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
    for(int i=1;i<=color;i++){
        if(!vis[i]){
            dfs(i);
        }
    }
    int ans=0;
    for(int i=1;i<=color;i++){
        ans=max(ans,sum[i]);
    }
    cout<<ans<<endl;
    return 0;
}
