#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int MAXH = 22;
const long long INF = 1ll<<60;

int n,q,k,p;

int headg[MAXN];
int nxtg[MAXN<<1];
int tog[MAXN<<1];
int cntg=1;

int headv[MAXN];
int nxtv[MAXN];
int tov[MAXN];
int cntv=1;

int dep[MAXN];
int dfn[MAXN];
int st[MAXN][MAXH];
int dfncnt;

int arr[MAXN];
bool iskey[MAXN];

int tmp[MAXN<<1];
int sta[MAXN];

int sz[MAXN];
long long sum[MAXN];
long long near[MAXN];
long long far[MAXN];
long long costsum, costmin, costmax;

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

inline void addedgeg(int u,int v){
    nxtg[cntg]=headg[u];
    tog[cntg]=v;
    headg[u]=cntg++;
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    dfn[u]=++dfncnt;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        if(v!=fa){
            dfs(v,u);
        }
    }
}

bool cmp(int a,int b){
    return dfn[a]<dfn[b];
}

int lca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int i=p;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b){
        return a;
    }
    for(int i=p;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

inline void addedgev(int u,int v){
    nxtv[cntv]=headv[u];
    tov[cntv]=v;
    headv[u]=cntv++;
}

int buildvirtualtree1(){
    sort(arr+1,arr+k+1,cmp);
    int len=0;
    for(int i=1;i<k;i++){
        tmp[++len]=arr[i];
        tmp[++len]=lca(arr[i],arr[i+1]);
    }
    tmp[++len]=arr[k];
    sort(tmp+1,tmp+len+1,cmp);

    int m=1;
    for(int i=2;i<=len;i++){
        if(tmp[i]!=tmp[i-1]){
            tmp[++m]=tmp[i];
        }
    }

    cntv=1;
    for(int i=1;i<=m;i++){
        headv[tmp[i]]=0;
    }
    for(int i=1;i<m;i++){
        addedgev(lca(tmp[i],tmp[i+1]),tmp[i+1]);
    }
    return tmp[1];
}

int buildvirtualtree2(){
    sort(arr+1,arr+k+1,cmp);
    cntv=1;

    int top=0;
    sta[++top]=arr[1];
    headv[arr[1]]=0;
    for(int i=2;i<=k;i++){
        int x=arr[i];
        int y=sta[top];
        int fa=lca(x,y);
        while(top>1&&dfn[sta[top-1]]>=dfn[fa]){
            addedgev(sta[top-1],sta[top]);
            top--;
        }
        if(fa!=sta[top]){
            headv[fa]=0;
            addedgev(fa,sta[top]);
            sta[top]=fa;
        }
        headv[x]=0;
        sta[++top]=x;
    }
    while(top>1){
        addedgev(sta[top-1],sta[top]);
        top--;
    }
    return sta[1];
}

void dp(int u){
    sz[u]=iskey[u]?1:0;
    sum[u]=0;

    if(iskey[u]){
        near[u]=far[u]=0;
    }
    else{
        near[u]=INF;
        far[u]=-INF;
    }

    for(int i=headv[u];i;i=nxtv[i]){
        int v=tov[i];
        dp(v);
    }

    for(int i=headv[u];i;i=nxtv[i]){
        int v=tov[i];
        long long len=(long long)dep[v]-dep[u];

        costsum+=(sum[u]+1ll*sz[u]*len)*sz[v]+sum[v]*sz[u];
        sz[u]+=sz[v];
        sum[u]+=sum[v]+len*sz[v];
        costmin=min(costmin,near[u]+near[v]+len);
        costmax=max(costmax,far[u]+far[v]+len);
        near[u]=min(near[u],near[v]+len);
        far[u]=max(far[u],far[v]+len);
    }
}

void compute(){
    for(int i=1;i<=k;i++){
        iskey[arr[i]]=1;
    }
    // int tree=buildvirtualtree1();
    int tree=buildvirtualtree2();
    costsum=0;
    costmin=INF;
    costmax=-INF;
    dp(tree);
    for(int i=1;i<=k;i++){
        iskey[arr[i]]=0;
    }
}

int main()
{
    n=read();
    p=log2(n)+1;
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedgeg(u,v);
        addedgeg(v,u);
    }
    dfs(1,0);
    q=read();
    for(int t=1;t<=q;t++){
        k=read();
        for(int i=1;i<=k;i++){
            arr[i]=read();
        }
        compute();
        cout<<costsum<<' '<<costmin<<' '<<costmax<<endl;
    }
    return 0;
}