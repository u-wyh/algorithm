#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;
const int MAXM = 6e3+5;

int n,m;

int dp[MAXN];
int in[MAXN];
queue<int>q;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cnt=1;

int head1[MAXN];
int nxt1[MAXM];
int to1[MAXM];
int cnt1=1;

int dfn[MAXN];
int low[MAXN];
int dfncnt,color;
int col[MAXN];
int st[MAXN];
bool instack[MAXN];
int top=0;

void prepare(){
    dfncnt=color=0;
    cnt=1,cnt1=1;
    top=0;
    for(int i=1;i<=n;i++){
        head[i]=0;
        head1[i]=0;
        dfn[i]=0;
        low[i]=0;
        col[i]=0;
        instack[i]=0;
        in[i]=0;
        dp[i]=0;
    }
}

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void Addedge(int u,int v){
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
    if(low[u]==dfn[u]){
        col[u]=++color;
        while(st[top]!=u){
            col[st[top--]]=color;
        }
        top--;
    }
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        prepare();
        for(int i=1;i<=m;i++){
            int u,v;
            cin>>u>>v;
            addedge(u,v);
        }
        for(int i=1;i<=n;i++){
            if(!dfn[i]){
                tarjan(i);
            }
        }
        if(color==1){
            cout<<"Yes"<<endl;
            continue;
        }
        for(int i=1;i<=n;i++){
            for(int j=head[i];j;j=nxt[j]){
                int v=to[j];
                if(col[i]!=col[v]){
                    Addedge(col[i],col[v]);
                    in[col[v]]++;
                }
            }
        }
        for(int i=1;i<=color;i++){
            if(in[i]==0){
                q.push(i);
                dp[i]=1;
            }
        }
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int i=head1[u];i;i=nxt1[i]){
                int v=to1[i];
                in[v]--;
                if(in[v]==0){
                    q.push(v);
                    dp[v]=dp[u]+1;
                }
            }
        }
        bool flag=false;
        for(int i=1;i<=color;i++){
            if(dp[i]>=color){
                flag=true;
                break;
            }
        }
        cout<<(flag?"Yes":"No")<<endl;
    }
    return 0;
}