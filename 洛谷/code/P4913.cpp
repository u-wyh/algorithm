// https://www.luogu.com.cn/problem/P4913
// 题意：给定一棵 n 个结点的二叉树（根为 1）及每个结点的左右子节点编号，求这棵二叉树的最大深度（根节点为第 1 层）。
// 数据范围：n <= 10^6。
#include<iostream>
// 算法标签：二叉树、深度优先搜索
using namespace std;

const int MAXN=2e5+7;

struct Node{
    int left,right;
}t[MAXN];

int n;
void build(){
    for(int i=1;i<=n;i++)
        cin>>t[i].left>>t[i].right;
}

int dfs(int x){
    if(!x)
        return 0;
    return max(dfs(t[x].left),dfs(t[x].right))+1;
}

int main()
{
    cin>>n;
    build();
    cout<<dfs(1);
    return 0;
}
