#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXM = 3e6+5;

int n,m;
char s[MAXN];

// len[i]: 状态i表示的最长子串长度
int len[MAXN];
// fa[i]: 状态i的后缀链接（parent指针）
int fa[MAXN];
// nxt[i][c]: 状态i在字符c上的转移
int nxt[MAXN][10];
int pos[MAXN];
int lst=1;
// 当前节点总数
int tot=1;

int head[MAXN];
int nxtg[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int headq[MAXM];
int nxtq[MAXM];
int toq[MAXM];
int idq[MAXM];
int cntq=1;

int sz[MAXN];
int son[MAXN];
bool vis[MAXN];

int tree[MAXN];

long long ans[MAXN];

inline void addedgeq(int u,int v,int id){
    nxtq[cntq]=headq[u];
    toq[cntq]=v;
    idq[cntq]=id;
    headq[u]=cntq++;
}

inline int lowbit(int x){
    return x&-x;
}

inline void add(int x,int v){
    if(x==0){
        return ;
    }
    // cout<<' '<<x<<' '<<v<<endl;
    while(x<=n){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

inline int query(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

inline void addedge(int u,int v){
    nxtg[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

// 后缀自动机扩展函数：向自动机中添加一个字符
void extend(char c,int posi){
    int cur=++tot;
    // 新状态的长度是上一个状态长度+1  初始出现次数为1
    len[cur]=len[lst]+1;
    pos[cur]=posi;

    // 从上一个状态开始，沿着后缀链接向上遍历
    int p=lst;
    while(p&&!nxt[p][c-'0']){
        // 为没有字符c转移的状态添加转移到cur
        nxt[p][c-'0']=cur;
        p=fa[p];
    }

    // 情况1：没有找到有字符c转移的状态  也就是说这个字符是第一次出现
    if(p==0){
        // 直接挂到根节点上
        fa[cur]=1;
    }
    else{
        // 找到状态p在字符c上的转移状态q
        int q=nxt[p][c-'0'];

        // 情况2：q的长度正好是p的长度+1 直接将cur的后缀链接指向q
        if(len[p]+1==len[q]){
            fa[cur]=q;
        }
        else{
            int nq=++tot;
            len[nq]=len[p]+1;
            pos[nq]=pos[q];

            // 复制q的所有转移
            for(int i=0;i<10;i++){
                nxt[nq][i]=nxt[q][i];
            }
            // 设置nq的后缀链接为q的后缀链接，并更新q和cur的后缀链接
            fa[nq]=fa[q],fa[q]=nq,fa[cur]=nq;

            // 将原本指向q的转移重定向到nq
            while(p&&nxt[p][c-'0']==q){
                nxt[p][c-'0']=nq;
                p=fa[p];
            }
        }
    }
    lst=cur;
}

void dfs1(int u){
    sz[u]=1;
    for(int i=head[u];i;i=nxtg[i]){
        int v=to[i];
        dfs1(v);
        sz[u]+=sz[v];
        if(sz[son[u]]<sz[v]){
            son[u]=v;
        }
    }
}

void effect(int u){
    if(!vis[pos[u]]&&pos[u]){
        add(pos[u],1);
        vis[pos[u]]=true;
    }
    for(int i=head[u];i;i=nxtg[i]){
        int v=to[i];
        effect(v);
    }
}

void cancel(int u){
    if(vis[pos[u]]&&pos[u]){
        vis[pos[u]]=false;
        add(pos[u],-1);
    }
    for(int i=head[u];i;i=nxtg[i]){
        int v=to[i];
        cancel(v);
    }
}

void dfs2(int u,int keep){
    for(int i=head[u];i;i=nxtg[i]){
        int v=to[i];
        if(v!=son[u]){
            dfs2(v,0);
        }
    }
    if(son[u]){
        dfs2(son[u],1);
    }

    if(!vis[pos[u]]&&pos[u]){
        vis[pos[u]]=true;
        add(pos[u],1);
    }
    
    for(int i=head[u];i;i=nxtg[i]){
        int v=to[i];
        if(v!=son[u]){
            effect(v);
        }
    }

    for(int i=headq[u];i;i=nxtq[i]){
        int v=toq[i];
        int id=idq[i];
        ans[id]+=query(v);
    }
    if(!keep){
        cancel(u);
    }
}

int main()
{
    scanf("%d",&n);
    scanf("%s",s+1);

    for(int i=1;i<=n;i++){
        extend(s[i],i);
    }

    for(int i=2;i<=tot;i++){
        addedge(fa[i],i);
    }

    // for(int i=1;i<=tot;i++){
    //     cout<<pos[i]<<' ';
    // }
    // cout<<endl<<endl;

    dfs1(1);
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        scanf("%s",s+1);
        int len=strlen(s+1);
        int now=1,d=1;
        while(d<=len&&nxt[now][s[d]-'0']){
            now=nxt[now][s[d]-'0'];
            d++;
        }

        int stop;
        if(d<=len){
            stop=n+len;
        }
        else{
            stop=pos[now];
        }

        ans[i]=stop-len;

        now=1;
        for(int j=1;j<=len;j++){
            if(!nxt[now][s[j]-'0']){
                break;
            }
            now=nxt[now][s[j]-'0'];
            int limit=min(n,stop-len+j);
            addedgeq(now,limit,i);
            // cout<<' '<<now<<' '<<limit<<' '<<i<<endl;
        }
    }

    dfs2(1,1);
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}