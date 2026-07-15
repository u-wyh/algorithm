#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int cnt=1;//用于赋值新编号   全部从1开始使用
int tree[MAXN][26];//表示最多只有26个字符
//tree[i][j]:表示编号为i的节点通过j（代表一个字符）这条路径到达下一个节点
//如果这个位置上是0  表示没有这条路
int en[MAXN];
int path;

int n,m;
string s;
int ans=0;
int len;
int vis[MAXN];

void insert(string word){
    int cur=1;
    for (char ch : word){
        path=ch-'a';
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
            //没有路就要新建一条路  并赋予编号
        }
        cur=tree[cur][path];
    }
    en[cur]++;
    //cout<<cur<<endl;
}

int search(string word){
    int cur=1;
    for (char ch : word){
        path=ch-'a';
        if(tree[cur][path]==0){
            return 0;
            //没有路说明走不通
        }
        cur=tree[cur][path];
    }
    return en[cur];
}

void dfs(int cur,int u,bool f,int now){
    if(u==len+1){
        if(f){
            if(vis[cur]!=now){
                ans+=en[cur];
                vis[cur]=now;
            }
        }
        else{
            for(int i=0;i<26;i++){
                if(vis[tree[cur][i]]!=now){
                    ans+=en[tree[cur][i]];
                    vis[tree[cur][i]]=now;
                }
            }
        }
    }
    path=s[u-1]-'a';
    if(tree[cur][path]!=0){
        dfs(tree[cur][path],u+1,f,now);
    }
    if(tree[cur][path]==0){
        if(u==len&&!f){
            if(vis[cur]!=now){
                ans+=en[cur];
                vis[cur]=now;
            }
        }
    }
    if(!f){
        //以前没有用过
        for(int i=0;i<26;i++){
            dfs(tree[cur][i],u,1,now);//删除字母
            dfs(tree[cur][i],u+1,1,now);//变换字母
        }
        dfs(cur,u+1,1,now);//添加字母
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>s;
        insert(s);
    }
    for(int i=1;i<=m;i++){
        cin>>s;
        if(search(s)){
            cout<<-1<<endl;
            continue;
        }
        len=s.length();
        ans=0;
        dfs(1,1,0,i);
        //cout<<endl;
        cout<<ans<<endl;
    }
    return 0;
}

