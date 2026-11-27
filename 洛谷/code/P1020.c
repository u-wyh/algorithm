// https://www.luogu.com.cn/problem/P1020
// 题意：给一列按到达顺序排列的高度。每套系统只能按顺序处理高度不升的一串目标。先输出一套最多能处理几个，再输出覆盖所有目标最少要几套。
// 数据范围：目标数最多 10^5，高度为正整数且不超过 5 × 10^4。
// 算法标签：贪心、二分查找

#include<stdio.h>
#include<stdlib.h>
#define MAX 100000+5

int bs1(int* ends, int len, int num) {
    int l = 0, r = len - 1, m, ans = -1;
    while (l <= r) {
        m = (l + r) / 2;
        if (ends[m] > num) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return ans;
}

int lengthOfLIS2(int* nums,int n) {
    int ends [n];
    int len = 0;
    for (int i = 0, find; i < n; i++) {
        find = bs1(ends, len, nums[i]);
        if (find == -1) {
            ends[len++] = nums[i];
        } else {
            ends[find] = nums[i];
        }
    }
    return len;
}

int main()
{
    int a[MAX],b[MAX];
    int i=0;
    while(scanf("%d",&a[i++])==1);
    int n=i-1;
    //printf("%d\n",n);
    for(int i=0;i<n;i++)
    {
        b[i]=a[n-i-1];
    }
    printf("%d\n",lengthOfLIS2(b,n));
    printf("%d\n",lengthOfLIS2(a,n));
    return 0;
}

