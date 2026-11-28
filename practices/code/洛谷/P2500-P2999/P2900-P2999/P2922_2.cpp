// https://www.luogu.com.cn/problem/P2922
// 题意：输入截获信息条数 M、暗号条数 N，M 条截获二进制串的前 b_i 位，
// 以及 N 条暗号二进制串的前 c_j 位。
// 对每条暗号 j，统计有多少条截获信息 i 与之匹配，
// 即两者在前 min(b_i, c_j) 位上完全相同（具有相同前缀）。
// 依次计算每条暗号的匹配信息数量。
// 输出共 N 行，第 i 行一个整数表示第 i 个暗号可以匹配的消息数。
// 数据范围：对于 100% 的数据，1 <= M, N <= 50000，
// 1 <= b_i, c_j <= 10000
// 且总位数 sum(b_i) + sum(c_j) <= 5*10^5。
// 难度评分：1500（洛谷分级换算）
// 算法标签：字典树
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
