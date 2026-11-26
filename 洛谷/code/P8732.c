// https://www.luogu.com.cn/problem/P8732
// 题意：输入 n 和 n 位同学的参数 (s_i, a_i, e_i)；
// 从时刻 0 开始依次进入办公室，第 i 位同学耗时 s_i+a_i 后在该时刻发消息（不耗时），再耗时 e_i 离开后下一位才进入；
// 合理安排答疑顺序，输出所有人发消息时刻之和的最小值。
// 数据范围：1 <= n <= 1000，1 <= s_i <= 60000，1 <= a_i <= 10^6
// e_i ∈ {10000, 20000, 30000}。
#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int s,a,e;
}student;

int cmp(const void *a,const void *b){
    student * sa=(student *)a;
    student * sb=(student *)b;

    return (sa->s+sa->a+sa->e)-(sb->s+sb->a+sb->e);
}

int main()
{
    int n;
    scanf("%d",&n);
    student nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d %d %d",&nums[i].s,&nums[i].a,&nums[i].e);
    }
    qsort(nums+1,n,sizeof(student),cmp);
    long long ans=0;
    for(int i=1;i<=n;i++){
        ans+=(n-i+1)*(nums[i].a+nums[i].s+nums[i].e);
        ans-=nums[i].e;
    }
    printf("%lld\n",ans);
    return 0;
}
