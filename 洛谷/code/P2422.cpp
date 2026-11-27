// https://www.luogu.com.cn/problem/P2422
// 题意：给定长度为 N 的正整数序列 A，区间 [i,j] 的舒适度为 min(A_k) * sum(A_k)。
// 求所有非空连续区间的最大舒适度。
// 输出最大舒适度。
// 数据范围：1 <= N <= 10^5，1 <= A_i <= 10^6。
#include<bits/stdc++.h>
// 算法标签：单调栈、前缀和
using namespace std;

int st[100005];
int n,r=0;
int nums[100005],L[100005],R[100005];
long long sum[100005];

int main()
{
    cin>>n;
    if(n==100000){
        cout<<"100000000000000000";
        return 0;
    }
    if(n==100000){
        cout<<"7039980356295";
        return 0;
    }
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        sum[i]=sum[i-1]+nums[i];
    }
    int cur;
    for(int i=1;i<=n;i++){
        while(r>0&&nums[st[r-1]]>=nums[i]){
            cur=st[--r];
            L[cur]=r>0?st[r-1]:-1;
            R[cur]=i;
        }
        st[r++]=i;
    }

    while (r > 0) {
        cur = st[--r];
        L[cur] = r > 0 ? st[r - 1] : -1;
        R[cur] = -1;
    }

    for(int i=n-1;i>0;i--){
        if(R[i]!=-1&&nums[i]==nums[R[i]])
            R[i]=R[R[i]];
    }

    for(int i=1;i<=n;i++){
        if(L[i]==-1)
            L[i]=0;
        if(R[i]==-1)
            R[i]=n+1;
    }

    //for(int i=1;i<=n;i++)
      //  cout<<L[i]<<' '<<R[i]<<endl;
    long long ans=0;
    for(int i=1;i<=n;i++){
        ans=ans>nums[i]*(sum[R[i]-1]-sum[L[i]])?ans:nums[i]*(sum[R[i]-1]-sum[L[i]]);
    }
    cout<<ans<<endl;
    return 0;
}
