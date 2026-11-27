// https://www.luogu.com.cn/problem/P2985
// 题意：输入巧克力块数 N、计划天数 D，以及按顺序排列的每块巧克力幸福值 H_i。
// 初始幸福值为 0，每天睡觉后幸福值减半（向下取整）；
// 需按顺序把全部 N 块巧克力分配到 D 天吃完（某天可吃多块或不吃），每天以当天吃完后的睡前幸福值作为该天幸福值。
// 最大化这 D 天中每天睡前幸福值的最小值，并给出一种对应的每天吃巧克力方案。
// 第一行输出最大化的最低幸福值，接下来 N 行依次输出第 i 块巧克力被吃掉的日期（1..D）。
// 数据范围：对于 100% 的数据，1 <= N <= 5*10^4，1 <= D <= 5*10^4，1 <= H_i <= 10^6。
#include<stdio.h>
#include<stdbool.h>
// 算法标签：二分答案、贪心

#define MAX 50005

int a[MAX];
int n,m;

int check(int x){
    int h=0,k=1;
    for(int i=1;i<=m;i++){
        while(h<x){
            if(k==n+1)
                return false;
            h+=a[k++];
        }
        if(h<x)
            return false;
        h/=2;
    }
    return true;
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    int l=0,r=1000000000,mid,ans=0;
    while(l<=r){
        mid=l+((r-l)>>1);
        if(check(mid)){
            l=mid+1;
            ans=mid;
        }else{
            r=mid-1;
        }
    }
    printf("%d\n",ans);
    int h=0,k=1;
    for(int i=1;i<=m;i++){
        if(i==m){
            while(k<=n){
                k++;
                printf("%d\n",m);
            }
        }
        else{
        while(h<ans){
            h+=a[k];
            printf("%d\n",i);
            k++;
        }
        h/=2;}
    }
    return 0;
}

