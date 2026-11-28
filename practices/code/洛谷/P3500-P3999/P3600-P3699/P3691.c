// https://www.luogu.com.cn/problem/P3691
// 题意：输入已知弹幕数 n、询问数 m、测试点编号 x，n 个弹幕坐标与类型
// (x, y, k)（k=1 日光，k=-1 月光）
// 以及 m 个待预测坐标 (x, y)。
// 场地上非垂直的分界直线上方为日光弹幕（k=1）、下方与线上为月光弹幕
// （k=-1），但已知数据中至多有 0.1% 的类别被标错。
// 输出 m 行 1 或 -1 预测每个询问点的弹幕类型，
// Special Judge 要求达到各测试点规定正确率（30%~80%）。
// 数据范围：测试点 2~5 时 n=m=1000（需 >=60% 正确），
// 其余测试点 n=m=100000（第 1 点 >=30%
// 第 6~7 点 >=70%，第 8~10 点 >=80%）；
// 0.000 <= x, y <= 100.000，保留 3 位小数。
// 难度评分：1200（洛谷分级换算）
// 算法标签：二分查找、排序
#include<stdio.h>
#include<stdlib.h>

#define MAX 5000000+5

int m,n,a[MAX],b[MAX];

int cmp(const void *a,const void *b){
    return (*(int *)a - *(int *)b);
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;i++){
        scanf("%d",&b[i]);
    }
    qsort(b+1,m,sizeof(int),cmp);
    for(int i=1;i<=n;i++){
        int l=1,r=m,mid,ans=-1;
        while(l<=r){
            mid=(l+r)/2;
            if(b[mid]>=a[i]){
                if(b[mid]==a[i]){
                    a[i]=0;
                    ans=mid;
                    break;
                }
                r=mid-1;
            }else{
                l=mid+1;
            }
        }
    }
    int cnt=a[1]==0?0:1;
    for(int i=2;i<=n;i++){
        if(a[i]!=0&&a[i-1]==0)
            cnt++;
    }
    printf("%d\n",cnt);
    return 0;
}
