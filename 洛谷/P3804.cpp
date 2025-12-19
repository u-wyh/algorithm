#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e6+5;

int n;
char s[MAXN];

int len[MAXN];
int fa[MAXN];
int nxt[MAXN][26];
int cnt[MAXN];
int lst;
int tot;

int head[MAXN];
int nxtg[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

inline void addedge(int u,int v){
    nxtg[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void extend(char c){
    int cur=++tot;
    len[cur]=len[lst]+1;
    cnt[cur]=1;

    int p=lst;
    while(p&&!nxt[p][c-'a']){
        nxt[p][c-'a']=cur;
        p=fa[p];
    }

    if(p==0){
        fa[cur]=1;
    }
    else{
        int q=nxt[p][c-'a'];

        if(len[p]+1==len[q]){
            fa[cur]=q;
        }
        else{
            int nq=++tot;
            len[nq]=len[p]+1;

            for(int i=0;i<26;i++){
                nxt[nq][i]=nxt[q][i];
            }
            fa[nq]=fa[q],fa[q]=nq,fa[cur]=nq;

            while(p&&nxt[p][c-'a']==q){
                nxt[p][c-'a']=nq;
                p=fa[p];
            }
        }
    }
    lst=cur;
}

void buildtree(){
    for(int i=2;i<=tot;i++){
        addedge(fa[i],i);
    }
}

void dfs(int u){
    for(int i=head[u];i;i=nxtg[i]){
        int v=to[i];
        dfs(v);
        cnt[u]+=cnt[v];
    }
}

long long compute(){
    buildtree();
    dfs(1);
    long long ans=0;
    for(int i=1;i<=tot;i++){
        if(cnt[i]>1){
            ans=max(ans,1ll*cnt[i]*len[i]);
        }
    }
    return ans;
}

int main()
{
    tot=1;
    lst=1;

    scanf("%s",s+1);
    n=strlen(s+1);

    for(int i=1;i<=n;i++){
        extend(s[i]);
    }
    cout<<compute()<<endl;
    return 0;
}