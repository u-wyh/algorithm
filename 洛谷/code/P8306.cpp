#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3000001;
const int MAXM = 1e5+5;

int cnt=1,cnt1=0;//用于赋值新编号   全部从1开始使用
int tree[MAXN][80];//表示最多只有26个字符
//tree[i][j]:表示编号为i的节点通过j（代表一个字符）这条路径到达下一个节点
//如果这个位置上是0  表示没有这条路
int en[MAXN];
int pass[MAXN];
//end  pass表示这个编号上的经过信息和结尾信息
int path;
string name[MAXM];
string word[MAXM];

void insert(string word){
    int cur=1;
    pass[cur]++;
    for (char ch : word){
        path=ch-'0';
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
        path=ch-'0';
        if(tree[cur][path]==0){
            return 0;
            //没有路说明走不通
        }
        cur=tree[cur][path];
    }
    return pass[cur];
}

void clear(){
    for(int i=cnt1;i<=cnt;i++){
        pass[i]=0;
        en[i]=0;
        for(int j=0;j<65;j++){
            tree[i][j]=0;
        }
    }
    cnt1=cnt-1;
}
//将产生的脏数据全部清空

int main()
{
    int t;
    cin>>t;
    while(t--){
        int n,m;
        cin>>n>>m;
        //cnt=1;
        for(int i=1;i<=n;i++){
            cin>>name[i];
            insert(name[i]);
        }
        for(int i=1;i<=m;i++){
            cin>>word[i];
            cout<<preword(word[i])<<endl;
        }
        clear();
    }
    return 0;
}
