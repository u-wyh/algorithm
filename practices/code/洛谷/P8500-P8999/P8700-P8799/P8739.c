// https://www.luogu.com.cn/problem/P8739
// 题意：输入整数 K 和只含小写字母的字符串 S，
// 计算最少修改 S 中几个字符可使 S 变为由某个字符串重复 K 次构成；
// 若无法修改成 K 次重复串，输出 -1。
// 数据范围：1 <= K <= 10^5，1 <= |S| <= 10^5。
// 难度评分：900（洛谷分级换算）
// 算法标签：贪心、字符串
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 100000+5

int cmp(const void *a,const void *b){
    return (*(int *)b-*(int *)a);
}

int main()
{
    int k;
    scanf("%d",&k);
    getchar();
    char s[MAX];
    scanf("%s",s);
    int n=strlen(s);
    //printf("%c %c %c\n",s[0],s[n-2],s[n-1]);
    if(n<k||n%k!=0){
        printf("-1\n");
        return 0;
    }
    int cnt[26],ans=0;
    for(int i=0;i<n/k;i++){
        memset(cnt,0,sizeof(cnt));
        for(int j=0;j<k;j++){
            cnt[s[i+j*(n/k)]-'a']++;
        }
        qsort(cnt,26,sizeof(int),cmp);
        ans+=k-cnt[0];
    }
    printf("%d\n",ans);
    return 0;
}
