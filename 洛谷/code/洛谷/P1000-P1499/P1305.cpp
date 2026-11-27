// https://www.luogu.com.cn/problem/P1305
// 题意：输入一棵二叉树，每行给一个节点字符以及它的左右孩子。
// 首行描述的是根，没有孩子用星号。输出先序遍历，即先根、再左树、再右树。
// 数据范围：1 ≤ n ≤ 26。
// 算法标签：二叉树、深度优先搜索

#include<bits/stdc++.h>
using namespace std;

struct
{
    char l,r;
}nums[100];

void dfs(char x){
    if(x=='*')
        return;
    cout<<x;
    dfs(nums[x].l);
    dfs(nums[x].r);
}

int main()
{
    int n;
    cin>>n;
    char a,b;
    for(int i=1;i<=n;i++){
        cin>>a;
        if(i==1)
            b=a;
        cin>>nums[a].l>>nums[a].r;
    }
    dfs(b);
    return 0;
}
