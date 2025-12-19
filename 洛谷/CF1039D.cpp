#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,blen;
int fa[MAXN];
int dfncnt;
int dfn[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int len[MAXN];
int max1[MAXN];
int max2[MAXN];

int ans[MAXN];

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

void dfs(int u,int f){
    dfn[++dfncnt]=u;
    fa[u]=f;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=f){
            dfs(v,u);
        }
    }
}

void prepare(){
    blen=max(1,(int)sqrt(n*log2(n)));
    for(int i=1;i<=n;i++){
        ans[i]=-1;
    }
}

int query(int limit){
    int cnt=0;
    for(int i=n;i>=1;i--){
        int u=dfn[i];
        int f=fa[u];
        if(max1[u]+max2[u]+1>=limit){
            cnt++;
            len[u]=0;
        }
        else{
            len[u]=1+max1[u];
        }
        if(len[u]>max1[f]){
            max2[f]=max1[f];
            max1[f]=len[u];
        }
        else if(len[u]>max2[f]){
            max2[f]=len[u];
        }
    }
    for(int i=0;i<=n;i++){
        len[i]=max1[i]=max2[i]=0;
    }
    return cnt;
}

int jump(int l,int r,int len){
    int ans=l;
    while(l<=r){
        int mid=(l+r)>>1;
        int check=query(mid);
        if(check==len){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    return ans+1;
}

void compute(){
    for(int i=1;i<=blen;i++){
        ans[i]=query(i);
    }
    for(int i=blen+1;i<=n;i=jump(i,n,ans[i])){
        ans[i]=query(i);
    }
}

int main()
{
    n=read();
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1,0);
    prepare();
    compute();
    for(int i=1;i<=n;i++){
        if(ans[i]==-1){
            ans[i]=ans[i-1];
        }
        printf("%d\n",ans[i]);
    }
    return 0;
}