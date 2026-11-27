// https://www.luogu.com.cn/problem/P3294
// 题意：
// 给定 n 个互不相同的小写字母单词，需为它们排列一个学习顺序。
// 若位于位置 x 的单词 s 存在某个后缀排在它后面，则 s 代价为 n * n。
// 若不存在其他单词是 s 的后缀，则 s 代价为 x。
// 若所有是 s 后缀的单词都在前面且最靠后位置为 y，则 s 代价为 x - y。
// 输出最小总代价。
// 数据范围：
// 1 <= n <= 100000
// 1 <= sum |S| <= 510000（所有单词长度总和）
#include<bits/stdc++.h>
// 算法标签：Trie树、贪心
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