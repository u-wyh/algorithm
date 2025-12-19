#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;
const int MAXM = 1e5+5;

int n,m;
string name[MAXN];
string word[MAXM];
int cnt=1;//用于赋值新编号   全部从1开始使用
int tree[MAXN*50][26];//表示最多只有26个字符
//tree[i][j]:表示编号为i的节点通过j（代表一个字符）这条路径到达下一个节点
//如果这个位置上是0  表示没有这条路
int en[MAXN*50];
int pass[MAXN*50];
int path;
//end  pass表示这个编号上的经过信息和结尾信息

void insert(string word){
    int cur=1;
    //pass[cur]++;
    for (char ch : word){
        path=ch-'a';
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
            //没有路就要新建一条路  并赋予编号
        }
        cur=tree[cur][path];
        //pass[cur]++;
    }
    en[cur]++;
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
    pass[cur]++;
    if(en[cur]!=0&&pass[cur]<=1){
        return 1;
    }else if(pass[cur]>1){
        return 2;
    }else {
        return 0;
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>name[i];
        insert(name[i]);
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>word[i];
        int k=search(word[i]);
        if(k==0){
            cout<<"WRONG\n";
        }else if(k==1){
            cout<<"OK\n";
        }else
            cout<<"REPEAT\n";
    }
    return 0;
}

