#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e7+5;
const int MAXM = 105;
const int MAXT = 1e5+5;

int n,m;
char s[MAXN];
char t[MAXT][MAXM];

int trie[MAXN][4];
int fail[MAXN];
bool vis[MAXN];
int cnt;

inline int tran(char c){
    if(c=='E'){
        return 0;
    }
    else if(c=='S'){
        return 1;
    }
    else if(c=='W'){
        return 2;
    }
    else{
        return 3;
    }
}

void insert(int id){
    int cur=0;
    int len=strlen(t[id]+1);
    for(int i=1;i<=len;i++){
        char ch=t[id][i];
        int path=tran(ch);
        if(trie[cur][path]==0){
            trie[cur][path]=++cnt;
        }
        cur=trie[cur][path];
    }
}

void setfail(){
    queue<int>q;
    for(int i=0;i<4;i++){
        if(trie[0][i]){
            q.push(trie[0][i]);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=0;i<4;i++){
            if(trie[u][i]==0){
                trie[u][i]=trie[fail[u]][i];
            }
            else{
                fail[trie[u][i]]=trie[fail[u]][i];
                q.push(trie[u][i]);
            }
        }
    }
}

int query(int id){
    int n=strlen(t[id]+1);
    int cur=0;
    int ans=0;
    for(int i=1;i<=n;i++){
        cur=trie[cur][tran(t[id][i])];
        if(!vis[cur]){
            break;
        }
        ans++;
    }
    return ans;
}

int main()
{
    scanf("%d %d",&n,&m);
    scanf("%s",s+1);
    for(int i=1;i<=m;i++){
        scanf("%s",t[i]+1);
        insert(i);
    }
    setfail();
    int cur=0;
    for(int i=1;i<=n;i++){
        cur=trie[cur][tran(s[i])];
        for(int p=cur;vis[p]==false;p=fail[p]){
            vis[p]=true;
        }
    }
    for(int i=1;i<=m;i++){
        cout<<query(i)<<endl;
    }
    return 0;
}