#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n,q;
int val[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXN];
int to[MAXN];

int dfncnt;
int dfn[MAXN];
int seg[MAXN];
int sz[MAXN];

int maxx[MAXN<<2];//维护区间最大值
// int minn[MAXN<<2];
int all[MAXN<<2];

int tree2[MAXN<<2];//也是维护区间最大值 不过是答案最大值
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

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u){
    dfn[u]=++dfncnt;
    seg[dfncnt]=u;
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v);
        sz[u]+=sz[v];
    }
}

void up1(int i){
    maxx[i]=max(maxx[i<<1],maxx[i<<1|1]);
    // minn[i]=min(minn[i<<1],minn[i<<1|1]);
}

void build1(int l,int r,int i){
    if(l==r){
        maxx[i]=-val[seg[l]];
        // minn[i]=val[seg[l]];
    }
    else{
        int mid=(l+r)>>1;
        build1(l,mid,i<<1);
        build1(mid+1,r,i<<1|1);
        up1(i);
    }
}

void up2(int i){
    tree2[i]=max(tree2[i<<1],tree2[i<<1|1]);
}

void lazy(int i,int v){
    tree2[i]+=v;
    tag[i]+=v;
}

void down(int i){
    if(tag[i]){
        lazy(i<<1,tag[i]);
        lazy(i<<1|1,tag[i]);
        tag[i]=0;
    }
}

void add(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,1);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            add(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,mid+1,r,i<<1|1);
        }
        up2(i);
    }
}

void lazy1(int i,int v){
    all[i]+=v;
    maxx[i]+=v;
}

void down1(int i){
    if(all[i]){
        lazy1(i<<1,all[i]);
        lazy1(i<<1|1,all[i]);
        all[i]=0;
    }
}

void del(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy1(i,jobv);
    }
    else{
        int mid=(l+r)>>1;
        down1(i);
        if(jobl<=mid){
            del(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            del(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up1(i);
    }
}

int t=0;

//这种做法是爆栈了吗
// void find(int l,int r,int i){
//     if(maxx[i]<0){
//         return ;
//     }
//     if(l==r){
//         add(l,l+sz[seg[l]]-1,1,n,1);
//         maxx[i]=INT_MIN;
//     }
//     else{
//         int mid=(l+r)/2;
//         down1(i);
//         find(l,mid,i<<1);
//         find(mid+1,r,i<<1|1);
//         up1(i);
//     }
// }

void find(int l, int r, int i) {
    t++;
    if (maxx[i] < 0) return;
    
    if (l == r) {
        add(l, l+sz[seg[l]]-1, 1, n, 1);
        maxx[i] = INT_MIN;
        return;
    }
    
    down1(i);
    int mid = (l + r) >> 1;
    if (maxx[i<<1] >= 0) find(l, mid, i<<1);
    if (maxx[i<<1|1] >= 0) find(mid+1, r, i<<1|1);
    up1(i);
}

int main()
{
    // freopen("C:\\Users\\wyh15\\Downloads\\P12361_14.in", "r", stdin);
    // std::clock_t start = std::clock();
    n=read(),q=read();
    for(int i=2;i<=n;i++){
        int u=read();
        addedge(u,i);
    }
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    dfs(1);
    build1(1,n,1);
    for(int i=1;i<=q;i++){
        int u,v;
        u=read(),v=read();
        del(dfn[u],dfn[u]+sz[u]-1,v,1,n,1);
        find(1,n,1);
        printf("%d\n",tree2[1]);
    }
    // std::clock_t end = std::clock();

    // double duration = (double)(end - start) / CLOCKS_PER_SEC;

    // std::cout << "CPU时间: " << duration << " 秒" << std::endl;

    cout<<t<<endl;
    return 0;
}