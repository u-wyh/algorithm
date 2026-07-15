#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4e6+5;
const int MAXM = 1e7+5;

int n,m,k;
int nums[MAXN];

int dfn[MAXN];
int low[MAXN];
int dfncnt;
int color;
int st[MAXN];
bool instack[MAXN];
int top;
int col[MAXN];

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cnt=1;

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

void tarjan(int u){
    dfn[u]=low[u]=++dfncnt;
    st[++top]=u;
    instack[u]=true;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(instack[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(dfn[u]==low[u]){
        col[u]=++color;
        instack[u]=false;
        while(st[top]!=u){
            instack[st[top]]=false;
            col[st[top--]]=color;
        }
        top--;
    }
}

int main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addedge(u*2,v*2-1);
        addedge(v*2,u*2-1);
    }

    while(k--){
        int t=read();
        for(int i=1;i<=t;i++){
            nums[i]=read();
            addedge(nums[i]*2-1,2*n+nums[i]*2-1);
            addedge(nums[i]*2+2*n,nums[i]*2);
        }
        for(int i=1;i<t;i++){
            addedge(nums[i]*2-1+2*n,nums[i+1]*2-1+2*n);
            addedge(nums[i]*2-1+2*n,nums[i+1]*2);
        }
        for(int i=1;i<t;i++){
            addedge(nums[i+1]*2+2*n,nums[i]*2+2*n);
            addedge(nums[i+1]*2-1,nums[i]*2+2*n);
        }
    }

    for(int i=1;i<=4*n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }

    bool flag=false;
    for(int i=1;i<=n;i++){
        if(col[i*2-1]==col[2*i]){
            flag=true;
            break;
        }
    }
    if(flag){
        cout<<"NIE"<<endl;
    }
    else{
        cout<<"TAK"<<endl;
    }
    return 0;
}