#include<stdio.h>
#include<stdlib.h>
#define Max 100000+5

typedef struct
{
    int a,b;
}sword;

int cmp(const void *a,const void *b){
    sword * sa=(sword *)a;
    sword * sb=(sword *)b;

    if(sa->a > sb->a)
        return -1;
    if(sa->a < sb->a)
        return 1;
    return sa->b-sb->b;
}

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
int lengthOfLIS2(sword* nums,int n) {
    int ends [n];
    // len表示ends数组目前的有效区长度
    // ends[0...len-1]是有效区，有效区内的数字一定严格升序
    int len = 0;
    for (int i = 0, find; i < n; i++) {
        find = bs1(ends, len, nums[i].b);
        if (find == -1) {
            ends[len++] = nums[i].b;
        } else {
            ends[find] = nums[i].b;
        }
    }
    return len;
}

int main()
{
    int n;
    scanf("%d",&n);
    sword nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d %d",&nums[i].a,&nums[i].b);
    }
    qsort(nums+1,n,sizeof(sword),cmp);
    printf("%d\n",lengthOfLIS2(nums,n));
    return 0;
}

