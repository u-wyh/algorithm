// https://www.luogu.com.cn/problem/P1618
// 题意：把 1 到 9 各用一次，拼成三个三位数，要求它们的比例是 A:B:C。按第一个三位数从小到大输出全部方案，无解输出 No!!!。
// 数据范围：固定使用数字 1 到 9，比例由输入的三个整数给出。
// 算法标签：枚举、模拟

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

int b[10];

void go(int x){
    b[x%10]=1;
    b[x/10%10]=1;
    b[x/100]=1;
}

bool check(int x,int y,int z){
    memset(b,0,sizeof(b[0]));
    if(y>=999||z>=999)
        return false;
    go(x);
    go(y);
    go(z);
    for(int i=1;i<=9;i++){
        if(!b[i])
            return false;
    }
    return true;
}

int main()
{
    int A,B,C,cnt=0;
    scanf("%d %d %d",&A,&B,&C);
    for(int x=123;x<=987;x++){
        if(check(x,x*B/A,x*C/A)){
            cnt++;
            printf("%d %d %d\n",x,x*B/A,x*C/A);
        }
    }
    if(!cnt)
        printf("No!!!\n");
    return 0;
}
