// https://www.luogu.com.cn/problem/P5829
// 失配树是根据kmp算法完成的树形数据结构
// 我们首先根据kmp算法生成nxt数组  然后根据nxt数组的值连边 nxt[i]->i
// 最终我们可以得到一个树形数据结构  在这个树上 每个节点的祖先节点既是它的前缀 也是他的后缀
// 树的顶点编号是0   不需要特别处理  因为如果一个前缀片段的前后缀匹配长度就是0的话  那么就正常处理即可
// 并且节点编号也是这个字符串的长度 因为这个字符串是从头到这个编号
// 使用1based可以使逻辑更加简洁   要注意 border必须是在前缀树这个节点的父亲以及祖先节点   自己不能算
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int LIMIT = 22;

int n,p;
int Next[MAXN];
char s[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt=1;

int dep[MAXN];
int st[MAXN][LIMIT];

// 计算1-based next数组
void calcnext(){
    Next[1]=0;
    for(int i=2,j=0;i<=n;i++){
        // 当不匹配时，通过next数组回溯
        while(j>0&&s[i]!=s[j+1]){
            j=Next[j];
        }
        // 如果当前字符匹配，j增加
        if(s[i]==s[j+1]){
            j++;
        }
        // 设置当前位置的next值
        Next[i]=j;
    }
}

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v,u);
    }
}

int lca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int i=p;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b){
        //如果相同说明就是祖先关系
        //那么还要向上跳一下  因为要求的是border
        //实际上也可以求stjump[u][0],stjump[v][0]的lca  这样不用跳  直接就是lca
        return st[a][0];
    }
    for(int i=p;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    p=log2(n+1)+1;
    calcnext();
    for(int i=1;i<=n;i++){
        addedge(Next[i],i);
    }
    dfs(0,0);
    int T;
    cin>>T;
    while(T--){
        int u,v;
        cin>>u>>v;
        cout<<lca(u,v)<<endl;
    }
    return 0;
}