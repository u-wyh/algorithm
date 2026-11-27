// https://www.luogu.com.cn/problem/P1229
// 题意：给一棵二叉树的先序和后序遍历。
// 它们可能对应多棵二叉树，求这些树能产生多少种不同的中序遍历。
// 数据范围：节点用不重复的小写字母表示，保证至少有一种树，
// 答案不超过 2^63-1。
// 算法标签：二叉树、枚举

#include<stdio.h>
#include<string.h>

int main()
{
    char s1[70],s2[70];
    int ans=0;
    scanf("%s",s1);
    scanf("%s",s2);
    for(int i=0;i<strlen(s1)-1;i++){
        for(int j=1;j<strlen(s2);j++){
            if(s1[i]==s2[j]&&s1[i+1]==s2[j-1])
                ans++;
        }
    }
    printf("%lld\n",1<<ans);
    return 0;
}
