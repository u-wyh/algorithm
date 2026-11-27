// https://www.luogu.com.cn/problem/P4683
// 题意：初始空打印机可在末尾加小写字母、删末尾字母或打印当前串，
// 以任意顺序打印给定 n 个互异单词（结束可留字母），求最少操作数及一种方案。
// 数据范围：1 <= n <= 25000，单词由小写字母组成且长度 1~20。
// 算法标签：字典树、深度优先搜索、贪心
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

string str;
int n;
string s[25005];
string maxs;
int ans=0;

int cnt=1;
int tree[MAXN][27];
int en[MAXN];
bool mark[MAXN];

void insert(string s){
    int cur=1;
    for(int i=0;i<s.length();i++){
        int path=s[i]-'a'+1;
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
        }
        cur=tree[cur][path];
    }
    en[cur]++;
}

void fun(string s){
    int cur=1;
    for(int i=0;i<s.length();i++){
        int path=s[i]-'a'+1;
        cur=tree[cur][path];
        mark[cur]=true;
    }
}

void dfs(int u){
    if(en[u]==1&&u!=0){
        ans++;
        str+='P';
    }
    if(ans==n){
        cout<<(str.length())<<endl;
        for(int i=0;i<str.length();i++){
            cout<<str[i]<<endl;
        }
        exit(0);
        return ;
    }
    for(int i=1;i<=26;i++){
        int path=tree[u][i];
        if(path!=0&&!mark[path]){
            str+=('a'+i-1);
            dfs(path);
            str+='-';
        }
    }
    for(int i=1;i<=26;i++){
        int path=tree[u][i];
        if(path!=0&&mark[path]){
            str+=('a'+i-1);
            dfs(path);
        }
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        cin>>s[i];
        insert(s[i]);
        if(s[i].length()>maxs.length()){
            maxs=s[i];
        }
    }
    fun(maxs);
    dfs(1);
    return 0;
}
