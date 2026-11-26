// https://www.luogu.com.cn/problem/P1571
// 题意：给两份获奖编号名单，找出两份里都出现的人。按他们在第一份名单里的顺序输出编号。
// 数据范围：0 ≤ n,m ≤ 10^5，编号为小于 2 × 10^9 的正整数，同一份名单内无重复。

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int cmp(const void *a,const void *b){
    return (*(int *)a-*(int *)b);
}

bool binarysearch(int *b,int m,int x){
    int l=1,r=m;
    while(l<=r){
        int mid=l+((r-l)>>1);
        if(b[mid]==x){
            return true;
        }else if(b[mid]>x){
            r=mid-1;
        }else {
            l=mid+1;
        }
    }
    return false;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n+1];
    int b[m+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int j=1;j<=m;j++){
        scanf("%d",&b[j]);
    }
    qsort(b+1,m,sizeof(int),cmp);
    for(int i=1;i<=n;i++){
        if(!binarysearch(b,m,a[i]))
            continue;
        else
            printf("%d ",a[i]);
    }
    return 0;
}
