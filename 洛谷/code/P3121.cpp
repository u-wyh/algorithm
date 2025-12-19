#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXS = 1e5+5;

// AC自动机
int trie[MAXS][26];
int len[MAXS];
int fail[MAXS];
int cnt = 0;

// 具体题目相关，本题为收集词频
// 所以每个节点记录词频
int times[MAXS];
// 可以用作队列或者栈，一个容器而已
int box[MAXS];

string s;
string text;
int path;
int n;

int st[MAXS][2];
int top;

void insert(string word){
    //i是目标串的编号
    int cur=0;//头结点设置为0
    for (char ch : word){
        path=ch-'a';
        if(trie[cur][path]==0){
            trie[cur][path]=++cnt;
            //没有路就要新建一条路  并赋予编号
        }
        cur=trie[cur][path];
    }
    len[cur]=word.length();
}

void setFail() {
    // box当做队列来使用
    int l = 0;
    int r = 0;
    for (int i = 0; i <= 25; i++) {
        if (trie[0][i] > 0) {
            box[r++] = trie[0][i];
        }
    }
    while (l < r) {
        int u = box[l++];
        for (int i = 0; i <= 25; i++) {
            if (trie[u][i] == 0) {
                trie[u][i] = trie[fail[u]][i];
            } else {
                fail[trie[u][i]] = trie[fail[u]][i];//设置这个孩子节点的fail指针   直通表辅助不用绕环
                box[r++] = trie[u][i];//表示有这条支路  加入到队列中
            }
        }
    }
}

int main()
{
    cin>>text;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s;
        insert(s);
    }
    setFail();
    n=text.length();
    ++top;
    st[top][0]=0;
    st[top][1]=0;
    for(int i=0;i<n;i++){
        int u=st[top][1];
        int v=trie[u][text[i]-'a'];
        ++top;
        st[top][0]=i;
        st[top][1]=v;
        if(len[v]){
            top-=len[v];
        }
    }
    for(int i=2;i<=top;i++){
        cout<<text[st[i][0]];
    }
    return 0;
}