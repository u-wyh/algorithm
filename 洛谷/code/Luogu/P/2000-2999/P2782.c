#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define Max 1000000

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
