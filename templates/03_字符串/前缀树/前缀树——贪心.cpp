// https://www.luogu.com.cn/problem/P3294
//这道题我们首先要避免第一种情况（n*n的代价）  所以一定是后缀全部填进去了
//我们把单词逆转一下  把后缀变为前缀
//总代价可表示为：Σ(当前序号) - Σ(后缀单词最大序号)
//那么我们的目标就是将后缀序号最大化
//我们建立一个树  一个节点子树都是以它为后缀的单词编号  头结点是0  根节点
//接下来考虑如何分配节点编号  使用贪心策略  对于一个节点而言  它的子节点中子树大的编号分配更大编号
//因为大的子树节点越大  那么他影响的也就越多  这个贪心是对的
//我们借用栈结构来实现  很巧妙
#include<bits/stdc++.h>
using namespace std;
const int MAXM = 510005;
const int MAXN = 1e5+5;

int n;
int len;
char s[MAXM];
char t[MAXM];
int en[MAXM];
int trie[MAXM][26];
int cnt;

vector<int>vec[MAXN];
int sz[MAXN];

void insert(int i){
    int cur=0;
    for(int i=1;i<=len;i++){
        int path=t[i]-'a';
        if(trie[cur][path]==0){
            trie[cur][path]=++cnt;
        }
        cur=trie[cur][path];
    }
    en[cur]=i;
}

void dfs(int u,int last){
    for(int i=0;i<26;i++){
        if(trie[u][i]){
            if(en[trie[u][i]]){
                vec[last].push_back(en[trie[u][i]]);
                dfs(trie[u][i],en[trie[u][i]]);
            }
            else{
                dfs(trie[u][i],last);
            }
        }
    }
}

void dfs(int u){
    sz[u]=1;
    for(int i=0;i<(int)vec[u].size();i++){
        int v=vec[u][i];
        dfs(v);
        sz[u]+=sz[v];
    }
}

bool cmp(int a,int b){
    return sz[a]>sz[b];
}

stack<int>st;

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);
        len=strlen(s+1);
        for(int j=1;j<=len;j++){
            t[j]=s[len-j+1];
        }
        insert(i);
    }
    dfs(0,0);
    dfs(0);
    sort(vec[0].begin(),vec[0].end(),cmp);
    for(int i=0;i<(int)vec[0].size();i++){
        st.push(vec[0][i]);
    }
    long long y=0;
    long long ans=(1ll*n*(n+1))/2;
    int cur=0;
    while(!st.empty()){
        int u=st.top();
        st.pop();
        cur++;
        if(vec[u].size()){
            sort(vec[u].begin(),vec[u].end(),cmp);
            y+=1ll*cur*vec[u].size();
            for(int i=0;i<(int)vec[u].size();i++){
                st.push(vec[u][i]);
            }
        }
    }
    ans-=y;
    cout<<ans<<endl;
    return 0;
}