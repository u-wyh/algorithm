#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const int MAXM = 5e5+5;

int m,n;
string word[MAXN];
string code[MAXN];

int cnt=1;//用于赋值新编号   全部从1开始使用
int tree[MAXN][26];//表示最多只有26个字符
//tree[i][j]:表示编号为i的节点通过j（代表一个字符）这条路径到达下一个节点
//如果这个位置上是0  表示没有这条路
int en[MAXN];
int pass[MAXN];
//end  pass表示这个编号上的经过信息和结尾信息
int path;

void insert(string word){
    int cur=1;
    pass[cur]++;
    for (char ch : word){
        path=ch-'a';
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
            //没有路就要新建一条路  并赋予编号
        }
        cur=tree[cur][path];
        pass[cur]++;
    }
    en[cur]++;
}

int preword(string word){
    int cur=1;
    for (char ch : word){
        path=ch-'a';
        if(tree[cur][path]==0){
            return en[cur];
            //没有路说明走不通
        }
        cur=tree[cur][path];
    }
    return pass[cur];
}

int main()
{
    cin>>m>>n;
    for(int i=1;i<=m;i++){
        //cin>>t;
        cin>>word[i];
        insert(word[i]);
    }
    for(int i=1;i<=n;i++){
        cin>>code[i];
        cout<<preword(code[i])<<endl;
    }
    return 0;
}
