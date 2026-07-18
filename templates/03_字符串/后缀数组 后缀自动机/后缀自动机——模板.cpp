// https://www.luogu.com.cn/problem/P3804
// 后缀自动机中最多会有2*n-1个节点  有3*n-4条边
// i节点所代表的不同的子串个数为len[i] - len[fa[i]];
// 后缀自动机中每个节点代表的所有字符串的长度是连续的
// fa[u]最长真后缀：状态 u 表示的所有子串中，最长的那个子串的真后缀对应的状态
// 同时也是在连接具有包含关系的 endpos 集合
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e6+5;

int n;
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

int head[MAXN];
int nxtg[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

inline void addedge(int u,int v){
    nxtg[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
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
    // 初始状态：根节点1
    tot=1,lst=1;

    scanf("%s",s+1);
    n=strlen(s+1);

    for(int i=1;i<=n;i++){
        extend(s[i]);
    }
    cout<<compute()<<endl;
    return 0;
}