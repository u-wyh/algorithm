#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;

int n,q;
int fa[MAXN];
int sz[MAXN];
bool vis[MAXN];

long long sum;
int cnt;

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;

struct node{
    long long all;
    int val; 
    bool operator<(const node& a) const {
        if(all*a.val!=a.all*val){
            return all*a.val<a.all*val;
        }
        return val<a.val;
    }
};
node val[MAXN];

node tree[MAXN<<2];

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
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        sum=sum-1ll*sz[fx]*sz[fx]-1ll*sz[fy]*sz[fy]+1ll*(sz[fx]+sz[fy])*(sz[fx]+sz[fy]);
        fa[fx]=fy;
        sz[fy]+=sz[fx];
        cnt--;
    }
}

void up(int i){
    tree[i]=max(tree[i<<1],tree[i<<1|1]);
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]=val[l];
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

node query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;
        node ans={0,0};
        if(jobl<=mid){
            ans=max(ans,query(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=max(ans,query(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

signed main()
{
    n=read(),q=read();
    for(int i=1;i<=n;i++){
        int val=read();
        addedge(val,i);
    }
    for(int i=1;i<=n;i++){
        fa[i]=i;
        sz[i]=1;
    }
    for(int u=1;u<=1e6;u++){
        if(head[u]){
            for(int i=head[u];i;i=nxt[i]){
                int v=to[i];
                vis[v]=true;
                sum++;
                cnt++;
                if(vis[v-1]){
                    un(v-1,v);
                }
                if(vis[v+1]){
                    un(v+1,v);
                }
            }
            val[cnt]=max(val[cnt],node{sum,u});
        }
    }
    build(1,n,1);
    long long lastans=0;
    for(int i=1;i<=q;i++){
        long long a,b,x,y,l,r;
        a=read(),b=read(),x=read(),y=read();
        l=(a*lastans+x-1)%n+1;
        r=(b*lastans+y-1)%n+1;
        if(l>r){
            swap(l,r);
        }
        int pre=lastans;
        node ans=query(l,r,1,n,1);
        if(ans.val){
            cout<<ans.all<<' '<<ans.val<<endl;
            lastans=ans.all*ans.val%n;
        }
        else{
            cout<<"-1 -1\n";
            lastans=1;
        }
        cout<<l<<' '<<r<<' '<<pre<<endl;
    }
    return 0;
}