// https://www.luogu.com.cn/problem/P2678
// 题意：起点到终点距离 L，中间有 N 块岩石（位置递增），至多移走 M 块。
// 求移走后相邻岩石（含起点终点）最短跳跃距离的最大值。
// 输出最大最短距离。
// 数据范围：0 <= M <= N <= 50000，1 <= L <= 10^9。
#include<stdio.h>
#include<stdbool.h>

bool check(int limit,int *nums,int k,int m){
    int ans=0,n=k-1;
    for(int i=0;i<=n;){
        int temp=nums[i];
        ans--;
        while(nums[i]-temp<limit){
            i++;
            ans++;
            if(i==n+2)
                break;
        }
    }
    return ans<=m;
}

int main()
{
    int L,n,m;
    scanf("%d %d %d",&L,&n,&m);
    int a[n+2];
    a[0]=0;
    a[n+1]=L;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    int l=1,r=L,ans=1,mid;
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid,a,n+1,m)){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
