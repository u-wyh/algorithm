// 用途：小写英文单词的插入、删除、精确词频和前缀词频。
// 时间：单次操作 O(字符串长度)。
// 空间：O(26×总字符数)。
// 注意：所有插入字符数不超过 1e5；main 为空，按题意调用这些函数。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

int cnt=1;//用于赋值新编号   全部从1开始使用
int tree[MAXN][26];//表示最多只有26个字符
// en 记完整词出现次数，pass 记经过节点的词数。
int en[MAXN];
int pass[MAXN];
int path;

void insert(string word){
    int cur=1;
    pass[cur]++;
    for (char ch : word){
        path=ch-'a';
        if(tree[cur][path]==0){
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
            return 0;
        }
        cur=tree[cur][path];
    }
    return pass[cur];
}

void erase(string word){
    if(search(word)>0){
        int cur=1;
        pass[cur]--;
        for (char ch : word){
            path=ch-'a';
            if(--pass[tree[cur][path]]==0){
                tree[cur][path]=0;
                return ;
            }
            cur=tree[cur][path];
        }
        en[cur]--;
    }
}

void clear(){
    for(int i=1;i<=cnt;i++){
        pass[i]=0;
        en[i]=0;
        for(int j=0;j<26;j++){
            tree[i][j]=0;
        }
    }
    cnt=1;
}

int main()
{
    return 0;
}
