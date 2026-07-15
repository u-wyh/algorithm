#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n,m;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int head1[MAXN];
int nxt1[MAXN];
int to1[MAXN];
int id1[MAXN];
int cnt1=1;

int head2[MAXN];
int nxt2[MAXN];
int to2[MAXN];
int id2[MAXN];
int cnt2=1;

int cnt[MAXN];

int ans[MAXN];

int stk[MAXN];
int top;

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
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void addedge1(int u,int v,int id){
    nxt1[cnt1]=head1[u];
    to1[cnt1]=v;
    id1[cnt1]=id;
    head1[u]=cnt1++;
}

void addedge2(int u,int v,int id){
    nxt2[cnt2]=head2[u];
    to2[cnt2]=v;
    id2[cnt2]=id;
    head2[u]=cnt2++;
}

void dfs1(int u){
    stk[++top]=u;
    for(int i=head1[u];i;i=nxt1[i]){
        int v=to1[i];
        int id=id1[i];
        if(top>v){
            addedge2(stk[top-v],v,id);
        }
        else{
            ans[id]=1;
        }
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs1(v);
    }
    top--;
}

void dfs2(int u,int d){
    cnt[d]++;
    for(int i=head2[u];i;i=nxt2[i]){
        int v=to2[i];
        int id=id2[i];
        ans[id]-=cnt[d+v];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs2(v,d+1);
    }
    for(int i=head2[u];i;i=nxt2[i]){
        int v=to2[i];
        int id=id2[i];
        ans[id]+=cnt[d+v];
    }
}

int main()
{
    n=read(),m=read();
    for(int i=2;i<=n;i++){
        int u=read();
        addedge(u,i);
    }
    for(int i=1;i<=m;i++){
        int u,k;
        u=read(),k=read();
        addedge1(u,k,i);
    }
    dfs1(1);
    dfs2(1,1);
    for(int i=1;i<=m;i++){
        printf("%d ",ans[i]-1);
    }
    return 0;
}