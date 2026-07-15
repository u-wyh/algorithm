#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXT = 4e6+5;

int n,m,A;
int age[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cntg=1;

int fa[MAXN];
int sz[MAXN];
int top[MAXN];
int dep[MAXN];
int son[MAXN];
int dist[MAXN];

bool vis[MAXN];
int centfa[MAXN];

struct node{
    int age;
    long long sum;
};

int curl[MAXN];
int curr[MAXN];
node curarr[MAXT];
int cntc;

int fal[MAXN];
int far[MAXN];
node faarr[MAXT];
int cntf;

bool cmp(node &a,node &b){
    return a.age<b.age;
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

inline void addedge(int u,int v,int w){
    nxt[cntg]=head[u];
    to[cntg]=v;
    weight[cntg]=w;
    head[u]=cntg++;
}

void dfs1(int u,int f,int dis){
    dep[u]=dep[f]+1;
    dist[u]=dis;
    fa[u]=f;
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=f){
            dfs1(v,u,dis+w);
            sz[u]+=sz[v];
            if(sz[son[u]]<sz[v]){
                son[u]=v;
            }
        }
    }
}

void dfs2(int u,int t){
    top[u]=t;
    if(son[u]){
        dfs2(son[u],t);
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa[u]&&v!=son[u]){
            dfs2(v,v);
        }
    }
}

int getlca(int a,int b){
    while(top[a]!=top[b]){
        if(dep[top[a]]<dep[top[b]]){
            b=fa[top[b]];
        }
        else{
            a=fa[top[a]];
        }
    }
    return dep[a]<dep[b]?a:b;
}

int getdist(int a,int b){
    return dist[a]+dist[b]-(dist[getlca(a,b)]<<1);
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
                find=false;
                fa=u;
                u=v;
                break;
            }
        }
    }
    return u;
}

void getlist(int u,int fa,int dis,int rt){
    curarr[++cntc]={age[u],dis};
    if(centfa[rt]){
        faarr[++cntf]={age[u],getdist(u,centfa[rt])};
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=fa&&!vis[v]){
            getlist(v,u,dis+w,rt);
        }
    }
}

void centroidtree(int u,int fa){
    centfa[u]=fa;
    vis[u]=true;
    curl[u]=cntc+1;
    fal[u]=cntf+1;
    getlist(u,0,0,u);
    curr[u]=cntc;
    far[u]=cntf;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]){
            centroidtree(getcentroid(v,u),u);
        }
    }
}

int find(node *arr,int l,int r,int val){
    int ans=r+1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(arr[mid].age>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

long long nodecnt;
long long pathsum;

void query(node *arr,int l,int r,int agel,int ager){
    nodecnt=0,pathsum=0;
    if(l<=r){
        int a=find(arr,l,r,agel);
        int b=find(arr,l,r,ager+1)-1;
        if(a<=b){
            nodecnt=b-a+1;
            pathsum=arr[b].sum-(a==l?0:arr[a-1].sum);
        }
    }
}

long long compute(int u,int agel,int ager){
    query(curarr,curl[u],curr[u],agel,ager);
    long long ans=pathsum;
    long long cnt1,sum1,cnt2,sum2;
    for(int cur=u,fa=centfa[cur];fa;cur=fa,fa=centfa[cur]){
        query(curarr,curl[fa],curr[fa],agel,ager);
        cnt1=nodecnt;
        sum1=pathsum;
        query(faarr,fal[cur],far[cur],agel,ager);
        cnt2=nodecnt;
        sum2=pathsum;
        ans+=sum1;
        ans-=sum2;
        ans+=(cnt1-cnt2)*getdist(u,fa);
    }
    return ans;
}

int main()
{
    n=read(),m=read(),A=read();
    for(int i=1;i<=n;i++){
        age[i]=read();
    }
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dfs1(1,0,0);
    dfs2(1,1);
    centroidtree(getcentroid(1,0),0);
    for(int i=1;i<=n;i++){
        sort(curarr+curl[i],curarr+curr[i]+1,cmp);
        sort(faarr+fal[i],faarr+far[i]+1,cmp);
        for(int j=curl[i]+1;j<=curr[i];j++){
            curarr[j].sum+=curarr[j-1].sum;
        }
        for(int j=fal[i]+1;j<=far[i];j++){
            faarr[j].sum+=faarr[j-1].sum;
        }
    }
    long long ans=0;
    for(int i=1;i<=m;i++){
        int u,l,r;
        u=read(),l=read(),r=read();
        l=(int)((ans+l)%A);
        r=(int)((ans+r)%A);
        if(l>r){
            swap(l,r);
        }
        ans=compute(u,l,r);
        cout<<ans<<endl;
    }
    return 0;
}