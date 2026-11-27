// https://www.luogu.com.cn/problem/P2782
// 题意：输入城市对数 N，以及 N 行每行两个整数，分别表示南岸和北岸一对友好城市的坐标。
// 河的南北两岸各有 N 个位置不同的城市，北岸每个城市唯一对应南岸一个友好城市，每对申请修一条直线航道。
// 要求选出尽量多的航道申请予以批准，使得任意两条被批准的航道都不相交。
// 输出一个整数，表示政府所能批准的最多申请数量。
// 数据范围：对于 100% 的数据，1 <= N <= 2*10^5，0 <= x_i <= 10^6。
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define Max 1000000
// 算法标签：最长上升子序列、二分查找、排序

int bs1(int* ends, int len, int num) {
    int l = 0, r = len - 1, m, ans = -1;
    while (l <= r) {
        m = (l + r) / 2;
        if (ends[m] >= num) {
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
    // len表示ends数组目前的有效区长度
    // ends[0...len-1]是有效区，有效区内的数字一定严格升序
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

void swap(int i, int j,int *arr)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int partition(int l, int r,int  x,int *arr)
{
    int a=l,xi=0;
    for(int i=l;i<=r;i++)
    {
        if(arr[i]<=x)
        {
            swap(a,i,arr);
            if(arr[a]==x)
                xi=a;
            a++;
        }
    }
    swap(xi,a-1,arr);
    return a-1;
}
void quicksort(int l,int r,int *arr)
{
    if(l>=r)
        return ;
    int x=arr[rand()%(r-l+1)+l];
    int mid=partition(l,r,x,arr);
    quicksort(l,mid-1,arr);
    quicksort(mid+1,r,arr);
}

int main()
{
    int n;
    scanf("%d",&n);
    int a[n],b[n],c[Max];
    for(int i=0;i<n;i++)
    {
        scanf("%d %d",&a[i],&c[a[i]]);
    }
    quicksort(0,n-1,a);
    for(int i=0;i<n;i++)
    {
        b[i]=c[a[i]];
    }
    printf("%d\n",lengthOfLIS2(b,n));
    return 0;
}
