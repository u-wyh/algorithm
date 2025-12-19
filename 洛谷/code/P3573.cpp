#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXM = 1e6+5;

int n,m;

int x[MAXM],y[MAXM];

int in[MAXN];

int q[MAXN];
int t[MAXN];

int dis1[MAXN];
int dis2[MAXN];

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cnt=1;

int f[MAXN];
int g[MAXN];

int tree[MAXN<<2];
int tag[MAXN<<2];

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

void topo(){
    for(int i=1;i<=m;i++){
        addedge(x[i],y[i]);
        in[y[i]]++;
    }
    int sz=0;
    queue<int>que;
    for(int i=1;i<=n;i++){
        if(in[i]==0){
            que.push(i);
            q[++sz]=i;
            t[i]=sz;
            dis1[i]=0;
        }
    }
    while(!que.empty()){
        int u=que.front();
        que.pop();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            dis1[v]=max(dis1[v],dis1[u]+1);
            if(--in[v]==0){
                que.push(v);
                q[++sz]=v;
                t[v]=sz;
            }
        }
    }

    for(int i=1;i<=n;i++){
        head[i]=0;
    }
    cnt=1;
    for(int i=1;i<=m;i++){
        addedge(y[i],x[i]);
        in[x[i]]++;
    }
    for(int i=1;i<=n;i++){
        if(in[i]==0){
            que.push(i);
            dis2[i]=0;
        }
    }
    while(!que.empty()){
        int u=que.front();
        que.pop();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            dis2[v]=max(dis2[v],dis2[u]+1);
            if(--in[v]==0){
                que.push(v);
            }
        }
    }
}

void lazy(int i,int v){
    tree[i]=max(tree[i],v);
    tag[i]=max(tag[i],v);
}

void down(int i){
    if(tag[i]){
        lazy(i<<1,tag[i]);
        lazy(i<<1|1,tag[i]);
        tag[i]=0;
    }
}

void update(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,jobv);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            update(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            update(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
    }
}

int query(int pos,int l,int r,int i){
    if(l==r){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(pos<=mid){
            return query(pos,l,mid,i<<1);
        }
        else{
            return query(pos,mid+1,r,i<<1|1);
        }
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        x[i]=read(),y[i]=read();
    }
    topo();
    for(int i=1;i<=n;i++){
        f[i]=max(f[i-1],dis1[q[i]]);
    }
    for(int i=n;i>=1;i--){
        g[i]=max(g[i+1],dis2[q[i]]);
    }
    for(int i=1;i<=m;i++){
        int d=dis1[x[i]]+dis2[y[i]]+1;
        int l=t[x[i]]+1;
        int r=t[y[i]]-1;
        if(l<=r){
            update(l,r,d,1,n,1);
        }
    }
    int ans=MAXM,pos=0;
    for(int i=1;i<=n;i++){
        int val=query(t[i],1,n,1);
        int tmp=max(val,max(f[t[i]-1],g[t[i]+1]));
        cout<<i<<":  "<<tmp<<endl;
        if(tmp<ans){
            ans=tmp;
            pos=i;
        }
    }
    cout<<pos<<' '<<ans<<endl;
    return 0;
}
/*
5 4
1 2 1 3
2 4 3 5

6 5
1 2 2 3 3 4 4 5 1 6
*/