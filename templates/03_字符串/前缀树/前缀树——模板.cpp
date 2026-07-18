#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;//视情况而定

int cnt=1;//用于赋值新编号   全部从1开始使用
//tree[i][j]:表示编号为i的节点通过j（代表一个字符）这条路径到达下一个节点
//如果这个位置上是0  表示没有这条路
int tree[MAXN][26];//表示最多只有26个字符
//end  pass表示这个编号上的经过信息和结尾信息
int en[MAXN];
int pass[MAXN];
int path;

void insert(string word){
    int cur=1;
    pass[cur]++;
    for (char ch : word){
        path=ch-'a';
        if(tree[cur][path]==0){
            //没有路就要新建一条路  并赋予编号
            tree[cur][path]=++cnt;
        }
        cur=tree[cur][path];
        pass[cur]++;
    }
    en[cur]++;
}

int search(string word){
    int cur=1;
    for (char ch : word){
        path=ch-'a';
        if(tree[cur][path]==0){
            //没有路说明走不通
            return 0;
        }
        cur=tree[cur][path];
    }
    return en[cur];
}

int preword(string word){
    int cur=1;
    for (char ch : word){
        path=ch-'a';
        if(tree[cur][path]==0){
            //没有路说明走不通
            return 0;
        }
        cur=tree[cur][path];
    }
    return pass[cur];
}

//在删除之前必须要检测一下这个单词是否存在
//如果存在  在遍历的过程中减少词频  如果出现次数变为0  说明这个分支直接断了  那么直接删除分支
void erase(string word){
    if(search(word)>0){
        int cur=1;
        for (char ch : word){
            path=ch-'a';
            if(--pass[tree[cur][path]]==0){
                //将这个节点设置为0  那么这个节点所连着的路全部失效
                //因为即使后来有结点重新连接上  但是会赋予这个新节点另外一个编号
                tree[cur][path]=0;
                return ;
            }
            cur=tree[cur][path];
        }
        en[cur]--;
    }
}

//将产生的脏数据全部清空
void clear(){
    for(int i=1;i<=cnt;i++){
        pass[i]=0;
        en[i]=0;
        for(int j=0;j<26;j++){
            tree[i][j]=0;
        }
    }
}

int main()
{
    return 0;
}