// 后缀自动机结合虚树做法
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e6+5;
const int MAXH = 22;
const int MOD = 23333333333333333;
const int MAXM = 3e6+5;

int n,m,p;
int ans;
char s[MAXN];

// len[i]: 状态i表示的最长子串长度
int len[MAXN];
// fa[i]: 状态i的后缀链接（parent指针）
int fa[MAXN];
// nxt[i][c]: 状态i在字符c上的转移
int nxt[MAXN][26];
// cnt[i]: 状态i对应的endpos集合大小，即该状态表示的子串在字符串中的出现次数
int cnt[MAXN];
int lst=1;
// 当前节点总数
int tot=1;

int pos[MAXN];

int headg[MAXN];
int nxtg[MAXN<<1];
int tog[MAXN<<1];
int cntg=1;

int dep[MAXN];
int dfn[MAXN];
int st[MAXN][MAXH];
int cntd;

int headv[MAXN];
int nxtv[MAXN];
int tov[MAXN];
int cntv;

bool iskey[MAXN];

int arr[MAXM];
int stk[MAXM];
bool vis[MAXM];
int k;

inline void addedge(int u,int v){
    nxtg[cntg]=headg[u];
    tog[cntg]=v;
    headg[u]=cntg++;
}

// 后缀自动机扩展函数：向自动机中添加一个字符
void extend(char c){
    int cur=++tot;
    // 新状态的长度是上一个状态长度+1  初始出现次数为1
    len[cur]=len[lst]+1;
    cnt[cur]=1;

    // 从上一个状态开始，沿着后缀链接向上遍历
    int p=lst;
    while(p&&!nxt[p][c-'a']){
        // 为没有字符c转移的状态添加转移到cur
        nxt[p][c-'a']=cur;
        p=fa[p];
    }

    // 情况1：没有找到有字符c转移的状态  也就是说这个字符是第一次出现
    if(p==0){
        // 直接挂到根节点上
        fa[cur]=1;
    }
    else{
        // 找到状态p在字符c上的转移状态q
        int q=nxt[p][c-'a'];

        // 情况2：q的长度正好是p的长度+1 直接将cur的后缀链接指向q
        if(len[p]+1==len[q]){
            fa[cur]=q;
        }
        else{
            int nq=++tot;
            len[nq]=len[p]+1;

            // 复制q的所有转移
            for(int i=0;i<26;i++){
                nxt[nq][i]=nxt[q][i];
            }
            // 设置nq的后缀链接为q的后缀链接，并更新q和cur的后缀链接
            fa[nq]=fa[q],fa[q]=nq,fa[cur]=nq;

            // 将原本指向q的转移重定向到nq
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

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    dfn[u] = ++cntd;
    st[u][0] = fa;
    for (int i = 1; i <= p; i++) {
        st[u][i] = st[st[u][i - 1]][i - 1];
    }
    for (int e = headg[u]; e; e = nxtg[e]) {
        if (tog[e] != fa) {
            dfs(tog[e], u);
        }
    }
}

int getLca(int a, int b) {
    if (dep[a] < dep[b]) {
        swap(a, b);
    }
    for (int i = p; i >= 0; i--) {
        if (dep[st[a][i]] >= dep[b]) a = st[a][i];
    }
    if (a == b) {
        return a;
    }
    for (int i = p; i >= 0; i--) {
        if (st[a][i] != st[b][i]) {
            a = st[a][i];
            b = st[b][i];
        }
    }
    return st[a][0];
}

bool cmp(int x, int y) {
    return dfn[x] < dfn[y];
}

inline void addedgev(int u,int v){
    nxtv[cntv]=headv[u];
    tov[cntv]=v;
    headv[u]=cntv++;
}

// 单调栈的方式建立虚树
int buildVirtualTree() {
    sort(arr + 1, arr + k + 1, cmp);
    cntv = 1;
    // 在入栈时清空连边
    headv[arr[1]] = 0;
    int top = 0;
    stk[++top] = arr[1];
    for (int i = 2; i <= k; i++) {
        if(arr[i]==arr[i-1]){
            continue;
        }
        int x = arr[i];
        int y = stk[top];
        int lca = getLca(x, y);
        while (top > 1 && dfn[stk[top - 1]] >= dfn[lca]) {
            addedgev(stk[top - 1], stk[top]);
            top--;
        }
        if (lca != stk[top]) {
            headv[lca] = 0;
            addedgev(lca, stk[top]);
            // 这里是换顶  完整的应该是top-- stk[top++]=lca
            stk[top] = lca;
        }
        headv[x] = 0;
        stk[++top] = x;
    }
    while (top > 1) {
        addedgev(stk[top - 1], stk[top]);
        top--;
    }
    return stk[1];
}

int dfs(int u){
    int a=iskey[u]?1:0;
    int val=len[u];
    for(int i=headv[u];i;i=nxtv[i]){
        int v=tov[i];
        int b=dfs(v);
        ans=(ans+(a*b%MOD)*val)%MOD;
        a+=b;
    }
    return a;
}

int compute(){
    ans=0;
    for(int i=1;i<=k;i++){
        iskey[arr[i]]=true;
    }
    int tree=buildVirtualTree();
    dfs(tree);
    for(int i=1;i<=k;i++){
        iskey[arr[i]]=false;
    }
    return ans;
}

signed main()
{
    // 初始状态：根节点1
    tot=1,lst=1;

    scanf("%d %d",&n,&m);
    scanf("%s",s+1);

    for(int i=1;i<=n;i++){
        extend(s[n-i+1]);
        pos[n-i+1]=lst;
    }
    buildtree();

    p=log2(tot)+1;
    dfs(1,0);

    for(int i=1;i<=m;i++){
        scanf("%d",&k);
        for(int i=1;i<=k;i++){
            scanf("%d",&arr[i]);
            arr[i]=pos[arr[i]];
        }
        if(k==1){
            cout<<0<<endl;
            continue;
        }
        cout<<compute()<<endl;
    }
    return 0;
}
/*
7 3
popoqqq
1 4
2 3 5
4 1 2 5 6
*/