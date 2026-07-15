#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXT = MAXN*40;

int n,m,rt;
int limit;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

long long ans[MAXN];

int dfncnt;
int dfn[MAXN];
int seg[MAXN];
int sz[MAXN];

int soncnt;
int son[MAXN];
int sonlt[MAXN];
int sonrt[MAXN];

int root[MAXN];
int ls[MAXT];
int rs[MAXT];
int sum[MAXT];
int cntt;

char *p1,*p2,buf[100000];
#define nc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
int read()
{
    int x=0,f=1;
    char ch=nc();
    while(ch<48||ch>57)
    {
        if(ch=='-')
            f=-1;
        ch=nc();
    }
    while(ch>=48&&ch<=57)
        x=x*10+ch-48,ch=nc();
   	return x*f;
}

void write(long long x)
{
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs(int u,int fa){
    dfn[u]=++dfncnt;
    seg[dfncnt]=u;
    sz[u]=1;

    sonlt[u]=soncnt+1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            son[++soncnt]=v;
        }
    }
    sonrt[u]=soncnt;

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs(v,u);
            sz[u]+=sz[v];
        }
    }
}

bool cmp(int a,int b){
    return sz[a]>sz[b];
}

int build(int l,int r){
    int i=++cntt;
    if(l<r){
        int mid=(l+r)>>1;
        ls[i]=build(l,mid);
        rs[i]=build(mid+1,r);
    }
    return i;
}

int insert(int pos,int l,int r,int i){
    int cur=++cntt;
    sum[cur]=sum[i]+1;
    ls[cur]=ls[i];
    rs[cur]=rs[i];
    if(l<r){
        int mid=(l+r)>>1;
        if(pos<=mid){
            ls[cur]=insert(pos,l,mid,ls[i]);
        }
        else{
            rs[cur]=insert(pos,mid+1,r,rs[i]);
        }
    }
    return cur;
}

int query(int jobl,int jobr,int l,int r,int i){
    if(i==0){
        return 0;
    }
    if(jobl<=l&&r<=jobr){
        return sum[i];
    }
    else{
        int ans=0;
        int mid=(l+r)>>1;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,ls[i]);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,rs[i]);
        }
        return ans;
    }
}

void prepare(){
    dfs(rt,0);

    for(int i=1;i<=n;i++){
        if(sonlt[i]<=sonrt[i]){
            sort(son+sonlt[i],son+sonrt[i]+1,cmp);
        }
    }

    root[0]=build(1,n);
    for(int i=1;i<=n;i++){
        root[i]=insert(seg[i],1,n,root[i-1]);
    }

    limit=3;
}

struct node{
    int l,r,id,x;
};
int nodecnt;
node nums[MAXN];

int blen;

bool cmpnode2(node &a,node &b){
    int ba=(a.l-1)/blen;
    int bb=(b.l-1)/blen;
    
    if(ba!=bb){
        return ba<bb;
    }
    if(ba&1){
        return a.r>b.r;
    }
    else{
        return a.r<b.r;
    }
}

long long comb(int x){
    return ((long long)x*(x-1))>>1;
}

void calc(int l,int r,int x,int id){
    int sonsize=sonrt[x]-sonlt[x]+1;
    int siz=-query(l,r,1,n,root[dfn[x]-1])+query(l,r,1,n,root[dfn[x]+sz[x]-1]);
    ans[id]=comb(siz);

    if(sonsize<=limit){
        for(int i=sonlt[x];i<=sonrt[x];i++){
            int u=son[i];
            int siz=-query(l,r,1,n,root[dfn[u]-1])+query(l,r,1,n,root[dfn[u]+sz[u]-1]);
            ans[id]-=comb(siz);
        }
    }
    else{
        for(int i=sonlt[x];i<=sonlt[x]+limit-1;i++){
            int u=son[i];
            int siz=-query(l,r,1,n,root[dfn[u]-1])+query(l,r,1,n,root[dfn[u]+sz[u]-1]);
            ans[id]-=comb(siz);
        }
        nums[++nodecnt]={l,r,id,x};
    }
}

bool cmpnode1(node &a,node &b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    return a.l<b.l;
}

struct Point{
    int x,col;
};
Point point[MAXN];
int pointcnt;
int colorcnt;

int cnt[MAXN];

bool pointcmp(Point &a,Point &b){
    return a.x<b.x;
}

void dfs1(int u,int fa,int col){
    point[++pointcnt]={u,col};
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs1(v,u,col);
        }
    }
}

int find2(int val){
    int l=1,r=pointcnt,ans=1+pointcnt;
    while(l<=r){
        int mid=(l+r)>>1;
        if(point[mid].x>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int find1(int val){
    int l=1,r=pointcnt,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(point[mid].x<=val){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    return ans;
}

long long same;

void add(int x){
    int c=point[x].col;
    same+=cnt[c];
    cnt[c]++;
}

void del(int x){
    int c=point[x].col;
    cnt[c]--;
    same-=cnt[c];
}

void compute(){
    sort(nums+1,nums+nodecnt+1,cmpnode1);
    int lt=1,rt;
    while(lt<=nodecnt){
        rt=lt;
        while((rt+1)<=nodecnt&&nums[rt+1].x==nums[lt].x){
            rt++;
        }
        int u=nums[lt].x;
        pointcnt=0;
        colorcnt=0;
        for(int i=sonlt[u]+limit;i<=sonrt[u];i++){
            int v=son[i];
            dfs1(v,u,++colorcnt);
        }
        sort(point+1,point+pointcnt+1,pointcmp);

        for(int i=1;i<=colorcnt;i++){
            cnt[i]=0;
        }

        for(int i=lt;i<=rt;i++){
            nums[i].l=find2(nums[i].l);
            nums[i].r=find1(nums[i].r);
        }

        blen=max(1,(int)(pointcnt/sqrt(rt-lt+1)+1));
        sort(nums+lt,nums+rt+1,cmpnode2);

        same=0;
        int curl=1,curr=0;

        for(int i=lt;i<=rt;i++){
            int jobl=nums[i].l;
            int jobr=nums[i].r;
            if(jobl>jobr){
                continue;
            }

            while(curl>jobl){
                add(--curl);
            }
            while(curl<jobl){
                del(curl++);
            }
            while(curr<jobr){
                add(++curr);
            }
            while(curr>jobr){
                del(curr--);
            }
            ans[nums[i].id]-=same;
        }
        lt=rt+1;
    }
}

int main()
{
    n=read(),m=read(),rt=read();
    
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }

    prepare();

    for(int i=1;i<=m;i++){
        int l,r,x;
        l=read(),r=read(),x=read();
        calc(l,r,x,i);
    }

    compute();

    for(int i=1;i<=m;i++){
        write(ans[i]);
        putchar('\n');
    }
    return 0;
}