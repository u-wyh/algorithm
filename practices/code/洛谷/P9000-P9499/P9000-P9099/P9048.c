// https://www.luogu.com.cn/problem/P9048
// 题意：将长 n 的小写字母串 s 每个字符转为 8 位 ASCII 二进制串
// 并拼接成 8n 长度的 01 串，打乱后得到 t'。
// 根据 t' 还原任意一个合法的小写字母串 s，无解输出 NIE。
// 数据范围：1 <= n <= 10^5。
// 难度评分：1000（洛谷分级换算）
// 算法标签：构造、数学
#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    getchar();
    char s[8*n];
    scanf("%s",s);
    //printf("%c",s[1]);
    int cnt=0;
    for(int i=0;i<8*n;i++){
        if(s[i]=='1')
            cnt++;
    }
    if(cnt<3*n||cnt>6*n){
        printf("NIE\n");
        return 0;
    }
    int x[4]={0,0,0,0};
    x[3]=(cnt-3*n)/3;
    x[cnt%3]=1;
    x[0]=n-x[1]-x[2]-x[3];
    while(x[0]--)
        printf("a");
    while(x[1]--)
        printf("c");
    while(x[2]--)
        printf("g");
    while(x[3]--)
        printf("o");
    return 0;
}
