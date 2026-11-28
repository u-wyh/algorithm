// https://www.luogu.com.cn/problem/P1042
// 题意：按顺序读乒乓球的逐分记录，W 是己方得分，L 是对方得分，E 后全部忽略。
// 分别按 11 分制和 21 分制模拟，达到门槛且领先至少 2 分才结束一局。
// 逐局输出比分，包含最后尚未结束的一局，两种结果之间空一行。
// 数据范围：题面规定每行至多 25 字符、至多 2500 行，
// 洛谷保留了一个 2501 行的旧测试点。
// 难度评分：900（洛谷分级换算）
// 算法标签：模拟

#include<stdio.h>

int f[2]={11,21};
int a[25*2500+10],n=0;

int max(int a,int b){
    return a>b?a:b;
}

int main()
{
    char s;
    while(1){
        scanf("%c",&s);
        if(s=='E')
            break;
        else if(s=='W'){
            a[n++]=1;
        }else if(s=='L'){
            a[n++]=0;
        }
    }
    for(int k=0;k<2;k++){
        int w=0,l=0;
        for(int i=0;i<n;i++){
            w+=a[i];
            l+=1-a[i];
            if(max(w,l)>=f[k]&&abs(w-l)>=2){
                printf("%d:%d\n",w,l);
                w=0,l=0;
            }
        }
        printf("%d:%d\n",w,l);
        printf("\n");
    }
    return 0;
}
