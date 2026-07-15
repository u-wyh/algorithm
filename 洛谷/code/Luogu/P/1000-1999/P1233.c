#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int l,w;
}wooden;


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

int cmp(const void *a,const void *b)
{
    wooden * wa=(wooden *)a;
    wooden * wb=(wooden *)b;

    if(wa->l < wb->l)
        return 1;
    if(wa->l > wb->l)
        return -1;
    return wb->w - wa->w;
}

int main()
{
    int n;
    scanf("%d",&n);
    wooden nums[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d %d",&nums[i].l,&nums[i].w);
    }
    qsort(nums,n,sizeof(wooden),cmp);
    int a[n];
    for(int i=0;i<n;i++)
    {
        a[i]=nums[i].w;
    }
    printf("%d\n",lengthOfLIS2(a,n));
    return 0;
}
