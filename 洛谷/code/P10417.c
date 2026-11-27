// https://www.luogu.com.cn/problem/P10417
// 题意：给长度分别为 n、m 的数组 A、B，从两边各取一项相加，共得到 n×m 个和。求这些和中的第 K 小，重复值照常占排名。
// 数据范围：1 ≤ n,m ≤ 10^5，1 ≤ A[i],B[j] ≤ 10^9，1 ≤ K ≤ n×m。
// 算法标签：二分答案、双指针

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int cmp(const void *a,const void *b){
    return (*(int *)a - *(int *)b);
}

bool check(long long x,int *a,int n,int *b,int m,int k){
    int ans=0;
    for(int i=1,j=m;i<=n;i++){
        while((a[i]+b[j])>=x&&j>0){
            j--;
        }
        ans+=j;
        if(ans>=k)
            return false;
    }
    if(ans>=k)
        return false;
    return true;
}

int main()
{
    int n,m,k;
    scanf("%d %d %d",&n,&m,&k);
    int a[n+1],b[m+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;i++){
        scanf("%d",&b[i]);
    }
    qsort(a+1,n,sizeof(int),cmp);
    qsort(b+1,m,sizeof(int),cmp);
    long long l=0,r=a[n]+b[m],mid,ans;
    while(l<=r){
        mid=l+((r-l)>>1);
        if(check(mid,a,n,b,m,k)){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
