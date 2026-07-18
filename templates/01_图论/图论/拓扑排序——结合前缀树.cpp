//P3065
//这道题目很好的结合了 前缀树 和 拓扑排序
//树的结构保证了不用重复连边建图 
//这道题相当于建立了两张图  一张是前缀树  一张是字母之间的连边
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e4+5;
const int MAXM = 3e5+5;

int n;
string str[MAXN];
int cnt=1;
int tree[MAXM][26];
int en[MAXM];
//end  pass表示这个编号上的经过信息和结尾信息
int path;
int indegree[26];
int edge[26][26];
queue<int>q;

void build(){
    for(int i=0;i<26;i++){
        for(int j=0;j<26;j++){
            edge[i][j]=0;
        }
        indegree[i]=0;
    }
}

//拓扑排序 入度删除法
void topo(){
    for(int i=0;i<26;i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        for(int i=0;i<26;i++){
            if(edge[cur][i]){
                indegree[i]--;
                if(indegree[i]==0){
                    q.push(i);
                }
            }
        }
    }
}

bool check(string str){
    build();//全部初始化
    int u=1;
    int len=str.length();
    for(int i=0;i<len;i++){
        if(en[u]){
            //如果有单词是他的前缀 那么直接没希望  返回false
            return false;
        }
        int v=str[i]-'a';
        for(int j=0;j<26;j++){
            if(v!=j&&!edge[v][j]&&tree[u][j]){
                //将这个节点 向 他的所有兄弟节点连边
                edge[v][j]=1;
                indegree[j]++;
            }
        }
        u=tree[u][v];
    }
    topo();
    for(int i=0;i<26;i++){
        if(indegree[i]){
            //还有度 说明一定有环 表示不可能 返回false
            return false;
        }
    }
    return true;
}

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
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>str[i];
        insert(str[i]);//将所有字符串插入前缀树中
    }
    int ans=0;
    int t[MAXN];
    for(int i=1;i<=n;i++){
        if(check(str[i])){
            //枚举检查每一个字符串是否有资格作为最小的
            t[ans]=i;//记录编号
            ans++;
        }
    }
    cout<<ans<<endl;
    for(int i=0;i<ans;i++){
        cout<<str[t[i]]<<endl;
    }
    return 0;
}
