#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;

int n,m;
int nums[MAXN];

int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int cnt=1;

int head1[MAXN];
int nxt1[MAXM<<1];
int to1[MAXM<<1];
int cnt1=1;

bool vis[MAXN];

bool flag;
int A;

int dfn[MAXN];
int low[MAXN];
int dfncnt;
int color;
int val[MAXN];
int st[MAXN];
bool instack[MAXN];
int top;
int col[MAXN];

int black;
int pos;

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

inline void Addedge(int u,int v){
    nxt1[cnt1]=head1[u];
    to1[cnt1]=v;
    head1[u]=cnt1++;
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
        val[color]|=(1<<nums[u]);
        while(st[top]!=u){
            val[color]|=(1<<nums[st[top]]);
            instack[st[top]]=false;
            col[st[top--]]=color;
        }
        top--;
        if(val[color]==3){
            flag=true;
            return ;
        }
        if(val[color]==2){
            black++;
        }
    }
}

void dfs(int u){
    if(A){
        return ;
    }
    for(int i=head1[u];i;i=nxt1[i]){
        int v=to1[i];
        if(col[v]==2){
            A=v;
            return ;
        }
        dfs(v);
    }
}

void dfs1(int u){
    for(int i=head1[u];i;i=nxt1[i]){
        int v=to1[i];
        if(col[v]==1){
            A=0;
            return ;
        }
        else{
            black--;
            dfs1(v);
        }
    }
}

void prepare(){
    flag=false;
    for(int i=1;i<=n;i++){
        head[i]=0;
        dfn[i]=low[i]=0;
        instack[i]=false;
    }
    for(int i=1;i<=color;i++){
        val[i]=0;
        head1[i]=0;
        vis[i]=false;
    }
    color=0;
    dfncnt=0;
    cnt=1,cnt1=1;
    top=0;
    black=0;
    A=0;
}

int main()
{
    int T;
    T=read();
    while(T--){
        n=read(),m=read();
        prepare();
        for(int i=1;i<=m;i++){
            int u,v;
            u=read(),v=read();
            addedge(u,v);
            addedge(v,u);
        }
        for(int i=1;i<=n;i++){
            nums[i]=read();
        }
        int block=0;
        for(int i=1;i<=n;i++){
            if(!dfn[i]){
                block++;
                tarjan(i);
                if(flag){
                    break;
                }
            }
        }
        if(flag){
            cout<<'N';
            continue;
        }

        for(int u=1;u<=n;u++){
            for(int i=head[u];i;i=nxt[i]){
                int v=to[i];
                if(col[u]!=col[v]){
                    Addedge(col[u],col[v]);
                }
            }
        }
        for(int i=1;i<=color;i++){
            if(!vis[i]){
                if(val[i]==1){
                    dfs(i);
                }
                else{
                    A=i;
                }
                if(A){
                    break;
                }
            }
        }

        if(A==0){
            //全是白色
            cout<<'B';
            continue;
        }
        else{
            dfs1(A);
            black--;
            if(A&(black==0)){
                cout<<'A';
                continue;
            }
        }

        if((color==2&&(cnt1==1)&&(val[1]==2&&val[2]==2))||(cnt1==2&&val[to1[1]]==1&&val[head1[1]]==2)){
            cout<<'B';
            continue;
        }

        cout<<'N';
    }
    return 0;
}