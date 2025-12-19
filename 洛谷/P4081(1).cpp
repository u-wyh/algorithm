// 后缀自动机解法
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;
vector<string>s;

// len[i]: 状态i表示的最长子串长度
int len[MAXN];
// fa[i]: 状态i的后缀链接（parent指针）
int fa[MAXN];
// nxt[i][c]: 状态i在字符c上的转移
int nxt[MAXN][26];
// cnt[i]: 状态i对应的endpos集合大小，即该状态表示的子串在字符串中的出现次数
int cnt[MAXN];
int lst;
// 当前节点总数
int tot;

int vis[MAXN];
long long ans[MAXN];

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

void update(int u,int i){
    while(u&&vis[u]!=-1){
        if(vis[u]==0){
            vis[u]=i;
        }
        else if(vis[u]!=i){
            vis[u]=-1;
        }
        else{
            break;
        }
        u=fa[u];
    }
}

int main()
{
    tot=1,lst=1;
    cin>>n;
    s.resize(n+1);
    for(int i=1;i<=n;i++){
        cin>>s[i];
        int len=s[i].length();
        lst=1;
        for(int j=1;j<=len;j++){
            extend(s[i][j-1]);
        }
    }
    for(int i=1;i<=n;i++){
        int cur=1;
        for(char c:s[i]){
            cur=nxt[cur][c-'a'];
            update(cur,i);
        }
    }
    for(int i=1;i<=tot;i++){
        if(vis[i]>0){
            int id=vis[i];
            ans[id]+=len[i]-len[fa[i]];
        }
    }
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}