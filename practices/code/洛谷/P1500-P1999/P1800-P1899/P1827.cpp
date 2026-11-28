// https://www.luogu.com.cn/problem/P1827
// 题意：输入同一棵二叉树的中序遍历和前序遍历，输出它的后序遍历。
// 数据范围：节点由互不相同的字母标记，最多 26 个节点。
// 难度评分：1000（洛谷分级换算）
// 算法标签：二叉树、递归

#include<bits/stdc++.h>
using namespace std;

char a[30],b[30];

void build(int l1,int r1,int l2,int r2){
    for(int i=l2;i<=r2;i++){
        if(b[i]==a[l1]){
            int cnt=i-l2;
            build(l1+1,l1+cnt,l2,i-1);
            build(l1+cnt+1,r1,i+1,r2);
            printf("%c",a[l1]);
            return ;
        }
    }
}

int main()
{
    int n=1;
    while(scanf("%c",&b[n])==1&&b[n]!='\n')
        n++;
    for(int i=1;i<=n-1;i++)
        cin>>a[i];
    //printf("%d\n",n);
    build(1,n-1,1,n-1);
    return 0;
}
