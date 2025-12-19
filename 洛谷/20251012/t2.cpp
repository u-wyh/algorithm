#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n,m;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int len[MAXN];
int son[MAXN];

int nums[MAXN];
int cntg;

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

void init(){
    cnt=1;
    for(int i=1;i<=n;i++){
        head[i]=0;
        len[i]=0;
        son[i]=0;
    }
    cntg=0;
}

void dfs1(int u,int fa){
    // len[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs1(v,u);
            if(len[v]>len[son[u]]){
                son[u]=v;
            }
        }
    }
    len[u]=len[son[u]]+1;
}

void dfs2(int u,int fa){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=son[u]&&v!=fa){
            dfs2(v,u);
            nums[++cntg]=len[v];
        }
        else if(v!=fa){
            dfs2(v,u);
        }
    }
}

bool cmp(int a,int b){
    return a>b;
}

int main()
{
    int T=read();
    while(T--){
        n=read();
        init();
        for(int i=2;i<=n;i++){
            int u=read();
            addedge(u,i);
            addedge(i,u);
        }
        dfs1(1,0);
        dfs2(1,0);
        // for(int i=1;i<=n;i++){
        //     cout<<i<<": "<<len[i]<<endl;
        // }
        nums[++cntg]=len[1];
        sort(nums+1,nums+cntg+1,cmp);
        int ans=min(cntg,nums[1]);
        for(int i=2;i<=cntg;i++){
            ans=min(ans,nums[i]+i-1);
        }
        cout<<ans<<endl;
    }
    return 0;
}