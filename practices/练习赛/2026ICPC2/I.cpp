#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXM = 1e6+5;
const int MAXV = 5e6+5;
const int MAXE = 1e7+5;

int n;
string arr[MAXN<<1];

int trie[MAXM][26];
int fa[MAXM];
int up[MAXM];
int down[MAXM];
int cntp;

int cntt;
int headg[MAXV];
int nxtg[MAXE];
int tog[MAXE];
int cntg=1;

int headx[MAXM];
int tox[MAXM];
int nxtx[MAXM];
int cntx=1;

int group[MAXM];
int gsiz;

int dfn[MAXV];
int low[MAXV];
int dfncnt;
int sta[MAXV];
int top;
int belong[MAXV];
int sccCnt;

inline void addedge(int u,int v){
    nxtg[cntg]=headg[u];
    tog[cntg]=v;
    headg[u]=cntg++;
}

inline int other(int x){
    return (x<=n)?(x+n):(x-n);
}

inline int newnode(){
    headg[++cntt]=0;
    return cntt;
}

inline int newtrienode(int f){
    int u=++cntp;
    for(int i=0;i<26;i++){
        trie[u][i]=0;
    }
    fa[u]=f;
    up[u]=down[u]=0;
    headx[u]=0;
    return u;
}

inline void addgroup(int u,int v){
    nxtx[cntx]=headx[u];
    tox[cntx]=v;
    headx[u]=cntx++;
}

void insert(int i){
    string word=arr[i];
    int cur=1;
    for(char c:word){
        int path=c-'a';
        if(trie[cur][path]==0){
            int v=newtrienode(cur);
            trie[cur][path]=v;

            up[v]=newnode();
            down[v]=newnode();

            addedge(up[v],up[cur]);
            addedge(down[cur],down[v]);
        }
        cur=trie[cur][path];
    }

    addedge(i,up[fa[cur]]);
    addedge(up[cur],other(i));
    addedge(i,down[cur]);
    addedge(down[fa[cur]],other(i));
    addgroup(cur,i);
}

void grouplink(){
    if(gsiz<=1){
        return ;
    }
    int cur=newnode();
    addedge(cur,other(group[1]));

    for(int i=2;i<=gsiz;i++){
        int lst=cur;
        cur=newnode();

        addedge(cur,lst);
        addedge(cur,other(group[i]));
        addedge(group[i],lst);
    }

    cur=newnode();
    addedge(cur,other(group[gsiz]));
    for(int i=gsiz-1;i>=1;i--){
        int lst=cur;
        cur=newnode();

        addedge(cur,lst);
        addedge(cur,other(group[i]));
        addedge(group[i],lst);
    }
}

void build(){
    cntt=n<<1;
    cntg=1;
    cntx=1;
    cntp=0;

    for(int i=1;i<=2*n;i++){
        headg[i]=0;
    }

    newtrienode(0);
    up[1]=newnode();
    down[1]=newnode();

    for(int i=1;i<=(n<<1);i++){
        insert(i);
    }

    for(int u=1;u<=cntp;u++){
        gsiz=0;
        for(int e=headx[u];e;e=nxtx[e]){
            int v=tox[e];
            group[++gsiz]=v;
        }
        grouplink();
    }
}

void tarjan(int u){
    dfn[u]=low[u]=++dfncnt;
    sta[++top]=u;
    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        if(dfn[v]==0){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(belong[v]==0){
            low[u]=min(low[u],dfn[v]);
        }
    }

    if(dfn[u]==low[u]){
        sccCnt++;
        int pop;
        do{
            pop=sta[top--];
            belong[pop]=sccCnt;
        }while(pop!=u);
    }
}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i]>>arr[i+n];
    }

    build();

    for(int i=1;i<=cntt;i++){
        dfn[i]=0;
        belong[i]=0;
    }
    dfncnt=0;
    top=0;
    sccCnt=0;

    for(int i=1;i<=cntt;i++){
        if(dfn[i]==0){
            tarjan(i);
        }
    }

    for(int i=1;i<=n;i++){
        if(belong[i]==belong[i+n]){
            cout<<"NO"<<endl;
            return ;
        }
    }
    cout<<"YES"<<endl;
    for(int i=1;i<=n;i++){
        if(belong[i]<belong[i+n]){
            cout<<"l";
        }
        else{
            cout<<"r";
        }
    }
    cout<<endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}