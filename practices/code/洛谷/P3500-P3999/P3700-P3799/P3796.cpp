// https://www.luogu.com.cn/problem/P3796
// 题意：多组数据（不超过 50 组，以 N = 0 结束），
// 每组第一行输入模式串数量 N。
// 随后 N 行每行输入一个仅含小写字母且互不相同的模式串，
// 再输入一行仅含小写字母的文本串 T。
// 对每组数据，第一行输出模式串在 T 中出现的最大次数，
// 随后按输入顺序每行输出一个达到该最多次数的模式串。
// 数据范围：数据组数 <= 50，1 <= N <= 150，
// 每个模式串长度 <= 70，文本串长度 |T| <= 10^6。
// 难度评分：2300（洛谷分级换算）
// 算法标签：AC自动机、深度优先搜索
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 150;
// 所有目标字符串的总字符数量
const int MAXS = 15000;

// 记录每个目标串的结尾节点编号
int en[MAXN];
string EN[MAXN];

// AC自动机
int tree[MAXS][26];
int fail[MAXS];
int cnt = 0;

// 具体题目相关，本题为收集词频
// 所以每个节点记录词频
int times[MAXS];
// 可以用作队列或者栈，一个容器而已
int box[MAXS];

// 链式前向星，为了建立fail指针的反图
int head[MAXS];
int Next[MAXS];
int to[MAXS];
int edge = 0;

string s;
int path;
int n;

void clear(){
    edge=0;
    cnt=0;
    //cout<<444<<endl;
    for(int i=1;i<=MAXS;i++){
        head[i]=0;
        Next[i]=0;
        to[i]=0;
        times[i]=0;
        box[i]=0;
        fail[i]=0;
        //cout<<555<<endl;
        for(int j=0;j<=25;j++){
            tree[i][j]=0;
        }
    }
    //s="";
}

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
    EN[i]=word;
}

// 加入所有目标字符串之后
// 设置fail指针 以及 设置直接直通表
// 做了AC自动机固定的优化
void setFail() {
    // box当做队列来使用
    int l = 0;
    int r = 0;
    //cout<<333<<endl;
    for (int i = 0; i <= 25; i++) {
        if (tree[0][i] > 0) {
            box[r++] = tree[0][i];
            //0节点中只有有孩子的节点加入队列中
            //这个队列里面存储过的所有节点都要有fail
        }
    }
    //cout<<l<<' '<<r<<endl;
    while (l < r) {
        int u = box[l++];
        cout<<u<<' ';
        system("pause");
        //cout<<111<<endl;
        for (int i = 0; i <= 25; i++) {
            if (tree[u][i] == 0) {
                tree[u][i] = tree[fail[u]][i];
            } else {
                fail[tree[u][i]] = tree[fail[u]][i];//设置这个孩子节点的fail指针   直通表辅助不用绕环
                box[r++] = tree[u][i];//表示有这条支路  加入到队列中
            }
        }
    }
}
//完成直通表  和  fail表

void addEdge(int u, int v) {
    Next[++edge] = head[u];
    head[u] = edge;
    to[edge] = v;
}

void f1(int u) {
    for (int i = head[u]; i > 0; i = Next[i]) {
        f1(to[i]);
        times[u] += times[to[i]];
    }
}

int main()
{
    //cin>>n;
    while(cin>>n&&n!=0){
        //cout<<666<<endl;
        for(int i=1;i<=n;i++){
            string str;
            cin>>str;
            insert(i,str);
        }
        //cout<<777<<endl;
        cout<<cnt<<endl;
        for(int i=1;i<=cnt;i++){
            for(int j=1;j<=26;j++){
                cout<<tree[i][j]<<' ';
            }
            cout<<endl;
        }
        setFail();
        //cout<<666<<endl;
        cin>>s;
        //getchar();
        int u=0;
        for (char ch:s) {
            u = tree[u][ch - 'a'];//表示到达下一个节点
            // 增加匹配次数
            times[u]++;
        }
        for (int i = 1; i <= cnt; i++) {
            // 根据fail指针建反图
            // 其实是一颗树
            addEdge(fail[i], i);
        }
        // 遍历fail指针建的树
        // 汇总每个节点的词频
        f1(0);
        int ans=0;
        for(int i=1;i<=n;i++){
            ans=max(ans,times[en[i]]);
        }
        cout<<ans<<endl;
        for(int i=1;i<=n;i++){
            if(times[en[i]]==ans)
                cout<<EN[i]<<endl;
        }
        clear();
    }
    return 0;
}

