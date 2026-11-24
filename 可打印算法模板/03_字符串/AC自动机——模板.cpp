// 用途：AC 自动机同时匹配多个模式串。
// 时间：O(字符总数×字符集大小)。
// 空间：O(节点数×字符集大小)。
// 注意：小写字母；总模式串长度<=2e5，词频按 fail 的反向 BFS 序汇总。
// 例题：https://www.luogu.com.cn/problem/P5357
// 题意：统计多个模式串在文本中的出现次数。
// 思路：Trie 上建立失配边，扫描文本后沿 fail 树汇总匹配次数。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200001;
// 所有目标字符串的总字符数量
const int MAXS = 200001;

// 记录每个目标串的结尾节点编号
int en[MAXN];

// AC自动机
int tree[MAXS][26];
int fail[MAXS];
int cnt = 0;

// 具体题目相关，本题为收集词频
// 所以每个节点记录词频
int times[MAXS];
// 可以用作队列或者栈，一个容器而已
int box[MAXS];

string s;
int path;
int n;

void insert(int i,string word){
    //i是目标串的编号
    int cur=0;//头结点设置为0
    for (char ch : word){
        path=ch-'a';
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
            //没有路就要新建一条路  并赋予编号
        }
        cur=tree[cur][path];
    }
    en[i]=cur;
}

// 加入所有目标字符串之后
// 设置fail指针 以及 设置直接直通表
// 做了AC自动机固定的优化
//完成直通表  和  fail表    所有的AC自动机都是可以这样优化的
void setFail() {
    // box当做队列来使用
    int l = 0;
    int r = 0;
    for (int i = 0; i <= 25; i++) {
        if (tree[0][i] > 0) {
            box[r++] = tree[0][i];
            //0节点中只有有孩子的节点加入队列中
            //这个队列里面存储过的所有节点都要有fail
        }
    }
    //最开始加入的这些节点的fail并不是没有设置  而是本来就是0  没有设置的必要
    while (l < r) {
        int u = box[l++];
        for (int i = 0; i <= 25; i++) {
            if (tree[u][i] == 0) {
                //这个选择没有  那么就是拷贝自己的失败节点的信息
                tree[u][i] = tree[fail[u]][i];
            } else {
                // 表示的是这个儿子如果失败了，那么就去自己的fail指针哪里
                fail[tree[u][i]] = tree[fail[u]][i];//设置这个孩子节点的fail指针   直通表辅助不用绕环
                box[r++] = tree[u][i];//表示有这条支路  加入到队列中
            }
        }
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        string str;
        cin>>str;
        insert(i,str);
    }
    setFail();
    cin>>s;
    int u=0;
    for (char ch:s) {
        u = tree[u][ch - 'a'];//表示到达下一个节点
        // 增加匹配次数
        times[u]++;
    }
    // 子节点在 BFS 队列中总排在 fail 父节点后面，逆序累加即可。
    for (int i = cnt - 1; i >= 0; --i) {
        int v = box[i];
        times[fail[v]] += times[v];
    }
    for(int i=1;i<=n;i++){
        cout<<times[en[i]]<<endl;
    }
    return 0;
}
