#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXT = MAXN*50;

int n,m;
int val[MAXN];
int arr[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int rt[MAXN];
int ls[MAXT];
int rs[MAXT];
int f[MAXT];//越往上越大
int g[MAXT];
int cntv;

int ans;

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

int find(int val){
    int l=1,r=m,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(arr[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

void up(int i){
    f[i]=max(f[ls[i]],f[rs[i]]);
    g[i]=max(g[ls[i]],g[rs[i]]);
}

int query1(int jobl,int jobr,int l,int r,int i){
    if(jobl>jobr||i==0){
        return 0;
    }
    if(jobl<=l&&r<=jobr){
        return f[i];
    }
    else{
        int mid=(l+r)>>1;
        int ans=0;
        if(jobl<=mid){
            ans=max(ans,query1(jobl,jobr,l,mid,ls[i]));
        }
        if(jobr>mid){
            ans=max(ans,query1(jobl,jobr,mid+1,r,rs[i]));
        }
        return ans;
    }
}

int query2(int jobl,int jobr,int l,int r,int i){
    if(jobl>jobr||i==0){
        return 0;
    }
    if(jobl<=l&&r<=jobr){
        return g[i];
    }
    else{
        int mid=(l+r)>>1;
        int ans=0;
        if(jobl<=mid){
            ans=max(ans,query2(jobl,jobr,l,mid,ls[i]));
        }
        if(jobr>mid){
            ans=max(ans,query2(jobl,jobr,mid+1,r,rs[i]));
        }
        return ans;
    }
}

int update(int pos,int valf,int valg,int l,int r,int i){
    int rt=i;
    if(rt==0){
        rt=++cntv;
    }
    if(l==r){
        f[rt]=max(f[rt],valf);
        g[rt]=max(g[rt],valg);
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            ls[rt]=update(pos,valf,valg,l,mid,ls[rt]);
        }
        else{
            rs[rt]=update(pos,valf,valg,mid+1,r,rs[rt]);
        }
        up(rt);
    }
    return rt;
}

int merge(int l,int r,int t1,int t2){
    if(t1==0||t2==0){
        return t1+t2;
    }
    if(l==r){
        f[t1]=max(f[t1],f[t2]);
        g[t1]=max(g[t1],g[t2]);
        ans=max(ans,max(f[t1],g[t1]));
    }
    else{
        ans=max(ans,max(f[ls[t1]]+g[rs[t2]],f[ls[t2]]+g[rs[t1]]));
        f[t1]=max(f[t1],f[t2]);
        g[t1]=max(g[t1],g[t2]);
        int mid=(l+r)>>1;
        ls[t1]=merge(l,mid,ls[t1],ls[t2]);
        rs[t1]=merge(mid+1,r,rs[t1],rs[t2]);
    }
    return t1;
}

void dfs(int u,int fa){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs(v,u);

            int len1=query1(1,val[u]-1,1,m,rt[u]);
            int len2=query2(val[u]+1,m,1,m,rt[u]);
            int len3=query1(1,val[u]-1,1,m,rt[v]);
            int len4=query2(val[u]+1,m,1,m,rt[v]);

            rt[u]=merge(1,m,rt[u],rt[v]);

            ans=max(ans,max(len1+len4,len2+len3)+1);
        }
    }
    int len1=query1(1,val[u]-1,1,m,rt[u]);
    int len2=query2(val[u]+1,m,1,m,rt[u]);
    rt[u]=update(val[u],len1+1,len2+1,1,m,rt[u]);
}

void compute(){
    for(int i=1;i<=n;i++){
        arr[i]=val[i];
    }
    sort(arr+1,arr+n+1);
    m=1;
    for(int i=2;i<=n;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    for(int i=1;i<=n;i++){
        val[i]=find(val[i]);
    }

    dfs(1,0);
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    compute();
    cout<<ans<<endl;
    return 0;
}