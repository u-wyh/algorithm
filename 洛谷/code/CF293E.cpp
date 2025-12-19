#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int n,limitl,limitw;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;

bool vis[MAXN];
int sz[MAXN];

struct node{
    int dis,edge;
};
node nums[MAXN];
int cnta;

int tree[MAXN];

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

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int v){
    x++;
    while(x<=limitl+1){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

int sum(int x){
    x++;
    int ans=0;
    while(x>0){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

bool cmp(node a,node b){
    return a.dis<b.dis;
}

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void getsize(int u,int fa){
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa&&!vis[v]){
            getsize(v,u);
            sz[u]+=sz[v];
        }
    }
}

int getcentroid(int u,int fa){
    getsize(u,fa);
    int half=sz[u]>>1;
    bool find=false;
    while(!find){
        find=true;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v!=fa&&!vis[v]&&sz[v]>half){
                fa=u;
                u=v;
                find=false;
                break;
            }
        }
    }
    return u;
}

void dfs(int u,int fa,int dis,int edge){
    if(dis>limitw||edge>limitl){
        return ;
    }
    nums[++cnta]={dis,edge};
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=fa&&!vis[v]){
            dfs(v,u,dis+w,edge+1);
        }
    }
}

int calc(int u,int dis,int edge){
    cnta=0;
    dfs(u,0,dis,edge);
    sort(nums+1,nums+cnta+1,cmp);
    for(int i=1;i<=cnta;i++){
        add(nums[i].edge,1);
    }
    int ans=0;
    for(int l=1,r=cnta;l<=r;){
        if(nums[l].dis+nums[r].dis<=limitw){
            add(nums[l].edge,-1);
            ans+=sum(limitl-nums[l].edge);
            l++;
        }
        else{
            add(nums[r].edge,-1);
            r--;
        }
    }
    return ans;
}

int compute(int u){
    vis[u]=true;
    int ans=calc(u,0,0);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(!vis[v]){
            ans-=calc(v,w,1);
            ans+=compute(getcentroid(v,u));
        }
    }
    return ans;
}

signed main()
{
    n=read(),limitl=read(),limitw=read();
    for(int i=2;i<=n;i++){
        int u,w;
        u=read(),w=read();
        addedge(i,u,w);
        addedge(u,i,w);
    }
    cout<<compute(getcentroid(1,0))<<endl;
    return 0;
}