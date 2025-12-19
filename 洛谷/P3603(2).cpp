#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 405;
const int MAXV = 3e4+5;
const int MAXP = 20;

int n,m,f,p;
int arr[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int dep[MAXN];
int st[MAXN][MAXP];

int marknum;
bool vis[MAXN];
int marknode[MAXN];
int kthmark[MAXN];
int up[MAXN];
bitset<MAXV>bit[MAXM];

bitset<MAXV>ans;

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

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs(v,u);
    }
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

void prepare(){
    dfs(1,0);
    int len=sqrt(n*10);
    marknum=(n+len-1)/len;
    for(int b=1;b<=marknum;b++){
        int pick=0;
        do{
            pick=rand()%n+1;
        }while(vis[pick]);
        vis[pick]=true;
        marknode[b]=pick;
        kthmark[pick]=b;
    }
    for(int b=1;b<=marknum;b++){
        bit[b][arr[marknode[b]]]=1;
        int cur=st[marknode[b]][0];
        while(cur!=0){
            if(kthmark[cur]>0){
                up[marknode[b]]=cur;
                break;
            }
            else{
                bit[b][arr[cur]]=1;
                cur=st[cur][0];
            }
        }
    }
}

void query(int x,int xylca){
    while(kthmark[x]==0&&x!=xylca){
        ans[arr[x]]=1;
        x=st[x][0];
    }
    while(up[x]&&dep[up[x]]>dep[xylca]){
        ans|=bit[kthmark[x]];
        x=up[x];
    }
    while(x!=xylca){
        ans[arr[x]]=1;
        x=st[x][0];
    }
}

void update(int x,int y){
    int xylca=lca(x,y);
    query(x,xylca);
    query(y,xylca);
    ans[arr[xylca]]=1;
}

int main()
{
    srand(time(0));
    n=read(),m=read(),f=read();
    p=log2(n)+1;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    prepare();
    int lastans=0;
    for(int i=1;i<=m;i++){
        ans.reset();
        int k=read();
        for(int j=1;j<=k;j++){
            int x,y;
            x=read(),y=read();
            if(f){
                x^=lastans;
                y^=lastans;
            }
            update(x,y);
        }
        int ans1=ans.count();
        int ans2=MAXV;
        for(int i=0;i<MAXV;i++){
            if(ans[i]==0){
                ans2=i;
                break;
            }
        }
        printf("%d %d\n",ans1,ans2);
        lastans=ans1+ans2;
    }
    return 0;
}