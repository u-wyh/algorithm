#include<bits/stdc++.h>
using namespace std;
const int MAXN = 25005;
const int MAXM = 1e6+5;

int n;
string str[MAXN];

int edge[26][26];
int degree[26];
queue<int>q;
queue<int>ans;

int tree[MAXM][26];
int en[MAXM];
int cnt=1;

void insert(string s){
    int cur=1;
    int len=s.length();
    for(int i=0,path;i<len;i++){
        path=s[i]-'a';
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
        }
        cur=tree[cur][path];
    }
    en[cur]++;
}

bool check(string s){
    while(!q.empty()){
        q.pop();
    }
    while(!ans.empty()){
        ans.pop();
    }
    for(int i=0;i<26;i++){
        degree[i]=0;
        for(int j=0;j<26;j++){
            edge[i][j]=0;
        }
    }

    int len=s.length();
    int cur=1;
    for(int i=0;i<len;i++){
        if(en[cur]){
            return 0;
        }
        int path=s[i]-'a';
        for(int j=0;j<26;j++){
            if(tree[cur][j]&&j!=path&&!edge[path][j]){
                degree[j]++;
                edge[path][j]=1;
            }
        }
        cur=tree[cur][path];
    }
    for(int i=0;i<26;i++){
        if(degree[i]==0){
            ans.push(i);
            q.push(i);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=0;i<26;i++){
            if(edge[u][i]){
                degree[i]--;
                if(degree[i]==0){
                    ans.push(i);
                    q.push(i);
                }
            }
        }
    }
    for(int i=0;i<26;i++){
        if(degree[i]){
            return 0;
        }
    }
    return 1;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>str[i];
        insert(str[i]);
    }
    for(int i=1;i<=n;i++){
        if(check(str[i])){
            for(int i=0;i<26;i++){
                cout<<char('a'+ans.front());
                ans.pop();
            }
            cout<<endl;
        }
        else{
            cout<<"nemoguce"<<endl;
        }
    }
    return 0;
}
